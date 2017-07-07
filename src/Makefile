PROGRAMS = sat2isingModel
OBJS = sat2isingModel.o io.o reduction.o

CXX = g++
CXXFLAGS = -Wall -O3

.SUFFIXES: .cpp .o

all: $(PROGRAMS)

$(PROGRAMS): $(OBJS)
	$(CXX) -o $@ $^
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) $(PROGRAMS) *.o
