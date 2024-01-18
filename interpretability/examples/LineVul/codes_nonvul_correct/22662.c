// commit message FFmpeg@67400f6b62 (target=0, prob=0.39395586, correct=True): mov: Prevent segfaults on mov_write_hdlr_tag
/*0  */ static int mov_write_hdlr_tag(AVIOContext *pb, MOVTrack *track)            // (7) 0.04297
/*2  */ {                                                                          // (20) 0.001953
/*4  */     const char *hdlr, *descr = NULL, *hdlr_type = NULL;                    // (6) 0.04492
/*6  */     int64_t pos = avio_tell(pb);                                           // (16) 0.03125
/*10 */     if (!track) { /* no media --> data handler */                          // (17) 0.0293
/*12 */         hdlr      = "dhlr";                                                // (12) 0.03906
/*14 */         hdlr_type = "url ";                                                // (15) 0.0332
/*16 */         descr     = "DataHandler";                                         // (14) 0.03516
/*18 */     } else {                                                               // (19) 0.01172
/*20 */         hdlr = (track->mode == MODE_MOV) ? "mhlr" : "\0\0\0\0";            // (2) 0.07422
/*22 */         if (track->enc->codec_type == AVMEDIA_TYPE_VIDEO) {                // (5) 0.05273
/*24 */             hdlr_type = "vide";                                            // (11) 0.04102
/*26 */             descr     = "VideoHandler";                                    // (9) 0.04297
/*28 */         } else if (track->enc->codec_type == AVMEDIA_TYPE_AUDIO) {         // (4) 0.05859
/*30 */             hdlr_type = "soun";                                            // (10) 0.04102
/*32 */             descr     = "SoundHandler";                                    // (8) 0.04297
/*34 */         } else if (track->enc->codec_type == AVMEDIA_TYPE_SUBTITLE) {      // (3) 0.0625
/*36 */             if (track->tag == MKTAG('t','x','3','g')) hdlr_type = "sbtl";  // (1) 0.07812
/*38 */             else                                      hdlr_type = "text";  // (0) 0.1133
/*40 */             descr = "SubtitleHandler";                                     // (13) 0.03711
/*42 */         } else if (track->enc->codec_tag == MKTAG('r','t','p',' ')) {      // 0.0
/*44 */             hdlr_type = "hint";                                            // 0.0
/*46 */             descr     = "HintHandler";                                     // 0.0
/*48 */         }                                                                  // (18) 0.01562
/*50 */     }                                                                      // 0.0
/*54 */     avio_wb32(pb, 0); /* size */                                           // 0.0
/*56 */     ffio_wfourcc(pb, "hdlr");                                              // 0.0
/*58 */     avio_wb32(pb, 0); /* Version & flags */                                // 0.0
/*60 */     avio_write(pb, hdlr, 4); /* handler */                                 // 0.0
/*62 */     ffio_wfourcc(pb, hdlr_type); /* handler type */                        // 0.0
/*64 */     avio_wb32(pb, 0); /* reserved */                                       // 0.0
/*66 */     avio_wb32(pb, 0); /* reserved */                                       // 0.0
/*68 */     avio_wb32(pb, 0); /* reserved */                                       // 0.0
/*70 */     if (!track || track->mode == MODE_MOV)                                 // 0.0
/*72 */         avio_w8(pb, strlen(descr)); /* pascal string */                    // 0.0
/*74 */     avio_write(pb, descr, strlen(descr)); /* handler description */        // 0.0
/*76 */     if (track && track->mode != MODE_MOV)                                  // 0.0
/*78 */         avio_w8(pb, 0); /* c string */                                     // 0.0
/*80 */     return update_size(pb, pos);                                           // 0.0
/*82 */ }                                                                          // 0.0
