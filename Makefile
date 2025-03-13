# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./SQLAPI/include

# Detect OS and Architecture
UNAME_S := $(shell uname -s)
ARCH := $(shell uname -m)

# Set the correct linker flags based on OS and architecture
ifeq ($(UNAME_S), Linux)
    LDFLAGS = -L./SQLAPI/lib -Wl,-Bstatic -lsqlapi -Wl,-Bdynamic
else ifeq ($(UNAME_S), Darwin)
    ifeq ($(ARCH), x86_64)
        # Add PostgreSQL include and library paths for x86_64
        CXXFLAGS += -I/usr/local/opt/libpq/include
        LDFLAGS = -L./SQLAPI/lib/x86_64 -lsqlapi -Wl,-rpath,@loader_path/SQLAPI/lib/x86_64 -L/usr/local/opt/libpq/lib -lpq
    else ifeq ($(ARCH), arm64)
        # Add PostgreSQL include and library paths for arm64
        CXXFLAGS += -I/usr/local/opt/libpq/include
        LDFLAGS = -L./SQLAPI/lib/arm64 -lsqlapi -Wl,-rpath,@loader_path/SQLAPI/lib/arm64 -L/usr/local/opt/libpq/lib -lpq
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