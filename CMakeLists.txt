cmake_minimum_required(VERSION 3.16)

project(Hotel VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appHotel
    main.cpp
)

qt_add_qml_module(appHotel
    URI Hotel
    QML_FILES Main.qml
    SOURCES hotelbackend.h hotelbackend.cpp
    SOURCES components/QDatePicker/src/qdatepicker.cpp
    SOURCES components/QDatePicker/src/qdatepicker.h
    QML_FILES AdminDashboard.qml
    QML_FILES UserDashboard.qml
    QML_FILES components/QDatePicker/src/DatePicker.qml
    QML_FILES LoginView.qml
    QML_FILES LandingPage.qml
    RESOURCES images/hotel.jpg
    RESOURCES images/logo.png
    RESOURCES images/logonotext.png
    RESOURCES images/logovertical.png
    RESOURCES images/standard.jpg
    RESOURCES images/deluxe.jpg
    RESOURCES images/suite.jpg
    QML_FILES RegisterView.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appHotel PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appHotel
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHotel
    PRIVATE Qt6::Quick
)

install(TARGETS appHotel
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
