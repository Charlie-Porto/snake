cmake_minimum_required (VERSION 2.6)

set(PROJECT Snake)
set(SDL_PATH /Users/charlieporto/realshit/cppstuff/packages/SDL2/SDL2)
project (${PROJECT})
add_compile_options(-std=c++17)

add_executable(${PROJECT}
    src/main.cpp
    src/core/CoreManager.cpp
    src/core/Simulation.cpp
)

target_include_directories(${PROJECT} PUBLIC
    ${SDL_PATH}/include/SDL2_include
    ${SDL_PATH}/include/SDL2image_include
)

target_link_libraries(${PROJECT} PUBLIC
    ${SDL_PATH}/lib/sdl2/2.0.16/lib/libSDL2-2.0.0.dylib
    ${SDL_PATH}/lib/sdl2_image/2.0.5/lib/libSDL2_image-2.0.0.dylib
    #sdl2
    #sdl2_image
)
