## hack ffmpeg

### os

1. uname -a
  ```
  Linux pc 4.15.0-88-generic #88-Ubuntu SMP Tue Feb 11 20:11:34 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
  ```
2. gcc --version
  ```
  gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
  Copyright (C) 2017 Free Software Foundation, Inc.
  This is free software; see the source for copying conditions.  There is NO
  warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  ```
### x264

1. x264
  ```
  x264 0.160.x
  built on Jul 30 2020, gcc: 7.4.0
  x264 configuration: --chroma-format=all
  libx264 configuration: --chroma-format=all
  x264 license: GPL version 2 or later
  ```
2. configure
  ```
  ./configure --disable-asm --enable-static --prefix=~/Project/github.com/haormj/hack-ffmpeg/x264
  ```
3. make & make install
  ```
  make -j4
  make install
  ```
4. tree
  ```
  ├── bin
  │   └── x264
  ├── include
  │   ├── x264_config.h
  │   └── x264.h
  └── lib
     ├── libx264.a
     └── pkgconfig
         └── x264.pc
  ```

### ffmpeg

1. ffmpeg 4.3.1
2. configure
  ```
  ./configure --disable-x86asm --enable-libx264 --enable-gpl --extra-cflags="-I/home/haormj/Project/github.com/haormj/hack-ffmpeg/x264/include" --extra-libs="-L/home/haormj/Project/github.com/haormj/hack-ffmpeg/x264/lib -lx264 -lpthread -lm -ldl" --prefix=/home/haormj/Project/github.com/haormj/hack-ffmpeg/ffmpeg
  ```
3. make & make install
  ```
  make -j4
  make install
  ```
4. tree
  ```
  ├── bin
  │   ├── ffmpeg
  │   └── ffprobe
  ├── include
  │   ├── libavcodec
  │   ├── libavdevice
  │   ├── libavfilter
  │   ├── libavformat
  │   ├── libavutil
  │   ├── libpostproc
  │   ├── libswresample
  │   └── libswscale
  ├── lib
  │   ├── libavcodec.a
  │   ├── libavdevice.a
  │   ├── libavfilter.a
  │   ├── libavformat.a
  │   ├── libavutil.a
  │   ├── libpostproc.a
  │   ├── libswresample.a
  │   ├── libswscale.a
  │   └── pkgconfig
  └── share
      ├── ffmpeg
      └── man
  ```

### module

1. camera264
    - 调用ffmpeg库获取摄像头视频并转化为h264编码
    - 经过我最近的尝试，获取到流最后格式为yuyv422，不能直接编码为264
    - 需要将yuyv422转为yuv420p,但是我目前不知道如何进行（试过好久没搞定，后续有时间尝试）
2. camera-by-pipe
    - 因为ffmpeg命令封装的很成熟，从而直接通过调用这个命令进行
    - 对于其他进程需要数据的，这边可以直接通过管道进行通信
