#include "spdlog/spdlog.h"

#include "Audio.hpp"

Audio::Audio() = default;

Audio::~Audio() {
    engine->drop();
}

void Audio::init(const std::string& fileName) {
    engine = irrklang::createIrrKlangDevice();

    if ( !engine ) {
        spdlog::error("[IrrKlang] Could not startup engine");
    }

    snd = engine->play2D(fileName.c_str(), true, true, true);
    snd->setVolume(0.2);
}

void Audio::play(bool paused) {
    snd->setIsPaused(!paused);
}

void Audio::playOne(const std::string& fileName) {
    engine->play2D(fileName.c_str());
}

