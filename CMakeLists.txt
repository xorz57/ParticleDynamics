cmake_minimum_required(VERSION 3.26)

project(ParticlePhysics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(VCPKG_TARGET_TRIPLET MATCHES "-static$")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

find_package(spdlog REQUIRED)
find_package(glm REQUIRED)
find_package(SFML 2.5.0 COMPONENTS system window graphics REQUIRED)
find_package(ImGui-SFML REQUIRED)
find_package(implot REQUIRED)

set(SOURCES src/Application.cpp
            src/DoubleSpringPendulum.cpp
            src/Logging.cpp
            src/Main.cpp
            src/Particle.cpp
            src/SoftBody1.cpp
            src/SoftBody2.cpp
            src/SoftBody3.cpp
            src/Spring.cpp
            src/SpringPendulum.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(${PROJECT_NAME} PRIVATE implot::implot)
