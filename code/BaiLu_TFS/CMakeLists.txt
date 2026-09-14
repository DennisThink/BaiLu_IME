cmake_minimum_required(VERSION 3.10)
project(BaiLu_IME)
#add_compile_definitions(UNICODE _UNICODE)
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
./BaiLuLanguageBarItemButton.hpp
./BaiLuLanguageBarItemButton.cpp
./BaiLuInputCore.hpp 
./BaiLuInputCore.cpp
./CommonFunction.hpp
./CommonFunction.cpp
./BaiLuEditSession.hpp 
./BaiLuEditSession.cpp
./BaiLu_DeleteBeforeEditSession.hpp 
./BaiLu_DeleteBeforeEditSession.cpp
./BaiLuIME.rc
./BaiLuIME.def)

SET(GENERATOR_SOURCE_FOLDER ../BaiLu_CandidateGenerator/source)
SET(CANDIDATE_GENERATOR_SOURCE_FILE ${GENERATOR_SOURCE_FOLDER}/SimpleCandidateGenerator.cpp)

SET(WINDOW_SOURCE_FOLDER ../BaiLu_CandidateWindow/source)
SET(CANDIDATE_WINDOW_SOURCE_FILE  ${WINDOW_SOURCE_FOLDER}/CandidateWindow.cpp
${WINDOW_SOURCE_FOLDER}/CandidateWindow.h
${WINDOW_SOURCE_FOLDER}/ListCandidateView.cpp
${WINDOW_SOURCE_FOLDER}/ListCandidateView.h)


SET(TEST_FILES ./test_main.cpp ./GlobalValues.cpp ./RegKeyFunction.cpp ./Log.cpp)
add_library(BaiLuIME SHARED ${BAILU_IME_SOURCE_FILE} ${CANDIDATE_GENERATOR_SOURCE_FILE} ${CANDIDATE_WINDOW_SOURCE_FILE})
add_executable(testIME ${TEST_FILES})
