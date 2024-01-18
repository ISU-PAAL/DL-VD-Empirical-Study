// commit message FFmpeg@028cc42a16 (target=1, prob=0.5689971, correct=True): read_gab2_sub: fix null pointer dereference
/*0  */ static int read_gab2_sub(AVStream *st, AVPacket *pkt) {                                    // (8) 0.04492
/*2  */     if (!strcmp(pkt->data, "GAB2") && AV_RL16(pkt->data+5) == 2) {                         // (2) 0.06836
/*4  */         uint8_t desc[256];                                                                 // (15) 0.0293
/*6  */         int score = AVPROBE_SCORE_MAX / 2, ret;                                            // (7) 0.04687
/*8  */         AVIStream *ast = st->priv_data;                                                    // (13) 0.03711
/*10 */         AVInputFormat *sub_demuxer;                                                        // (14) 0.0332
/*12 */         AVRational time_base;                                                              // (17) 0.02734
/*14 */         AVIOContext *pb = avio_alloc_context( pkt->data + 7,                               // (6) 0.05273
/*16 */                                               pkt->size - 7,                               // (1) 0.1016
/*18 */                                               0, NULL, NULL, NULL, NULL);                  // (0) 0.1074
/*20 */         AVProbeData pd;                                                                    // (18) 0.02734
/*22 */         unsigned int desc_len = avio_rl32(pb);                                             // (10) 0.04102
/*26 */         if (desc_len > pb->buf_end - pb->buf_ptr)                                          // (5) 0.05273
/*28 */             goto error;                                                                    // (16) 0.02734
/*32 */         ret = avio_get_str16le(pb, desc_len, desc, sizeof(desc));                          // (3) 0.05859
/*34 */         avio_skip(pb, desc_len - ret);                                                     // (12) 0.03906
/*36 */         if (*desc)                                                                         // (19) 0.02148
/*38 */             av_dict_set(&st->metadata, "title", desc, 0);                                  // (4) 0.05469
/*42 */         avio_rl16(pb);   /* flags? */                                                      // (9) 0.04102
/*44 */         avio_rl32(pb);   /* data size */                                                   // (11) 0.04102
/*48 */         pd = (AVProbeData) { .buf = pb->buf_ptr, .buf_size = pb->buf_end - pb->buf_ptr };  // 0.0
/*50 */         if (!(sub_demuxer = av_probe_input_format2(&pd, 1, &score)))                       // 0.0
/*52 */             goto error;                                                                    // 0.0
/*56 */         if (!(ast->sub_ctx = avformat_alloc_context()))                                    // 0.0
/*58 */             goto error;                                                                    // 0.0
/*62 */         ast->sub_ctx->pb      = pb;                                                        // 0.0
/*64 */         if (!avformat_open_input(&ast->sub_ctx, "", sub_demuxer, NULL)) {                  // 0.0
/*66 */             ff_read_packet(ast->sub_ctx, &ast->sub_pkt);                                   // 0.0
/*68 */             *st->codec = *ast->sub_ctx->streams[0]->codec;                                 // 0.0
/*70 */             ast->sub_ctx->streams[0]->codec->extradata = NULL;                             // 0.0
/*72 */             time_base = ast->sub_ctx->streams[0]->time_base;                               // 0.0
/*74 */             avpriv_set_pts_info(st, 64, time_base.num, time_base.den);                     // 0.0
/*76 */         }                                                                                  // 0.0
/*78 */         ast->sub_buffer = pkt->data;                                                       // 0.0
/*80 */         memset(pkt, 0, sizeof(*pkt));                                                      // 0.0
/*82 */         return 1;                                                                          // 0.0
/*84 */ error:                                                                                     // 0.0
/*86 */         av_freep(&pb);                                                                     // 0.0
/*88 */     }                                                                                      // 0.0
/*90 */     return 0;                                                                              // 0.0
/*92 */ }                                                                                          // 0.0
