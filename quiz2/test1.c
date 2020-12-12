#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

bool is_ascii_v1(const char str[], size_t size)
{
    if (size == 0)
        return false;
    for (int i = 0; i < size; i++) {
        if (str[i] & 0x80) {
            return false;
        }
        // return true;
    }
}

bool is_ascii_v2(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

// bool is_ascii(const char str[], size_t size)
// {
//     if (size == 0)
//         return false;
//     int i = 0;
//     while ((i + 8) <= size) {
//         uint64_t payload;
//         memcpy(&payload, str + i, 8);
//         if (payload & 0x8080808080808080) {
//             // printf("False\n");
//             return false;
//         }
//         i += 8;
//     }
//     while (i < size) {
//         if (str[i] & 0x80) {
//             // printf("False\n");
//             return false;
//         }
//         i++;
//     }
//     // printf("Ture\n");
//     return true;
// }

int main(int argc, char *argv[])
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &len, stream)) != -1) {
        printf("Retrieved line of length %zd:\n", nread);
        fwrite(line, nread, 1, stdout);
    }

    if (is_ascii_v2(line, strlen(line)))
        printf("True\n");
    else
        printf("False\n");

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
