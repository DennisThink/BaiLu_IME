cmake_minimum_required(VERSION 3.10)
project(BaiLu_IME)
SET(BAILU_IME_SOURCE_FILE 
./DllMain.cpp 
./DllServerFunction.cpp 
./GlobalValues.cpp
./Log.cpp
./RegKeyFunction.cpp
./RegProfileFunction.cpp
./RegCategoryFunction.cpp
./BaiLuIME_main.cpp
./BaiLu_ClassFactory.cpp
./BaiLuInputMethodClass.cpp
./BaiLuInputMethodInterface.cpp
./BaiLuKeyEventSink.hpp
./BaiLuKeyEventSink.cpp
./BaiLuIME.rc
./BaiLuIME.def)

SET(TEST_FILES ./test_main.cpp ./GlobalValues.cpp ./RegKeyFunction.cpp ./Log.cpp)
add_library(BaiLuIME SHARED ${BAILU_IME_SOURCE_FILE})
add_executable(testIME ${TEST_FILES})
