// commit message qemu@3435f39513 (target=0, prob=0.4376626, correct=True): exec: Reduce ifdeffery around -mem-path
/*0   */ void qemu_ram_remap(ram_addr_t addr, ram_addr_t length)                         // (5) 0.04688
/*2   */ {                                                                               // (25) 0.001953
/*4   */     RAMBlock *block;                                                            // (21) 0.01563
/*6   */     ram_addr_t offset;                                                          // (19) 0.01953
/*8   */     int flags;                                                                  // (22) 0.01172
/*10  */     void *area, *vaddr;                                                         // (18) 0.02148
/*14  */     QTAILQ_FOREACH(block, &ram_list.blocks, next) {                             // (6) 0.04492
/*16  */         offset = addr - block->offset;                                          // (16) 0.0293
/*18  */         if (offset < block->length) {                                           // (14) 0.03125
/*20  */             vaddr = block->host + offset;                                       // (11) 0.03906
/*22  */             if (block->flags & RAM_PREALLOC_MASK) {                             // (3) 0.05273
/*24  */                 ;                                                               // (15) 0.03125
/*26  */             } else if (xen_enabled()) {                                         // (10) 0.04102
/*28  */                 abort();                                                        // (13) 0.0332
/*30  */             } else {                                                            // (17) 0.02734
/*32  */                 flags = MAP_FIXED;                                              // (8) 0.04297
/*34  */                 munmap(vaddr, length);                                          // (7) 0.04492
/*36  */                 if (mem_path) {                                                 // (9) 0.04297
/*38  */ #if defined(__linux__) && !defined(TARGET_S390X)                                // (12) 0.03711
/*40  */                     if (block->fd) {                                            // (4) 0.05078
/*42  */ #ifdef MAP_POPULATE                                                             // (20) 0.01758
/*44  */                         flags |= mem_prealloc ? MAP_POPULATE | MAP_SHARED :     // (0) 0.08594
/*46  */                             MAP_PRIVATE;                                        // (1) 0.06445
/*48  */ #else                                                                           // (23) 0.003906
/*50  */                         flags |= MAP_PRIVATE;                                   // (2) 0.0625
/*52  */ #endif                                                                          // (24) 0.003906
/*54  */                         area = mmap(vaddr, length, PROT_READ | PROT_WRITE,      // 0.0
/*56  */                                     flags, block->fd, offset);                  // 0.0
/*58  */                     } else {                                                    // 0.0
/*60  */                         flags |= MAP_PRIVATE | MAP_ANONYMOUS;                   // 0.0
/*62  */                         area = mmap(vaddr, length, PROT_READ | PROT_WRITE,      // 0.0
/*64  */                                     flags, -1, 0);                              // 0.0
/*66  */                     }                                                           // 0.0
/*68  */ #else                                                                           // 0.0
/*70  */                     abort();                                                    // 0.0
/*72  */ #endif                                                                          // 0.0
/*74  */                 } else {                                                        // 0.0
/*76  */ #if defined(TARGET_S390X) && defined(CONFIG_KVM)                                // 0.0
/*78  */                     flags |= MAP_SHARED | MAP_ANONYMOUS;                        // 0.0
/*80  */                     area = mmap(vaddr, length, PROT_EXEC|PROT_READ|PROT_WRITE,  // 0.0
/*82  */                                 flags, -1, 0);                                  // 0.0
/*84  */ #else                                                                           // 0.0
/*86  */                     flags |= MAP_PRIVATE | MAP_ANONYMOUS;                       // 0.0
/*88  */                     area = mmap(vaddr, length, PROT_READ | PROT_WRITE,          // 0.0
/*90  */                                 flags, -1, 0);                                  // 0.0
/*92  */ #endif                                                                          // 0.0
/*94  */                 }                                                               // 0.0
/*96  */                 if (area != vaddr) {                                            // 0.0
/*98  */                     fprintf(stderr, "Could not remap addr: "                    // 0.0
/*100 */                             RAM_ADDR_FMT "@" RAM_ADDR_FMT "\n",                 // 0.0
/*102 */                             length, addr);                                      // 0.0
/*104 */                     exit(1);                                                    // 0.0
/*106 */                 }                                                               // 0.0
/*108 */                 memory_try_enable_merging(vaddr, length);                       // 0.0
/*110 */                 qemu_ram_setup_dump(vaddr, length);                             // 0.0
/*112 */             }                                                                   // 0.0
/*114 */             return;                                                             // 0.0
/*116 */         }                                                                       // 0.0
/*118 */     }                                                                           // 0.0
/*120 */ }                                                                               // 0.0
