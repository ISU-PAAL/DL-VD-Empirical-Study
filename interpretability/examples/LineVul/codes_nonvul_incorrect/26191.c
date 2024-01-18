// commit message qemu@b9ce1454e1 (target=0, prob=0.58913463, correct=False): savevm: some coding style cleanups
/*0  */ int qemu_get_buffer(QEMUFile *f, uint8_t *buf, int size1)  // (0) 0.08182
/*2  */ {                                                          // (21) 0.00303
/*4  */     int size, l;                                           // (17) 0.02424
/*8  */     if (f->is_write)                                       // (11) 0.03333
/*10 */         abort();                                           // (15) 0.02727
/*14 */     size = size1;                                          // (18) 0.02424
/*16 */     while (size > 0) {                                     // (14) 0.0303
/*18 */         l = f->buf_size - f->buf_index;                    // (4) 0.06364
/*20 */         if (l == 0) {                                      // (9) 0.04242
/*22 */             qemu_fill_buffer(f);                           // (3) 0.06364
/*24 */             l = f->buf_size - f->buf_index;                // (1) 0.07576
/*26 */             if (l == 0)                                    // (5) 0.05152
/*28 */                 break;                                     // (6) 0.05152
/*30 */         }                                                  // (19) 0.02424
/*32 */         if (l > size)                                      // (10) 0.03939
/*34 */             l = size;                                      // (7) 0.04545
/*36 */         memcpy(buf, f->buf + f->buf_index, l);             // (2) 0.07576
/*38 */         f->buf_index += l;                                 // (8) 0.04545
/*40 */         buf += l;                                          // (12) 0.03333
/*42 */         size -= l;                                         // (13) 0.03333
/*44 */     }                                                      // (20) 0.01212
/*46 */     return size1 - size;                                   // (16) 0.02727
/*48 */ }                                                          // (22) 0.00303
