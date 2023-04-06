cmake_minimum_required(VERSION 3.22)
set(SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jni)

set(libYUV_H ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jni/libyuv/include)
set(libYUV_S ${CMAKE_CURRENT_SOURCE_DIR}/src/main/jni/libyuv/source)

include_directories(${SOURCE_PATH} ${libYUV_H})

aux_source_directory(${SOURCE_PATH} Source)

aux_source_directory(${libYUV_S} libyuv)

add_library(Demo SHARED ${Source} ${libyuv})

#target_compile_options(Demo PRIVATE -fsanitize=hwaddress -fno-omit-frame-pointer)
#set_target_properties(Demo PROPERTIES LINK_FLAGS -fsanitize=hwaddress)

find_library(log-lib
        log
)
target_link_libraries(
        Demo
        ${log-lib}
        GLESv3
        android
)