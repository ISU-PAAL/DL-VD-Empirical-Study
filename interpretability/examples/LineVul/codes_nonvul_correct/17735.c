// commit message FFmpeg@1eb57e1d9b (target=0, prob=0.18631308, correct=True): lavc: eliminate tb_unreliable()
/*0  */ static int tb_unreliable(AVCodecContext *c)             // (6) 0.07921
/*2  */ {                                                       // (9) 0.00495
/*4  */     if (c->time_base.den >= 101L * c->time_base.num ||  // (5) 0.1188
/*6  */         c->time_base.den <    5L * c->time_base.num ||  // (0) 0.1436
/*8  */         // c->codec_tag == AV_RL32("DIVX") ||           // (3) 0.1188
/*10 */         // c->codec_tag == AV_RL32("XVID") ||           // (4) 0.1188
/*12 */         c->codec_id == AV_CODEC_ID_MPEG2VIDEO ||        // (1) 0.1337
/*14 */         c->codec_id == AV_CODEC_ID_H264)                // (2) 0.1238
/*16 */         return 1;                                       // (7) 0.0495
/*18 */     return 0;                                           // (8) 0.0297
/*20 */ }                                                       // (10) 0.00495
