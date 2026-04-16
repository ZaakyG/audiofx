#include <stdio.h>
#include <stdlib.h>
#include <portaudio.h>
#include <math.h>
#include <stdint.h>

#include "utils/utils.h"

#define FRAMES_PER_BUFFER 512 
#define SAMPLE_RATE 44100

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
    (void) framesPerBuffer;

    const float *in = (const float*)inputBuffer;
    
    //rms_display(in);

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
    printf("\n");
    Pa_CloseStream(stream);
    Pa_Terminate();
   
     
    // printf("\r");    
    fflush(stdout);
    printf("\n");    
    return 0;
}

