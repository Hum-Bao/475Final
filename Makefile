# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./SQLAPI/include

# Detect OS
UNAME_S := $(shell uname -s)

# OS-specific linker flags
ifeq ($(UNAME_S), Linux)
    LDFLAGS = -L./SQLAPI/lib -Wl,-Bstatic -lsqlapi -Wl,-Bdynamic
else ifeq ($(UNAME_S), Darwin)
    LDFLAGS = -L./SQLAPI/lib -lsqlapi
endif

# Source files
SRC = main.cpp  # Add all your .cpp files
OBJ = $(SRC:.cpp=.o)
EXEC = main

# Default target
all: $(EXEC)

# Linking with static library
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
