/* hardcoded_demo.c
 * Simple program: hardcoded string -> transform -> print
 * Compile: gcc -std=c11 -O2 -o hardcoded_demo hardcoded_demo.c
 * Run:     ./hardcoded_demo
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

static inline uint32_t rol32(uint32_t x, int r) {
    return (x << (r & 31)) | (x >> ((32 - (r & 31)) & 31));
}

/* A tiny, deterministic transform (harmless toy "obfuscation") */
static void transform(const char *in, char *out, size_t n) {
    uint32_t key = 0xA5A5A5A5u;
    for (size_t i = 0; i < n; ++i) {
        uint8_t b = (uint8_t)in[i];
        /* mix with evolving key and position-dependent rotation */
        key ^= (uint32_t)(b + (uint8_t)i);
        key = rol32(key, (int)(i + 3));
        out[i] = (char)( (uint8_t)(b ^ (key & 0xFF)) );
    }
    out[n] = '\0';
}

int main(void) {
    const char hard[] = "echidna";           /* hardcoded input — never changed */
    char out[64];

    transform(hard, out, strlen(hard));

    printf("Original : %s\n", hard);
    printf("Transformed (hex): ");
    for (size_t i = 0; i < strlen(out); ++i)
        printf("%02X", (unsigned char)out[i]);
    printf("\n");
    printf("Transformed (as bytes): %s\n", out);

    return 0;
}
