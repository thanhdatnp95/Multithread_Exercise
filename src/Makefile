CC = g++
CFLAGS = -std=c++11 -Wall -g -pthread
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = IOCache

all:	$(TARGET)

$(TARGET):	$(OBJS)
	@echo "======================================="
	@echo "-- Linking --"
	@echo "======================================="
	$(CC) $(CFLAGS) -o $@ $^
	@echo "======================================="
	@echo -- Linking Complete --
	@echo "======================================="

%.o:	%.cpp
	@echo "======================================="
	@echo "-- Compiling $<--"
	@echo "======================================="
	$(CC) $(CFLAGS) -D DEBUG -c $< -o $@
	@echo "======================================="
	@echo "-- Compiling $< Complete --"
	@echo "======================================="

.PHONY:	clean
clean:
	@echo "======================================="
	@echo "-- Cleaning --"
	@echo "======================================="
	rm -rf *.o $(TARGET)
	@echo "======================================="
	@echo -- Cleaning Complete --
	@echo "======================================="

