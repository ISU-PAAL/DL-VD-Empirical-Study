// commit message qemu@0d82d0e8b9 (target=0, prob=0.67400944, correct=False): migration: move buffered_file.c code into migration.c
/*0  */ static ssize_t buffered_flush(QEMUFileBuffered *s)                                     // (10) 0.04043
/*2  */ {                                                                                      // (24) 0.002128
/*4  */     size_t offset = 0;                                                                 // (16) 0.02128
/*6  */     ssize_t ret = 0;                                                                   // (14) 0.0234
/*10 */     DPRINTF("flushing %zu byte(s) of data\n", s->buffer_size);                         // (7) 0.05532
/*14 */     while (s->bytes_xfer < s->xfer_limit && offset < s->buffer_size) {                 // (3) 0.05957
/*16 */         size_t to_send = MIN(s->buffer_size - offset, s->xfer_limit - s->bytes_xfer);  // (1) 0.08085
/*18 */         ret = migrate_fd_put_buffer(s->migration_state, s->buffer + offset,            // (2) 0.06383
/*20 */                                     to_send);                                          // (0) 0.08298
/*22 */         if (ret <= 0) {                                                                // (12) 0.02979
/*24 */             DPRINTF("error flushing data, %zd\n", ret);                                // (4) 0.05957
/*26 */             break;                                                                     // (13) 0.02766
/*28 */         } else {                                                                       // (17) 0.02128
/*30 */             DPRINTF("flushed %zd byte(s)\n", ret);                                     // (5) 0.05957
/*32 */             offset += ret;                                                             // (11) 0.03191
/*34 */             s->bytes_xfer += ret;                                                      // (9) 0.04255
/*36 */         }                                                                              // (20) 0.01702
/*38 */     }                                                                                  // (22) 0.008511
/*42 */     DPRINTF("flushed %zu of %zu byte(s)\n", offset, s->buffer_size);                   // (6) 0.05957
/*44 */     memmove(s->buffer, s->buffer + offset, s->buffer_size - offset);                   // (8) 0.05106
/*46 */     s->buffer_size -= offset;                                                          // (15) 0.0234
/*50 */     if (ret < 0) {                                                                     // (18) 0.02128
/*52 */         return ret;                                                                    // (19) 0.02128
/*54 */     }                                                                                  // (23) 0.008511
/*56 */     return offset;                                                                     // (21) 0.01277
/*58 */ }                                                                                      // (25) 0.002128
