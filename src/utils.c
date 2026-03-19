/* This is where the main utils for the handling of the audio
 * are stored. This should include:
 * - Read
 * - Write
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
// TODO


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

// Write audio
// format: Header, data 
int write_out(FILE * orig, int16_t *samples, long data_offset, uint32_t data_size){
    printf("Writing to file\n");
    FILE *out = fopen("test_files/processed.wav", "wb");

    if (out == NULL){
       printf("Error handling output file\n");
       return 1;
    }
    
    fseek(orig, 0, SEEK_SET);

    uint8_t *header = malloc(data_offset);
    fread(header, sizeof(uint8_t), data_offset, orig);
    fwrite(header, sizeof(uint8_t), data_offset, out); 

    long num_samples = data_size/sizeof(int16_t);

    fwrite(samples, sizeof(int16_t), num_samples, out);

    free(header);
    //free(samples);

    fclose(orig);
    fclose(out);
    
    return 0;
}

int print_wav_info(WAVFormat *format, long data_offset, uint32_t data_size){
    
   bool print = true; 
   if (print == true){
       printf("Channels: %d\n", format->num_channels);
       printf("Sample rate: %d\n", format->sample_rate);
       printf("Bits per Sample: %d\n", format->bits_per_sample);
       printf("Data Offset: %ld\n", data_offset);
       printf("Data Size: %u \n", data_size);
   }
}
