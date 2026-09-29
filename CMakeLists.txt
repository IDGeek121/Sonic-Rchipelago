cmake_minimum_required(VERSION 3.20)

project(Sonic-Rchipelago LANGUAGES CXX)

add_compile_definitions(WIN32 _WINDOWS _USRDLL)

# APCpp
# Build APCpp from its own CMakeLists and consume it as a static dependency.
set(APCPP_BUILD_SHARED OFF CACHE BOOL "Build APCpp as a static library" FORCE)
set(BUNDLED_JSONCPP ON CACHE BOOL "" FORCE)
if (MINGW)
  set(IXWEBSOCKET_SYSTEM_CERT_STORE OFF CACHE BOOL "Disable Windows certificate store" FORCE)
endif ()
set(ZLIB_BUILD_TESTING OFF)

add_subdirectory(vendor/APCpp)

add_library(mod-loader-common STATIC
        vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon/IniFile.cpp
	vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon/TextConv.cpp
)
target_include_directories(mod-loader-common SYSTEM PRIVATE
        ${CMAKE_SOURCE_DIR}/vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon)

add_subdirectory(Sonic-Rchipelago)
