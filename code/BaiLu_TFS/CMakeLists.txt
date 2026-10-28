cmake_minimum_required(VERSION 3.10)
project(BaiLu_IME)
SET(CMAKE_CXX_STANDARD 20)
#add_compile_definitions(UNICODE _UNICODE)
include_directories(../external/BaiLuIME_Common/include)
include_directories(../external/BaiLuIME_Common/thirdparty/json11/)
include_directories(../external/BaiLuIME_CandidateGenerator/code/include)
include_directories(../external/BaiLuIME_CandidateWindow/code/source/)
SET(BAILU_IME_SOURCE_FILE 
./DllMain.cpp 
./DllServerFunction.cpp 
./GlobalValues.cpp
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
./BaiLuConnectThread.h
./BaiLuConnectThread.cpp
./BaiLuIME.rc
./BaiLuIME.def
../external/BaiLuIME_Common/src/core/Logger.cpp
../external/BaiLuIME_Common/src/core/CommonFunction.cpp
)

SET(GENERATOR_SOURCE_FOLDER ../external/BaiLuIME_CandidateGenerator/code/src/core/)
SET(CANDIDATE_GENERATOR_SOURCE_FILE 
${GENERATOR_SOURCE_FOLDER}/SimpleCandidateGenerator.cpp
${GENERATOR_SOURCE_FOLDER}/SimpleQuanPinGenerator.cpp
${GENERATOR_SOURCE_FOLDER}/RimeCandidateGenerator.cpp
${GENERATOR_SOURCE_FOLDER}/RimeIceDictionary.cpp
${GENERATOR_SOURCE_FOLDER}/LocalTcpGenerator.cpp
${GENERATOR_SOURCE_FOLDER}/TcpClient.cpp
../external/BaiLuIME_Common/thirdparty/json11/json11.cpp)

SET(WINDOW_SOURCE_FOLDER ../external/BaiLuIME_CandidateWindow/code/source)
SET(CANDIDATE_WINDOW_SOURCE_FILE  
${WINDOW_SOURCE_FOLDER}/CandidateWindow.cpp
${WINDOW_SOURCE_FOLDER}/CandidateWindow.h
${WINDOW_SOURCE_FOLDER}/ListCandidateView.cpp
${WINDOW_SOURCE_FOLDER}/ListCandidateView.h
${WINDOW_SOURCE_FOLDER}/PreeditWindow.cpp
${WINDOW_SOURCE_FOLDER}/WindowBase.cpp)


SET(TEST_FILES ./test_main.cpp ./GlobalValues.cpp ./RegKeyFunction.cpp)
link_libraries(ws2_32.lib)
add_library(BaiLuIME SHARED ${BAILU_IME_SOURCE_FILE} ${CANDIDATE_GENERATOR_SOURCE_FILE} ${CANDIDATE_WINDOW_SOURCE_FILE})
add_executable(testIME ${TEST_FILES})
