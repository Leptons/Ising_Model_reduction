PROGRAMS = sat_isingModel sat_isingModel2 maxsat_isingModel indset_isingModel
OBJS = io.o reduction.o


CXX = g++ -std=gnu++11
CXXFLAGS = -O3

.SUFFIXES: .cpp .o

all: $(PROGRAMS)

$(PROGRAMS): %: $(OBJS) %.o
	$(CXX) -o $@ $^ 
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	$(RM) $(PROGRAMS) *.o *.exe
