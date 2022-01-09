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

#aux_source_directory(src SRC)
set(SRC
	src/App.cpp
	src/AppContext.cpp
	src/Console.cpp
	src/Editor.cpp
	src/EditTextState.cpp
	src/TextFile.cpp
	src/main.cpp
)

include_directories(src/includes)
	
add_executable(Polifeditor ${SRC} ${INCLUDES})

target_link_libraries(Polifeditor ${NCURSES_LIB})