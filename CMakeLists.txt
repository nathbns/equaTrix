cmake_minimum_required(VERSION 3.16)

project(EquaTrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activer MOC, RCC, UIC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Trouver Qt avec les modules requis
find_package(Qt6 COMPONENTS Widgets Charts Concurrent QUIET)
if (NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets Charts Concurrent REQUIRED)
    set(QT_PREFIX Qt5)
else()
    set(QT_PREFIX Qt6)
endif()

# ANTLR4 Configuration
set(ANTLR4_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr4/runtime/src)
file(GLOB_RECURSE ANTLR4_RUNTIME_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr4/runtime/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr4/runtime/src/atn/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr4/runtime/src/dfa/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/antlr4/runtime/src/misc/*.cpp
)

add_library(antlr4_runtime STATIC ${ANTLR4_RUNTIME_SOURCES})
target_include_directories(antlr4_runtime PUBLIC ${ANTLR4_INCLUDE_DIR})


# Add ANTLR4 generated sources
set(ANTLR4_SOURCES
    src/antlr4/CalcLexer.cpp
    src/antlr4/CalcParser.cpp
)

# Inclure les fichiers pour l'application Qt (sans src/main.cpp)
set(SOURCES
    src/backend/Function.cpp
    src/backend/Integral.cpp
    src/backend/Matrix.cpp 
    src/backend/System.cpp
    src/qt/mainQt.cpp
    src/qt/mainwindow.cpp
    src/antlr4/ExprTree.cpp
    ${ANTLR4_SOURCES}
)

set(HEADERS
    src/backend/Function.h
    src/backend/Integral.h
    src/backend/Matrix.h
    src/backend/System.h
    src/antlr4/ExprTree.h
    src/qt/mainwindow.h
)

set(RESOURCES
    src/qt/resources.qrc
    src/qt/mainwindow.ui
)

# Configurer l'exécutable Qt
add_executable(EquaTrix_qt ${SOURCES} ${RESOURCES})

# Inclure les répertoires d'en-têtes
target_include_directories(EquaTrix_qt PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${ANTLR4_INCLUDE_DIR}
)

# Configurer l'application
set_target_properties(EquaTrix_qt PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

# Librairies spécifiques à la plateforme
if(APPLE)
    find_library(FOUNDATION_LIBRARY Foundation REQUIRED)
    find_library(APPKIT_LIBRARY AppKit REQUIRED)
    target_link_libraries(EquaTrix_qt PRIVATE 
        ${FOUNDATION_LIBRARY} 
        ${APPKIT_LIBRARY}
    )
elseif(WIN32)
    target_link_libraries(EquaTrix_qt PRIVATE user32 gdi32)
endif()

# Lier les bibliothèques Qt
target_link_libraries(EquaTrix_qt PRIVATE 
    ${QT_PREFIX}::Widgets
    ${QT_PREFIX}::Charts
    ${QT_PREFIX}::Concurrent
    antlr4_runtime
)

# Installation
install(TARGETS EquaTrix_qt
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)