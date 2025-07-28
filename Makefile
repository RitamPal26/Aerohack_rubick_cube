CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

# Corrected Source Files:
# - Added Phase1Heuristic.cpp and Phase2Heuristic.cpp
# - Removed the old Heuristic.cpp and PatternDatabase.cpp
SRCS = src/main.cpp src/Cube.cpp src/IDASolver.cpp src/Phase1Heuristic.cpp src/Phase2Heuristic.cpp

TARGET = rubiks_solver

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)