CPP=g++
CC=gcc
MV=mv

OBJS=libopencvjs.o
BIN=libopencvjs.so

CFLAGS+=-Wall -g -O3 -I../common
LDFLAGS+=-L/opt/vc/lib/ -lm -shared

INCLUDES+=-I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))

all: $(BIN)


%.o: %.c
	@rm -f $@
	$(CC) $(CFLAGS) $(INCLUDES) -L -g -c $< -o $@ -Wno-deprecated-declarations
libopencvjs
%.o: %.cpp
	@rm -f $@
	$(CPP) $(CFLAGS) $(INCLUDES) -L -g -c -o $@ $<

#Link everything

$(BIN): $(OBJS)
	$(CC) -o $@ -Wl,--whole-archive $(OBJS) $(LDFLAGS) -Wl,--no-whole-archive -rdynamic

clean:
	@rm -f $(OBJS)
	@rm -f $(BIN)

install:
	cp $(BIN) ..
	cp $(BIN) /usr/lib
