# --- Compiler and flags ---
CXX = g++
CXXFLAGS = -Wall

# --- Output binary ---
TARGET = bin/pixel_artillery

# --- Source files ---
SRCS = src/phys_graph2_terve.cpp \
	src/physics2.cpp \
	src/sound.cpp

# --- Libraries ---
LIBS = -lopengl32 -lglu32 -lfreeglut -lwinmm

# --- Build rule ---
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# --- Convenience rule ---
all: $(TARGET)

# --- Clean rule ---
clean:
	rm -f $(TARGET)
