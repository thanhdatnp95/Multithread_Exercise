CC = g++
CFLAGS = -std=c++11 -Wall -g -pthread --coverage
INC = -I../ 
GTESTFLAGS = -lgtest_main -lgtest -pthread -lpthread -L/usr/local/lib
SRCS = $(wildcard *.cpp)
DEP = MessageQueue.o Producer.o Consumer.o
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = FunctionalTest

all:	run lcov

run:	$(TARGET)	
	./$(TARGET)

$(TARGET):	$(OBJS) $(DEP)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(GTESTFLAGS)

%.o:	%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@ $(GTESTFLAGS)

$(DEP):	../MessageQueue.cpp ../Producer.cpp ../Consumer.cpp
	$(CC) $(CFLAGS) $(INC) -c $^ $(GTESTFLAGS)

lcov:
	lcov --capture --directory ./ --output-file Report.info
	lcov --remove Report.info '/usr/include/c++/*' '/usr/include/c++/5/*' '/usr/local/include/*' '/usr/local/include/gtest/*' -o Report.info
	genhtml Report.info --output-directory HTMLReport

.PHONY:	clean
clean:
	rm -rf *.o $(TARGET)
	rm -rf HTMLReport
	rm -rf *.gcno *.gcda *.info
