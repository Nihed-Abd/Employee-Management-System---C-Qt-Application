QT       += core gui
QT       += sql
QT += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Mailer/smtpclient.cpp \
    client.cpp \
    connection.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Mailer/SmtpMime \
    Mailer/mimeattachment.h \
    Mailer/mimecontentformatter.h \
    Mailer/mimefile.h \
    Mailer/mimehtml.h \
    Mailer/mimeinlinefile.h \
    Mailer/mimemessage.h \
    Mailer/mimemultipart.h \
    Mailer/mimepart.h \
    Mailer/mimetext.h \
    Mailer/quotedprintable.h \
    Mailer/smtpclient.h \
    Mailer/smtpexports.h \
    client.h \
    connection.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    ../../416362684_1072327003911747_812320314637004758_n.png
