# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -I./SQLAPI/include

# Detect OS and Architecture
UNAME_S := $(shell uname -s)
ARCH := $(shell uname -m)

# Set the correct linker flags based on OS and architecture
ifeq ($(UNAME_S), Linux)
    LDFLAGS = -L./SQLAPI/lib -Wl,-Bstatic -lsqlapi -Wl,-Bdynamic
    POST_BUILD = echo "No post-build steps required for Linux"
else ifeq ($(UNAME_S), Darwin)
    ifeq ($(ARCH), x86_64)
        CXXFLAGS += -I/usr/local/opt/libpq/include
        LDFLAGS = -L./SQLAPI/lib/x86_64 -lsqlapi -Wl,-rpath,@loader_path/SQLAPI/lib/x86_64 -L/usr/local/opt/libpq/lib -lpq
    else ifeq ($(ARCH), arm64)
        CXXFLAGS += -I/usr/local/opt/libpq/include
        LDFLAGS = -L./SQLAPI/lib/arm64 -lsqlapi -Wl,-rpath,@loader_path/SQLAPI/lib/arm64 -L/usr/local/opt/libpq/lib -lpq
    endif
    POST_BUILD = install_name_tool -id '@rpath/libsqlapi.dylib' $(CURDIR)/SQLAPI/lib/$(ARCH)/libsqlapi.dylib && \
                 codesign -s - -f -o linker-signed $(CURDIR)/SQLAPI/lib/$(ARCH)/libsqlapi.dylib
endif

# Automatically find all .cpp files in the directory
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = main

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)
	$(POST_BUILD)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
