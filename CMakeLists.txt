cmake_minimum_required(VERSION 2.6)

# nom e l'executable
set (PROJ Bomberman)

# Nom du projet
project(${PROJ})

# repertoire du binaire
set (BINNAME ${PROJ})

# On ajoute SDL
Find_Package(SDL REQUIRED)

if ( NOT SDL_FOUND )
    message(FATAL_ERROR "SDL not found !")
endif ( NOT SDL_FOUND )

include_directories(${SDL_INCLUDE_DIR})


# On ajoute SDL_image
Find_Package(SDL_image REQUIRED)

if ( NOT SDLIMAGE_FOUND )
    message(FATAL_ERROR "SDL_image not found !")
endif ( NOT SDLIMAGE_FOUND )

include_directories(${SDLIMAGE_INCLUDE_DIR})


# On ajoute SDL_ttf
Find_Package(SDL_ttf REQUIRED)

message(${SDL_FOUND})
if ( NOT SDLTTF_FOUND )
    message(FATAL_ERROR "SDL_ttf not found !")
endif ( NOT SDLTTF_FOUND )

include_directories(${SDLTTF_INCLUDE_DIR})

# On ajoute netez
set (NETEZ_INCLUDE_DIR $ENV{HOME}/include/netez)
set (NETEZ_LIBRARY $ENV{HOME}/lib/netez)

include_directories(${NETEZ_INCLUDE_DIR})

file(
    GLOB_RECURSE
    source_files
    Code/*
)

# Déclaration de l'exécutable
add_executable(
    ${BINNAME}
    ${source_files}
)

ADD_DEFINITIONS(-std=c++0x)

# On link les libs
target_link_libraries(
    ${BINNAME}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
    --copy-dt-needed-entries 
    -lnetez
)