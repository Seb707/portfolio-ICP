cmake_minimum_required(VERSION 3.15)

project(labo02)

# Setup language requirements
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#--------------------------------------------------
# Sous MAC, OpenGL est Deprecated, mais toujours
# fonctionnel, on veut éviter tous les warnings
# durant la compilation.
#--------------------------------------------------
if (APPLE)
  add_definitions( -DGL_SILENCE_DEPRECATION )
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add .cpp and .h files
set(HEADERS Icp.h IcpApplication.h IcpGLCanvas.h SVD.h)
set(SOURCE main.cpp Icp.cpp IcpApplication.cpp IcpGLCanvas.cpp)
add_executable(labo02 ${SOURCE} ${HEADERS})

target_link_libraries(labo02 labo01 nanogui ${NANOGUI_EXTRA_LIBS})

if(MSVC) 
	set_property(TARGET labo02 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/labo02/obj)
endif()