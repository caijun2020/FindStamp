# FindStamp
This is a C++ code developed by Qt4.8.6 (MinGW32) and OpenCV3.4.12 to find red stamp in picture.

2021-Apr-06
1. OpenCV3.4.12 is built by MinGW32 gcc 4.8.2
2. Relase is a console program
3. It's derived from a python program, I convert it to C++ with Qt.


How to use the releae exe
recognize_stamp.exe fileName threshold[default=500]
example1: recognize_stamp.exe stamp005.jpg 1000
example2: recognize_stamp.exe stamp005.jpg


How to build
1. Run qmake
2. Run build
3. Copy all dll files in source dir OpenCV/bin/ to shadow build dir, otherwise when run application it will crash
