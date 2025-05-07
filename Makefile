# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iheaders

# Raylib library paths (adjust if necessary)
RAYLIB_FLAGS = -lraylib 

# Source and output
SRC = $(wildcard sources/*.cpp)
OUT = wisdom.exe

# Build target
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(RAYLIB_FLAGS)
	./$(OUT)

# Clean target
clean:
	del $(OUT)
