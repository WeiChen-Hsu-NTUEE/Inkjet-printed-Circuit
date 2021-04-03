# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: ./bin/conflict_graph
	@echo -n ""

# optimized version
./bin/conflict_graph: main.o function.o lib
			$(CC) $(OPTFLAGS) main.o function.o -ltm_usage -Llib -o bin/conflict_graph
main.o: src/main.cpp lib/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@
function.o: src/function.cpp src/function.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*
