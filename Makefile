TARGET = chess_game
CXX = g++
PKG = sdl2 SDL2_image

CXXFLAGS = -std=c++17 -Wall -Wextra -g $(shell pkg-config --cflags $(PKG)) -I. -Iinclude
LDFLAGS = $(shell pkg-config --libs $(PKG))

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:.cc=.o)
DEPS = $(SRCS:.cc=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

# Compile source files and generate dependency files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files if they exist
-include $(DEPS)

clean: $(TARGET)
	rm -f $(OBJS) $(DEPS)