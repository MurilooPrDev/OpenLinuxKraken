#ifndef KRAKEN_H
#define KRAKEN_H

#include <vector>
#include <cstdint>
#include <string>

class KrakenDecompressor {
public:
    static bool processFile(const std::string& inputPath, const std::string& outputPath);

private:
    struct RansState {
        uint32_t state;
    };

    static void ransInit(RansState* r, const uint8_t** ptr);
    static uint32_t ransDecode(RansState* r, const uint8_t** ptr);
    static void lzDecompress(const uint8_t* src, uint8_t* dst, size_t outSize);
};

#endif
