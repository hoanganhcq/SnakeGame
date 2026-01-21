# all: 
# 	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2

# Makefile

#----------------------------------------------------------------------------

# all:
# 	g++ -I src/include -L src/lib \
# 		main.cpp src/gameLoop.cpp \
# 		-o main.exe \
# 		-lmingw32 -lSDL2main -lSDL2

# clean:
# 	del main.exe

#----------------------------------------------------------------------------

# Makefile nâng cao - tự động dependency

CC = g++
CFLAGS = -std=c++17 -Wall -I src/include -MMD -MP
LDFLAGS = -L src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Tìm tất cả source
SOURCES = $(wildcard *.cpp src/*.cpp src/**/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
DEPENDS = $(OBJECTS:.o=.d)

all: main.exe

main.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o main.exe $(LDFLAGS)

# Rule compile + sinh dependency
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Include các file dependency đã sinh ra
-include $(DEPENDS)

clean:
	del /Q $(OBJECTS) $(DEPENDS) main.exe *.exe