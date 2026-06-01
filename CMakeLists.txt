cmake_minimum_required(VERSION 3.24)

project(AudioLibSwitcher_applaudio LANGUAGES CXX)

set(AUDIOLIBSWITCHER_APPLAUDIO_APPLAUDIO_SOURCE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/../applaudio"
    CACHE PATH "Path to the applaudio checkout")

if(NOT TARGET applaudio::applaudio)
  add_subdirectory("${AUDIOLIBSWITCHER_APPLAUDIO_APPLAUDIO_SOURCE_DIR}"
                   "${CMAKE_CURRENT_BINARY_DIR}/applaudio"
                   EXCLUDE_FROM_ALL)
endif()

add_library(AudioLibSwitcher_applaudio INTERFACE)
add_library(AudioLibSwitcher_applaudio::AudioLibSwitcher_applaudio
            ALIAS AudioLibSwitcher_applaudio)

target_compile_features(AudioLibSwitcher_applaudio INTERFACE cxx_std_20)
target_include_directories(AudioLibSwitcher_applaudio INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/AudioLibSwitcher/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(AudioLibSwitcher_applaudio INTERFACE
  applaudio::applaudio
)

