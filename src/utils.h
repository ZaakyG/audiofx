#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Structs definition
typedef struct {
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
} WAVFormat;

// Parser function to reade header of wav file
int parse_wav(FILE *file, WAVFormat *format, long *data_offset, uint32_t *data_size);

// To save new file after processing
int write_out(FILE *orig, int16_t *samples, long data_offset, uint32_t data_size);

// To display wav info
int print_wav_info(WAVFormat *format, long data_offset, uint32_t data_size);

#endif
