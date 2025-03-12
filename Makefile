# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./SQLAPI/include

# Detect OS and Architecture
UNAME_S := $(shell uname -s)
ARCH := $(shell uname -m)

# Default library path
LIB_PATH = -L./SQLAPI/lib

# Set the correct linker flags based on OS and architecture
ifeq ($(UNAME_S), Linux)
    LDFLAGS = $(LIB_PATH) -Wl,-Bstatic -lsqlapi -Wl,-Bdynamic
else ifeq ($(UNAME_S), Darwin)
    ifeq ($(ARCH), x86_64)
        LDFLAGS = $(LIB_PATH) -lsqlapi_x86_64  -Wl,-rpath,@executable_path/SQLAPI/lib # Use x86_64 version
    else ifeq ($(ARCH), arm64)
        LDFLAGS = $(LIB_PATH) -lsqlapi_arm64  -Wl,-rpath,@executable_path/SQLAPI/lib # Use arm64 version
    endif
endif

# Source files
SRC = main.cpp  # Add all your .cpp files here
OBJ = $(SRC:.cpp=.o)
EXEC = main

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
