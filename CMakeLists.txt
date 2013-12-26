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

if ( NOT SDL_IMAGE_FOUND )
    message(FATAL_ERROR "SDL_image not found !")
endif ( NOT SDL_IMAGE_FOUND )

include_directories(${SDL_IMAGE_INCLUDE_DIR})


# On ajoute SDL_ttf
Find_Package(SDL_ttf REQUIRED)

if ( NOT SDL_TTF_FOUND )
    message(FATAL_ERROR "SDL_ttf not found !")
endif ( NOT SDL_TTF_FOUND )

include_directories(${SDL_TTF_INCLUDE_DIR})

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

# On link les libs
target_link_libraries(
    ${BINNAME}
    ${SDL_LIBRARY}
    ${SDL_IMAGE_LIBRARIES}
    ${SDL_TTF_LIBRARIES}
)