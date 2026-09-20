cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

set(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

set(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

project(sonic-r-archipelago LANGUAGES CXX)

add_compile_definitions(WIN32 _WINDOWS _USRDLL)

# APCpp
# Build APCpp from its own CMakeLists and consume it as a static dependency.
set(APCPP_BUILD_SHARED OFF CACHE BOOL "Build APCpp as a static library" FORCE)
set(BUNDLED_JSONCPP ON CACHE BOOL "" FORCE)
if (MINGW)
  set(IXWEBSOCKET_SYSTEM_CERT_STORE OFF CACHE BOOL "Disable Windows certificate store" FORCE)
endif ()
add_subdirectory(vendor/APCpp EXCLUDE_FROM_ALL)

add_library(mod-loader-common STATIC
        vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon/IniFile.cpp
	vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon/TextConv.cpp
)
target_include_directories(mod-loader-common SYSTEM PRIVATE
        ${CMAKE_SOURCE_DIR}/vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon)

add_library(sonic-r-archipelago SHARED src/config.cpp src/mod.cpp src/apworld.cpp)

target_compile_features(sonic-r-archipelago PRIVATE cxx_std_17)

target_include_directories(sonic-r-archipelago SYSTEM PRIVATE
	${CMAKE_SOURCE_DIR}/vendor/sonicr-mod-loader/SonicRModLoader/include
	${CMAKE_SOURCE_DIR}/vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon
)

target_link_libraries(sonic-r-archipelago PRIVATE APCpp mod-loader-common)

set_target_properties(sonic-r-archipelago PROPERTIES PREFIX "" OUTPUT_NAME "sonic-r-archipelago")
