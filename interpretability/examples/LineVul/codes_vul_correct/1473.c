// commit message qemu@51b0c6065a (target=1, prob=0.55561244, correct=True): fix crash in migration, 32-bit userspace on 64-bit host
/*0  */ static int kvm_physical_sync_dirty_bitmap(target_phys_addr_t start_addr,             // (6) 0.04883
/*2  */                                           target_phys_addr_t end_addr)               // (0) 0.1016
/*4  */ {                                                                                    // (23) 0.001953
/*6  */     KVMState *s = kvm_state;                                                         // (11) 0.02734
/*8  */     unsigned long size, allocated_size = 0;                                          // (14) 0.02539
/*10 */     KVMDirtyLog d;                                                                   // (18) 0.01953
/*12 */     KVMSlot *mem;                                                                    // (19) 0.01953
/*14 */     int ret = 0;                                                                     // (20) 0.01562
/*18 */     d.dirty_bitmap = NULL;                                                           // (17) 0.02344
/*20 */     while (start_addr < end_addr) {                                                  // (12) 0.02734
/*22 */         mem = kvm_lookup_overlapping_slot(s, start_addr, end_addr);                  // (4) 0.06055
/*24 */         if (mem == NULL) {                                                           // (13) 0.02734
/*26 */             break;                                                                   // (15) 0.02539
/*28 */         }                                                                            // (21) 0.01562
/*32 */         size = ALIGN(((mem->memory_size) >> TARGET_PAGE_BITS), HOST_LONG_BITS) / 8;  // (1) 0.08008
/*34 */         if (!d.dirty_bitmap) {                                                       // (9) 0.0332
/*36 */             d.dirty_bitmap = qemu_malloc(size);                                      // (5) 0.05273
/*38 */         } else if (size > allocated_size) {                                          // (8) 0.03516
/*40 */             d.dirty_bitmap = qemu_realloc(d.dirty_bitmap, size);                     // (3) 0.06641
/*42 */         }                                                                            // (22) 0.01562
/*44 */         allocated_size = size;                                                       // (16) 0.02539
/*46 */         memset(d.dirty_bitmap, 0, allocated_size);                                   // (7) 0.04492
/*50 */         d.slot = mem->slot;                                                          // (10) 0.0293
/*54 */         if (kvm_vm_ioctl(s, KVM_GET_DIRTY_LOG, &d) == -1) {                          // (2) 0.07227
/*56 */             DPRINTF("ioctl failed %d\n", errno);                                     // 0.0
/*58 */             ret = -1;                                                                // 0.0
/*60 */             break;                                                                   // 0.0
/*62 */         }                                                                            // 0.0
/*66 */         kvm_get_dirty_pages_log_range(mem->start_addr, d.dirty_bitmap,               // 0.0
/*68 */                                       mem->start_addr, mem->memory_size);            // 0.0
/*70 */         start_addr = mem->start_addr + mem->memory_size;                             // 0.0
/*72 */     }                                                                                // 0.0
/*74 */     qemu_free(d.dirty_bitmap);                                                       // 0.0
/*78 */     return ret;                                                                      // 0.0
/*80 */ }                                                                                    // 0.0
