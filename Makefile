CXX = g++
CXXFLAGS = -std=c++17 -IC:/sfml/include
LDFLAGS = -LC:/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -static-libgcc -static-libstdc++

SRC = src/main.cpp \
      src/GameManager.cpp \
      src/ManualClicker.cpp \
      src/AutoGenerator.cpp \
      src/Factory.cpp \
      src/Grandma.cpp \
      src/Autoclicker.cpp

OUT = bin/cookie.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

clean:
	del /Q bin\\*.exe

rebuild: clean all
