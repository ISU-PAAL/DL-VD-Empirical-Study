// commit message qemu@3f2cbf0d1a (target=1, prob=0.03510333, correct=False): target-i386: Mask NX bit from cpu_get_phys_page_debug result
/*0   */ target_phys_addr_t cpu_get_phys_page_debug(CPUState *env, target_ulong addr)              // (1) 0.05469
/*2   */ {                                                                                         // (22) 0.001953
/*4   */     target_ulong pde_addr, pte_addr;                                                      // (15) 0.0332
/*6   */     uint64_t pte;                                                                         // (19) 0.01953
/*8   */     target_phys_addr_t paddr;                                                             // (17) 0.02539
/*10  */     uint32_t page_offset;                                                                 // (18) 0.02148
/*12  */     int page_size;                                                                        // (21) 0.01562
/*16  */     if (env->cr[4] & CR4_PAE_MASK) {                                                      // (8) 0.04297
/*18  */         target_ulong pdpe_addr;                                                           // (16) 0.0332
/*20  */         uint64_t pde, pdpe;                                                               // (12) 0.03516
/*24  */ #ifdef TARGET_X86_64                                                                      // (20) 0.01953
/*26  */         if (env->hflags & HF_LMA_MASK) {                                                  // (7) 0.04492
/*28  */             uint64_t pml4e_addr, pml4e;                                                   // (4) 0.05273
/*30  */             int32_t sext;                                                                 // (13) 0.03516
/*34  */             /* test virtual address sign extension */                                     // (14) 0.03516
/*36  */             sext = (int64_t)addr >> 47;                                                   // (5) 0.04687
/*38  */             if (sext != 0 && sext != -1)                                                  // (6) 0.04687
/*40  */                 return -1;                                                                // (11) 0.03711
/*44  */             pml4e_addr = ((env->cr[3] & ~0xfff) + (((addr >> 39) & 0x1ff) << 3)) &        // (0) 0.09375
/*46  */                 env->a20_mask;                                                            // (9) 0.04297
/*48  */             pml4e = ldq_phys(pml4e_addr);                                                 // (2) 0.05469
/*50  */             if (!(pml4e & PG_PRESENT_MASK))                                               // (3) 0.05273
/*52  */                 return -1;                                                                // (10) 0.03711
/*56  */             pdpe_addr = ((pml4e & ~0xfff) + (((addr >> 30) & 0x1ff) << 3)) &              // 0.0
/*58  */                 env->a20_mask;                                                            // 0.0
/*60  */             pdpe = ldq_phys(pdpe_addr);                                                   // 0.0
/*62  */             if (!(pdpe & PG_PRESENT_MASK))                                                // 0.0
/*64  */                 return -1;                                                                // 0.0
/*66  */         } else                                                                            // 0.0
/*68  */ #endif                                                                                    // 0.0
/*70  */         {                                                                                 // 0.0
/*72  */             pdpe_addr = ((env->cr[3] & ~0x1f) + ((addr >> 27) & 0x18)) &                  // 0.0
/*74  */                 env->a20_mask;                                                            // 0.0
/*76  */             pdpe = ldq_phys(pdpe_addr);                                                   // 0.0
/*78  */             if (!(pdpe & PG_PRESENT_MASK))                                                // 0.0
/*80  */                 return -1;                                                                // 0.0
/*82  */         }                                                                                 // 0.0
/*86  */         pde_addr = ((pdpe & ~0xfff) + (((addr >> 21) & 0x1ff) << 3)) &                    // 0.0
/*88  */             env->a20_mask;                                                                // 0.0
/*90  */         pde = ldq_phys(pde_addr);                                                         // 0.0
/*92  */         if (!(pde & PG_PRESENT_MASK)) {                                                   // 0.0
/*94  */             return -1;                                                                    // 0.0
/*96  */         }                                                                                 // 0.0
/*98  */         if (pde & PG_PSE_MASK) {                                                          // 0.0
/*100 */             /* 2 MB page */                                                               // 0.0
/*102 */             page_size = 2048 * 1024;                                                      // 0.0
/*104 */             pte = pde & ~( (page_size - 1) & ~0xfff); /* align to page_size */            // 0.0
/*106 */         } else {                                                                          // 0.0
/*108 */             /* 4 KB page */                                                               // 0.0
/*110 */             pte_addr = ((pde & ~0xfff) + (((addr >> 12) & 0x1ff) << 3)) &                 // 0.0
/*112 */                 env->a20_mask;                                                            // 0.0
/*114 */             page_size = 4096;                                                             // 0.0
/*116 */             pte = ldq_phys(pte_addr);                                                     // 0.0
/*118 */         }                                                                                 // 0.0
/*120 */         if (!(pte & PG_PRESENT_MASK))                                                     // 0.0
/*122 */             return -1;                                                                    // 0.0
/*124 */     } else {                                                                              // 0.0
/*126 */         uint32_t pde;                                                                     // 0.0
/*130 */         if (!(env->cr[0] & CR0_PG_MASK)) {                                                // 0.0
/*132 */             pte = addr;                                                                   // 0.0
/*134 */             page_size = 4096;                                                             // 0.0
/*136 */         } else {                                                                          // 0.0
/*138 */             /* page directory entry */                                                    // 0.0
/*140 */             pde_addr = ((env->cr[3] & ~0xfff) + ((addr >> 20) & 0xffc)) & env->a20_mask;  // 0.0
/*142 */             pde = ldl_phys(pde_addr);                                                     // 0.0
/*144 */             if (!(pde & PG_PRESENT_MASK))                                                 // 0.0
/*146 */                 return -1;                                                                // 0.0
/*148 */             if ((pde & PG_PSE_MASK) && (env->cr[4] & CR4_PSE_MASK)) {                     // 0.0
/*150 */                 pte = pde & ~0x003ff000; /* align to 4MB */                               // 0.0
/*152 */                 page_size = 4096 * 1024;                                                  // 0.0
/*154 */             } else {                                                                      // 0.0
/*156 */                 /* page directory entry */                                                // 0.0
/*158 */                 pte_addr = ((pde & ~0xfff) + ((addr >> 10) & 0xffc)) & env->a20_mask;     // 0.0
/*160 */                 pte = ldl_phys(pte_addr);                                                 // 0.0
/*162 */                 if (!(pte & PG_PRESENT_MASK))                                             // 0.0
/*164 */                     return -1;                                                            // 0.0
/*166 */                 page_size = 4096;                                                         // 0.0
/*168 */             }                                                                             // 0.0
/*170 */         }                                                                                 // 0.0
/*172 */         pte = pte & env->a20_mask;                                                        // 0.0
/*174 */     }                                                                                     // 0.0
/*178 */     page_offset = (addr & TARGET_PAGE_MASK) & (page_size - 1);                            // 0.0
/*180 */     paddr = (pte & TARGET_PAGE_MASK) + page_offset;                                       // 0.0
/*182 */     return paddr;                                                                         // 0.0
/*184 */ }                                                                                         // 0.0
