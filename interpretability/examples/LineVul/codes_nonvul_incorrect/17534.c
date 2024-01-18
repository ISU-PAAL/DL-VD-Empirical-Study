// commit message FFmpeg@b6db385922 (target=0, prob=0.711385, correct=False): v4l2: use C99 struct initializer
/*0  */ static void mmap_release_buffer(AVPacket *pkt)                  // (7) 0.05031
/*2  */ {                                                               // (18) 0.003145
/*4  */     struct v4l2_buffer buf;                                     // (12) 0.03774
/*6  */     int res, fd;                                                // (15) 0.0283
/*8  */     struct buff_data *buf_descriptor = pkt->priv;               // (5) 0.05975
/*12 */     if (pkt->data == NULL)                                      // (11) 0.03774
/*14 */         return;                                                 // (16) 0.0283
/*18 */     memset(&buf, 0, sizeof(struct v4l2_buffer));                // (4) 0.06289
/*20 */     buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;                     // (1) 0.07233
/*22 */     buf.memory = V4L2_MEMORY_MMAP;                              // (6) 0.05975
/*24 */     buf.index = buf_descriptor->index;                          // (8) 0.04717
/*26 */     fd = buf_descriptor->fd;                                    // (9) 0.04403
/*28 */     av_free(buf_descriptor);                                    // (10) 0.04088
/*32 */     res = ioctl(fd, VIDIOC_QBUF, &buf);                         // (2) 0.06604
/*34 */     if (res < 0)                                                // (17) 0.0283
/*36 */         av_log(NULL, AV_LOG_ERROR, "ioctl(VIDIOC_QBUF): %s\n",  // (0) 0.1132
/*38 */                strerror(errno));                                // (3) 0.06604
/*42 */     pkt->data = NULL;                                           // (13) 0.03145
/*44 */     pkt->size = 0;                                              // (14) 0.03145
/*46 */ }                                                               // (19) 0.003145
