#include "sound.h"
#include <iostream>

static ma_engine engine;
static ma_sound cannonSound;
static ma_sound elevation;

void initAudio()
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine\n";
        return;
    }

    if (ma_sound_init_from_file(&engine, "cannon2.wav", 0, NULL, NULL, &cannonSound) != MA_SUCCESS) {
        std::cerr << "Failed to load cannon2.wav\n";
        return;
    }

    if(ma_sound_init_from_file(&engine, "elevation.wav", 0, NULL, NULL, &elevation) != MA_SUCCESS){
         std::cerr << "Failed to load elevation.wav\n";
        return;
    }
}

void playCannon()
{
    ma_sound_start(&cannonSound);
}

void playElevation(){
    ma_sound_start(&elevation);
}

void shutdownAudio()
{
    ma_sound_uninit(&cannonSound);
    ma_sound_uninit(&elevation);
    ma_engine_uninit(&engine);
}
