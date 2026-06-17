QT += core gui widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    EnvironmentalImpact.cpp \
    WaterImpact.cpp \
    LandImpact.cpp \
    MenuItem.cpp \
    MenuDatabase.cpp \
    ImpactCalculator.cpp

HEADERS += \
    mainwindow.h \
    EnvironmentalImpact.h \
    WaterImpact.h \
    LandImpact.h \
    MenuItem.h \
    MenuDatabase.h \
    ImpactCalculator.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc