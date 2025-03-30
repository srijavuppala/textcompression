# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
SRCS = adsa_test.cpp
OBJS = $(SRCS:.cpp=.o)
# Target executable name
TARGET = dict


# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
