// commit message FFmpeg@2bfd0a9758 (target=1, prob=0.99902713, correct=True): avcodec/cllc: Check num_bits
/*0  */ static int read_code_table(CLLCContext *ctx, GetBitContext *gb, VLC *vlc)  // (2) 0.05273
/*1  */ {                                                                          // (24) 0.001953
/*2  */     uint8_t symbols[256];                                                  // (19) 0.02148
/*3  */     uint8_t bits[256];                                                     // (20) 0.02148
/*4  */     uint16_t codes[256];                                                   // (21) 0.02148
/*5  */     int num_lens, num_codes, num_codes_sum, prefix;                        // (8) 0.04102
/*6  */     int i, j, count;                                                       // (23) 0.01953
/*7  */     prefix        = 0;                                                     // (16) 0.02734
/*8  */     count         = 0;                                                     // (15) 0.0293
/*9  */     num_codes_sum = 0;                                                     // (22) 0.02148
/*10 */     num_lens = get_bits(gb, 5);                                            // (14) 0.03125
/*11 */     for (i = 0; i < num_lens; i++) {                                       // (11) 0.03711
/*12 */         num_codes      = get_bits(gb, 9);                                  // (4) 0.04688
/*13 */         num_codes_sum += num_codes;                                        // (13) 0.0332
/*14 */         if (num_codes_sum > 256) {                                         // (12) 0.03516
/*15 */             av_log(ctx->avctx, AV_LOG_ERROR,                               // (3) 0.05078
/*16 */                    "Too many VLCs (%d) to be read.\n", num_codes_sum);     // (0) 0.07813
/*17 */         for (j = 0; j < num_codes; j++) {                                  // (7) 0.04297
/*18 */             symbols[count] = get_bits(gb, 8);                              // (5) 0.04688
/*19 */             bits[count]    = i + 1;                                        // (6) 0.04492
/*20 */             codes[count]   = prefix++;                                     // (9) 0.03906
/*21 */             count++;                                                       // (17) 0.02539
/*22 */         if (prefix > (65535 - 256)/2) {                                    // (10) 0.03906
/*23 */         prefix <<= 1;                                                      // (18) 0.02344
/*24 */     return ff_init_vlc_sparse(vlc, VLC_BITS, count, bits, 1, 1,            // (1) 0.06055
/*25 */                               codes, 2, 2, symbols, 1, 1, 0);              // 0.0
