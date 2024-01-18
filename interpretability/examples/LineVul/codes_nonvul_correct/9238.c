// commit message FFmpeg@486637af8e (target=0, prob=0.004468202, correct=True): AC-3 decoder, soc revision 32, Jul 17 09:37:32 2006 UTC by cloud9 Latest commit. There is no error in parsing and or recovering transform coefficients. Double checked with ac3dec. Getting consistent results with the bit allocation routine and transform coefficients. The code is able to parse valid ac3 bitstreams without error from start to end. I have also implemented the imdct when block switching is not enabled. However, can anybody provide an insight into how to convert float samples to int16_t ? lrint is of no help cuz it produces output -1, 0 or 1 whereas the output should be between -32768 to 32767.
/*0  */ static inline void mix_3f_1r_to_mono(AC3DecodeContext *ctx)           // (1) 0.1371
/*2  */ {                                                                     // (8) 0.005714
/*4  */     int i;                                                            // (7) 0.03429
/*6  */     float (*output)[256] = ctx->audio_block.block_output;             // (2) 0.12
/*10 */     for (i = 0; i < 256; i++)                                         // (6) 0.08571
/*12 */         output[1][i] = (output[2][i] + output[3][i] + output[4][i]);  // (0) 0.2
/*14 */     memset(output[2], 0, sizeof(output[2]));                          // (3) 0.1086
/*16 */     memset(output[3], 0, sizeof(output[3]));                          // (4) 0.1086
/*18 */     memset(output[4], 0, sizeof(output[4]));                          // (5) 0.1086
/*20 */ }                                                                     // (9) 0.005714
