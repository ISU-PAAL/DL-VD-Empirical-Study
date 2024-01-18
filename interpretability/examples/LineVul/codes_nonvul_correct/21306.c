// commit message qemu@375cb56029 (target=0, prob=0.009267576, correct=True): hw/pl110: Use LOG_GUEST_ERROR rather than hw_error()
/*0  */ static uint64_t pl110_read(void *opaque, hwaddr offset,        // (3) 0.03906
/*2  */                            unsigned size)                      // (0) 0.05664
/*4  */ {                                                              // (32) 0.001953
/*6  */     pl110_state *s = (pl110_state *)opaque;                    // (4) 0.03711
/*10 */     if (offset >= 0xfe0 && offset < 0x1000) {                  // (5) 0.03711
/*12 */         return idregs[s->version][(offset - 0xfe0) >> 2];      // (1) 0.05273
/*14 */     }                                                          // (30) 0.007812
/*16 */     if (offset >= 0x200 && offset < 0x400) {                   // (6) 0.03516
/*18 */         return s->raw_palette[(offset - 0x200) >> 2];          // (2) 0.04883
/*20 */     }                                                          // (31) 0.007812
/*22 */     switch (offset >> 2) {                                     // (26) 0.01953
/*24 */     case 0: /* LCDTiming0 */                                   // (18) 0.02344
/*26 */         return s->timing[0];                                   // (11) 0.0293
/*28 */     case 1: /* LCDTiming1 */                                   // (19) 0.02344
/*30 */         return s->timing[1];                                   // (12) 0.0293
/*32 */     case 2: /* LCDTiming2 */                                   // (20) 0.02344
/*34 */         return s->timing[2];                                   // (13) 0.0293
/*36 */     case 3: /* LCDTiming3 */                                   // (21) 0.02344
/*38 */         return s->timing[3];                                   // (14) 0.0293
/*40 */     case 4: /* LCDUPBASE */                                    // (22) 0.02344
/*42 */         return s->upbase;                                      // (16) 0.02539
/*44 */     case 5: /* LCDLPBASE */                                    // (23) 0.02344
/*46 */         return s->lpbase;                                      // (17) 0.02539
/*48 */     case 6: /* LCDIMSC */                                      // (25) 0.02148
/*50 */         if (s->version != PL110) {                             // (8) 0.0332
/*52 */             return s->cr;                                      // (10) 0.03125
/*54 */         }                                                      // (28) 0.01562
/*56 */         return s->int_mask;                                    // (15) 0.02734
/*58 */     case 7: /* LCDControl */                                   // (27) 0.01953
/*60 */         if (s->version != PL110) {                             // (9) 0.0332
/*62 */             return s->int_mask;                                // (7) 0.03516
/*64 */         }                                                      // (29) 0.01562
/*66 */         return s->cr;                                          // (24) 0.02344
/*68 */     case 8: /* LCDRIS */                                       // 0.0
/*70 */         return s->int_status;                                  // 0.0
/*72 */     case 9: /* LCDMIS */                                       // 0.0
/*74 */         return s->int_status & s->int_mask;                    // 0.0
/*76 */     case 11: /* LCDUPCURR */                                   // 0.0
/*78 */         /* TODO: Implement vertical refresh.  */               // 0.0
/*80 */         return s->upbase;                                      // 0.0
/*82 */     case 12: /* LCDLPCURR */                                   // 0.0
/*84 */         return s->lpbase;                                      // 0.0
/*86 */     default:                                                   // 0.0
/*88 */         hw_error("pl110_read: Bad offset %x\n", (int)offset);  // 0.0
/*90 */         return 0;                                              // 0.0
/*92 */     }                                                          // 0.0
/*94 */ }                                                              // 0.0
