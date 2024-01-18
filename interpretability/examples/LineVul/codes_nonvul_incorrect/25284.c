// commit message qemu@b3be28969b (target=0, prob=0.6362198, correct=False): qemu-file: Fix qemu_put_compression_data flaw
/*0   */ static int ram_save_compressed_page(QEMUFile *f, PageSearchStatus *pss,       // (4) 0.04883
/*2   */                                     bool last_stage,                          // (2) 0.07813
/*4   */                                     uint64_t *bytes_transferred)              // (1) 0.08789
/*6   */ {                                                                             // (25) 0.001953
/*8   */     int pages = -1;                                                           // (21) 0.01758
/*10  */     uint64_t bytes_xmit;                                                      // (15) 0.02344
/*12  */     uint8_t *p;                                                               // (19) 0.01953
/*14  */     int ret;                                                                  // (22) 0.01172
/*16  */     RAMBlock *block = pss->block;                                             // (14) 0.02539
/*18  */     ram_addr_t offset = pss->offset;                                          // (12) 0.0293
/*22  */     p = block->host + offset;                                                 // (16) 0.02148
/*26  */     bytes_xmit = 0;                                                           // (20) 0.01953
/*28  */     ret = ram_control_save_page(f, block->offset,                             // (10) 0.03711
/*30  */                                 offset, TARGET_PAGE_SIZE, &bytes_xmit);       // (0) 0.0918
/*32  */     if (bytes_xmit) {                                                         // (17) 0.02148
/*34  */         *bytes_transferred += bytes_xmit;                                     // (11) 0.03516
/*36  */         pages = 1;                                                            // (18) 0.02148
/*38  */     }                                                                         // (23) 0.007812
/*40  */     if (block == last_sent_block) {                                           // (13) 0.02734
/*42  */         offset |= RAM_SAVE_FLAG_CONTINUE;                                     // (8) 0.04102
/*44  */     }                                                                         // (24) 0.007812
/*46  */     if (ret != RAM_SAVE_CONTROL_NOT_SUPP) {                                   // (7) 0.04297
/*48  */         if (ret != RAM_SAVE_CONTROL_DELAYED) {                                // (3) 0.05078
/*50  */             if (bytes_xmit > 0) {                                             // (9) 0.04102
/*52  */                 acct_info.norm_pages++;                                       // (5) 0.04688
/*54  */             } else if (bytes_xmit == 0) {                                     // (6) 0.04492
/*56  */                 acct_info.dup_pages++;                                        // 0.0
/*58  */             }                                                                 // 0.0
/*60  */         }                                                                     // 0.0
/*62  */     } else {                                                                  // 0.0
/*64  */         /* When starting the process of a new block, the first page of        // 0.0
/*66  */          * the block should be sent out before other pages in the same        // 0.0
/*68  */          * block, and all the pages in last block should have been sent       // 0.0
/*70  */          * out, keeping this order is important, because the 'cont' flag      // 0.0
/*72  */          * is used to avoid resending the block name.                         // 0.0
/*74  */          */                                                                   // 0.0
/*76  */         if (block != last_sent_block) {                                       // 0.0
/*78  */             flush_compressed_data(f);                                         // 0.0
/*80  */             pages = save_zero_page(f, block, offset, p, bytes_transferred);   // 0.0
/*82  */             if (pages == -1) {                                                // 0.0
/*84  */                 set_compress_params(&comp_param[0], block, offset);           // 0.0
/*86  */                 /* Use the qemu thread to compress the data to make sure the  // 0.0
/*88  */                  * first page is sent out before other pages                  // 0.0
/*90  */                  */                                                           // 0.0
/*92  */                 bytes_xmit = do_compress_ram_page(&comp_param[0]);            // 0.0
/*94  */                 acct_info.norm_pages++;                                       // 0.0
/*96  */                 qemu_put_qemu_file(f, comp_param[0].file);                    // 0.0
/*98  */                 *bytes_transferred += bytes_xmit;                             // 0.0
/*100 */                 pages = 1;                                                    // 0.0
/*102 */             }                                                                 // 0.0
/*104 */         } else {                                                              // 0.0
/*106 */             pages = save_zero_page(f, block, offset, p, bytes_transferred);   // 0.0
/*108 */             if (pages == -1) {                                                // 0.0
/*110 */                 pages = compress_page_with_multi_thread(f, block, offset,     // 0.0
/*112 */                                                         bytes_transferred);   // 0.0
/*114 */             }                                                                 // 0.0
/*116 */         }                                                                     // 0.0
/*118 */     }                                                                         // 0.0
/*122 */     return pages;                                                             // 0.0
/*124 */ }                                                                             // 0.0
