QT += widgets

CONFIG += c++17

INCLUDEPATH += ../HonorsPrjV2

RESOURCES += resources.qrc \
    resources.qrc

SOURCES += \
    ../HonorsPrjV2/EnvironmentalImpact.cpp \
    ../HonorsPrjV2/ImpactCalculator.cpp \
    ../HonorsPrjV2/LandImpact.cpp \
    ../HonorsPrjV2/MenuDatabase.cpp \
    ../HonorsPrjV2/MenuItem.cpp \
    ../HonorsPrjV2/WaterImpact.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../HonorsPrjV2/EnvironmentalImpact.h \
    ../HonorsPrjV2/ImpactCalculator.h \
    ../HonorsPrjV2/LandImpact.h \
    ../HonorsPrjV2/MenuDatabase.h \
    ../HonorsPrjV2/MenuItem.h \
    ../HonorsPrjV2/WaterImpact.h \
    mainwindow.h

FORMS += \
    mainwindow.ui