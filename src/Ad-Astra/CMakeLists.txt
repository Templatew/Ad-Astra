cmake_minimum_required(VERSION 3.16)

project(Ad-Astra VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(QT_NO_CREATE_VERSIONLESS_TARGETS ON)
set(QT_NO_CREATE_VERSIONLESS_FUNCTIONS ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    OpenGLWidgets
)

qt6_standard_project_setup()

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

include_directories(include)

qt6_add_resources(resource.qrc)

qt6_add_executable(
    Ad-Astra
    ${SOURCES}
    ${HEADERS}
    resources/resources.qrc
)

target_link_libraries(Ad-Astra PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGLWidgets
)

set_target_properties(Ad-Astra PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
