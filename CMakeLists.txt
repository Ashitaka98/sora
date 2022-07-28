cmake_minimum_required(VERSION 3.14)
project(SORA)

set(CMAKE_CXX_STANDARD 11)

include_directories(./dependency/glm)
include_directories(./dependency/stb)
include_directories(./dependency/freeglut/include)
include_directories(./include)

set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
add_subdirectory(./dependency/freeglut freeglut)

set(SORA_H
	./include/rasterizer.h
	./include/primitiveFactory.h
	./include/utils.h
	./include/defines.h
	./include/camera.h
	./include/illuminare.h
	./include/texture.h
	./include/renderController.h
)

set(SORA_S 
	./src/main.cpp
	./src/rasterizer.cpp
	./src/texture.cpp
	./src/renderController.cpp
)

source_group("Header" FILES
	${SORA_H}
)

source_group("Source" FILES
	${SORA_S}
)

add_executable(SORA ${SORA_S} ${SORA_H})
target_link_libraries(SORA freeglut_static)