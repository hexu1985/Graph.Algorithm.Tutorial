
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -std=c++17
INCLUDES = -I../../../src
LDFLAGS =
LDPATH =

SOURCES = $(shell ls *.cpp)
PROGS = $(SOURCES:%.cpp=%)

all: $(PROGS)
	@echo "PROGS = $(PROGS)" 

clean:
	$(RM) $(PROGS) *.dot *.png

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDPATH)
