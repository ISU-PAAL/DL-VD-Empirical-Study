// commit message FFmpeg@668494acd8 (target=1, prob=0.99904627, correct=True): ffmpeg: add image size check to codec_get_buffer()
/*0  */ static int codec_get_buffer(AVCodecContext *s, AVFrame *frame)                           // (9) 0.03906
/*1  */ {                                                                                        // (24) 0.001953
/*2  */     InputStream *ist = s->opaque;                                                        // (17) 0.02539
/*3  */     FrameBuffer *buf;                                                                    // (21) 0.01562
/*4  */     int ret, i;                                                                          // (22) 0.01562
/*5  */     if (!ist->buffer_pool && (ret = alloc_buffer(s, ist, &ist->buffer_pool)) < 0)        // (3) 0.06445
/*6  */         return ret;                                                                      // (19) 0.01953
/*7  */     buf              = ist->buffer_pool;                                                 // (7) 0.04883
/*8  */     ist->buffer_pool = buf->next;                                                        // (15) 0.02734
/*9  */     buf->next        = NULL;                                                             // (12) 0.03125
/*10 */     if (buf->w != s->width || buf->h != s->height || buf->pix_fmt != s->pix_fmt) {       // (0) 0.07422
/*11 */         av_freep(&buf->base[0]);                                                         // (10) 0.03516
/*12 */         av_free(buf);                                                                    // (18) 0.02539
/*13 */         ist->dr1 = 0;                                                                    // (13) 0.0293
/*14 */         if ((ret = alloc_buffer(s, ist, &buf)) < 0)                                      // (5) 0.05078
/*15 */             return ret;                                                                  // (14) 0.02734
/*16 */     }                                                                                    // (23) 0.007813
/*17 */     buf->refcount++;                                                                     // (20) 0.01563
/*18 */     frame->opaque        = buf;                                                          // (11) 0.0332
/*19 */     frame->type          = FF_BUFFER_TYPE_USER;                                          // (6) 0.04883
/*20 */     frame->extended_data = frame->data;                                                  // (16) 0.02734
/*21 */     frame->pkt_pts       = s->pkt ? s->pkt->pts : AV_NOPTS_VALUE;                        // (1) 0.07422
/*22 */     for (i = 0; i < FF_ARRAY_ELEMS(buf->data); i++) {                                    // (4) 0.05273
/*23 */         frame->base[i]     = buf->base[i];  // XXX h264.c uses base though it shouldn't  // (2) 0.07227
/*24 */         frame->data[i]     = buf->data[i];                                               // (8) 0.04687
/*25 */         frame->linesize[i] = buf->linesize[i];                                           // 0.0
/*26 */     }                                                                                    // 0.0
/*27 */     return 0;                                                                            // 0.0
/*28 */ }                                                                                        // 0.0
