# Executable
add_executable (crab-battle
                BaseObject.cpp
                exceptions.cpp
                GameState.cpp
                main.cpp
                MenuState.cpp
                PausedState.cpp
                Player.cpp
                PlayerSelect.cpp
                Rect.cpp
                SoundEffect.cpp
                Sprite.cpp
                State.cpp
                Surface.cpp
                util.cpp
                VictoryScreen.cpp)
add_dependencies (crab-battle resources)

# Libraries
find_library (libSDL SDL)
set (libSDL ${libSDL} CACHE FILEPATH "SDL Library")
find_library (libSDL_image SDL_image)
set (libSDL_image ${libSDL_image} CACHE FILEPATH "SDL_image Library")
find_library (libSDL_mixer SDL_mixer)
set (libSDL_mixer ${libSDL_mixer} CACHE FILEPATH "SDL_mixer Library")
find_library (libSDL_ttf SDL_ttf)
set (libSDL_ttf ${libSDL_ttf} CACHE FILEPATH "SDL_ttf Library")
find_library (libode ode)
set (libode ${libode} CACHE FILEPATH "ODE Library")
target_link_libraries (crab-battle
                       ${libSDL}
                       ${libSDL_image}
                       ${libSDL_mixer}
                       ${libSDL_ttf}
                       ${libode})
# Headers
find_file (SDL_include SDL)
set (SDL_include ${SDL_include} CACHE PATH "SDL headers")
include_directories (${SDL_include})
