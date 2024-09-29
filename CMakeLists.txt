cmake_minimum_required(VERSION 3.10)
project(ClientServerConnTDE)

set(CMAKE_CXX_STANDARD 14)

set(HOME_BRIDGE_INCLUDE_DIR "/opt/homebrew/include")
set(HOME_BRIDGE_LIB_DIR "/opt/homebrew/lib")

find_path(MYSQLX_INCLUDE_DIR
	NAMES mysqlx/xdevapi.h 
	PATHS ${HOME_BRIDGE_INCLUDE_DIR}
	PATH_SUFFIXES mysqlx
)

find_library(MYSQLX_LIBRARIES 
	NAMES mysqlcppconnx
	PATHS ${HOME_BRIDGE_LIB_DIR}
)

if (MYSQLX_INCLUDE_DIR AND MYSQLX_LIBRARIES)
	message(STATUS "MySQL Connector/C++ X DevAPI found.")
else()
	message(FATAL_ERROR "MySQL Connector/C++ X DevAPI not found, verify installation")
endif()

include_directories(${MYSQLX_INCLUDE_DIR})

add_executable(crud_app src/main.cpp src/crud.cpp)

target_link_libraries(crud_app ${MYSQLX_LIBRARIES})
