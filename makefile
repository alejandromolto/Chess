# Name of the executable
TARGET    = chess_game

# Compiler and packages
CXX       = g++
PKG       = sdl2 SDL2_image

# Compiler and linker flags
CXXFLAGS  = -std=c++17 -Wall -Wextra -g $(shell pkg-config --cflags $(PKG)) -I.
LDFLAGS   = $(shell pkg-config --libs $(PKG))

# Directories
SRC_DIR   = src
INC_DIR   = include

# Source and object files
SRCS      = $(wildcard $(SRC_DIR)/*.cc)
OBJS      = $(SRCS:.cc=.o)

# Build target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

# Compile source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
