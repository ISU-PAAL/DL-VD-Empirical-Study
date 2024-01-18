// commit message qemu@c5b9729ae9 (target=0, prob=0.34577125, correct=True): ppc-40x: Correct check for Endian swapping TLB entries.
/*0   */ void helper_4xx_tlbwe_hi (target_ulong entry, target_ulong val)                  // (7) 0.04688
/*2   */ {                                                                                // (22) 0.001953
/*4   */     ppcemb_tlb_t *tlb;                                                           // (15) 0.0293
/*6   */     target_ulong page, end;                                                      // (18) 0.02148
/*10  */     LOG_SWTLB("%s entry %d val " TARGET_FMT_lx "\n", __func__, (int)entry,       // (2) 0.07031
/*12  */               val);                                                              // (16) 0.0293
/*14  */     entry &= 0x3F;                                                               // (19) 0.02148
/*16  */     tlb = &env->tlb[entry].tlbe;                                                 // (12) 0.0332
/*18  */     /* Invalidate previous TLB (if it's valid) */                                // (13) 0.03125
/*20  */     if (tlb->prot & PAGE_VALID) {                                                // (14) 0.03125
/*22  */         end = tlb->EPN + tlb->size;                                              // (9) 0.03906
/*24  */         LOG_SWTLB("%s: invalidate old TLB %d start " TARGET_FMT_lx " end "       // (1) 0.07031
/*26  */                   TARGET_FMT_lx "\n", __func__, (int)entry, tlb->EPN, end);      // (0) 0.08789
/*28  */         for (page = tlb->EPN; page < end; page += TARGET_PAGE_SIZE)              // (4) 0.06055
/*30  */             tlb_flush_page(env, page);                                           // (8) 0.04297
/*32  */     }                                                                            // (21) 0.007812
/*34  */     tlb->size = booke_tlb_to_page_size((val >> 7) & 0x7);                        // (5) 0.05664
/*36  */     /* We cannot handle TLB size < TARGET_PAGE_SIZE.                             // (10) 0.03711
/*38  */      * If this ever occurs, one should use the ppcemb target instead             // (11) 0.03711
/*40  */      * of the ppc or ppc64 one                                                   // (17) 0.02734
/*42  */      */                                                                          // (20) 0.009766
/*44  */     if ((val & 0x40) && tlb->size < TARGET_PAGE_SIZE) {                          // (6) 0.05078
/*46  */         cpu_abort(env, "TLB size " TARGET_FMT_lu " < %u "                        // (3) 0.06055
/*48  */                   "are not supported (%d)\n",                                    // 0.0
/*50  */                   tlb->size, TARGET_PAGE_SIZE, (int)((val >> 7) & 0x7));         // 0.0
/*52  */     }                                                                            // 0.0
/*54  */     tlb->EPN = val & ~(tlb->size - 1);                                           // 0.0
/*56  */     if (val & 0x40)                                                              // 0.0
/*58  */         tlb->prot |= PAGE_VALID;                                                 // 0.0
/*60  */     else                                                                         // 0.0
/*62  */         tlb->prot &= ~PAGE_VALID;                                                // 0.0
/*64  */     if (val & 0x20) {                                                            // 0.0
/*66  */         /* XXX: TO BE FIXED */                                                   // 0.0
/*68  */         cpu_abort(env, "Little-endian TLB entries are not supported by now\n");  // 0.0
/*70  */     }                                                                            // 0.0
/*72  */     tlb->PID = env->spr[SPR_40x_PID]; /* PID */                                  // 0.0
/*74  */     LOG_SWTLB("%s: set up TLB %d RPN " TARGET_FMT_plx " EPN " TARGET_FMT_lx      // 0.0
/*76  */               " size " TARGET_FMT_lx " prot %c%c%c%c PID %d\n", __func__,        // 0.0
/*78  */               (int)entry, tlb->RPN, tlb->EPN, tlb->size,                         // 0.0
/*80  */               tlb->prot & PAGE_READ ? 'r' : '-',                                 // 0.0
/*82  */               tlb->prot & PAGE_WRITE ? 'w' : '-',                                // 0.0
/*84  */               tlb->prot & PAGE_EXEC ? 'x' : '-',                                 // 0.0
/*86  */               tlb->prot & PAGE_VALID ? 'v' : '-', (int)tlb->PID);                // 0.0
/*88  */     /* Invalidate new TLB (if valid) */                                          // 0.0
/*90  */     if (tlb->prot & PAGE_VALID) {                                                // 0.0
/*92  */         end = tlb->EPN + tlb->size;                                              // 0.0
/*94  */         LOG_SWTLB("%s: invalidate TLB %d start " TARGET_FMT_lx " end "           // 0.0
/*96  */                   TARGET_FMT_lx "\n", __func__, (int)entry, tlb->EPN, end);      // 0.0
/*98  */         for (page = tlb->EPN; page < end; page += TARGET_PAGE_SIZE)              // 0.0
/*100 */             tlb_flush_page(env, page);                                           // 0.0
/*102 */     }                                                                            // 0.0
/*104 */ }                                                                                // 0.0
