#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define HEADER_SIZE 78

// Define struct for wav header

typedef struct {
    uint16_t audio_format;
    uint16_t num_channels;
    uint16_t sample_rate;
    uint16_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
} WAVFormat;

int parse_wav(FILE *file, WAVFormat *format, long *data_offset, uint32_t *data_size);


int main(){
    /*
    FILE *input = fopen("sample_mono.wav", "rb");
    FILE *output = fopen("output.wav", "wb");

    if (!input || !output){
        printf("Error opening files\n");
        return 1;
    }
    printf("I/O files oppened succesfully\n");

    // Copy header 
    uint8_t header[HEADER_SIZE];
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Determine file size
    fseek(input, 0, SEEK_END);
    long file_size = ftell(input);
    long data_size = file_size - HEADER_SIZE;
    long num_samples = data_size / sizeof(int16_t);
    fseek (input, HEADER_SIZE, SEEK_SET);

    int16_t *samples = malloc(data_size);
    fread(samples, sizeof(int16_t), num_samples, input);

    for (long i=0; i < num_samples; i++){
        samples[i] = samples[i]/2; // simple volume reduction
    }

    fwrite(samples, sizeof(int16_t), num_samples, output);

    free(samples);
    fclose(input);
    fclose(output);

    return 0;
    */

    FILE *file = fopen("mono_bass.wav", "rb");
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

    printf("Channels: %d\n", format.num_channels);
    printf("Sample rate: %d\n", format.sample_rate);
    printf("Bits per Sample: %d", format.bits_per_sample);
    printf("Data Offset: %ld\n", data_offset);
    printf("Data Size: %u \n", data_size);

    fseek(file, data_offset, SEEK_SET);
}

int parse_wav(FILE *file, WAVFormat *format, long *data_offset, uint32_t *data_size){
    char chunk_id[5];
    uint32_5 chunk_size;
    fread(chunk_id, 1, 4, file);
    chunk_id[4] = '\0';

    // Get riff 
    if(strcmp(chunk_id, "RIFF") != 0){
        printf("Not a RIFF file\n");
        return 0;       
    }
  
    fread(&chunk_size, 4, 1, file);

    fread(chunk_id, 1, 4, file);
    chunk_id[4] = '\0';

    // Get wave
    if (strcmp(chunk_id, "WAVE") !=0){
        print("Not a WAVE file\n");
        return 0;
    }
    
    // read chunks 
    while(!feof(file)) {
        if (fread(chunk_id, 1, 4, file)
            break;
        chunk_id[4] = '\0';
        fread(&chunk_size, 4, 1, file);
        
        if (strcmp(chunk_id, "fmt ") == 0){
            fread(&format->audio_format, sizeof(uint16_t), 1, file);
            fread(&format->num_channels, sizeof(uint16_t), 1, file;
            fread(&format->sample_rate, sizeof(uint32_t), 2, file;
            fread(&format->byte_rate, sizeof(uint32_t), 1, file);
            fread(&format->block_align, sizeof(uint16_t), 1, file);
            fread(&format->bits_per_sample, sizeof(uint16_t), 1, file);
        
            if (chunk_size>16){
                fseek(file, chunk_size-16, SEEK_CUR);
            }    
        }   
        else if(strcmp(chunk_id, "data") == 0) {
            *data_offset = ftell(file);
            *data_size = chunk_size;
            return 1; // means success
        }
        else {
            // Skip unkonw chunk (like FLLR)
            fseek(file, chunk_size, SEEK_CUR);
        }

    } 

    return 0; 

}
