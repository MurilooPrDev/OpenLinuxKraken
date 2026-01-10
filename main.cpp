#include "kraken.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "--- Kraken Unpacker Linux ---\n";
        std::cout << "Uso: ./kraken_linux <entrada.bin> <saida.dec>\n";
        return 1;
    }

    if (KrakenDecompressor::processFile(argv[1], argv[2])) {
        std::cout << "[+] Sucesso! Arquivo descompactado.\n";
    } else {
        std::cerr << "[-] Erro no processamento.\n";
        return 1;
    }

    return 0;
}
