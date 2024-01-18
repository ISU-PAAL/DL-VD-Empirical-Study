// commit message FFmpeg@52a2138656 (target=0, prob=0.52934396, correct=False): avformat/avidec: Use a buffer with sufficient padding in read_gab2_sub()
/*0   */ static int read_gab2_sub(AVStream *st, AVPacket *pkt)                      // (8) 0.04297
/*2   */ {                                                                          // (20) 0.001953
/*4   */     if (pkt->size >= 7 &&                                                  // (18) 0.02344
/*6   */         !strcmp(pkt->data, "GAB2") && AV_RL16(pkt->data + 5) == 2) {       // (2) 0.07422
/*8   */         uint8_t desc[256];                                                 // (14) 0.0293
/*10  */         int score      = AVPROBE_SCORE_EXTENSION, ret;                     // (4) 0.05664
/*12  */         AVIStream *ast = st->priv_data;                                    // (12) 0.03711
/*14  */         AVInputFormat *sub_demuxer;                                        // (13) 0.0332
/*16  */         AVRational time_base;                                              // (15) 0.02734
/*18  */         AVIOContext *pb = avio_alloc_context(pkt->data + 7,                // (6) 0.05273
/*20  */                                              pkt->size - 7,                // (1) 0.09961
/*22  */                                              0, NULL, NULL, NULL, NULL);   // (0) 0.1055
/*24  */         AVProbeData pd;                                                    // (16) 0.02734
/*26  */         unsigned int desc_len = avio_rl32(pb);                             // (10) 0.04102
/*30  */         if (desc_len > pb->buf_end - pb->buf_ptr)                          // (7) 0.05273
/*32  */             goto error;                                                    // (17) 0.02734
/*36  */         ret = avio_get_str16le(pb, desc_len, desc, sizeof(desc));          // (3) 0.05859
/*38  */         avio_skip(pb, desc_len - ret);                                     // (11) 0.03906
/*40  */         if (*desc)                                                         // (19) 0.02148
/*42  */             av_dict_set(&st->metadata, "title", desc, 0);                  // (5) 0.05469
/*46  */         avio_rl16(pb);   /* flags? */                                      // (9) 0.04102
/*48  */         avio_rl32(pb);   /* data size */                                   // 0.0
/*52  */         pd = (AVProbeData) { .buf      = pb->buf_ptr,                      // 0.0
/*54  */                              .buf_size = pb->buf_end - pb->buf_ptr };      // 0.0
/*56  */         if (!(sub_demuxer = av_probe_input_format2(&pd, 1, &score)))       // 0.0
/*58  */             goto error;                                                    // 0.0
/*62  */         if (!(ast->sub_ctx = avformat_alloc_context()))                    // 0.0
/*64  */             goto error;                                                    // 0.0
/*68  */         ast->sub_ctx->pb = pb;                                             // 0.0
/*70  */         if (!avformat_open_input(&ast->sub_ctx, "", sub_demuxer, NULL)) {  // 0.0
/*72  */             ff_read_packet(ast->sub_ctx, &ast->sub_pkt);                   // 0.0
/*74  */             *st->codec = *ast->sub_ctx->streams[0]->codec;                 // 0.0
/*76  */             ast->sub_ctx->streams[0]->codec->extradata = NULL;             // 0.0
/*78  */             time_base = ast->sub_ctx->streams[0]->time_base;               // 0.0
/*80  */             avpriv_set_pts_info(st, 64, time_base.num, time_base.den);     // 0.0
/*82  */         }                                                                  // 0.0
/*84  */         ast->sub_buffer = pkt->data;                                       // 0.0
/*86  */         memset(pkt, 0, sizeof(*pkt));                                      // 0.0
/*88  */         return 1;                                                          // 0.0
/*92  */ error:                                                                     // 0.0
/*94  */         av_freep(&pb);                                                     // 0.0
/*96  */     }                                                                      // 0.0
/*98  */     return 0;                                                              // 0.0
/*100 */ }                                                                          // 0.0
