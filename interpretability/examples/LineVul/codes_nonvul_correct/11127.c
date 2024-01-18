// commit message qemu@5dafc53f1f (target=0, prob=0.39304194, correct=True): Refactor QEMUFile for live migration
/*0  */ static void qemu_fill_buffer(QEMUFile *f)                        // (4) 0.05592
/*2  */ {                                                                // (18) 0.003289
/*4  */     int len;                                                     // (15) 0.01974
/*8  */     if (f->is_writable)                                          // (9) 0.03947
/*10 */         return;                                                  // (14) 0.02961
/*12 */     if (f->is_file) {                                            // (10) 0.03947
/*14 */         fseek(f->outfile, f->buf_offset, SEEK_SET);              // (3) 0.08553
/*16 */         len = fread(f->buf, 1, IO_BUF_SIZE, f->outfile);         // (2) 0.09868
/*18 */         if (len < 0)                                             // (7) 0.04276
/*20 */             len = 0;                                             // (5) 0.04934
/*22 */     } else {                                                     // (16) 0.01974
/*24 */         len = bdrv_pread(f->bs, f->base_offset + f->buf_offset,  // (1) 0.102
/*26 */                          f->buf, IO_BUF_SIZE);                   // (0) 0.1151
/*28 */         if (len < 0)                                             // (8) 0.04276
/*30 */             len = 0;                                             // (6) 0.04934
/*32 */     }                                                            // (17) 0.01316
/*34 */     f->buf_index = 0;                                            // (11) 0.03618
/*36 */     f->buf_size = len;                                           // (12) 0.03618
/*38 */     f->buf_offset += len;                                        // (13) 0.03618
/*40 */ }                                                                // (19) 0.003289
