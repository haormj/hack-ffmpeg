# variable
CC         = gcc
CFLAGS     =
LDFLAGS    = -lpthread
SRC        = ./main.c
BINARYNAME = camera264-by-pipe

all: build

fmt:
	clang-format -i *.c

build:
	${CC} ${CFLAGS} -o ${BINARYNAME} ${SRC} ${LDFLAGS}

clean:
	rm -rf *.o *~
	rm -rf ${BINARYNAME}
