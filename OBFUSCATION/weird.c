/*
 * weird_fixed.c — Deterministic Obfuscated Demo
 * ----------------------------------
 * Compile:
 *   gcc -std=c11 -O2 -o weird weird_fixed.c
 * Run:
 *   ./weird <guess>
 * Example:
 *   ./weird echidna
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROL32(x,n) (((uint32_t)(x) << ((n)&31)) | ((uint32_t)(x) >> (32-((n)&31))))
#define ROR64(x,n) (((uint64_t)(x) >> ((n)&63)) | ((uint64_t)(x) << (64-((n)&63))))
#define NOINLINE __attribute__((noinline))

// XOR helper
static void duff_xor(uint8_t *dst, const uint8_t *src, size_t n, uint8_t k) {
    for (size_t i = 0; i < n; ++i)
        dst[i] = src[i] ^ (uint8_t)(k + i);
}

// small PRNG
typedef struct { uint64_t s[2]; } xs128p;
static uint64_t NOINLINE xs128p_next(xs128p *st){
    uint64_t x = st->s[0], y = st->s[1];
    st->s[0] = y;
    x ^= x << 23; x ^= x >> 17; x ^= y ^ (y >> 26);
    st->s[1] = x;
    return x + y;
}

// Feistel
static uint32_t fmix(uint32_t x){
    x ^= x >> 16; x *= 0x7feb352d; x ^= x >> 15; x *= 0x846ca68b; x ^= x >> 16;
    return x;
}
static uint64_t tiny_feistel(uint64_t v){
    uint32_t L = (uint32_t)v, R = (uint32_t)(v>>32);
    for (int r=0;r<4;++r){
        uint32_t k = fmix(0x9e3779b9u*(r+1));
        uint32_t F = fmix(R ^ k) + ROL32(R, (r*7+3)&31);
        uint32_t nL = R, nR = L ^ F;
        L = nL; R = nR;
    }
    return ((uint64_t)R<<32)|L;
}

// Encoded strings
static const uint8_t BLOB[] = {
    0xAE,0x8A,0x9B,0x98,0x98,0x8B,0xD9,0x97,0x8C,0x9E,0x98,0x8D,0x8C,0x9B,0xC9, // "Access granted\n"
    0xBB,0xAA,0xA1,0xB2,0xB9,0xE8                   // "nope: "
};

// Secret key
static const uint8_t SECRET[] = { 7, 'e'^0x55, 'c'^0x55, 'h'^0x55, 'i'^0x55, 'd'^0x55, 'n'^0x55, 'a'^0x55 };

static int check_secret(const char* s) {
    size_t n = strlen(s);
    if (n != SECRET[0]) return 0;
    for (size_t i=0;i<n;i++){
        if ((uint8_t)s[i] != ((SECRET[i+1]) ^ 0x55))
            return 0;
    }
    return 1;
}

static void decode_blob(char *out, size_t off, size_t len) {
    duff_xor((uint8_t*)out, BLOB+off, len, 0x55);
    out[len]='\0';
}

int main(int argc, char** argv) {
    char msg[32];
    if (argc < 2) {
        decode_blob(msg, 15, 6);
        printf("%s(no input)\n", msg);
        return 0;
    }

    if (check_secret(argv[1])) {
        decode_blob(msg, 0, 15);
        printf("%s", msg);
    } else {
        decode_blob(msg, 15, 6);
        uint64_t fake = time(NULL);
        printf("%s%llu\n", msg, (unsigned long long)fake);
    }
    return 0;
}
