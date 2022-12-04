CXX=g++
CXX_OPT=-march=native -O2 -std=c++17
SRCS=newton.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
HEADERS=newton.hpp bitmap_image.hpp
TARGET=newton.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXX_OPT) $(OBJS) -o $@

$(OBJS): $(HEADERS)

.cpp.o:
	$(CXX) $(CXX_OPT) -c $< -o $@

clean:
	rm *.o $(TARGET)
