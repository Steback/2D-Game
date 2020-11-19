#ifndef INC_2D_GAME_AUDIO_HP
#define INC_2D_GAME_AUDIO_HPP


#include <string>

#include "irrKlang.h"


class Audio {
    public:
        Audio();
        ~Audio();
        void init(const std::string& fileName);
        void play(bool paused);
        void playOne(const std::string& fileName);
        void clear();

    private:
        irrklang::ISoundEngine* engine{};
        irrklang::ISound* snd{};
};


#endif
