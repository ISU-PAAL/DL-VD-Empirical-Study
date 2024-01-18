// commit message FFmpeg@8eb76217d0 (target=1, prob=0.998973, correct=True): avcodec/interplayvideo: Check that enough data is available for opcode_0x7/8/D
/*0  */ static int ipvideo_decode_block_opcode_0xD(IpvideoContext *s, AVFrame *frame)  // (2) 0.1142
/*1  */ {                                                                              // (13) 0.003937
/*2  */     int y;                                                                     // (12) 0.02362
/*3  */     unsigned char P[2];                                                        // (9) 0.03543
/*4  */     /* 4-color block encoding: each 4x4 block is a different color */          // (5) 0.07874
/*5  */     for (y = 0; y < 8; y++) {                                                  // (7) 0.06299
/*6  */         if (!(y & 3)) {                                                        // (8) 0.05905
/*7  */             P[0] = bytestream2_get_byte(&s->stream_ptr);                       // (1) 0.122
/*8  */             P[1] = bytestream2_get_byte(&s->stream_ptr);                       // (0) 0.122
/*9  */         memset(s->pixel_ptr,     P[0], 4);                                     // (3) 0.1024
/*10 */         memset(s->pixel_ptr + 4, P[1], 4);                                     // (4) 0.09449
/*11 */         s->pixel_ptr += s->stride;                                             // (6) 0.07087
/*12 */     /* report success */                                                       // (10) 0.02756
/*13 */     return 0;                                                                  // (11) 0.02362
