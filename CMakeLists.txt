cmake_minimum_required(VERSION 3.16)

project(TestSystem VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TestSystem
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        networkmanager.h networkmanager.cpp
        teacherwindow.h teacherwindow.cpp teacherwindow.ui
        uploadquestionwindow.h uploadquestionwindow.cpp uploadquestionwindow.ui
        singleselectwindow.h singleselectwindow.cpp singleselectwindow.ui
        mulselectwindow.h mulselectwindow.cpp mulselectwindow.ui
        judgewindow.h judgewindow.cpp judgewindow.ui
        shortanswerwindow.h shortanswerwindow.cpp shortanswerwindow.ui
        questionmanagewindow.h questionmanagewindow.cpp questionmanagewindow.ui
        administratorwindow.h administratorwindow.cpp administratorwindow.ui
        usermanagewindow.h usermanagewindow.cpp usermanagewindow.ui
        testproductwindow.h testproductwindow.cpp testproductwindow.ui
        userinfomanager.h userinfomanager.cpp
        config.h
        changesinglewindow.h changesinglewindow.cpp changesinglewindow.ui
        studentwindow.h studentwindow.cpp studentwindow.ui
        changemulwindow.h changemulwindow.cpp changemulwindow.ui
        changejudgewindow.h changejudgewindow.cpp changejudgewindow.ui
        changeshortwindow.h changeshortwindow.cpp changeshortwindow.ui
        testview.h testview.cpp testview.ui


    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TestSystem APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TestSystem SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TestSystem
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TestSystem PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TestSystem)
endif()
set_target_properties(TestSystem PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TestSystem
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TestSystem)
endif()


