// commit message qemu@a426e12217 (target=0, prob=0.39299536, correct=True): kvm: Fix coding style violations
/*0   */ static void kvm_set_phys_mem(target_phys_addr_t start_addr,                      // (6) 0.04297
/*2   */ 			     ram_addr_t size,                                                         // (17) 0.02734
/*4   */ 			     ram_addr_t phys_offset)                                                  // (11) 0.03125
/*6   */ {                                                                                // (27) 0.001953
/*8   */     KVMState *s = kvm_state;                                                     // (14) 0.02734
/*10  */     ram_addr_t flags = phys_offset & ~TARGET_PAGE_MASK;                          // (4) 0.04687
/*12  */     KVMSlot *mem, old;                                                           // (20) 0.02344
/*14  */     int err;                                                                     // (26) 0.01172
/*18  */     /* kvm works in page size chunks, but the function may be called             // (9) 0.03516
/*20  */        with sub-page size and unaligned start address. */                        // (10) 0.03516
/*22  */     size = TARGET_PAGE_ALIGN(size);                                              // (13) 0.03125
/*24  */     start_addr = TARGET_PAGE_ALIGN(start_addr);                                  // (8) 0.03906
/*28  */     /* KVM does not support read-only slots */                                   // (15) 0.02734
/*30  */     phys_offset &= ~IO_MEM_ROM;                                                  // (12) 0.03125
/*34  */     while (1) {                                                                  // (23) 0.01563
/*36  */         mem = kvm_lookup_overlapping_slot(s, start_addr, start_addr + size);     // (0) 0.06445
/*38  */         if (!mem) {                                                              // (22) 0.02344
/*40  */             break;                                                               // (18) 0.02539
/*42  */         }                                                                        // (24) 0.01562
/*46  */         if (flags < IO_MEM_UNASSIGNED && start_addr >= mem->start_addr &&        // (2) 0.06055
/*48  */             (start_addr + size <= mem->start_addr + mem->memory_size) &&         // (3) 0.06055
/*50  */             (phys_offset - start_addr == mem->phys_offset - mem->start_addr)) {  // (1) 0.06445
/*52  */             /* The new slot fits into the existing one and comes with            // (5) 0.04492
/*54  */              * identical parameters - nothing to be done. */                     // (7) 0.04297
/*56  */             return;                                                              // (19) 0.02539
/*58  */         }                                                                        // (25) 0.01562
/*62  */         old = *mem;                                                              // (21) 0.02344
/*66  */         /* unregister the overlapping slot */                                    // (16) 0.02734
/*68  */         mem->memory_size = 0;                                                    // 0.0
/*70  */         err = kvm_set_user_memory_region(s, mem);                                // 0.0
/*72  */         if (err) {                                                               // 0.0
/*74  */             fprintf(stderr, "%s: error unregistering overlapping slot: %s\n",    // 0.0
/*76  */                     __func__, strerror(-err));                                   // 0.0
/*78  */             abort();                                                             // 0.0
/*80  */         }                                                                        // 0.0
/*84  */         /* Workaround for older KVM versions: we can't join slots, even not by   // 0.0
/*86  */          * unregistering the previous ones and then registering the larger       // 0.0
/*88  */          * slot. We have to maintain the existing fragmentation. Sigh.           // 0.0
/*90  */          *                                                                       // 0.0
/*92  */          * This workaround assumes that the new slot starts at the same          // 0.0
/*94  */          * address as the first existing one. If not or if some overlapping      // 0.0
/*96  */          * slot comes around later, we will fail (not seen in practice so far)   // 0.0
/*98  */          * - and actually require a recent KVM version. */                       // 0.0
/*100 */         if (s->broken_set_mem_region &&                                          // 0.0
/*102 */             old.start_addr == start_addr && old.memory_size < size &&            // 0.0
/*104 */             flags < IO_MEM_UNASSIGNED) {                                         // 0.0
/*106 */             mem = kvm_alloc_slot(s);                                             // 0.0
/*108 */             mem->memory_size = old.memory_size;                                  // 0.0
/*110 */             mem->start_addr = old.start_addr;                                    // 0.0
/*112 */             mem->phys_offset = old.phys_offset;                                  // 0.0
/*114 */             mem->flags = 0;                                                      // 0.0
/*118 */             err = kvm_set_user_memory_region(s, mem);                            // 0.0
/*120 */             if (err) {                                                           // 0.0
/*122 */                 fprintf(stderr, "%s: error updating slot: %s\n", __func__,       // 0.0
/*124 */                         strerror(-err));                                         // 0.0
/*126 */                 abort();                                                         // 0.0
/*128 */             }                                                                    // 0.0
/*132 */             start_addr += old.memory_size;                                       // 0.0
/*134 */             phys_offset += old.memory_size;                                      // 0.0
/*136 */             size -= old.memory_size;                                             // 0.0
/*138 */             continue;                                                            // 0.0
/*140 */         }                                                                        // 0.0
/*144 */         /* register prefix slot */                                               // 0.0
/*146 */         if (old.start_addr < start_addr) {                                       // 0.0
/*148 */             mem = kvm_alloc_slot(s);                                             // 0.0
/*150 */             mem->memory_size = start_addr - old.start_addr;                      // 0.0
/*152 */             mem->start_addr = old.start_addr;                                    // 0.0
/*154 */             mem->phys_offset = old.phys_offset;                                  // 0.0
/*156 */             mem->flags = 0;                                                      // 0.0
/*160 */             err = kvm_set_user_memory_region(s, mem);                            // 0.0
/*162 */             if (err) {                                                           // 0.0
/*164 */                 fprintf(stderr, "%s: error registering prefix slot: %s\n",       // 0.0
/*166 */                         __func__, strerror(-err));                               // 0.0
/*168 */                 abort();                                                         // 0.0
/*170 */             }                                                                    // 0.0
/*172 */         }                                                                        // 0.0
/*176 */         /* register suffix slot */                                               // 0.0
/*178 */         if (old.start_addr + old.memory_size > start_addr + size) {              // 0.0
/*180 */             ram_addr_t size_delta;                                               // 0.0
/*184 */             mem = kvm_alloc_slot(s);                                             // 0.0
/*186 */             mem->start_addr = start_addr + size;                                 // 0.0
/*188 */             size_delta = mem->start_addr - old.start_addr;                       // 0.0
/*190 */             mem->memory_size = old.memory_size - size_delta;                     // 0.0
/*192 */             mem->phys_offset = old.phys_offset + size_delta;                     // 0.0
/*194 */             mem->flags = 0;                                                      // 0.0
/*198 */             err = kvm_set_user_memory_region(s, mem);                            // 0.0
/*200 */             if (err) {                                                           // 0.0
/*202 */                 fprintf(stderr, "%s: error registering suffix slot: %s\n",       // 0.0
/*204 */                         __func__, strerror(-err));                               // 0.0
/*206 */                 abort();                                                         // 0.0
/*208 */             }                                                                    // 0.0
/*210 */         }                                                                        // 0.0
/*212 */     }                                                                            // 0.0
/*216 */     /* in case the KVM bug workaround already "consumed" the new slot */         // 0.0
/*218 */     if (!size)                                                                   // 0.0
/*220 */         return;                                                                  // 0.0
/*224 */     /* KVM does not need to know about this memory */                            // 0.0
/*226 */     if (flags >= IO_MEM_UNASSIGNED)                                              // 0.0
/*228 */         return;                                                                  // 0.0
/*232 */     mem = kvm_alloc_slot(s);                                                     // 0.0
/*234 */     mem->memory_size = size;                                                     // 0.0
/*236 */     mem->start_addr = start_addr;                                                // 0.0
/*238 */     mem->phys_offset = phys_offset;                                              // 0.0
/*240 */     mem->flags = 0;                                                              // 0.0
/*244 */     err = kvm_set_user_memory_region(s, mem);                                    // 0.0
/*246 */     if (err) {                                                                   // 0.0
/*248 */         fprintf(stderr, "%s: error registering slot: %s\n", __func__,            // 0.0
/*250 */                 strerror(-err));                                                 // 0.0
/*252 */         abort();                                                                 // 0.0
/*254 */     }                                                                            // 0.0
/*256 */ }                                                                                // 0.0
