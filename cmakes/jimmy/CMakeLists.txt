cmake_minimum_required(VERSION 2.6)

# nom de l'executable
set (PROJ Bomberman)

ADD_DEFINITIONS(-std=c++0x)
ADD_DEFINITIONS(-g)
# Nom du projet
project(${PROJ} C CXX)

# repertoire du binaire
set (BINNAME ${PROJ})

set (CLI client)
set (SER server)

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
if ( NOT SDLTTF_FOUND )
    message(FATAL_ERROR "SDL_ttf not found !")
endif ( NOT SDLTTF_FOUND )

include_directories(${SDLTTF_INCLUDE_DIR})

file(
    GLOB_RECURSE
    source_files_global
    ../../Code/global/*
)

file(
    GLOB_RECURSE
    source_files_client
    ../../Code/client/*
)

file(
    GLOB_RECURSE
    source_files_server
    ../../Code/server/*
)

file(
    GLOB_RECURSE
    source_files_proto
    ../../Code/proto/*
)


# Déclaration de l'exécutable
add_executable(
    ${BINNAME}
    ${source_files_global}
    ../../Code/main.cpp
)

# Déclaration de l'exécutable
add_executable(
    ${CLI}
    ${source_files_client}
    ${source_files_global}
    ${source_files_proto}
)

# Déclaration de l'exécutable
add_executable(
    ${SER}
    ${source_files_server}
    ${source_files_global}
    ${source_files_proto}
)

# On link les libs
target_link_libraries(
    ${BINNAME}
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
)

target_link_libraries(
    ${CLI} 
    -lboost_iostreams-mt
	-lboost_thread-mt
	-lboost_program_options-mt
    -lnetez
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
)

target_link_libraries(
    ${SER}
    -lboost_iostreams-mt
	-lboost_thread-mt
	-lboost_program_options-mt
	-lpthread
    -lnetez
    ${SDL_LIBRARY}
    ${SDLIMAGE_LIBRARY}
    ${SDLTTF_LIBRARY}
)
