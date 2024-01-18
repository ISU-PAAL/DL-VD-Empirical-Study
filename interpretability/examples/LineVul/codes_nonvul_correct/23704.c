// commit message FFmpeg@0058584580 (target=0, prob=0.0047996277, correct=True): AC-3 decoder, soc revision 31, Jul 14 23:53:28 2006 UTC by cloud9 Removed _ from names Removed temporary storage for the exponents Removed ctx->samples Now each transform coefficients are stored in audio block as an array of transform coefficients for each channel added ctx->delay (output of later half of previous block) added audio_block->block_output(output of this block)
/*0  */ static inline void downmix_3f_1r_to_mono(float *samples)                         // (2) 0.1732
/*2  */ {                                                                                // (7) 0.007874
/*4  */     int i;                                                                       // (4) 0.04724
/*8  */     for (i = 0; i < 256; i++) {                                                  // (3) 0.126
/*10 */         samples[i] += (samples[i + 256] + samples[i + 512] + samples[i + 768]);  // (0) 0.2677
/*12 */         samples[i + 256] = samples[i + 512] = samples[i + 768] = 0;              // (1) 0.2362
/*14 */     }                                                                            // (5) 0.0315
/*16 */ }                                                                                // (6) 0.007874
