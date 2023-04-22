#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include <raylib.h>

float lerp(float a, float b, float f)
{
    return a * (1.0 - f) + (b * f);
}


int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        printf("error, not enough arguments\n");
        return 0;
    }

    SetTraceLogLevel(99);

    float strength = atof(argv[1]);

    Wave audio = LoadWave(argv[2]);

    WaveFormat(&audio, 48000, 32, 2);

    Wave newAudio = WaveCopy(audio);

    int errorAmount = 0;

    for(int i = 2; i < audio.frameCount; i++)
    {
        // printf("%i\n", ((ufloat*)audio.data)[i]);
        float point = ((float*)audio.data)[i];
        float lastPoint = ((float*)audio.data)[i-2];

        float difference = point - lastPoint;
        float originalDiff = difference;

        difference = difference * strength;

        float newPoint = difference + lastPoint;

        float error = fabsf((float)difference/(float)originalDiff);
        // if(i % 48000 == 0)
        // if(i > 48000*10 && i < 48000*11)
        // // if(abs(originalDiff-difference) > 110000000)
        // // if(abs(originalDiff-difference) > 100000000)
        // // printf("error %f\n", error);
        // // if(error > 0.08 && abs(originalDiff-difference) > 5)
        // // if(abs(originalDiff-difference) > 100000000)
        // // if(abs(originalDiff-difference) > 10000)
        // {
        //     printf("previous %f point %f  estimated: %f\tdifference %f modified: %f\terror: %f\n", lastPoint, point, newPoint, originalDiff, difference, error);
        //     // difference = originalDiff;
        //     // errorAmount++;
        // }

        newPoint = difference + lastPoint;

        // if(newPoint > 2147483647 || newPoint < -2147483648)
        // {
        //     printf("peaking !!! %ld  %ld  %ld\n", newPoint, point, difference);
        // }

        // if(newPoint > 2147483647)
        //     newPoint = 2147483647;

        // if(newPoint < -2147483648)
        //     newPoint = -2147483648;

        ((float*)newAudio.data)[i] = newPoint;
    }

    // printf("error amount %ld\t%f\%\n", errorAmount, errorAmount / (float)audio.frameCount * 100);

    // WaveFormat(&newAudio, 48000, 32, 2);

    ExportWave(newAudio, argv[3]);
}