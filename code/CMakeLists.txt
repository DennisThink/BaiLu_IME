cmake_minimum_required(VERSION 3.10)
project(BaiLu_IME)
SET(BAILU_IME_SOURCE_FILE 
./DllMain.cpp 
./DllServerFunction.cpp 
./GlobalValues.cpp
./Log.cpp
./RegKeyFunction.cpp)
add_library(BaiLuIME SHARED ${BAILU_IME_SOURCE_FILE})