QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Alojamiento.h \
    Anfitrion.h \
    Huesped.h \
    Lista.h \
    MonitorSistema.h \
    Nodo.h \
    Reservacion.h \
    SistemaUdeAStay.h
