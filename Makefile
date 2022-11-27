CXX=g++
CXX_OPT=-march=native -O2 -std=c++23
SRCS=newton.cpp main.cpp
OBJS=$(SRCS:.cpp=.o)
HEADERS=newton.hpp bitmap_image.hpp
TARGET=newton.out

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $(CXX_OPT) $(OBJS) -o $@

$(OBJS): $(HEADERS) $(SRCS)

.cpp.o:
	g++ $(CXX_OPT) -c $< -o $@

clean:
	rm *.o $(TARGET)
