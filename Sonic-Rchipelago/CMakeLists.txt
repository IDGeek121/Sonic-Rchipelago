add_library(Sonic-Rchipelago SHARED "apworld.cpp" "config.cpp" "mod.cpp")

target_include_directories(Sonic-Rchipelago SYSTEM PRIVATE
	${CMAKE_SOURCE_DIR}/vendor/sonicr-mod-loader/SonicRModLoader/include
	${CMAKE_SOURCE_DIR}/vendor/sonicr-mod-loader/mod-loader-common/ModLoaderCommon
)

#target_compile_features(Sonic-Rchipelago PRIVATE cxx_std_17)

target_link_libraries(Sonic-Rchipelago PRIVATE APCpp mod-loader-common)

if (MINGW)
  target_link_options(APCpp PRIVATE -static -static-libstdc++ -static-libgcc)
endif (MINGW)

set_target_properties(Sonic-Rchipelago PROPERTIES PREFIX "" OUTPUT_NAME "Sonic-Rchipelago")

add_custom_command(
  TARGET Sonic-Rchipelago
  POST_BUILD
  COMMAND ${CMAKE_COMMAND}
  ARGS -E copy $<TARGET_FILE:Sonic-Rchipelago> ${CMAKE_SOURCE_DIR}/mods/Sonic-Rchipelago
)
