#ifndef LUA_MANAGER_HPP
#define LUA_MANAGER_HPP

#include <string>

struct Entity;

class LuaManager {
    public:
        LuaManager();
        ~LuaManager();
        static std::string loadFile(const std::string& filePath_, Entity& player);
};

#endif
