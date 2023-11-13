cmake_minimum_required(VERSION 3.5)
project(SlotMachine)


list(APPEND CMAKE_PREFIX_PATH Library/SDL2/cmake)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
find_package(SDL2_ttf REQUIRED CONFIG REQUIRED COMPONENTS SDL2_ttf)

 set(SDL_CMAKE_DEBUG_POSTFIX "d" 
     CACHE STRING "Name suffix for debug builds") 

### Main ###

file(GLOB HEADER_FILES Source/*/*.h Source/*.h)
file(GLOB SOURCE_FILES Source/*/*.cpp Source/*.cpp)

add_executable(SlotMachine ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(SlotMachine SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

############


if(WIN32)
	add_custom_command( TARGET SlotMachine POST_BUILD

		COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:SlotMachine>"
		COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_image::SDL2_image>" "$<TARGET_FILE_DIR:SlotMachine>"
		COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2_ttf::SDL2_ttf>" "$<TARGET_FILE_DIR:SlotMachine>"
		COMMAND "${CMAKE_COMMAND}" -E copy_directory ${CMAKE_SOURCE_DIR}/Content "$<TARGET_FILE_DIR:SlotMachine>/Content"
		VERBATIM
	)
endif()