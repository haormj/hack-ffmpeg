#include "libavdevice/avdevice.h"

void main() {
  avdevice_register_all();

  AVFormatContext *avf;
  avf = avformat_alloc_context();
  int ret;
  if (ret = avformat_open_input(&avf, "/dev/video0", NULL, NULL) < 0) {
    printf("Impossible to open /dev/video0\n");
    avformat_close_input(&avf);
    return;
  }
  if (ret = avformat_find_stream_info(avf, NULL) < 0) {
    printf("Impossible to open /dev/video0\n");
    avformat_close_input(avf);
    return;
  }

  AVPacket pkt;
  if (ret = av_read_frame(avf, &pkt) < 0) {
    printf("av_read_frame error\n");
    return;
  }

  AVStream *stream = avf->streams[0];
  AVCodecContext *codecCtx = stream->codec;
  AVCodec *codec = avcodec_find_decoder(codecCtx->codec_id);
  if (codec == NULL) {
    printf("codec not found\n");
    return;
  }
  printf("AV_CODEC_ID_NONE:%d, AV_CODEC_ID_RAWVIDEO: %d, codecID: %d\n",
         AV_CODEC_ID_NONE, AV_CODEC_ID_RAWVIDEO, codecCtx->codec_id);
  printf("av_codec_name: %s, long_name: %s, fmt:%d\n", codec->name,
         codec->long_name, codecCtx->pix_fmt);
  if (avcodec_open2(codecCtx, codec, NULL) < 0) {
    printf("Could not open codec\n");
    return;
  }

  AVFrame *decode_frame;
  decode_frame = av_frame_alloc();

  ret = avcodec_send_packet(codecCtx, &pkt);
  if (ret < 0) {
    printf("avcodec_send_packet error\n");
    return;
  }
  ret = avcodec_receive_frame(codecCtx, decode_frame);
  if (ret < 0) {
    printf("avcodec_receive_frame error\n");
    return;
  }

  printf("AV_PIX_FMT_NONE: %d, AV_PIX_FMT_YUYV422: %d, fmt: %d, width: %d, "
         "height:%d\n",
         AV_PIX_FMT_NONE, AV_PIX_FMT_YUYV422, decode_frame->format,
         decode_frame->width, decode_frame->height);
  avformat_close_input(&avf);
}
