cmake_minimum_required(VERSION 3.5)

project(SimulationApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt5
# Specify the components (modules) you need: Core, Gui, Widgets are common.
find_package(Qt5 COMPONENTS Core Gui Widgets OpenGL REQUIRED)
find_package(OpenGL REQUIRED) # Find system OpenGL

# Add your source files
# If mainwindow.h is just a header and mainwindow.cpp contains the Q_OBJECT macro,
# it should be automatically processed by AUTOMOC if it's included by a .cpp file
# listed in add_executable. However, it's good practice to list headers if they
# might contain Q_OBJECT themselves or for clarity.
add_executable(SimulationApp
    main.cpp
    mainwindow.cpp
    mainwindow.h # Listing headers can help IDEs and ensure AUTOMOC runs if needed
    qtopenglviewwidget.cpp
    qtopenglviewwidget.h
    guievent_qt.h
)

# Link against the Qt modules
target_link_libraries(SimulationApp PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL OpenGL::GL)

# Optional: Set C++ standard if needed
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optional: Install rules (useful for packaging)
# install(TARGETS SimulationApp DESTINATION bin)
