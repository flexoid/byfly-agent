QT += network
SOURCES += main.cpp \
    view.cpp \
    scene.cpp \
    graphbutton.cpp \
    controller.cpp \
    http.cpp \
    settingsfile.cpp \
    settingsdialog.cpp \
    menu.cpp \
    animimage.cpp
HEADERS += view.h \
    scene.h \
    graphbutton.h \
    controller.h \
    http.h \
    settingsfile.h \
    menu.h \
    settingsdialog.h \
    animimage.h
RESOURCES += res.qrc
FORMS += settingsdialog.ui
TRANSLATIONS = lang_ru.ts \
    lang_by.ts
#LIBS += -LC:\OpenSSL\lib -ssleay32
RC_FILE = byfly-agent.rc

