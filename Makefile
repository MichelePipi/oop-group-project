CXX = g++
CXXFLAGS = -std=c++17 -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = src/main.cpp \
      src/GameManager.cpp \
      src/ManualClicker.cpp \
      src/AutoGenerator.cpp \
      src/Factory.cpp \
      src/Grandma.cpp \
      src/Autoclicker.cpp \
      src/SaveFileManager.cpp

OUT = bin/cookie

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

clean:
	rm -f bin/cookie

rebuild: clean all