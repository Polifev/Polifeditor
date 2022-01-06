cmake_minimum_required(VERSION 3.0)
project(Polifeditor)

# Include folder
#set (
#	INCLUDES
#	src/includes/**.h
#)

# Ncurses library
set (
	NCURSES_LIB
	/usr/lib/x86_64-linux-gnu/libncurses.so
)

aux_source_directory(src SRC)
include_directories(src/includes)
	
add_executable(Polifeditor ${SRC} ${INCLUDES})

target_link_libraries(Polifeditor ${NCURSES_LIB})