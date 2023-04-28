.PHONY: all clean

CXXFLAGS = -g -lcrypt -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -D_GLIBCXX_ASSERTIONS -std=c++17

OBJS = searcher ClockT.o

all: ${OBJS} 

ClockT.o: ClockT.h
searcher: ClockT.o

clean:
	rm -f ${OBJS}
