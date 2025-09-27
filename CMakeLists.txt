cmake_minimum_required(VERSION 3.16)

project(barcodeDecoder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt setup
find_package(Qt6 REQUIRED COMPONENTS Quick Multimedia)
qt_standard_project_setup(REQUIRES 6.8)

# Executable
qt_add_executable(appbarcodeDecoder
    main.cpp
)

qt_add_qml_module(appbarcodeDecoder
    URI barcodeDecoder
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        barcodedecoder.h barcodedecoder.cpp
        videomanager.h videomanager.cpp
        appcontroller.h appcontroller.cpp
)

# OpenCV setup
set(OpenCV_DIR "C:/opencv/OpenCV-MinGW-Build-OpenCV-4.5.5-x64")
# set(OpenCV_DIR "C:/opencv/OpenCV-MSVC-2022-Build-4.10.0/build/x64/vc16/lib")
find_package(OpenCV REQUIRED)
target_include_directories(appbarcodeDecoder PRIVATE ${OpenCV_INCLUDE_DIRS})

# ZXing-Cpp setup
# Use the install path from your "cmake --install"
# It should contain lib/cmake/ZXing/ZXingConfig.cmake
# set(ZXing_DIR "C:/zxing-cpp/install/lib/cmake/ZXing")
list(APPEND CMAKE_PREFIX_PATH "C:/ZXing")
find_package(ZXing REQUIRED)
# REQUIRED HINTS "C:/zxing-cpp/install/lib/cmake/ZXing")

# Properties
set_target_properties(appbarcodeDecoder PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# Linking
target_link_libraries(appbarcodeDecoder
    PRIVATE
    Qt6::Quick
    Qt6::Multimedia
    ZXing::ZXing
    ${OpenCV_LIBS}
)

# Install rules
include(GNUInstallDirs)
install(TARGETS appbarcodeDecoder
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
