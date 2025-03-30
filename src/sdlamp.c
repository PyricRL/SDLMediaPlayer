#include "SDL2\SDL.h"
#include <stdio.h>

// gcc src/sdlamp.c -o sdlamp `build/sdl2-config --cflags --libs`
// in ucrt64 terminal

static SDL_AudioDeviceID audio_device = 0;

static void panic_and_abort(const char *title, const char *text) {
    fprintf(stderr, "PANIC: %s ... %s\n", title, text);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, text, NULL);
    SDL_Quit();
    exit(1);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
        panic_and_abort("SDL_Init failed", SDL_GetError());
    }

    SDL_AudioSpec wavspec;
    Uint8 *wavbuf = NULL;
    Uint32 wavlen = 0;
    if (SDL_LoadWAV("music.wav", &wavspec, &wavbuf, &wavlen) == NULL) {
        panic_and_abort("Couldn't load wav file!", SDL_GetError());
    }

#if 0 // !!! FIXME: Come back to this.
    SDL_AudioSpec desired;
    SDL_zero(desired);
    desired.freq = 48000;
    desired.format = AUDIO_F32;
    desired.channels = 2;
    desired.samples = 1096;
    desired.callback = NULL;    
#endif

    audio_device = SDL_OpenAudioDevice(NULL, 0, &wavspec, NULL, 0);
    if (audio_device == 0) {
        panic_and_abort("Could not open audio device!", SDL_GetError());
    }

    SDL_QueueAudio(audio_device, wavbuf, wavlen);
    SDL_FreeWAV(wavbuf);

    SDL_PauseAudioDevice(audio_device, 0);

    SDL_Delay(5000);

    SDL_CloseAudioDevice(audio_device);
    SDL_Quit();

    return 0;
}