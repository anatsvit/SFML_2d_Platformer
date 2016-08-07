del *.exe
mingw32-g++.exe -g -IC:\MinGW\bin -c editor.cpp -o editor.o
mingw32-g++.exe -LC:\MinGW\bin -o editor.exe editor.o C:\MinGW\lib\libsfml-system.a C:\MinGW\lib\libsfml-graphics.a C:\MinGW\lib\libsfml-audio.a C:\MinGW\lib\libsfml-window.a
del *.o