// commit message qemu@e568f9df08 (target=0, prob=0.6335886, correct=False): linux-user: Allow -R values up to 0xffff0000 for 32-bit ARM guests
/*0  */ static int validate_guest_space(unsigned long guest_base,                    // (13) 0.0293
/*2  */                                 unsigned long guest_size)                    // (1) 0.07227
/*4  */ {                                                                            // (26) 0.001953
/*6  */     unsigned long real_start, test_page_addr;                                // (14) 0.0293
/*10 */     /* We need to check that we can force a fault on access to the           // (8) 0.03516
/*12 */      * commpage at 0xffff0fxx                                                // (16) 0.02734
/*14 */      */                                                                      // (22) 0.009766
/*16 */     test_page_addr = guest_base + (0xffff0f00 & qemu_host_page_mask);        // (3) 0.06055
/*20 */     /* If the commpage lies within the already allocated guest space,        // (10) 0.03125
/*22 */      * then there is no way we can allocate it.                              // (15) 0.0293
/*24 */      */                                                                      // (23) 0.009766
/*26 */     if (test_page_addr >= guest_base                                         // (18) 0.02734
/*28 */         && test_page_addr <= (guest_base + guest_size)) {                    // (6) 0.04883
/*30 */         return -1;                                                           // (20) 0.02148
/*32 */     }                                                                        // (24) 0.007813
/*36 */     /* Note it needs to be writeable to let us initialise it */              // (9) 0.03516
/*38 */     real_start = (unsigned long)                                             // (19) 0.02148
/*40 */                  mmap((void *)test_page_addr, qemu_host_page_size,           // (2) 0.07227
/*42 */                      PROT_READ | PROT_WRITE,                                 // (4) 0.05664
/*44 */                      MAP_ANONYMOUS | MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);    // (0) 0.08789
/*48 */     /* If we can't map it then try another address */                        // (12) 0.0293
/*50 */     if (real_start == -1ul) {                                                // (17) 0.02734
/*52 */         return 0;                                                            // (21) 0.01953
/*54 */     }                                                                        // (25) 0.007813
/*58 */     if (real_start != test_page_addr) {                                      // (11) 0.03125
/*60 */         /* OS didn't put the page where we asked - unmap and reject */       // (7) 0.04492
/*62 */         munmap((void *)real_start, qemu_host_page_size);                     // (5) 0.05078
/*64 */         return 0;                                                            // 0.0
/*66 */     }                                                                        // 0.0
/*70 */     /* Leave the page mapped                                                 // 0.0
/*72 */      * Populate it (mmap should have left it all 0'd)                        // 0.0
/*74 */      */                                                                      // 0.0
/*78 */     /* Kernel helper versions */                                             // 0.0
/*80 */     __put_user(5, (uint32_t *)g2h(0xffff0ffcul));                            // 0.0
/*84 */     /* Now it's populated make it RO */                                      // 0.0
/*86 */     if (mprotect((void *)test_page_addr, qemu_host_page_size, PROT_READ)) {  // 0.0
/*88 */         perror("Protecting guest commpage");                                 // 0.0
/*90 */         exit(-1);                                                            // 0.0
/*92 */     }                                                                        // 0.0
/*96 */     return 1; /* All good */                                                 // 0.0
/*98 */ }                                                                            // 0.0
