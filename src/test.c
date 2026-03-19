#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

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

    // Do processing
    int16_t *samples = malloc(data_size);
    long num_samples = data_size / sizeof(int16_t); 
    fread(samples, sizeof(int16_t), num_samples, file);

    for (int i=0; i < num_samples; i++){
        samples[i] = samples[i]/10; 
    }

    write_out(file, samples, data_offset, data_size);   
    free(samples);

}

