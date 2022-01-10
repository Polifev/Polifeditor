cmake_minimum_required(VERSION 3.0)
project(Polifeditor)


# NCURSES library
Find_package(Curses)

# every source file
set(SRC
	src/App.cpp
	src/AppContext.cpp
	src/Console.cpp
	src/Editor.cpp
	src/EditTextState.cpp
	src/FileBrowser.cpp
	src/Keyboard.cpp
	src/SaveState.cpp
	src/ScrollingWindow.cpp
	src/TextFile.cpp
	src/main.cpp
)

# headers location
include_directories(src/includes)
	
# build executable
add_executable(Polifeditor ${SRC} ${INCLUDES})

# Use C++17
target_compile_features(Polifeditor PUBLIC cxx_std_17)

# link libraries
target_link_libraries(Polifeditor ${CURSES_LIBRARIES})