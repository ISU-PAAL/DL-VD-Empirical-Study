// commit message FFmpeg@482ee63641 (target=1, prob=0.45340145, correct=False): thpdemux: Check that packed sizes are within the files data size and filesize. Fixes Ticket774 Bug found by: Diana Elena Muscalu
/*0   */ static int thp_read_header(AVFormatContext *s,                            // (13) 0.0293
/*2   */                            AVFormatParameters *ap)                        // (6) 0.0625
/*4   */ {                                                                         // (18) 0.001953
/*6   */     ThpDemuxContext *thp = s->priv_data;                                  // (12) 0.03516
/*8   */     AVStream *st;                                                         // (16) 0.01563
/*10  */     AVIOContext *pb = s->pb;                                              // (14) 0.02539
/*12  */     int i;                                                                // (17) 0.01172
/*16  */     /* Read the file header.  */                                          // (15) 0.02148
/*18  */                            avio_rb32(pb); /* Skip Magic.  */              // (3) 0.07812
/*20  */     thp->version         = avio_rb32(pb);                                 // (9) 0.04687
/*24  */                            avio_rb32(pb); /* Max buf size.  */            // (2) 0.08008
/*26  */                            avio_rb32(pb); /* Max samples.  */             // (4) 0.07812
/*30  */     thp->fps             = av_d2q(av_int2float(avio_rb32(pb)), INT_MAX);  // (0) 0.08594
/*32  */     thp->framecnt        = avio_rb32(pb);                                 // (8) 0.04883
/*34  */     thp->first_framesz   = avio_rb32(pb);                                 // (11) 0.04102
/*36  */                            avio_rb32(pb); /* Data size.  */               // (5) 0.07812
/*40  */     thp->compoff         = avio_rb32(pb);                                 // (7) 0.04883
/*42  */                            avio_rb32(pb); /* offsetDataOffset.  */        // (1) 0.08008
/*44  */     thp->first_frame     = avio_rb32(pb);                                 // (10) 0.04297
/*46  */     thp->last_frame      = avio_rb32(pb);                                 // 0.0
/*50  */     thp->next_framesz    = thp->first_framesz;                            // 0.0
/*52  */     thp->next_frame      = thp->first_frame;                              // 0.0
/*56  */     /* Read the component structure.  */                                  // 0.0
/*58  */     avio_seek (pb, thp->compoff, SEEK_SET);                               // 0.0
/*60  */     thp->compcount       = avio_rb32(pb);                                 // 0.0
/*64  */     /* Read the list of component types.  */                              // 0.0
/*66  */     avio_read(pb, thp->components, 16);                                   // 0.0
/*70  */     for (i = 0; i < thp->compcount; i++) {                                // 0.0
/*72  */         if (thp->components[i] == 0) {                                    // 0.0
/*74  */             if (thp->vst != 0)                                            // 0.0
/*76  */                 break;                                                    // 0.0
/*80  */             /* Video component.  */                                       // 0.0
/*82  */             st = avformat_new_stream(s, NULL);                            // 0.0
/*84  */             if (!st)                                                      // 0.0
/*86  */                 return AVERROR(ENOMEM);                                   // 0.0
/*90  */             /* The denominator and numerator are switched because 1/fps   // 0.0
/*92  */                is required.  */                                           // 0.0
/*94  */             avpriv_set_pts_info(st, 64, thp->fps.den, thp->fps.num);      // 0.0
/*96  */             st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                   // 0.0
/*98  */             st->codec->codec_id = CODEC_ID_THP;                           // 0.0
/*100 */             st->codec->codec_tag = 0;  /* no fourcc */                    // 0.0
/*102 */             st->codec->width = avio_rb32(pb);                             // 0.0
/*104 */             st->codec->height = avio_rb32(pb);                            // 0.0
/*106 */             st->codec->sample_rate = av_q2d(thp->fps);                    // 0.0
/*108 */             thp->vst = st;                                                // 0.0
/*110 */             thp->video_stream_index = st->index;                          // 0.0
/*114 */             if (thp->version == 0x11000)                                  // 0.0
/*116 */                 avio_rb32(pb); /* Unknown.  */                            // 0.0
/*118 */         } else if (thp->components[i] == 1) {                             // 0.0
/*120 */             if (thp->has_audio != 0)                                      // 0.0
/*122 */                 break;                                                    // 0.0
/*126 */             /* Audio component.  */                                       // 0.0
/*128 */             st = avformat_new_stream(s, NULL);                            // 0.0
/*130 */             if (!st)                                                      // 0.0
/*132 */                 return AVERROR(ENOMEM);                                   // 0.0
/*136 */             st->codec->codec_type = AVMEDIA_TYPE_AUDIO;                   // 0.0
/*138 */             st->codec->codec_id = CODEC_ID_ADPCM_THP;                     // 0.0
/*140 */             st->codec->codec_tag = 0;  /* no fourcc */                    // 0.0
/*142 */             st->codec->channels    = avio_rb32(pb); /* numChannels.  */   // 0.0
/*144 */             st->codec->sample_rate = avio_rb32(pb); /* Frequency.  */     // 0.0
/*148 */             avpriv_set_pts_info(st, 64, 1, st->codec->sample_rate);       // 0.0
/*152 */             thp->audio_stream_index = st->index;                          // 0.0
/*154 */             thp->has_audio = 1;                                           // 0.0
/*156 */         }                                                                 // 0.0
/*158 */     }                                                                     // 0.0
/*162 */     return 0;                                                             // 0.0
/*164 */ }                                                                         // 0.0
