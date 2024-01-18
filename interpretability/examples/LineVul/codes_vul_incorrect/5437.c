// commit message FFmpeg@e947b75b1c (target=1, prob=0.4930241, correct=False): libavformat/rtpdec_asf: zero initialize the AVIOContext struct
/*0   */ int ff_wms_parse_sdp_a_line(AVFormatContext *s, const char *p)                        // (2) 0.05078
/*2   */ {                                                                                     // (23) 0.001953
/*4   */     int ret = 0;                                                                      // (21) 0.01562
/*6   */     if (av_strstart(p, "pgmpu:data:application/vnd.ms.wms-hdr.asfv1;base64,", &p)) {  // (0) 0.08789
/*8   */         AVIOContext pb;                                                               // (19) 0.02539
/*10  */         RTSPState *rt = s->priv_data;                                                 // (12) 0.03711
/*12  */         AVDictionary *opts = NULL;                                                    // (17) 0.03125
/*14  */         int len = strlen(p) * 6 / 8;                                                  // (10) 0.03906
/*16  */         char *buf = av_mallocz(len);                                                  // (14) 0.03711
/*18  */         AVInputFormat *iformat;                                                       // (18) 0.02734
/*22  */         if (!buf)                                                                     // (20) 0.02148
/*24  */             return AVERROR(ENOMEM);                                                   // (11) 0.03906
/*26  */         av_base64_decode(buf, p, len);                                                // (9) 0.04102
/*30  */         if (rtp_asf_fix_header(buf, len) < 0)                                         // (3) 0.05078
/*32  */             av_log(s, AV_LOG_ERROR,                                                   // (7) 0.04492
/*34  */                    "Failed to fix invalid RTSP-MS/ASF min_pktsize\n");                // (1) 0.07812
/*36  */         init_packetizer(&pb, buf, len);                                               // (13) 0.03711
/*38  */         if (rt->asf_ctx) {                                                            // (16) 0.0332
/*40  */             avformat_close_input(&rt->asf_ctx);                                       // (6) 0.04883
/*42  */         }                                                                             // (22) 0.01562
/*46  */         if (!(iformat = av_find_input_format("asf")))                                 // (5) 0.04883
/*48  */             return AVERROR_DEMUXER_NOT_FOUND;                                         // (4) 0.04883
/*52  */         rt->asf_ctx = avformat_alloc_context();                                       // (8) 0.04297
/*54  */         if (!rt->asf_ctx) {                                                           // (15) 0.0332
/*56  */             av_free(buf);                                                             // 0.0
/*58  */             return AVERROR(ENOMEM);                                                   // 0.0
/*60  */         }                                                                             // 0.0
/*62  */         rt->asf_ctx->pb      = &pb;                                                   // 0.0
/*64  */         av_dict_set(&opts, "no_resync_search", "1", 0);                               // 0.0
/*68  */         if ((ret = ff_copy_whiteblacklists(rt->asf_ctx, s)) < 0) {                    // 0.0
/*70  */             av_dict_free(&opts);                                                      // 0.0
/*72  */             return ret;                                                               // 0.0
/*74  */         }                                                                             // 0.0
/*78  */         ret = avformat_open_input(&rt->asf_ctx, "", iformat, &opts);                  // 0.0
/*80  */         av_dict_free(&opts);                                                          // 0.0
/*82  */         if (ret < 0) {                                                                // 0.0
/*84  */             av_free(buf);                                                             // 0.0
/*86  */             return ret;                                                               // 0.0
/*88  */         }                                                                             // 0.0
/*90  */         av_dict_copy(&s->metadata, rt->asf_ctx->metadata, 0);                         // 0.0
/*92  */         rt->asf_pb_pos = avio_tell(&pb);                                              // 0.0
/*94  */         av_free(buf);                                                                 // 0.0
/*96  */         rt->asf_ctx->pb = NULL;                                                       // 0.0
/*98  */     }                                                                                 // 0.0
/*100 */     return ret;                                                                       // 0.0
/*102 */ }                                                                                     // 0.0
