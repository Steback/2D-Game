file(GLOB LUA_SOURCE *.c)

add_library(lua STATIC ${LUA_SOURCE})