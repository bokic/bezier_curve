cmake_minimum_required(VERSION 3.19)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(bezier_curve LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(bezier_curve
    WIN32 MACOSX_BUNDLE
    main.cpp
    dialog.cpp
    dialog.h
    dialog.ui
    qbeziercurvewidget.cpp
    qbeziercurvewidget.h
)

target_link_libraries(bezier_curve
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(bezier_curve PRIVATE Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS bezier_curve
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET bezier_curve
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
