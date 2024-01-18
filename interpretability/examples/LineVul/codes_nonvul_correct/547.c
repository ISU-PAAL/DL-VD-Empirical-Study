// commit message qemu@b7b6348ab4 (target=0, prob=0.10815864, correct=True): s390x/ioinst: Rework memory access in TSCH instruction
/*0  */ static void copy_irb_to_guest(IRB *dest, const IRB *src, PMCW *pmcw)       // (1) 0.05859
/*2  */ {                                                                          // (24) 0.001953
/*4  */     int i;                                                                 // (19) 0.01172
/*6  */     uint16_t stctl = src->scsw.ctrl & SCSW_CTRL_MASK_STCTL;                // (2) 0.05859
/*8  */     uint16_t actl = src->scsw.ctrl & SCSW_CTRL_MASK_ACTL;                  // (6) 0.05664
/*12 */     copy_scsw_to_guest(&dest->scsw, &src->scsw);                           // (9) 0.04688
/*16 */     for (i = 0; i < ARRAY_SIZE(dest->esw); i++) {                          // (10) 0.04688
/*18 */         dest->esw[i] = cpu_to_be32(src->esw[i]);                           // (4) 0.05664
/*20 */     }                                                                      // (20) 0.007812
/*22 */     for (i = 0; i < ARRAY_SIZE(dest->ecw); i++) {                          // (11) 0.04688
/*24 */         dest->ecw[i] = cpu_to_be32(src->ecw[i]);                           // (5) 0.05664
/*26 */     }                                                                      // (21) 0.007812
/*28 */     /* extended measurements enabled? */                                   // (16) 0.01758
/*30 */     if ((src->scsw.flags & SCSW_FLAGS_MASK_ESWF) ||                        // (8) 0.04883
/*32 */         !(pmcw->flags & PMCW_FLAGS_MASK_TF) ||                             // (7) 0.05273
/*34 */         !(pmcw->chars & PMCW_CHARS_MASK_XMWME)) {                          // (3) 0.05859
/*36 */         return;                                                            // (17) 0.01758
/*38 */     }                                                                      // (22) 0.007812
/*40 */     /* extended measurements pending? */                                   // (15) 0.01758
/*42 */     if (!(stctl & SCSW_STCTL_STATUS_PEND)) {                               // (12) 0.04492
/*44 */         return;                                                            // (18) 0.01758
/*46 */     }                                                                      // (23) 0.007812
/*48 */     if ((stctl & SCSW_STCTL_PRIMARY) ||                                    // (14) 0.03906
/*50 */         (stctl == SCSW_STCTL_SECONDARY) ||                                 // (13) 0.04492
/*52 */         ((stctl & SCSW_STCTL_INTERMEDIATE) && (actl & SCSW_ACTL_SUSP))) {  // (0) 0.07617
/*54 */         for (i = 0; i < ARRAY_SIZE(dest->emw); i++) {                      // 0.0
/*56 */             dest->emw[i] = cpu_to_be32(src->emw[i]);                       // 0.0
/*58 */         }                                                                  // 0.0
/*60 */     }                                                                      // 0.0
/*62 */ }                                                                          // 0.0
