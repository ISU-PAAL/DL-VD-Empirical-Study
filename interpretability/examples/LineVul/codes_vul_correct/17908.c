// commit message FFmpeg@4641ae352e (target=1, prob=0.5777356, correct=True): avformat: Add and use ff_copy_whitelists()
/*0   */ static int read_gab2_sub(AVFormatContext *s, AVStream *st, AVPacket *pkt)               // (5) 0.05469
/*2   */ {                                                                                       // (20) 0.001953
/*4   */     if (pkt->size >= 7 &&                                                               // (17) 0.02344
/*6   */         pkt->size < INT_MAX - AVPROBE_PADDING_SIZE &&                                   // (7) 0.05273
/*8   */         !strcmp(pkt->data, "GAB2") && AV_RL16(pkt->data + 5) == 2) {                    // (2) 0.07422
/*10  */         uint8_t desc[256];                                                              // (13) 0.0293
/*12  */         int score      = AVPROBE_SCORE_EXTENSION, ret;                                  // (4) 0.05664
/*14  */         AVIStream *ast = st->priv_data;                                                 // (11) 0.03711
/*16  */         AVInputFormat *sub_demuxer;                                                     // (12) 0.0332
/*18  */         AVRational time_base;                                                           // (16) 0.02734
/*20  */         int size;                                                                       // (19) 0.01953
/*22  */         AVIOContext *pb = avio_alloc_context(pkt->data + 7,                             // (8) 0.05273
/*24  */                                              pkt->size - 7,                             // (1) 0.09961
/*26  */                                              0, NULL, NULL, NULL, NULL);                // (0) 0.1055
/*28  */         AVProbeData pd;                                                                 // (14) 0.02734
/*30  */         unsigned int desc_len = avio_rl32(pb);                                          // (9) 0.04102
/*34  */         if (desc_len > pb->buf_end - pb->buf_ptr)                                       // (6) 0.05273
/*36  */             goto error;                                                                 // (15) 0.02734
/*40  */         ret = avio_get_str16le(pb, desc_len, desc, sizeof(desc));                       // (3) 0.05859
/*42  */         avio_skip(pb, desc_len - ret);                                                  // (10) 0.03906
/*44  */         if (*desc)                                                                      // (18) 0.02148
/*46  */             av_dict_set(&st->metadata, "title", desc, 0);                               // 0.0
/*50  */         avio_rl16(pb);   /* flags? */                                                   // 0.0
/*52  */         avio_rl32(pb);   /* data size */                                                // 0.0
/*56  */         size = pb->buf_end - pb->buf_ptr;                                               // 0.0
/*58  */         pd = (AVProbeData) { .buf      = av_mallocz(size + AVPROBE_PADDING_SIZE),       // 0.0
/*60  */                              .buf_size = size };                                        // 0.0
/*62  */         if (!pd.buf)                                                                    // 0.0
/*64  */             goto error;                                                                 // 0.0
/*66  */         memcpy(pd.buf, pb->buf_ptr, size);                                              // 0.0
/*68  */         sub_demuxer = av_probe_input_format2(&pd, 1, &score);                           // 0.0
/*70  */         av_freep(&pd.buf);                                                              // 0.0
/*72  */         if (!sub_demuxer)                                                               // 0.0
/*74  */             goto error;                                                                 // 0.0
/*78  */         if (!(ast->sub_ctx = avformat_alloc_context()))                                 // 0.0
/*80  */             goto error;                                                                 // 0.0
/*84  */         ast->sub_ctx->pb = pb;                                                          // 0.0
/*88  */         av_assert0(!ast->sub_ctx->codec_whitelist && !ast->sub_ctx->format_whitelist);  // 0.0
/*90  */         ast->sub_ctx-> codec_whitelist = av_strdup(s->codec_whitelist);                 // 0.0
/*92  */         ast->sub_ctx->format_whitelist = av_strdup(s->format_whitelist);                // 0.0
/*96  */         if (!avformat_open_input(&ast->sub_ctx, "", sub_demuxer, NULL)) {               // 0.0
/*98  */             ff_read_packet(ast->sub_ctx, &ast->sub_pkt);                                // 0.0
/*100 */             *st->codec = *ast->sub_ctx->streams[0]->codec;                              // 0.0
/*102 */             ast->sub_ctx->streams[0]->codec->extradata = NULL;                          // 0.0
/*104 */             time_base = ast->sub_ctx->streams[0]->time_base;                            // 0.0
/*106 */             avpriv_set_pts_info(st, 64, time_base.num, time_base.den);                  // 0.0
/*108 */         }                                                                               // 0.0
/*110 */         ast->sub_buffer = pkt->data;                                                    // 0.0
/*112 */         memset(pkt, 0, sizeof(*pkt));                                                   // 0.0
/*114 */         return 1;                                                                       // 0.0
/*118 */ error:                                                                                  // 0.0
/*120 */         av_freep(&pb);                                                                  // 0.0
/*122 */     }                                                                                   // 0.0
/*124 */     return 0;                                                                           // 0.0
/*126 */ }                                                                                       // 0.0
