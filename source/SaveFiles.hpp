#ifndef INC_2D_GAME_SAVEFILES_HPP
#define INC_2D_GAME_SAVEFILES_HPP


#include <string>


struct Entity;


class SaveFile {
    public:
        static void save(const std::string& filename, Entity player);
        static void load(const std::string& filename, Entity player);
};


#endif
