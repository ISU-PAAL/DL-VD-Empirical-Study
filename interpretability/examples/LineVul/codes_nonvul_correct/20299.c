// commit message qemu@6e0d8677cb (target=0, prob=0.06983856, correct=True): converted string OPs and LOOP insns to TCG
/*0  */ static void gen_exts(int ot, TCGv reg)  // (3) 0.08197
/*2  */ {                                       // (14) 0.005464
/*4  */     switch(ot) {                        // (11) 0.04372
/*6  */     case OT_BYTE:                       // (5) 0.04918
/*8  */         tcg_gen_ext8s_tl(reg, reg);     // (1) 0.1202
/*10 */         break;                          // (7) 0.04918
/*12 */     case OT_WORD:                       // (4) 0.04918
/*14 */         tcg_gen_ext16s_tl(reg, reg);    // (0) 0.1202
/*16 */         break;                          // (8) 0.04918
/*18 */     case OT_LONG:                       // (6) 0.04918
/*20 */         tcg_gen_ext32s_tl(reg, reg);    // (2) 0.1202
/*22 */         break;                          // (9) 0.04918
/*24 */     default:                            // (12) 0.02732
/*26 */         break;                          // (10) 0.04918
/*28 */     }                                   // (13) 0.02186
/*30 */ }                                       // (15) 0.005464
