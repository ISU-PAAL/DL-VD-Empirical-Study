// commit message FFmpeg@21bffa93a6 (target=1, prob=0.38445494, correct=False): avformat/movenc: Switch mov_write_uuidprof_tag() to avg_frame_rate
/*0   */ static void mov_write_uuidprof_tag(AVIOContext *pb, AVFormatContext *s)                    // (5) 0.04686
/*2   */ {                                                                                          // (23) 0.001953
/*4   */     AVStream       *video_st    = s->streams[0];                                           // (2) 0.05077
/*6   */     AVCodecParameters *video_par = s->streams[0]->codecpar;                                // (6) 0.04686
/*8   */     AVCodecParameters *audio_par = s->streams[1]->codecpar;                                // (4) 0.04687
/*10  */     int audio_rate = audio_par->sample_rate;                                               // (19) 0.03126
/*12  */     // TODO: should be avg_frame_rate                                                      // (22) 0.02753
/*14  */     int frame_rate = ((video_st->time_base.den) * (0x10000)) / (video_st->time_base.num);  // (0) 0.07227
/*16  */     int audio_kbitrate = audio_par->bit_rate / 1000;                                       // (8) 0.03905
/*18  */     int video_kbitrate = FFMIN(video_par->bit_rate / 1000, 800 - audio_kbitrate);          // (1) 0.06053
/*22  */     avio_wb32(pb, 0x94); /* size */                                                        // (14) 0.03515
/*24  */     ffio_wfourcc(pb, "uuid");                                                              // (20) 0.03124
/*26  */     ffio_wfourcc(pb, "PROF");                                                              // (21) 0.03124
/*30  */     avio_wb32(pb, 0x21d24fce); /* 96 bit UUID */                                           // (3) 0.04881
/*32  */     avio_wb32(pb, 0xbb88695c);                                                             // (17) 0.03515
/*34  */     avio_wb32(pb, 0xfac9c740);                                                             // (16) 0.03515
/*38  */     avio_wb32(pb, 0x0);  /* ? */                                                           // (11) 0.0371
/*40  */     avio_wb32(pb, 0x3);  /* 3 sections ? */                                                // (7) 0.041
/*44  */     avio_wb32(pb, 0x14); /* size */                                                        // (15) 0.03515
/*46  */     ffio_wfourcc(pb, "FPRF");                                                              // (18) 0.03319
/*48  */     avio_wb32(pb, 0x0);  /* ? */                                                           // (13) 0.0371
/*50  */     avio_wb32(pb, 0x0);  /* ? */                                                           // (12) 0.0371
/*52  */     avio_wb32(pb, 0x0);  /* ? */                                                           // (10) 0.0371
/*56  */     avio_wb32(pb, 0x2c);  /* size */                                                       // (9) 0.03905
/*58  */     ffio_wfourcc(pb, "APRF"); /* audio */                                                  // 0.0
/*60  */     avio_wb32(pb, 0x0);                                                                    // 0.0
/*62  */     avio_wb32(pb, 0x2);   /* TrackID */                                                    // 0.0
/*64  */     ffio_wfourcc(pb, "mp4a");                                                              // 0.0
/*66  */     avio_wb32(pb, 0x20f);                                                                  // 0.0
/*68  */     avio_wb32(pb, 0x0);                                                                    // 0.0
/*70  */     avio_wb32(pb, audio_kbitrate);                                                         // 0.0
/*72  */     avio_wb32(pb, audio_kbitrate);                                                         // 0.0
/*74  */     avio_wb32(pb, audio_rate);                                                             // 0.0
/*76  */     avio_wb32(pb, audio_par->channels);                                                    // 0.0
/*80  */     avio_wb32(pb, 0x34);  /* size */                                                       // 0.0
/*82  */     ffio_wfourcc(pb, "VPRF");   /* video */                                                // 0.0
/*84  */     avio_wb32(pb, 0x0);                                                                    // 0.0
/*86  */     avio_wb32(pb, 0x1);    /* TrackID */                                                   // 0.0
/*88  */     if (video_par->codec_id == AV_CODEC_ID_H264) {                                         // 0.0
/*90  */         ffio_wfourcc(pb, "avc1");                                                          // 0.0
/*92  */         avio_wb16(pb, 0x014D);                                                             // 0.0
/*94  */         avio_wb16(pb, 0x0015);                                                             // 0.0
/*96  */     } else {                                                                               // 0.0
/*98  */         ffio_wfourcc(pb, "mp4v");                                                          // 0.0
/*100 */         avio_wb16(pb, 0x0000);                                                             // 0.0
/*102 */         avio_wb16(pb, 0x0103);                                                             // 0.0
/*104 */     }                                                                                      // 0.0
/*106 */     avio_wb32(pb, 0x0);                                                                    // 0.0
/*108 */     avio_wb32(pb, video_kbitrate);                                                         // 0.0
/*110 */     avio_wb32(pb, video_kbitrate);                                                         // 0.0
/*112 */     avio_wb32(pb, frame_rate);                                                             // 0.0
/*114 */     avio_wb32(pb, frame_rate);                                                             // 0.0
/*116 */     avio_wb16(pb, video_par->width);                                                       // 0.0
/*118 */     avio_wb16(pb, video_par->height);                                                      // 0.0
/*120 */     avio_wb32(pb, 0x010001); /* ? */                                                       // 0.0
/*122 */ }                                                                                          // 0.0
