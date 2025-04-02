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
./BaiLu_ClassFactory.hpp
./BaiLu_ClassFactory.cpp
./BaiLuInputMethodClass.hpp
./BaiLuInputMethodClass.cpp
./BaiLuInputMethodInterface.cpp
./BaiLuKeyEventSink.hpp
./BaiLuKeyEventSink.cpp
./BaiLuThreadMgrEventSink.hpp
./BaiLuThreadMgrEventSink.cpp
./BaiLuTextEditSink.hpp
./BaiLuTextEditSink.cpp
./BaiLuCompositionSink.hpp
./BaiLuCompositionSink.cpp
./BaiLuDisplayAttributeProvider.hpp
./BaiLuDisplayAttributeProvider.cpp
./BaiLuActiveLanguageProfileNotifySink.hpp
./BaiLuActiveLanguageProfileNotifySink.cpp
./BaiLuThreadFocusSink.hpp
./BaiLuThreadFocusSink.cpp
./BaiLuFunctionProvider.hpp
./BaiLuFunctionProvider.cpp
./BaiLuFnGetPreferredTouchKeyboardLayout.hpp
./BaiLuFnGetPreferredTouchKeyboardLayout.cpp
./BaiLuInputProcessorProfileAgent.hpp
./BaiLuInputProcessorProfileAgent.cpp
./BaiLuIME.rc
./BaiLuIME.def)

SET(TEST_FILES ./test_main.cpp ./GlobalValues.cpp ./RegKeyFunction.cpp ./Log.cpp)
add_library(BaiLuIME SHARED ${BAILU_IME_SOURCE_FILE})
add_executable(testIME ${TEST_FILES})
