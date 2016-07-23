del *.exe
mingw32-g++.exe -g -IC:\MinGW\bin -c main.cpp -o main.o
mingw32-g++.exe -g -IC:\MinGW\bin -c tile.cpp -o tile.o
mingw32-g++.exe -g -IC:\MinGW\bin -c utils.cpp -o utils.o
mingw32-g++.exe -LC:\MinGW\bin -o main.exe main.o tile.o utils.o C:\MinGW\lib\libsfml-system.a C:\MinGW\lib\libsfml-graphics.a C:\MinGW\lib\libsfml-audio.a C:\MinGW\lib\libsfml-window.a
del *.o