#include <stdio.h>
#include <stdlib.h>
#include <portaudio.h>
#include <math.h>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512

// Create function to convert to rms
void rms_display(const float *in)  {
    float sum = 0.0f;
    for( unsigned int i = 0; i < FRAMES_PER_BUFFER; i++){
        sum += in[i] * in[i];
    }

    float rms = sqrtf(sum/FRAMES_PER_BUFFER);
    
    // Create status bar.
    // First convert to an scale
    int scale = 50; 
    int status = (int) rms/scale;
    printf("\rLevel: [");
    for(int i = 0; i < scale; i++){
        if (i <= rms){
            printf("#");
        } else {
            printf(" ");
        } 
    }
    printf("]  %0.5f   ",rms);
    //printf("\rRMS: %f", rms);
    fflush(stdout);
}

// Callback function to receive the audio samples 
static int audio_callback(
    const void *inputBuffer, //where samples will be stored
    void *outputBuffer, // buffer to write to
    unsigned long framesPerBuffer, // 
    const PaStreamCallbackTimeInfo * timeInfo, // 
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    // to prevent unused variable warning
    (void) outputBuffer;
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    const float *in = (const float*)inputBuffer;
    
    rms_display(in);

    return paContinue;
}

int main(void){
    const PaDeviceInfo *deviceInfo;
    PaStream *stream;
    PaError err;

    err = Pa_Initialize();

    err = Pa_OpenDefaultStream(
            &stream,
            1,
            0,
            paFloat32,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            audio_callback,
            NULL
    );

    err = Pa_StartStream(stream);

    printf("Listening ... Press Enter to stop\n");
    getchar();

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
   
     
    printf("\r");    
    fflush(stdout);
    printf("\n");    
    return 0;
}

