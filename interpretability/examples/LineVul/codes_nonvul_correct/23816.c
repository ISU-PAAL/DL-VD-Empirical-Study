// commit message qemu@ad674e53b5 (target=0, prob=0.14435743, correct=True): MAC DBDMA: store register values in native endianness
/*0  */ static void conditional_branch(DBDMA_channel *ch)                       // (10) 0.0293
/*2  */ {                                                                       // (31) 0.001953
/*4  */     dbdma_cmd *current = &ch->current;                                  // (9) 0.03125
/*6  */     uint16_t br;                                                        // (21) 0.01758
/*8  */     uint16_t sel_mask, sel_value;                                       // (8) 0.0332
/*10 */     uint32_t status;                                                    // (22) 0.01758
/*12 */     int cond;                                                           // (29) 0.01172
/*16 */     DBDMA_DPRINTF("conditional_branch\n");                              // (5) 0.03906
/*20 */     /* check if we must branch */                                       // (20) 0.01953
/*24 */     br = le16_to_cpu(current->command) & BR_MASK;                       // (4) 0.04297
/*28 */     switch(br) {                                                        // (26) 0.01562
/*30 */     case BR_NEVER:  /* don't branch */                                  // (12) 0.0293
/*32 */         next(ch);                                                       // (16) 0.02148
/*34 */         return;                                                         // (23) 0.01758
/*36 */     case BR_ALWAYS: /* always branch */                                 // (15) 0.02539
/*38 */         branch(ch);                                                     // (17) 0.02148
/*40 */         return;                                                         // (24) 0.01758
/*42 */     }                                                                   // (30) 0.007812
/*46 */     status = be32_to_cpu(ch->regs[DBDMA_STATUS]) & DEVSTAT;             // (2) 0.05664
/*50 */     sel_mask = (be32_to_cpu(ch->regs[DBDMA_BRANCH_SEL]) >> 16) & 0x0f;  // (0) 0.08008
/*52 */     sel_value = be32_to_cpu(ch->regs[DBDMA_BRANCH_SEL]) & 0x0f;         // (1) 0.07227
/*56 */     cond = (status & sel_mask) == (sel_value & sel_mask);               // (3) 0.04688
/*60 */     switch(br) {                                                        // (27) 0.01562
/*62 */     case BR_IFSET:  /* branch if condition bit is 1 */                  // (7) 0.03516
/*64 */         if (cond)                                                       // (18) 0.02148
/*66 */             branch(ch);                                                 // (13) 0.0293
/*68 */         else                                                            // (28) 0.01562
/*70 */             next(ch);                                                   // (11) 0.0293
/*72 */         return;                                                         // (25) 0.01758
/*74 */     case BR_IFCLR:  /* branch if condition bit is 0 */                  // (6) 0.03711
/*76 */         if (!cond)                                                      // (19) 0.02148
/*78 */             branch(ch);                                                 // (14) 0.0293
/*80 */         else                                                            // 0.0
/*82 */             next(ch);                                                   // 0.0
/*84 */         return;                                                         // 0.0
/*86 */     }                                                                   // 0.0
/*88 */ }                                                                       // 0.0
