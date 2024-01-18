// commit message FFmpeg@29c2fcb677 (target=1, prob=0.9341486, correct=True): Use correct value for range
/*0  */ static void lms_update(WmallDecodeCtx *s, int ich, int ilms, int16_t input, int16_t pred)  // (1) 0.07227
/*2  */ {                                                                                          // (19) 0.001953
/*4  */     int16_t icoef;                                                                         // (13) 0.02148
/*6  */     int recent = s->cdlms[ich][ilms].recent;                                               // (11) 0.03711
/*8  */     int16_t range = 1 << (s->bits_per_sample - 1);                                         // (10) 0.04297
/*10 */     int bps = s->bits_per_sample > 16 ? 4 : 2; // bytes per sample                         // (9) 0.04883
/*14 */     if (input > pred) {                                                                    // (14) 0.01953
/*16 */         for (icoef = 0; icoef < s->cdlms[ich][ilms].order; icoef++)                        // (5) 0.06836
/*18 */             s->cdlms[ich][ilms].coefs[icoef] +=                                            // (8) 0.05859
/*20 */                 s->cdlms[ich][ilms].lms_updates[icoef + recent];                           // (2) 0.07226
/*22 */     } else {                                                                               // (17) 0.01172
/*24 */         for (icoef = 0; icoef < s->cdlms[ich][ilms].order; icoef++)                        // (6) 0.06836
/*26 */             s->cdlms[ich][ilms].coefs[icoef] -=                                            // (7) 0.05859
/*28 */                 s->cdlms[ich][ilms].lms_updates[icoef];     // XXX: [icoef + recent] ?     // (0) 0.0957
/*30 */     }                                                                                      // (18) 0.007812
/*32 */     s->cdlms[ich][ilms].recent--;                                                          // (12) 0.0332
/*34 */     s->cdlms[ich][ilms].lms_prevvalues[recent] = av_clip(input, -range, range - 1);        // (3) 0.07031
/*38 */     if (input > pred)                                                                      // (16) 0.01758
/*40 */         s->cdlms[ich][ilms].lms_updates[recent] = s->update_speed[ich];                    // (4) 0.06836
/*42 */     else if (input < pred)                                                                 // (15) 0.01953
/*44 */         s->cdlms[ich][ilms].lms_updates[recent] = -s->update_speed[ich];                   // 0.0
/*48 */     /* XXX: spec says:                                                                     // 0.0
/*50 */     cdlms[iCh][ilms].updates[iRecent + cdlms[iCh][ilms].order >> 4] >>= 2;                 // 0.0
/*52 */     lms_updates[iCh][ilms][iRecent + cdlms[iCh][ilms].order >> 3] >>= 1;                   // 0.0
/*56 */         Questions is - are cdlms[iCh][ilms].updates[] and lms_updates[][][] two            // 0.0
/*58 */         seperate buffers? Here I've assumed that the two are same which makes              // 0.0
/*60 */         more sense to me.                                                                  // 0.0
/*62 */     */                                                                                     // 0.0
/*64 */     s->cdlms[ich][ilms].lms_updates[recent + s->cdlms[ich][ilms].order >> 4] >>= 2;        // 0.0
/*66 */     s->cdlms[ich][ilms].lms_updates[recent + s->cdlms[ich][ilms].order >> 3] >>= 1;        // 0.0
/*68 */     /* XXX: recent + (s->cdlms[ich][ilms].order >> 4) ? */                                 // 0.0
/*72 */     if (s->cdlms[ich][ilms].recent == 0) {                                                 // 0.0
/*74 */         /* XXX: This memcpy()s will probably fail if a fixed 32-bit buffer is used.        // 0.0
/*76 */                 follow kshishkov's suggestion of using a union. */                         // 0.0
/*78 */         memcpy(s->cdlms[ich][ilms].lms_prevvalues + s->cdlms[ich][ilms].order,             // 0.0
/*80 */                s->cdlms[ich][ilms].lms_prevvalues,                                         // 0.0
/*82 */                bps * s->cdlms[ich][ilms].order);                                           // 0.0
/*84 */         memcpy(s->cdlms[ich][ilms].lms_updates + s->cdlms[ich][ilms].order,                // 0.0
/*86 */                s->cdlms[ich][ilms].lms_updates,                                            // 0.0
/*88 */                bps * s->cdlms[ich][ilms].order);                                           // 0.0
/*90 */         s->cdlms[ich][ilms].recent = s->cdlms[ich][ilms].order;                            // 0.0
/*92 */     }                                                                                      // 0.0
/*94 */ }                                                                                          // 0.0
