// commit message qemu@d02532f08e (target=1, prob=0.16145785, correct=False): linux-user: Unlock mmap_lock when resuming guest from page_unprotect
/*0  */ int page_unprotect(target_ulong address, uintptr_t pc, void *puc)               // (6) 0.04492
/*2  */ {                                                                               // (27) 0.001953
/*4  */     unsigned int prot;                                                          // (25) 0.01367
/*6  */     PageDesc *p;                                                                // (22) 0.01563
/*8  */     target_ulong host_start, host_end, addr;                                    // (14) 0.0332
/*12 */     /* Technically this isn't safe inside a signal handler.  However we         // (12) 0.03516
/*14 */        know this only ever happens in a synchronous SEGV handler, so in         // (8) 0.04297
/*16 */        practice it seems to be ok.  */                                          // (16) 0.0293
/*18 */     mmap_lock();                                                                // (23) 0.01562
/*22 */     p = page_find(address >> TARGET_PAGE_BITS);                                 // (10) 0.03906
/*24 */     if (!p) {                                                                   // (24) 0.01562
/*26 */         mmap_unlock();                                                          // (17) 0.02539
/*28 */         return 0;                                                               // (20) 0.01953
/*30 */     }                                                                           // (26) 0.007812
/*34 */     /* if the page was really writable, then we change its                      // (15) 0.03125
/*36 */        protection back to writable */                                           // (18) 0.02344
/*38 */     if ((p->flags & PAGE_WRITE_ORG) && !(p->flags & PAGE_WRITE)) {              // (1) 0.05859
/*40 */         host_start = address & qemu_host_page_mask;                             // (7) 0.04492
/*42 */         host_end = host_start + qemu_host_page_size;                            // (4) 0.04883
/*46 */         prot = 0;                                                               // (19) 0.02148
/*48 */         for (addr = host_start ; addr < host_end ; addr += TARGET_PAGE_SIZE) {  // (0) 0.0625
/*50 */             p = page_find(addr >> TARGET_PAGE_BITS);                            // (3) 0.05469
/*52 */             p->flags |= PAGE_WRITE;                                             // (9) 0.04102
/*54 */             prot |= p->flags;                                                   // (13) 0.03516
/*58 */             /* and since the content will be modified, we must invalidate       // (5) 0.04688
/*60 */                the corresponding translated code. */                            // (11) 0.03906
/*62 */             tb_invalidate_phys_page(addr, pc, puc);                             // (2) 0.05664
/*64 */ #ifdef DEBUG_TB_CHECK                                                           // (21) 0.01563
/*66 */             tb_invalidate_check(addr);                                          // 0.0
/*68 */ #endif                                                                          // 0.0
/*70 */         }                                                                       // 0.0
/*72 */         mprotect((void *)g2h(host_start), qemu_host_page_size,                  // 0.0
/*74 */                  prot & PAGE_BITS);                                             // 0.0
/*78 */         mmap_unlock();                                                          // 0.0
/*80 */         return 1;                                                               // 0.0
/*82 */     }                                                                           // 0.0
/*84 */     mmap_unlock();                                                              // 0.0
/*86 */     return 0;                                                                   // 0.0
/*88 */ }                                                                               // 0.0
