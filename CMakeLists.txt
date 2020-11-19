cmake_minimum_required(VERSION 3.16)
project(lua-sol2)
set(CMAKE_CXX_STANDARD 17)

SET (APP_SOURCE_DIR "${PROJECT_SOURCE_DIR}/source")
SET (EXTERNALS_DIR "${PROJECT_SOURCE_DIR}/externals")
SET (LUA_DIR "${EXTERNALS_DIR}/lua")
SET (SOL2_DIR "${EXTERNALS_DIR}/sol")

# lua lib
add_library(
    lua STATIC
    ${LUA_DIR}/lapi.c
    ${LUA_DIR}/lauxlib.c
    ${LUA_DIR}/lbaselib.c
    ${LUA_DIR}/lcode.c
    ${LUA_DIR}/lcorolib.c
    ${LUA_DIR}/lctype.c
    ${LUA_DIR}/ldblib.c
    ${LUA_DIR}/ldebug.c
    ${LUA_DIR}/ldo.c
    ${LUA_DIR}/ldump.c
    ${LUA_DIR}/lfunc.c
    ${LUA_DIR}/lgc.c
    ${LUA_DIR}/linit.c
    ${LUA_DIR}/liolib.c
    ${LUA_DIR}/llex.c
    ${LUA_DIR}/lmathlib.c
    ${LUA_DIR}/lmem.c
    ${LUA_DIR}/loadlib.c
    ${LUA_DIR}/lobject.c
    ${LUA_DIR}/lopcodes.c
    ${LUA_DIR}/loslib.c
    ${LUA_DIR}/lparser.c
    ${LUA_DIR}/lstate.c
    ${LUA_DIR}/lstring.c
    ${LUA_DIR}/ltable.c
    ${LUA_DIR}/ltablib.c
    ${LUA_DIR}/ltm.c
    ${LUA_DIR}/lua.c
    ${LUA_DIR}/lundump.c
    ${LUA_DIR}/lutf8lib.c
    ${LUA_DIR}/lvm.c
    ${LUA_DIR}/lzio.c
)

# app
add_executable(
    sandbox
    ${APP_SOURCE_DIR}/main.cpp
)

target_link_libraries(
    sandbox 
    PRIVATE lua
)

target_include_directories(
    sandbox
    PRIVATE ${EXTERNALS_DIR}
    PRIVATE ${LUA_DIR} # as of sol2 3.2.2, lua.hpp must be accesible through root include '#include <lua.hpp>'
)