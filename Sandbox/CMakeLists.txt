cmake_minimum_required(VERSION 3.26)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(VCPKG_TARGET_TRIPLET MATCHES "-static$")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(SOURCES src/Sandbox.cpp
            src/SandboxLayer.cpp
            src/SpringPendulum.cpp
            src/DoubleSpringPendulum.cpp
            src/SoftBody1.cpp
            src/SoftBody2.cpp
            src/SoftBody3.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(ParticleDynamics::Sandbox ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE ParticleDynamics::Engine)
