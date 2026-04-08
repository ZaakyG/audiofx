#ifndef UTILS_H
#define UTILS_H

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

// To save .bat file
int saveToPlot(int16_t *samples, long num_samples);

// Functions from live listen
// dB conversion to rms
float dbToRms(float rms);

// Converts rms to linear scale for plotting
float linscale(float x);

// Function for status bar
void rms_display(const float *in);

#endif
