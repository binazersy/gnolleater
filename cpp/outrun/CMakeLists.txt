project(outrun)

set(SFML_PATH ~/gnolleater/SFML-2.5.1)

include_directories(${SFML_PATH}/include)

link_directories(${SFML_PATH}/lib)

add_executable(${CMAKE_PROJECT_NAME} outrun.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-window sfml-system)

#add_dependencies(outrun sfml-graphics sfml-window sfml-system)

