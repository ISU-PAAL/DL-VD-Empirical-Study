// commit message FFmpeg@e630ca5111 (target=1, prob=0.99927527, correct=True): avformat/mpegts: check sl.timestamp_len
/*0  */ static int parse_MP4SLDescrTag(MP4DescrParseContext *d, int64_t off, int len)  // (9) 0.05859
/*2  */ {                                                                              // (19) 0.001953
/*4  */     Mp4Descr *descr = d->active_descr;                                         // (12) 0.03711
/*6  */     int predefined;                                                            // (18) 0.01367
/*8  */     if (!descr)                                                                // (17) 0.01562
/*10 */         return -1;                                                             // (14) 0.02148
/*14 */     predefined = avio_r8(&d->pb);                                              // (13) 0.03125
/*16 */     if (!predefined) {                                                         // (16) 0.01758
/*18 */         int lengths;                                                           // (15) 0.01953
/*20 */         int flags = avio_r8(&d->pb);                                           // (11) 0.03906
/*22 */         descr->sl.use_au_start       = !!(flags & 0x80);                       // (6) 0.0625
/*24 */         descr->sl.use_au_end         = !!(flags & 0x40);                       // (3) 0.06641
/*26 */         descr->sl.use_rand_acc_pt    = !!(flags & 0x20);                       // (8) 0.06055
/*28 */         descr->sl.use_padding        = !!(flags & 0x08);                       // (7) 0.06055
/*30 */         descr->sl.use_timestamps     = !!(flags & 0x04);                       // (10) 0.05859
/*32 */         descr->sl.use_idle           = !!(flags & 0x02);                       // (2) 0.06836
/*34 */         descr->sl.timestamp_res      = avio_rb32(&d->pb);                      // (5) 0.0625
/*36 */                                        avio_rb32(&d->pb);                      // (0) 0.09375
/*38 */         descr->sl.timestamp_len      = avio_r8(&d->pb);                        // (4) 0.0625
/*45 */         descr->sl.ocr_len            = avio_r8(&d->pb);                        // (1) 0.07227
/*47 */         descr->sl.au_len             = avio_r8(&d->pb);                        // 0.0
/*49 */         descr->sl.inst_bitrate_len   = avio_r8(&d->pb);                        // 0.0
/*51 */         lengths                      = avio_rb16(&d->pb);                      // 0.0
/*53 */         descr->sl.degr_prior_len     = lengths >> 12;                          // 0.0
/*55 */         descr->sl.au_seq_num_len     = (lengths >> 7) & 0x1f;                  // 0.0
/*57 */         descr->sl.packet_seq_num_len = (lengths >> 2) & 0x1f;                  // 0.0
/*59 */     } else {                                                                   // 0.0
/*61 */         avpriv_report_missing_feature(d->s, "Predefined SLConfigDescriptor");  // 0.0
/*64 */     return 0;                                                                  // 0.0
