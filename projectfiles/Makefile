CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = main
SRC = main.cpp colors.cpp towers.cpp enemies.cpp gridvars.cpp pathfinding.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET).exe $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET).exe