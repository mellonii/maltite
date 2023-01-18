cmake_minimum_required(VERSION 3.16)

project(courseWork VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.4.0/mingw_64/lib/cmake")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)


qt_standard_project_setup()

set(QT_VERSION 6)
set(REQUIRED_LIBS Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt6::Widgets)

add_executable(${PROJECT_NAME}
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
    products.txt
    recipes.txt
        )

target_link_libraries(courseWork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(courseWork PRIVATE Qt6::Sql)
set_target_properties(courseWork PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS courseWork
    BUNDLE DESTINATION
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(courseWork)
endif()
