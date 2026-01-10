#include "kraken.h"
#include <fstream>
#include <iostream>
#include <cstring>

// Inicializa o estado rANS (Entropia)
void KrakenDecompressor::ransInit(RansState* r, const uint8_t** ptr) {
    r->state = (*ptr)[0] | ((*ptr)[1] << 8) | ((*ptr)[2] << 16) | ((*ptr)[3] << 24);
    *ptr += 4;
}

// Decodifica símbolos do fluxo de bits
uint32_t KrakenDecompressor::ransDecode(RansState* r, const uint8_t** ptr) {
    uint32_t symbol = r->state & 0x7FF; 
    r->state >>= 11;
    if (r->state < (1 << 16)) {
        r->state = (r->state << 16) | (*ptr)[0] | ((*ptr)[1] << 8);
        *ptr += 2;
    }
    return symbol;
}

// Motor de descompressão Sliding Window
void KrakenDecompressor::lzDecompress(const uint8_t* src, uint8_t* dst, size_t outSize) {
    const uint8_t* srcPtr = src;
    uint8_t* dstPtr = dst;
    uint8_t* dstEnd = dst + outSize;
    RansState rans;
    
    ransInit(&rans, &srcPtr);

    while (dstPtr < dstEnd) {
        uint32_t token = ransDecode(&rans, &srcPtr);

        if (token < 256) { // Caso seja um Literal (byte puro)
            *dstPtr++ = (uint8_t)token;
        } else { // Caso seja um Match (cópia de dados anteriores)
            uint32_t len = (token & 0x1F) + 3;
            uint32_t dist = (token >> 5) + 1;
            uint8_t* matchPtr = dstPtr - dist;

            if (matchPtr >= dst) {
                // Otimização: cópia rápida de memória
                while (len-- && dstPtr < dstEnd) {
                    *dstPtr++ = *matchPtr++;
                }
            }
        }
    }
}

bool KrakenDecompressor::processFile(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream file(inputPath, std::ios::binary);
    if (!file.is_open()) return false;

    // Lendo o Header (12 bytes padrão Oodle)
    uint8_t header[12];
    file.read((char*)header, 12);

    if (header[0] != 0x8C) {
        std::cerr << "[-] Erro: Formato Kraken/Oodle não identificado!" << std::endl;
        return false;
    }

    // Tamanho de saída costuma estar nos bytes 6-8 do header (Big-Endian)
    uint32_t outSize = (header[6] << 16) | (header[7] << 8) | header[8];
    
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(12, std::ios::beg); // Pula o header

    std::vector<uint8_t> input(fileSize - 12);
    file.read((char*)input.data(), input.size());

    std::vector<uint8_t> output(outSize);
    
    std::cout << "[*] Descomprimindo: " << inputPath << " -> " << outSize << " bytes" << std::endl;
    lzDecompress(input.data(), output.data(), outSize);

    std::ofstream outFile(outputPath, std::ios::binary);
    outFile.write((char*)output.data(), outSize);
    
    return true;
}
