// commit message qemu@53628efbc8 (target=1, prob=0.33741915, correct=False): char: fix broken EAGAIN retry on OS-X due to errno clobbering
/*0  */ int qemu_chr_fe_read_all(CharDriverState *s, uint8_t *buf, int len)  // (2) 0.05859
/*2  */ {                                                                    // (31) 0.001953
/*4  */     int offset = 0, counter = 10;                                    // (16) 0.02344
/*6  */     int res;                                                         // (26) 0.01172
/*10 */     if (!s->chr_sync_read) {                                         // (9) 0.0293
/*12 */         return 0;                                                    // (21) 0.01953
/*14 */     }                                                                // (28) 0.007812
/*16 */                                                                      // (29) 0.007812
/*18 */     if (s->replay && replay_mode == REPLAY_MODE_PLAY) {              // (6) 0.04297
/*20 */         return replay_char_read_all_load(buf);                       // (8) 0.03906
/*22 */     }                                                                // (27) 0.007813
/*26 */     while (offset < len) {                                           // (20) 0.01953
/*28 */         do {                                                         // (22) 0.01758
/*30 */             res = s->chr_sync_read(s, buf + offset, len - offset);   // (0) 0.0625
/*32 */             if (res == -1 && errno == EAGAIN) {                      // (4) 0.05078
/*34 */                 g_usleep(100);                                       // (5) 0.04297
/*36 */             }                                                        // (17) 0.02344
/*38 */         } while (res == -1 && errno == EAGAIN);                      // (7) 0.04297
/*42 */         if (res == 0) {                                              // (10) 0.02734
/*44 */             break;                                                   // (13) 0.02539
/*46 */         }                                                            // (23) 0.01562
/*50 */         if (res < 0) {                                               // (11) 0.02734
/*52 */             if (s->replay && replay_mode == REPLAY_MODE_RECORD) {    // (1) 0.06055
/*54 */                 replay_char_read_all_save_error(res);                // (3) 0.05664
/*56 */             }                                                        // (18) 0.02344
/*58 */             return res;                                              // (12) 0.02734
/*60 */         }                                                            // (24) 0.01562
/*64 */         offset += res;                                               // (19) 0.02148
/*68 */         if (!counter--) {                                            // (14) 0.02539
/*70 */             break;                                                   // (15) 0.02539
/*72 */         }                                                            // (25) 0.01562
/*74 */     }                                                                // (30) 0.007812
/*78 */     if (s->replay && replay_mode == REPLAY_MODE_RECORD) {            // 0.0
/*80 */         replay_char_read_all_save_buf(buf, offset);                  // 0.0
/*82 */     }                                                                // 0.0
/*84 */     return offset;                                                   // 0.0
/*86 */ }                                                                    // 0.0
