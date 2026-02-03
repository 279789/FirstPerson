cmake_minimum_required(VERSION 3.18)
project(CopperSpiceTest)
 
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)

#The Directorys is located where you downloaded CS
#You have to adjust your path:
set(CopperSpice_DIR "/home/phil/cpplibs/cs2.0_libs/lib/cmake/CopperSpice") 
find_package(CopperSpice REQUIRED)
 
# file locations for installing
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
  include(GNUInstallDirs)
 
  # where libraries are located relative to the executable
  set(CMAKE_INSTALL_RPATH "@executable_path/../Resources")
 
elseif(CMAKE_SYSTEM_NAME MATCHES "(Linux|OpenBSD|FreeBSD)")
  include(GNUInstallDirs)
  set(CMAKE_INSTALL_RPATH "\$ORIGIN")
 
elseif(MSVC)
   # use defaults
 
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
   set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
   include(${CopperSpice_DIR}/InstallMinGW.cmake)
 
endif()
 
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
 
# location for building binary files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
 
list(APPEND PROJECT_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

add_Library(RaycasterLib
	lib/Display3D.hpp
	lib/Display3D.cpp
	lib/FirstPerson.hpp
	lib/GameMaster.hpp
	lib/GameMaster.cpp
	lib/Map.hpp
	lib/Map.cpp
	lib/Player.hpp
	lib/Player.cpp
)



# Shows where the Libraries are. 
# The directorys are located where you downloaded CS
# You need to adjust your path:
include_directories(
    "/home/phil/cpplibs/cs2.0_libs/include"
    "/home/phil/cpplibs/cs2.0_libs/include/QtCore"
    "/home/phil/cpplibs/cs2.0_libs/include/QtGui"
    "/home/phil/cpplibs/cs2.0_libs/include/QtNetwork"
    "lib"

)
 
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
 
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  target_link_libraries(${PROJECT_NAME}
    PRIVATE
    netapi32 
    mpr
   -mwindows
  )
endif()
 

target_link_libraries(RaycasterLib
      	PRIVATE
  CopperSpice::CsCore
  CopperSpice::CsGui
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  CopperSpice::CsCore
  CopperSpice::CsGui
  RaycasterLib
)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
cs_copy_library(CsCore)
cs_copy_library(CsGui)
 
# installs the platform Gui plugin
cs_copy_plugins(CsGui)
