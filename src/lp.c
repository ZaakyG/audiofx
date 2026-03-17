#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Define struct for wav header
typedef struct {
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
} WAVFormat;

// Define functions used
int parse_wav(FILE *file, WAVFormat *format, long *data_offset, uint32_t *data_size);


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

    printf("Channels: %d\n", format.num_channels);
    printf("Sample rate: %d\n", format.sample_rate);
    printf("Bits per Sample: %d\n", format.bits_per_sample);
    printf("Data Offset: %ld\n", data_offset);
    printf("Data Size: %u \n", data_size);

    fseek(file, data_offset, SEEK_SET);

    // Do processing
    int N = 2;
    int16_t *samples = malloc(format.data_size);
    
    fread(samples, sizeof(int16_t), data_size, file);

    for (int i=samples; i < data_size; i++){
        samples[i] = samples[i]/2;
//        int sum = 0;
//
//        for (int j = 0; j < N; j++){
//            sum += samples[i-j];
//        }
    }
//    samples[i] = sum/N;

}

int parse_wav(FILE *file, WAVFormat *format, long *data_offset, uint32_t *data_size){
    // printf("Init parse\n");
    char chunk_id[5];
    uint32_t chunk_size;
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
        printf("Not a WAVE file\n");
        return 0;
    }
    
    // read chunks 
    while(!feof(file)) {
        //printf("Reading chunks\n");
        if (fread(chunk_id, 1, 4, file) != 4)
            break;
        
        chunk_id[4] = '\0';
        fread(&chunk_size, 4, 1, file);
        
        if (strcmp(chunk_id, "fmt ") == 0){
            fread(&format->audio_format, sizeof(uint16_t), 1, file);
            fread(&format->num_channels, sizeof(uint16_t), 1, file);
            fread(&format->sample_rate, sizeof(uint32_t), 1, file);
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

        // printf("No data chunk found\n");
    } 

    return 0; 

}

int write_out(){

}
