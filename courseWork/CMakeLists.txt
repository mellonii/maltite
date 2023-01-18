cmake_minimum_required(VERSION 3.5)

project(courseWork VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install" CACHE PATH "..." FORCE)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        create_prod.h
        create_prod.cpp
        create_prod.ui
        create_recipe.h
        create_recipe.cpp
        create_recipe.ui
        recipe.h
        recipe.cpp
        recipe.ui
        product.h
        product.cpp
        product.ui
        favfood.h
        favfood.cpp
        favfood.ui
        hatefood.h
        hatefood.cpp
        hatefood.ui
        adddish.h
        adddish.cpp
        adddish.ui
        #products.txt
        #recipes.txt
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(courseWork
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(courseWork SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(courseWork
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(courseWork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(courseWork PRIVATE Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(courseWork PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(courseWork)
endif()

######installation directly to build folder for proper debugging in VisualStudio####

####################################################################################
install(TARGETS courseWork DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES products.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(FILES recipes.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
####################################################################################


######normal installation in a folder specified by CMAKE_INSTALL_PREFIX#############

####################################################################################
install(TARGETS courseWork DESTINATION .)
install(FILES products.txt DESTINATION .)
install(FILES recipes.txt DESTINATION .)
####################################################################################
