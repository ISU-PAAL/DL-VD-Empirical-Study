// commit message qemu@17ad9b358b (target=0, prob=0.5258913, correct=False): Add XBZRLE to ram_save_block and ram_save_live
/*0  */ static int ram_save_block(QEMUFile *f)                                           // (12) 0.0293
/*2  */ {                                                                                // (21) 0.001953
/*4  */     RAMBlock *block = last_block;                                                // (16) 0.02344
/*6  */     ram_addr_t offset = last_offset;                                             // (13) 0.02734
/*8  */     int bytes_sent = -1;                                                         // (17) 0.02148
/*10 */     MemoryRegion *mr;                                                            // (18) 0.01562
/*14 */     if (!block)                                                                  // (19) 0.01367
/*16 */         block = QLIST_FIRST(&ram_list.blocks);                                   // (9) 0.04102
/*20 */     do {                                                                         // (20) 0.009766
/*22 */         mr = block->mr;                                                          // (14) 0.02734
/*24 */         if (memory_region_get_dirty(mr, offset, TARGET_PAGE_SIZE,                // (5) 0.05664
/*26 */                                     DIRTY_MEMORY_MIGRATION)) {                   // (1) 0.0957
/*28 */             uint8_t *p;                                                          // (11) 0.03516
/*30 */             int cont = (block == last_block) ? RAM_SAVE_FLAG_CONTINUE : 0;       // (3) 0.06836
/*34 */             memory_region_reset_dirty(mr, offset, TARGET_PAGE_SIZE,              // (4) 0.06055
/*36 */                                       DIRTY_MEMORY_MIGRATION);                   // (0) 0.09766
/*40 */             p = memory_region_get_ram_ptr(mr) + offset;                          // (6) 0.05469
/*44 */             if (is_dup_page(p)) {                                                // (8) 0.04492
/*46 */                 save_block_hdr(f, block, offset, cont, RAM_SAVE_FLAG_COMPRESS);  // (2) 0.07812
/*48 */                 qemu_put_byte(f, *p);                                            // (7) 0.05469
/*50 */                 bytes_sent = 1;                                                  // (10) 0.04102
/*52 */             } else {                                                             // (15) 0.02734
/*54 */                 save_block_hdr(f, block, offset, cont, RAM_SAVE_FLAG_PAGE);      // 0.0
/*56 */                 qemu_put_buffer(f, p, TARGET_PAGE_SIZE);                         // 0.0
/*58 */                 bytes_sent = TARGET_PAGE_SIZE;                                   // 0.0
/*60 */             }                                                                    // 0.0
/*64 */             break;                                                               // 0.0
/*66 */         }                                                                        // 0.0
/*70 */         offset += TARGET_PAGE_SIZE;                                              // 0.0
/*72 */         if (offset >= block->length) {                                           // 0.0
/*74 */             offset = 0;                                                          // 0.0
/*76 */             block = QLIST_NEXT(block, next);                                     // 0.0
/*78 */             if (!block)                                                          // 0.0
/*80 */                 block = QLIST_FIRST(&ram_list.blocks);                           // 0.0
/*82 */         }                                                                        // 0.0
/*84 */     } while (block != last_block || offset != last_offset);                      // 0.0
/*88 */     last_block = block;                                                          // 0.0
/*90 */     last_offset = offset;                                                        // 0.0
/*94 */     return bytes_sent;                                                           // 0.0
/*96 */ }                                                                                // 0.0
