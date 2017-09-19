CC = g++
CFLAGS = -Wall -g -pthread
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = IOCache

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:	clean
clean:
	rm -rf *.o $(TARGET)

