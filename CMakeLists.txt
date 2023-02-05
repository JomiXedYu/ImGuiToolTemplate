cmake_minimum_required (VERSION 3.8)

project ("ImGuiToolTemplate")

add_definitions( -D__PROJECT_NAME="${PROJECT_NAME}" )

set(CMAKE_CXX_STANDARD 23)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_compile_options("/utf-8")
endif()

include_directories(".")
include_directories("Lib")

add_subdirectory("./Lib/imgui")
add_subdirectory("./CoreLib")
add_subdirectory("./CoreLib.Serialization")

link_directories("Lib")

aux_source_directory(./ DIR_SRCS)
add_executable (${PROJECT_NAME} ${DIR_SRCS} "./Lib/glad.c")

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")

target_link_libraries(${PROJECT_NAME} glfw3)
target_link_libraries(${PROJECT_NAME} imgui)
target_link_libraries(${PROJECT_NAME} jxcorlib)
target_link_libraries(${PROJECT_NAME} jxcorlib.ser)