// commit message FFmpeg@51a1c1c6ac (target=0, prob=0.84751356, correct=False): avcodec/iff: check for end of buffer in input for delta_l decompression
/*0   */ static void decode_delta_l(uint8_t *dst,                                                                            // (14) 0.0332
/*2   */                            const uint8_t *buf, const uint8_t *buf_end,                                              // (0) 0.08594
/*4   */                            int w, int flag, int bpp, int dst_size)                                                  // (1) 0.08008
/*6   */ {                                                                                                                   // (24) 0.001953
/*8   */     GetByteContext off0, off1, dgb, ogb;                                                                            // (11) 0.03516
/*10  */     PutByteContext pb;                                                                                              // (22) 0.01758
/*12  */     unsigned poff0, poff1;                                                                                          // (20) 0.02344
/*14  */     int i, k, dstpitch;                                                                                             // (21) 0.02344
/*16  */     int planepitch_byte = (w + 7) / 8;                                                                              // (12) 0.03516
/*18  */     int planepitch = ((w + 15) / 16) * 2;                                                                           // (10) 0.03711
/*20  */     int pitch = planepitch * bpp;                                                                                   // (16) 0.02539
/*24  */     if (buf_end - buf <= 64)                                                                                        // (15) 0.02539
/*26  */         return;                                                                                                     // (23) 0.01758
/*30  */     bytestream2_init(&off0, buf, buf_end - buf);                                                                    // (8) 0.04102
/*32  */     bytestream2_init(&off1, buf + 32, buf_end - (buf + 32));                                                        // (2) 0.05078
/*34  */     bytestream2_init_writer(&pb, dst, dst_size);                                                                    // (9) 0.03906
/*38  */     dstpitch = flag ? (((w + 7) / 8) * bpp): 2;                                                                     // (3) 0.04687
/*42  */     for (k = 0; k < bpp; k++) {                                                                                     // (13) 0.0332
/*44  */         poff0 = bytestream2_get_be32(&off0);                                                                        // (5) 0.04687
/*46  */         poff1 = bytestream2_get_be32(&off1);                                                                        // (4) 0.04687
/*50  */         if (!poff0)                                                                                                 // (17) 0.02539
/*52  */             continue;                                                                                               // (18) 0.02539
/*56  */         if (2LL * poff0 >= buf_end - buf)                                                                           // (6) 0.04297
/*58  */             return;                                                                                                 // (19) 0.02539
/*62  */         if (2LL * poff1 >= buf_end - buf)                                                                           // (7) 0.04297
/*64  */             return;                                                                                                 // 0.0
/*68  */         bytestream2_init(&dgb, buf + 2 * poff0, buf_end - (buf + 2 * poff0));                                       // 0.0
/*70  */         bytestream2_init(&ogb, buf + 2 * poff1, buf_end - (buf + 2 * poff1));                                       // 0.0
/*74  */         while ((bytestream2_peek_be16(&ogb)) != 0xFFFF) {                                                           // 0.0
/*76  */             uint32_t offset = bytestream2_get_be16(&ogb);                                                           // 0.0
/*78  */             int16_t cnt = bytestream2_get_be16(&ogb);                                                               // 0.0
/*80  */             uint16_t data;                                                                                          // 0.0
/*84  */             offset = ((2 * offset) / planepitch_byte) * pitch + ((2 * offset) % planepitch_byte) + k * planepitch;  // 0.0
/*86  */             if (cnt < 0) {                                                                                          // 0.0
/*88  */                 bytestream2_seek_p(&pb, offset, SEEK_SET);                                                          // 0.0
/*90  */                 cnt = -cnt;                                                                                         // 0.0
/*92  */                 data = bytestream2_get_be16(&dgb);                                                                  // 0.0
/*94  */                 for (i = 0; i < cnt; i++) {                                                                         // 0.0
/*96  */                     bytestream2_put_be16(&pb, data);                                                                // 0.0
/*98  */                     bytestream2_skip_p(&pb, dstpitch - 2);                                                          // 0.0
/*100 */                 }                                                                                                   // 0.0
/*102 */             } else {                                                                                                // 0.0
/*104 */                 bytestream2_seek_p(&pb, offset, SEEK_SET);                                                          // 0.0
/*106 */                 for (i = 0; i < cnt; i++) {                                                                         // 0.0
/*108 */                     data = bytestream2_get_be16(&dgb);                                                              // 0.0
/*110 */                     bytestream2_put_be16(&pb, data);                                                                // 0.0
/*112 */                     bytestream2_skip_p(&pb, dstpitch - 2);                                                          // 0.0
/*114 */                 }                                                                                                   // 0.0
/*116 */             }                                                                                                       // 0.0
/*118 */         }                                                                                                           // 0.0
/*120 */     }                                                                                                               // 0.0
/*122 */ }                                                                                                                   // 0.0
