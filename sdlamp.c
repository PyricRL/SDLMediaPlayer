#include "SDL.h"

static SDL_AudioDeviceID audio_device = 0;

int main(int argc, char **argv) {
    // !!! FIXME: error checking!
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    audio_device = SDL_OpenAudioDevice();
    
    SDL_Quit();
    return 0;
}