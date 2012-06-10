
CXX = g++
CXXFLAGS = -c -Wall -g
INCLUDE = -I include/glm-0.9.3.0 -I include/gli-0.3.1.0 -I include/
LDFLAGS = -lGL -lGLEW -lglut

HEADER =  include/glf.hpp \
	  include/main.hpp

SOURCES = src/glf.cpp \
	  src/main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = shadowVolume

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@
# oder %.o : %.cpp

clean:
	rm src/*.o
