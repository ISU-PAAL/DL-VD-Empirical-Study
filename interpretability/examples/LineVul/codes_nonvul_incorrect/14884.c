// commit message FFmpeg@0273ceebbd (target=0, prob=0.63290006, correct=False): few more error checks
/*0  */ static void build_vlc(VLC *vlc, const uint8_t *bits_table, const uint8_t *val_table,   // (1) 0.1744
/*2  */                       int nb_codes)                                                    // (3) 0.1385
/*4  */ {                                                                                      // (8) 0.005128
/*6  */     uint8_t huff_size[256];                                                            // (5) 0.07179
/*8  */     uint16_t huff_code[256];                                                           // (6) 0.07179
/*12 */     memset(huff_size, 0, sizeof(huff_size));                                           // (4) 0.1026
/*14 */     build_huffman_codes(huff_size, huff_code, bits_table, val_table);                  // (2) 0.1487
/*16 */                                                                                        // (7) 0.02051
/*18 */     init_vlc(vlc, 9, nb_codes, huff_size, 1, 1, huff_code, 2, 2);                      // (0) 0.1846
/*20 */ }                                                                                      // (9) 0.005128
