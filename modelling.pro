TARGET = modelling

CONFIG += sailfishapp c++11

SOURCES += \
    src/model.cpp \
    src/solver.cpp \
    src/controller.cpp \
    src/main.cpp

DISTFILES += qml/modelling.qml \
    qml/cover/CoverPage.qml \
    rpm/modelling.changes.in \
    rpm/modelling.changes.run.in \
    rpm/modelling.spec \
    rpm/modelling.yaml \
    translations/*.ts \
    modelling.desktop \
    qml/pages/VisualPage.qml \
    qml/pages/PlotPage.qml \
    qml/pages/SettingsPage.qml

SAILFISHAPP_ICONS = 86x86 108x108 128x128

#CONFIG += sailfishapp_i18n
#TRANSLATIONS += translations/modelling-de.ts

HEADERS += \
    src/model.h \
    src/solver.h \
    src/controller.h
