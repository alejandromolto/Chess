CXX := g++
PKGCONFIG := $(shell command -v pkg-config 2>/dev/null)

SDL_CFLAGS := $(shell $(PKGCONFIG) --cflags sdl2 SDL2_image 2>/dev/null || echo -I/usr/include/SDL2)
SDL_LIBS   := $(shell $(PKGCONFIG) --libs   sdl2 SDL2_image 2>/dev/null || echo -lSDL2 -lSDL2_image)

INCLUDE_DIRS := $(shell find src -type d)
INCLUDES := $(addprefix -I,$(INCLUDE_DIRS))

CXXFLAGS := -std=c++17 -Wall -Wextra -MMD -MP $(INCLUDES) $(SDL_CFLAGS)
LDFLAGS  := $(SDL_LIBS)

SRCS := $(shell find src -name '*.cc')
OBJS := $(SRCS:.cc=.o)
DEPS := $(OBJS:.o=.d)

TARGET := bin/chess_game

.PHONY: all clean run debug
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

run: $(TARGET)
	./$(TARGET)  # ejecutar desde la raíz del proyecto

debug: CXXFLAGS += -g -O0
debug: clean all

clean:
	rm -f $(OBJS) $(DEPS)