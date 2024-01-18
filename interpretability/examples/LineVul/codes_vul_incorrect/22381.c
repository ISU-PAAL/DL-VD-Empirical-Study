// commit message qemu@e78815a554 (target=1, prob=0.45903414, correct=False): Introduce qemu_madvise()
/*0   */ int ram_load(QEMUFile *f, void *opaque, int version_id)                     // (9) 0.04297
/*2   */ {                                                                           // (24) 0.001953
/*4   */     ram_addr_t addr;                                                        // (20) 0.01953
/*6   */     int flags;                                                              // (21) 0.01172
/*10  */     if (version_id < 3 || version_id > 4) {                                 // (16) 0.03516
/*12  */         return -EINVAL;                                                     // (19) 0.02539
/*14  */     }                                                                       // (23) 0.007812
/*18  */     do {                                                                    // (22) 0.009766
/*20  */         addr = qemu_get_be64(f);                                            // (12) 0.03906
/*24  */         flags = addr & ~TARGET_PAGE_MASK;                                   // (11) 0.04102
/*26  */         addr &= TARGET_PAGE_MASK;                                           // (15) 0.03711
/*30  */         if (flags & RAM_SAVE_FLAG_MEM_SIZE) {                               // (7) 0.04687
/*32  */             if (version_id == 3) {                                          // (14) 0.03906
/*34  */                 if (addr != ram_bytes_total()) {                            // (2) 0.05078
/*36  */                     return -EINVAL;                                         // (4) 0.04883
/*38  */                 }                                                           // (17) 0.03125
/*40  */             } else {                                                        // (18) 0.02734
/*42  */                 /* Synchronize RAM block list */                            // (8) 0.04492
/*44  */                 char id[256];                                               // (13) 0.03906
/*46  */                 ram_addr_t length;                                          // (10) 0.04297
/*48  */                 ram_addr_t total_ram_bytes = addr;                          // (1) 0.05469
/*52  */                 while (total_ram_bytes) {                                   // (5) 0.04687
/*54  */                     RAMBlock *block;                                        // (6) 0.04687
/*56  */                     uint8_t len;                                            // (3) 0.04883
/*60  */                     len = qemu_get_byte(f);                                 // (0) 0.06055
/*62  */                     qemu_get_buffer(f, (uint8_t *)id, len);                 // 0.0
/*64  */                     id[len] = 0;                                            // 0.0
/*66  */                     length = qemu_get_be64(f);                              // 0.0
/*70  */                     QLIST_FOREACH(block, &ram_list.blocks, next) {          // 0.0
/*72  */                         if (!strncmp(id, block->idstr, sizeof(id))) {       // 0.0
/*74  */                             if (block->length != length)                    // 0.0
/*76  */                                 return -EINVAL;                             // 0.0
/*78  */                             break;                                          // 0.0
/*80  */                         }                                                   // 0.0
/*82  */                     }                                                       // 0.0
/*86  */                     if (!block) {                                           // 0.0
/*88  */                         fprintf(stderr, "Unknown ramblock \"%s\", cannot "  // 0.0
/*90  */                                 "accept migration\n", id);                  // 0.0
/*92  */                         return -EINVAL;                                     // 0.0
/*94  */                     }                                                       // 0.0
/*98  */                     total_ram_bytes -= length;                              // 0.0
/*100 */                 }                                                           // 0.0
/*102 */             }                                                               // 0.0
/*104 */         }                                                                   // 0.0
/*108 */         if (flags & RAM_SAVE_FLAG_COMPRESS) {                               // 0.0
/*110 */             void *host;                                                     // 0.0
/*112 */             uint8_t ch;                                                     // 0.0
/*116 */             if (version_id == 3)                                            // 0.0
/*118 */                 host = qemu_get_ram_ptr(addr);                              // 0.0
/*120 */             else                                                            // 0.0
/*122 */                 host = host_from_stream_offset(f, addr, flags);             // 0.0
/*126 */             ch = qemu_get_byte(f);                                          // 0.0
/*128 */             memset(host, ch, TARGET_PAGE_SIZE);                             // 0.0
/*130 */ #ifndef _WIN32                                                              // 0.0
/*132 */             if (ch == 0 &&                                                  // 0.0
/*134 */                 (!kvm_enabled() || kvm_has_sync_mmu())) {                   // 0.0
/*136 */                 madvise(host, TARGET_PAGE_SIZE, MADV_DONTNEED);             // 0.0
/*138 */             }                                                               // 0.0
/*140 */ #endif                                                                      // 0.0
/*142 */         } else if (flags & RAM_SAVE_FLAG_PAGE) {                            // 0.0
/*144 */             void *host;                                                     // 0.0
/*148 */             if (version_id == 3)                                            // 0.0
/*150 */                 host = qemu_get_ram_ptr(addr);                              // 0.0
/*152 */             else                                                            // 0.0
/*154 */                 host = host_from_stream_offset(f, addr, flags);             // 0.0
/*158 */             qemu_get_buffer(f, host, TARGET_PAGE_SIZE);                     // 0.0
/*160 */         }                                                                   // 0.0
/*162 */         if (qemu_file_has_error(f)) {                                       // 0.0
/*164 */             return -EIO;                                                    // 0.0
/*166 */         }                                                                   // 0.0
/*168 */     } while (!(flags & RAM_SAVE_FLAG_EOS));                                 // 0.0
/*172 */     return 0;                                                               // 0.0
/*174 */ }                                                                           // 0.0
