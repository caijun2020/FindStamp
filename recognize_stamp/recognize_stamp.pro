QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/OpenCV/include

LIBS += $$PWD/OpenCV/bin/libopencv_core3412.dll
LIBS += $$PWD/OpenCV/bin/libopencv_imgcodecs3412.dll
LIBS += $$PWD/OpenCV/bin/libopencv_imgproc3412.dll
#LIBS += $$PWD/OpenCV/bin/libopencv_highgui3412.dll
#LIBS += $$PWD/OpenCV/bin/libopencv_features2d3412.dll
#LIBS += $$PWD/OpenCV/bin/libopencv_calib3d3412.dll
