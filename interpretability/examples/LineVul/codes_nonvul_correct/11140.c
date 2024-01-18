// commit message FFmpeg@c4e554701e (target=0, prob=0.48352373, correct=True):     * misc. fixes and hacks to improve timing detection in raw DV
/*0  */ DVDemuxContext* dv_init_demux(AVFormatContext *s)    // (8) 0.03711
/*2  */ {                                                    // (33) 0.001953
/*4  */     DVDemuxContext *c;                               // (17) 0.01953
/*8  */     c = av_mallocz(sizeof(DVDemuxContext));          // (9) 0.03711
/*10 */     if (!c)                                          // (25) 0.01367
/*12 */         return NULL;                                 // (18) 0.01953
/*16 */     c->vst = av_new_stream(s, 0);                    // (10) 0.03516
/*18 */     c->ast[0] = av_new_stream(s, 0);                 // (7) 0.03906
/*20 */     if (!c->vst || !c->ast[0])                       // (12) 0.0332
/*22 */         goto fail;                                   // (19) 0.01953
/*24 */     av_set_pts_info(c->vst, 64, 1, 30000);           // (4) 0.04688
/*26 */     av_set_pts_info(c->ast[0], 64, 1, 30000);        // (3) 0.04883
/*30 */     c->fctx = s;                                     // (20) 0.01953
/*32 */     c->ast[1] = NULL;                                // (16) 0.02344
/*34 */     c->ach = 0;                                      // (22) 0.01758
/*36 */     c->frames = 0;                                   // (23) 0.01758
/*38 */     c->abytes = 0;                                   // (24) 0.01758
/*40 */     c->audio_pkt[0].size = 0;                        // (13) 0.03125
/*42 */     c->audio_pkt[1].size = 0;                        // (14) 0.03125
/*44 */                                                      // (27) 0.007812
/*46 */     c->vst->codec.codec_type = CODEC_TYPE_VIDEO;     // (5) 0.04688
/*48 */     c->vst->codec.codec_id = CODEC_ID_DVVIDEO;       // (2) 0.05078
/*50 */     c->vst->codec.bit_rate = 25000000;               // (11) 0.03516
/*52 */                                                      // (28) 0.007812
/*54 */     c->ast[0]->codec.codec_type = CODEC_TYPE_AUDIO;  // (1) 0.05273
/*56 */     c->ast[0]->codec.codec_id = CODEC_ID_PCM_S16LE;  // (0) 0.06055
/*58 */                                                      // (31) 0.005859
/*60 */     s->ctx_flags |= AVFMTCTX_NOHEADER;               // (6) 0.04492
/*62 */                                                      // (29) 0.007812
/*64 */     return c;                                        // (26) 0.01172
/*66 */                                                      // (30) 0.007812
/*68 */ fail:                                                // (32) 0.003906
/*70 */     if (c->vst)                                      // (21) 0.01953
/*72 */         av_free(c->vst);                             // (15) 0.03125
/*74 */     if (c->ast[0])                                   // 0.0
/*76 */         av_free(c->ast[0]);                          // 0.0
/*78 */     av_free(c);                                      // 0.0
/*80 */     return NULL;                                     // 0.0
/*82 */ }                                                    // 0.0
