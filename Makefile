CXX = g++
CXXFLAGS = -fPIC -shared -std=c++11
LDFLAGS = -ldl
TARGET = main
LIBS = librk4.so libadams_bashforth.so

SRCS = adams_bashforth.cpp rk4.cpp main.cpp

all: $(LIBS) $(TARGET)

librk4.so: rk4.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

libadams_bashforth.so: adams_bashforth.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

$(TARGET): main.cpp $(LIBS)
	$(CXX) -o $@ $< -L. -lrk4 -ladams_bashforth $(LDFLAGS)

clean:
	rm -f $(TARGET) $(LIBS)

run: $(TARGET)
	LD_LIBRARY_PATH=. ./$(TARGET)
