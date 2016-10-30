# Target app
TARGET = app

# Sources
SRCS = $(wildcard *.cpp)

# Associated Objects
OBJS = $(SRCS:%.cpp=%.o)

# Libs to load
LDLIBS =  -lglut -lGLU -lGL -lm 

# Use clang
CXX = clang++

# C++ Flags
CXXFLAGS = -std=c++14 -Wall -O2 

# Associate target app with its o file 
$(TARGET): $(OBJS)

# For linker to understand it's C++
LINK.o=$(LINK.cpp)

# Autodependencies
DEPS = $(patsubst %.cpp,%.d,$(SRCS))
-include $(DEPS)
%.d: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -MM -MF $@ -MP $<

# Cleanup
clean:
	rm -f  *~ *.gch  $(TARGET) $(OBJS) $(DEPS)

.PHONY: clean
