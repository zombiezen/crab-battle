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

target_link_libraries (crab-battle SDL SDL_image SDL_mixer SDL_ttf ode)
include_directories (/usr/include/SDL)
