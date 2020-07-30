# variable
CC         = gcc
CFLAGS     = -I../../ffmpeg/include
LDFLAGS    = -L../../ffmpeg/lib \
             -L../../x264/lib \
					   -lavdevice -lm -lxcb -lxcb-shm -lxcb-shape -lxcb-xfixes \
             -lavfilter -pthread -lm -lswscale -lm -lpostproc -lm \
             -lavformat -lm -lz -lavcodec -pthread -lm -llzma -lz \
             -lx264 -pthread -lm -lswresample -lm -lavutil -pthread -lm \
						 -ldl
SRC        = ./main.c
BINARYNAME = camera264

all: build

fmt:
	clang-format -i *.c

build:
	${CC} ${CFLAGS} -o ${BINARYNAME} ${SRC} ${LDFLAGS}

clean:
	rm -rf *.o *~
	rm -rf ${BINARYNAME}
