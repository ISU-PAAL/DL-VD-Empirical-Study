// commit message qemu@41a2b9596c (target=0, prob=0.26157546, correct=True): IDE SEEK_STAT flag
/*0   */ static void ide_atapi_cmd_reply_end(IDEState *s)                                     // (9) 0.03516
/*2   */ {                                                                                    // (26) 0.001953
/*4   */     int byte_count_limit, size, ret;                                                 // (18) 0.02734
/*6   */ #ifdef DEBUG_IDE_ATAPI                                                               // (21) 0.01758
/*8   */     printf("reply: tx_size=%d elem_tx_size=%d index=%d\n",                           // (3) 0.05664
/*10  */            s->packet_transfer_size,                                                  // (8) 0.03711
/*12  */            s->elementary_transfer_size,                                              // (7) 0.03711
/*14  */            s->io_buffer_index);                                                      // (10) 0.03516
/*16  */ #endif                                                                               // (25) 0.003906
/*18  */     if (s->packet_transfer_size <= 0) {                                              // (13) 0.0332
/*20  */         /* end of transfer */                                                        // (19) 0.02344
/*22  */         ide_transfer_stop(s);                                                        // (17) 0.0293
/*24  */         s->status = READY_STAT;                                                      // (16) 0.03125
/*26  */         s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;  // (1) 0.08203
/*28  */         ide_set_irq(s);                                                              // (15) 0.03125
/*30  */ #ifdef DEBUG_IDE_ATAPI                                                               // (22) 0.01758
/*32  */         printf("status=0x%x\n", s->status);                                          // (6) 0.04297
/*34  */ #endif                                                                               // (24) 0.003906
/*36  */     } else {                                                                         // (23) 0.01172
/*38  */         /* see if a new sector must be read */                                       // (12) 0.0332
/*40  */         if (s->lba != -1 && s->io_buffer_index >= s->cd_sector_size) {               // (2) 0.06641
/*42  */             ret = cd_read_sector(s->bs, s->lba, s->io_buffer, s->cd_sector_size);    // (0) 0.08203
/*44  */             if (ret < 0) {                                                           // (11) 0.03516
/*46  */                 ide_transfer_stop(s);                                                // (5) 0.04492
/*48  */                 ide_atapi_io_error(s, ret);                                          // (4) 0.05469
/*50  */                 return;                                                              // (14) 0.0332
/*52  */             }                                                                        // (20) 0.02344
/*54  */             s->lba++;                                                                // 0.0
/*56  */             s->io_buffer_index = 0;                                                  // 0.0
/*58  */         }                                                                            // 0.0
/*60  */         if (s->elementary_transfer_size > 0) {                                       // 0.0
/*62  */             /* there are some data left to transmit in this elementary               // 0.0
/*64  */                transfer */                                                           // 0.0
/*66  */             size = s->cd_sector_size - s->io_buffer_index;                           // 0.0
/*68  */             if (size > s->elementary_transfer_size)                                  // 0.0
/*70  */                 size = s->elementary_transfer_size;                                  // 0.0
/*72  */             ide_transfer_start(s, s->io_buffer + s->io_buffer_index,                 // 0.0
/*74  */                                size, ide_atapi_cmd_reply_end);                       // 0.0
/*76  */             s->packet_transfer_size -= size;                                         // 0.0
/*78  */             s->elementary_transfer_size -= size;                                     // 0.0
/*80  */             s->io_buffer_index += size;                                              // 0.0
/*82  */         } else {                                                                     // 0.0
/*84  */             /* a new transfer is needed */                                           // 0.0
/*86  */             s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO;                    // 0.0
/*88  */             byte_count_limit = s->lcyl | (s->hcyl << 8);                             // 0.0
/*90  */ #ifdef DEBUG_IDE_ATAPI                                                               // 0.0
/*92  */             printf("byte_count_limit=%d\n", byte_count_limit);                       // 0.0
/*94  */ #endif                                                                               // 0.0
/*96  */             if (byte_count_limit == 0xffff)                                          // 0.0
/*98  */                 byte_count_limit--;                                                  // 0.0
/*100 */             size = s->packet_transfer_size;                                          // 0.0
/*102 */             if (size > byte_count_limit) {                                           // 0.0
/*104 */                 /* byte count limit must be even if this case */                     // 0.0
/*106 */                 if (byte_count_limit & 1)                                            // 0.0
/*108 */                     byte_count_limit--;                                              // 0.0
/*110 */                 size = byte_count_limit;                                             // 0.0
/*112 */             }                                                                        // 0.0
/*114 */             s->lcyl = size;                                                          // 0.0
/*116 */             s->hcyl = size >> 8;                                                     // 0.0
/*118 */             s->elementary_transfer_size = size;                                      // 0.0
/*120 */             /* we cannot transmit more than one sector at a time */                  // 0.0
/*122 */             if (s->lba != -1) {                                                      // 0.0
/*124 */                 if (size > (s->cd_sector_size - s->io_buffer_index))                 // 0.0
/*126 */                     size = (s->cd_sector_size - s->io_buffer_index);                 // 0.0
/*128 */             }                                                                        // 0.0
/*130 */             ide_transfer_start(s, s->io_buffer + s->io_buffer_index,                 // 0.0
/*132 */                                size, ide_atapi_cmd_reply_end);                       // 0.0
/*134 */             s->packet_transfer_size -= size;                                         // 0.0
/*136 */             s->elementary_transfer_size -= size;                                     // 0.0
/*138 */             s->io_buffer_index += size;                                              // 0.0
/*140 */             ide_set_irq(s);                                                          // 0.0
/*142 */ #ifdef DEBUG_IDE_ATAPI                                                               // 0.0
/*144 */             printf("status=0x%x\n", s->status);                                      // 0.0
/*146 */ #endif                                                                               // 0.0
/*148 */         }                                                                            // 0.0
/*150 */     }                                                                                // 0.0
/*152 */ }                                                                                    // 0.0
