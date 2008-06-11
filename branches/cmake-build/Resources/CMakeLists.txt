# Resources CMake file

set (Resource_SubDirs audio images)
set (Resources
     "game-paths.txt"
     "pause-paths.txt"
     "icon.png"
     "times.ttf"
     "menu-paths.txt"
     "platforms.txt"
     "players.txt"
     "pselect-paths.txt")
set (resource_dependencies)

foreach (rsrc ${Resource_SubDirs} ${Resources})
    list (APPEND resource_dependencies ${rsrc})
endforeach (rsrc)

add_custom_target (resources
                   DEPENDS ${resource_dependencies})

foreach (Resource_SubDir ${Resource_SubDirs})
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${Resource_SubDir}
                        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/${Resource_SubDir} ${CMAKE_CURRENT_BINARY_DIR}/${Resource_SubDir}
                        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${Resource_SubDir})
endforeach (Resource_SubDir)

foreach (rsrc ${Resources})
    add_custom_command (OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${rsrc}
                        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${rsrc} ${CMAKE_CURRENT_BINARY_DIR}/${rsrc}
                        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${rsrc})
endforeach (rsrc)
