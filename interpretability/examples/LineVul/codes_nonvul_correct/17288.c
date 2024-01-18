// commit message FFmpeg@4fb3efd2c1 (target=0, prob=0.118451856, correct=True): lavf/mov: Use AVCOL_SPC constants when checking color_space.
/*0   */ static int mov_write_colr_tag(AVIOContext *pb, MOVTrack *track)                                                                    // (13) 0.04297
/*2   */ {                                                                                                                                  // (16) 0.001954
/*4   */     // Ref (MOV): https://developer.apple.com/library/mac/technotes/tn2162/_index.html#//apple_ref/doc/uid/DTS40013070-CH1-TNTAG9  // (0) 0.1074
/*6   */     // Ref (MP4): ISO/IEC 14496-12:2012                                                                                            // (14) 0.03711
/*10  */     if (track->enc->color_primaries == AVCOL_PRI_UNSPECIFIED &&                                                                    // (12) 0.04687
/*12  */         track->enc->color_trc == AVCOL_TRC_UNSPECIFIED &&                                                                          // (10) 0.05078
/*14  */         track->enc->colorspace == AVCOL_SPC_UNSPECIFIED) {                                                                         // (9) 0.05078
/*16  */         if ((track->enc->width >= 1920 && track->enc->height >= 1080)                                                              // (11) 0.04883
/*18  */           || (track->enc->width == 1280 && track->enc->height == 720)) {                                                           // (7) 0.05469
/*20  */             av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, assuming bt709\n");                                         // (3) 0.06836
/*22  */             track->enc->color_primaries = AVCOL_PRI_BT709;                                                                         // (6) 0.05664
/*24  */         } else if (track->enc->width == 720 && track->height == 576) {                                                             // (8) 0.05273
/*26  */             av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, assuming bt470bg\n");                                       // (2) 0.07031
/*28  */             track->enc->color_primaries = AVCOL_PRI_BT470BG;                                                                       // (5) 0.05859
/*30  */         } else if (track->enc->width == 720 &&                                                                                     // (15) 0.03711
/*32  */                    (track->height == 486 || track->height == 480)) {                                                               // (4) 0.06445
/*34  */             av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, assuming smpte170\n");                                      // (1) 0.07031
/*36  */             track->enc->color_primaries = AVCOL_PRI_SMPTE170M;                                                                     // 0.0
/*38  */         } else {                                                                                                                   // 0.0
/*40  */             av_log(NULL, AV_LOG_WARNING, "color primaries unspecified, unable to assume anything\n");                              // 0.0
/*42  */         }                                                                                                                          // 0.0
/*44  */         switch (track->enc->color_primaries) {                                                                                     // 0.0
/*46  */         case AVCOL_PRI_BT709:                                                                                                      // 0.0
/*48  */             track->enc->color_trc = AVCOL_TRC_BT709;                                                                               // 0.0
/*50  */             track->enc->colorspace = AVCOL_SPC_BT709;                                                                              // 0.0
/*52  */             break;                                                                                                                 // 0.0
/*54  */         case AVCOL_PRI_SMPTE170M:                                                                                                  // 0.0
/*56  */         case AVCOL_PRI_BT470BG:                                                                                                    // 0.0
/*58  */             track->enc->color_trc = AVCOL_TRC_BT709;                                                                               // 0.0
/*60  */             track->enc->colorspace = AVCOL_SPC_SMPTE170M;                                                                          // 0.0
/*62  */             break;                                                                                                                 // 0.0
/*64  */         }                                                                                                                          // 0.0
/*66  */     }                                                                                                                              // 0.0
/*70  */     /* We should only ever be called by MOV or MP4. */                                                                             // 0.0
/*72  */     av_assert0(track->mode == MODE_MOV || track->mode == MODE_MP4);                                                                // 0.0
/*76  */     avio_wb32(pb, 18 + (track->mode == MODE_MP4));                                                                                 // 0.0
/*78  */     ffio_wfourcc(pb, "colr");                                                                                                      // 0.0
/*80  */     if (track->mode == MODE_MP4)                                                                                                   // 0.0
/*82  */         ffio_wfourcc(pb, "nclx");                                                                                                  // 0.0
/*84  */     else                                                                                                                           // 0.0
/*86  */         ffio_wfourcc(pb, "nclc");                                                                                                  // 0.0
/*88  */     switch (track->enc->color_primaries) {                                                                                         // 0.0
/*90  */     case AVCOL_PRI_BT709:     avio_wb16(pb, 1); break;                                                                             // 0.0
/*92  */     case AVCOL_PRI_SMPTE170M:                                                                                                      // 0.0
/*94  */     case AVCOL_PRI_SMPTE240M: avio_wb16(pb, 6); break;                                                                             // 0.0
/*96  */     case AVCOL_PRI_BT470BG:   avio_wb16(pb, 5); break;                                                                             // 0.0
/*98  */     default:                  avio_wb16(pb, 2);                                                                                    // 0.0
/*100 */     }                                                                                                                              // 0.0
/*102 */     switch (track->enc->color_trc) {                                                                                               // 0.0
/*104 */     case AVCOL_TRC_BT709:     avio_wb16(pb, 1); break;                                                                             // 0.0
/*106 */     case AVCOL_TRC_SMPTE170M: avio_wb16(pb, 1); break; // remapped                                                                 // 0.0
/*108 */     case AVCOL_TRC_SMPTE240M: avio_wb16(pb, 7); break;                                                                             // 0.0
/*110 */     default:                  avio_wb16(pb, 2);                                                                                    // 0.0
/*112 */     }                                                                                                                              // 0.0
/*114 */     switch (track->enc->colorspace) {                                                                                              // 0.0
/*116 */     case AVCOL_TRC_BT709:     avio_wb16(pb, 1); break;                                                                             // 0.0
/*118 */     case AVCOL_SPC_BT470BG:                                                                                                        // 0.0
/*120 */     case AVCOL_PRI_SMPTE170M: avio_wb16(pb, 6); break;                                                                             // 0.0
/*122 */     case AVCOL_PRI_SMPTE240M: avio_wb16(pb, 7); break;                                                                             // 0.0
/*124 */     default:                  avio_wb16(pb, 2);                                                                                    // 0.0
/*126 */     }                                                                                                                              // 0.0
/*130 */     if (track->mode == MODE_MP4) {                                                                                                 // 0.0
/*132 */         int full_range = track->enc->color_range == AVCOL_RANGE_JPEG;                                                              // 0.0
/*134 */         avio_w8(pb, full_range << 7);                                                                                              // 0.0
/*136 */         return 19;                                                                                                                 // 0.0
/*138 */     } else {                                                                                                                       // 0.0
/*140 */         return 18;                                                                                                                 // 0.0
/*142 */     }                                                                                                                              // 0.0
/*144 */ }                                                                                                                                  // 0.0
