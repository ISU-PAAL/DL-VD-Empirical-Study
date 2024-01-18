// commit message FFmpeg@955aec3c7c (target=0, prob=0.3931301, correct=True): mpegaudiodecheader: check the header in avpriv_mpegaudio_decode_header
/*0  */ static int mp3_parse_vbr_tags(AVFormatContext *s, AVStream *st, int64_t base)                        // (2) 0.05664
/*2  */ {                                                                                                    // (25) 0.001953
/*4  */     uint32_t v, spf;                                                                                 // (15) 0.02344
/*6  */     MPADecodeHeader c;                                                                               // (21) 0.01953
/*8  */     int vbrtag_size = 0;                                                                             // (14) 0.02344
/*10 */     MP3DecContext *mp3 = s->priv_data;                                                               // (11) 0.0332
/*14 */     ffio_init_checksum(s->pb, ff_crcA001_update, 0);                                                 // (3) 0.05078
/*18 */     v = avio_rb32(s->pb);                                                                            // (13) 0.0293
/*20 */     if(ff_mpa_check_header(v) < 0)                                                                   // (9) 0.03711
/*22 */       return -1;                                                                                     // (24) 0.01758
/*26 */     if (avpriv_mpegaudio_decode_header(&c, v) == 0)                                                  // (6) 0.04492
/*28 */         vbrtag_size = c.frame_size;                                                                  // (10) 0.03711
/*30 */     if(c.layer != 3)                                                                                 // (18) 0.02148
/*32 */         return -1;                                                                                   // (20) 0.02148
/*36 */     spf = c.lsf ? 576 : 1152; /* Samples per frame, layer 3 */                                       // (4) 0.05078
/*40 */     mp3->frames = 0;                                                                                 // (23) 0.01953
/*42 */     mp3->size   = 0;                                                                                 // (16) 0.02344
/*46 */     mp3_parse_info_tag(s, st, &c, spf);                                                              // (7) 0.04297
/*48 */     mp3_parse_vbri_tag(s, st, base);                                                                 // (8) 0.03906
/*52 */     if (!mp3->frames && !mp3->size)                                                                  // (12) 0.03125
/*54 */         return -1;                                                                                   // (19) 0.02148
/*58 */     /* Skip the vbr tag frame */                                                                     // (17) 0.02148
/*60 */     avio_seek(s->pb, base + vbrtag_size, SEEK_SET);                                                  // (5) 0.04883
/*64 */     if (mp3->frames)                                                                                 // (22) 0.01953
/*66 */         st->duration = av_rescale_q(mp3->frames, (AVRational){spf, c.sample_rate},                   // (1) 0.07227
/*68 */                                     st->time_base);                                                  // (0) 0.08008
/*70 */     if (mp3->size && mp3->frames && !mp3->is_cbr)                                                    // 0.0
/*72 */         st->codec->bit_rate = av_rescale(mp3->size, 8 * c.sample_rate, mp3->frames * (int64_t)spf);  // 0.0
/*76 */     return 0;                                                                                        // 0.0
/*78 */ }                                                                                                    // 0.0
