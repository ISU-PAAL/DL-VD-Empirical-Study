// commit message qemu@f46e9a0b99 (target=0, prob=0.33077928, correct=True): target-ppc: Confirm That .bss Pages Are Valid
/*0  */ static void zero_bss(abi_ulong elf_bss, abi_ulong last_bss, int prot)           // (2) 0.05664
/*2  */ {                                                                               // (20) 0.001953
/*4  */     uintptr_t host_start, host_map_start, host_end;                             // (12) 0.04102
/*8  */     last_bss = TARGET_PAGE_ALIGN(last_bss);                                     // (7) 0.04297
/*12 */     /* ??? There is confusion between qemu_real_host_page_size and              // (11) 0.04102
/*14 */        qemu_host_page_size here and elsewhere in target_mmap, which             // (4) 0.04883
/*16 */        may lead to the end of the data section mapping from the file            // (15) 0.03711
/*18 */        not being mapped.  At least there was an explicit test and               // (16) 0.03711
/*20 */        comment for that here, suggesting that "the file size must               // (18) 0.03516
/*22 */        be known".  The comment probably pre-dates the introduction              // (17) 0.03516
/*24 */        of the fstat system call in target_mmap which does in fact               // (10) 0.04102
/*26 */        find out the size.  What isn't clear is if the workaround                // (13) 0.03906
/*28 */        here is still actually needed.  For now, continue with it,               // (14) 0.03906
/*30 */        but merge it with the "normal" mmap that would allocate the bss.  */     // (5) 0.04883
/*34 */     host_start = (uintptr_t) g2h(elf_bss);                                      // (8) 0.04297
/*36 */     host_end = (uintptr_t) g2h(last_bss);                                       // (9) 0.04297
/*38 */     host_map_start = (host_start + qemu_real_host_page_size - 1);               // (3) 0.05469
/*40 */     host_map_start &= -qemu_real_host_page_size;                                // (6) 0.04492
/*44 */     if (host_map_start < host_end) {                                            // (19) 0.03125
/*46 */         void *p = mmap((void *)host_map_start, host_end - host_map_start,       // (1) 0.0625
/*48 */                        prot, MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);   // (0) 0.0918
/*50 */         if (p == MAP_FAILED) {                                                  // 0.0
/*52 */             perror("cannot mmap brk");                                          // 0.0
/*54 */             exit(-1);                                                           // 0.0
/*56 */         }                                                                       // 0.0
/*60 */         /* Since we didn't use target_mmap, make sure to record                 // 0.0
/*62 */            the validity of the pages with qemu.  */                             // 0.0
/*64 */         page_set_flags(elf_bss & TARGET_PAGE_MASK, last_bss, prot|PAGE_VALID);  // 0.0
/*66 */     }                                                                           // 0.0
/*70 */     if (host_start < host_map_start) {                                          // 0.0
/*72 */         memset((void *)host_start, 0, host_map_start - host_start);             // 0.0
/*74 */     }                                                                           // 0.0
/*76 */ }                                                                               // 0.0
