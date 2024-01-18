// commit message FFmpeg@1c495b0bf6 (target=1, prob=0.95950645, correct=True): avcodec/jpeg2000: Move gainb handling into the quantization code
/*0   */ static void dwt_encode97_int(DWTContext *s, int *t)                   // (11) 0.04102
/*2   */ {                                                                     // (22) 0.001953
/*4   */     int lev,                                                          // (21) 0.01172
/*6   */         w = s->linelen[s->ndeclevels-1][0];                           // (4) 0.04883
/*8   */     int *line = s->i_linebuf;                                         // (15) 0.02734
/*10  */     line += 5;                                                        // (20) 0.01367
/*14  */     for (lev = s->ndeclevels-1; lev >= 0; lev--){                     // (8) 0.04297
/*16  */         int lh = s->linelen[lev][0],                                  // (12) 0.04102
/*18  */             lv = s->linelen[lev][1],                                  // (6) 0.04687
/*20  */             mh = s->mod[lev][0],                                      // (9) 0.04297
/*22  */             mv = s->mod[lev][1],                                      // (10) 0.04297
/*24  */             lp;                                                       // (17) 0.02734
/*26  */         int *l;                                                       // (19) 0.02148
/*30  */         // VER_SD                                                     // (18) 0.02148
/*32  */         l = line + mv;                                                // (16) 0.02734
/*34  */         for (lp = 0; lp < lh; lp++) {                                 // (7) 0.04492
/*36  */             int i, j = 0;                                             // (14) 0.03516
/*40  */             for (i = 0; i < lv; i++)                                  // (5) 0.04688
/*42  */                 l[i] = t[w*i + lp];                                   // (3) 0.05664
/*46  */             sd_1d97_int(line, mv, mv + lv);                           // (2) 0.05859
/*50  */             // copy back and deinterleave                             // (13) 0.03516
/*52  */             for (i =   mv; i < lv; i+=2, j++)                         // (1) 0.06055
/*54  */                 t[w*j + lp] = ((l[i] * I_LFTG_X) + (1 << 16)) >> 17;  // (0) 0.09375
/*56  */             for (i = 1-mv; i < lv; i+=2, j++)                         // 0.0
/*58  */                 t[w*j + lp] = ((l[i] * I_LFTG_K) + (1 << 16)) >> 17;  // 0.0
/*60  */         }                                                             // 0.0
/*64  */         // HOR_SD                                                     // 0.0
/*66  */         l = line + mh;                                                // 0.0
/*68  */         for (lp = 0; lp < lv; lp++){                                  // 0.0
/*70  */             int i, j = 0;                                             // 0.0
/*74  */             for (i = 0; i < lh; i++)                                  // 0.0
/*76  */                 l[i] = t[w*lp + i];                                   // 0.0
/*80  */             sd_1d97_int(line, mh, mh + lh);                           // 0.0
/*84  */             // copy back and deinterleave                             // 0.0
/*86  */             for (i =   mh; i < lh; i+=2, j++)                         // 0.0
/*88  */                 t[w*lp + j] = ((l[i] * I_LFTG_X) + (1 << 16)) >> 17;  // 0.0
/*90  */             for (i = 1-mh; i < lh; i+=2, j++)                         // 0.0
/*92  */                 t[w*lp + j] = ((l[i] * I_LFTG_K) + (1 << 16)) >> 17;  // 0.0
/*94  */         }                                                             // 0.0
/*98  */     }                                                                 // 0.0
/*100 */ }                                                                     // 0.0
