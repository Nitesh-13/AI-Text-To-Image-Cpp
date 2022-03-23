# Makefile for a C++ project with libcurl

# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++11 #-I./extra
LIBS = -lcurl

# Source code directory, output directory, and target executable name
SRCDIR = src
OUTDIR = bin
TARGET = main

# List of source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# List of object files (one for each source file)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OUTDIR)/%.o)

# Default target (the target to build when you run 'make' without arguments)
all: $(OUTDIR) $(OUTDIR)/$(TARGET)

# Rule to create the output directory
$(OUTDIR):
	mkdir -p $(OUTDIR)

# Rule to compile a source file into an object file
$(OUTDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build the target executable by linking object files
$(OUTDIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Clean rule to remove object files and the target executable
clean:
	rm -f $(OUTDIR)/*.o $(OUTDIR)/$(TARGET)

# Run rule to execute the target program
run:
	./$(OUTDIR)/$(TARGET)
