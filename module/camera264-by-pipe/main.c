#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *pipeName = "./output.pipe";

void read_pipe() {
  FILE *piper = fopen(pipeName, "rb");
  if (piper == NULL) {
    printf("fopen %s error\n", pipeName);
    return;
  }
  unsigned char buff[1024];
  while (1) {
    int size = fread(&buff, 1, 1024, piper);
    if (size <= 0) {
      break;
    }
    printf("read size %d\n", size);
  }
}

void write_pipe() {
  char *cmd = "../../ffmpeg/bin/ffmpeg -hide_banner -loglevel panic -i "
              "/dev/video0 -f h264 pipe:1 > output.pipe";
  int ret = system(cmd);
  if (ret < 0) {
    printf("system error, ret:%d\n", ret);
    return;
  }
}

void main() {
  int ret = -1;
  ret = access(pipeName, F_OK);
  if (ret != 0) {
    ret = mkfifo(pipeName, 0644);
    if (ret < 0) {
      printf("mkfifo error, ret:%d\n", ret);
      return;
    }
  }
  pthread_t tids[2];
  // start thread read
  pthread_create(&tids[0], NULL, read_pipe, NULL);
  // start thread write
  pthread_create(&tids[1], NULL, write_pipe, NULL);
  pthread_exit(NULL);
  return;
}
