CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -I include
LDFLAGS =

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = study_tracker

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
