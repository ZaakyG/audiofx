#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "fx.h"

int main(){
    
    FILE *file = fopen("test_files/sample_mono.wav", "rb");
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    WAVFormat format;
    long data_offset;
    uint32_t data_size;

    if (!parse_wav(file, &format, &data_offset, &data_size)){
        printf("Parsing failed\n");
        return 1;
    }
    
    print_wav_info(&format, data_offset, data_size);

    fseek(file, data_offset, SEEK_SET);

    // Prepare for processing
    int16_t *samples = malloc(data_size);
    long num_samples = data_size / sizeof(int16_t); 
    fread(samples, sizeof(int16_t), num_samples, file);
    
    // Apply effects
    int factor = 2; // factor to reduce volume: volume/factor
    volumeReduction(samples, num_samples, factor);

    // Write out to file
    write_out(file, samples, data_offset, data_size);   
    free(samples);

}

