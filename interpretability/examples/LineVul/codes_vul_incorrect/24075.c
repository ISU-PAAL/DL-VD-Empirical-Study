// commit message qemu@f3ced3c592 (target=1, prob=0.17343612, correct=False): tcg: consistently access cpu->tb_jmp_cache atomically
/*0  */ void tb_flush_jmp_cache(CPUState *cpu, target_ulong addr)             // (3) 0.1019
/*2  */ {                                                                     // (10) 0.00463
/*4  */     unsigned int i;                                                   // (9) 0.03241
/*8  */     /* Discard jump cache entries for any tb which might potentially  // (7) 0.07407
/*10 */        overlap the flushed page.  */                                  // (8) 0.06019
/*12 */     i = tb_jmp_cache_hash_page(addr - TARGET_PAGE_SIZE);              // (0) 0.125
/*14 */     memset(&cpu->tb_jmp_cache[i], 0,                                  // (4) 0.09259
/*16 */            TB_JMP_PAGE_SIZE * sizeof(TranslationBlock *));            // (1) 0.1204
/*20 */     i = tb_jmp_cache_hash_page(addr);                                 // (6) 0.08796
/*22 */     memset(&cpu->tb_jmp_cache[i], 0,                                  // (5) 0.09259
/*24 */            TB_JMP_PAGE_SIZE * sizeof(TranslationBlock *));            // (2) 0.1204
/*26 */ }                                                                     // (11) 0.00463
