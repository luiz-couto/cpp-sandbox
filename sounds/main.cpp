#include "sounds.h"

FMOD_RESULT F_CALLBACK sineCallback(FMOD_DSP_STATE* dsp_state, float* inbuffer, float* outbuffer, unsigned int length, int inchannels, int* outchannels) {
    static float phase = 0.0f;
    const float frequency = 440.0f;
    const float sampleRate = 48000.0f;

    for (unsigned int i = 0; i < length; i++) {
        float sample = sinf(phase);
        phase += 2.0f * M_PI * frequency / sampleRate;

        if (phase >= 2.0f * M_PI) {
            phase -= 2.0f * M_PI;
        }
        for (int j = 0; j < *outchannels; j++) {
            outbuffer[i * (*outchannels) + j] = sample;
        }
    }

    return FMOD_OK;
}

void playMusic(FMOD::System* system)
{
    FMOD::Sound* sound = NULL;
    FMOD::Channel* channel = NULL;
    system->createSound("music.mp3", FMOD_DEFAULT, NULL, &sound);
    system->playSound(sound, NULL, false, &channel);
    std::cout << "Press any key to quit" << std::endl;
    while (true)
    {
    std::cin.get();
    break;
    }
    sound->release();
}

int main() {
    // FMOD::System* system;
    // FMOD::System_Create(&system);
    // system->init(512, FMOD_INIT_NORMAL, NULL);

    // FMOD_DSP_DESCRIPTION dspDesc = {};
    // dspDesc.version = 0x00010000;
    // dspDesc.numinputbuffers = 0;
    // dspDesc.numoutputbuffers = 1;
    // dspDesc.read = sineCallback;
    // FMOD::DSP* dsp;
    // system->createDSP(&dspDesc, &dsp);

    // system->playDSP(dsp, NULL, false, NULL);

    // std::cout << "Press any key to quit" << std::endl;
    // while (true) {
    //     std::cin.get();
    //     break;
    // }

    // dsp->release();
    // system->close();
    // system->release();

    FMOD::System *system;
    FMOD::System_Create(&system);
    system->init(512, FMOD_INIT_NORMAL, NULL);
    playMusic(system);
    system->close();
    system->release();
    return 0;


    return 0;
}