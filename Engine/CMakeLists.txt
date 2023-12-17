cmake_minimum_required(VERSION 3.26)

project(Engine)

set(CMAKE_CXX_STANDARD 20)

find_package(spdlog REQUIRED)
find_package(glm REQUIRED)
find_package(SFML 2.5.0 COMPONENTS system window graphics REQUIRED)
find_package(ImGui-SFML REQUIRED)
find_package(implot REQUIRED)

set(SOURCES src/Application.cpp
            src/Layer.cpp
            src/LayerStack.cpp
            src/Logging.cpp
            src/Particle.cpp
            src/Spring.cpp)

add_library(${PROJECT_NAME} ${SOURCES})
add_library(ParticleDynamics::Engine ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} PUBLIC ImGui-SFML::ImGui-SFML)
target_link_libraries(${PROJECT_NAME} PUBLIC implot::implot)
