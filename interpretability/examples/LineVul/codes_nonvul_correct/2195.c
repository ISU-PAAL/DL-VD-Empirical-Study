// commit message qemu@eabb7b91b3 (target=0, prob=0.080536254, correct=True): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0  */ static void tcg_out_opc(TCGContext *s, int opc, int r, int rm, int x)       // (5) 0.05664
/*2  */ {                                                                           // (23) 0.001953
/*4  */     int rex;                                                                // (19) 0.01367
/*8  */     if (opc & P_GS) {                                                       // (17) 0.02539
/*10 */         tcg_out8(s, 0x65);                                                  // (11) 0.03711
/*12 */     }                                                                       // (20) 0.007812
/*14 */     if (opc & P_DATA16) {                                                   // (16) 0.02734
/*16 */         /* We should never be asking for both 16 and 64-bit operation.  */  // (6) 0.04688
/*18 */         assert((opc & P_REXW) == 0);                                        // (10) 0.04102
/*20 */         tcg_out8(s, 0x66);                                                  // (12) 0.03711
/*22 */     }                                                                       // (21) 0.007812
/*24 */     if (opc & P_ADDR32) {                                                   // (15) 0.0293
/*26 */         tcg_out8(s, 0x67);                                                  // (13) 0.03711
/*28 */     }                                                                       // (22) 0.007812
/*32 */     rex = 0;                                                                // (18) 0.01562
/*34 */     rex |= (opc & P_REXW) ? 0x8 : 0x0;  /* REX.W */                         // (4) 0.06445
/*36 */     rex |= (r & 8) >> 1;                /* REX.R */                         // (1) 0.07031
/*38 */     rex |= (x & 8) >> 2;                /* REX.X */                         // (2) 0.07031
/*40 */     rex |= (rm & 8) >> 3;               /* REX.B */                         // (3) 0.06836
/*44 */     /* P_REXB_{R,RM} indicates that the given register is the low byte.     // (7) 0.04688
/*46 */        For %[abcd]l we need no REX prefix, but for %{si,di,bp,sp}l we do,   // (0) 0.07031
/*48 */        as otherwise the encoding indicates %[abcd]h.  Note that the values  // (8) 0.04492
/*50 */        that are ORed in merely indicate that the REX byte must be present;  // (9) 0.04297
/*52 */        those bits get discarded in output.  */                              // (14) 0.0293
/*54 */     rex |= opc & (r >= 4 ? P_REXB_R : 0);                                   // 0.0
/*56 */     rex |= opc & (rm >= 4 ? P_REXB_RM : 0);                                 // 0.0
/*60 */     if (rex) {                                                              // 0.0
/*62 */         tcg_out8(s, (uint8_t)(rex | 0x40));                                 // 0.0
/*64 */     }                                                                       // 0.0
/*68 */     if (opc & (P_EXT | P_EXT38)) {                                          // 0.0
/*70 */         tcg_out8(s, 0x0f);                                                  // 0.0
/*72 */         if (opc & P_EXT38) {                                                // 0.0
/*74 */             tcg_out8(s, 0x38);                                              // 0.0
/*76 */         }                                                                   // 0.0
/*78 */     }                                                                       // 0.0
/*82 */     tcg_out8(s, opc);                                                       // 0.0
/*84 */ }                                                                           // 0.0
