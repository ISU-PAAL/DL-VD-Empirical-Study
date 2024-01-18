// commit message FFmpeg@01ecb7172b (target=1, prob=0.96904546, correct=True): AAC encoder: Extensive improvements
/*0   */ static void quantize_and_encode_band_cost_SPAIR_mips(struct AACEncContext *s,                         // (8) 0.05273
/*2   */                                                      PutBitContext *pb, const float *in, float *out,  // (0) 0.1309
/*4   */                                                      const float *scaled, int size, int scale_idx,    // (1) 0.1309
/*6   */                                                      int cb, const float lambda, const float uplim,   // (2) 0.127
/*8   */                                                      int *bits, const float ROUNDING)                 // (3) 0.1211
/*10  */ {                                                                                                     // (11) 0.001953
/*12  */     const float Q34 = ff_aac_pow34sf_tab[POW_SF2_ZERO - scale_idx + SCALE_ONE_POS - SCALE_DIV_512];   // (4) 0.09375
/*14  */     const float IQ  = ff_aac_pow2sf_tab [POW_SF2_ZERO + scale_idx - SCALE_ONE_POS + SCALE_DIV_512];   // (5) 0.09375
/*16  */     int i;                                                                                            // (10) 0.01172
/*18  */     int qc1, qc2, qc3, qc4;                                                                           // (9) 0.03906
/*22  */     uint8_t  *p_bits  = (uint8_t  *)ff_aac_spectral_bits[cb-1];                                       // (6) 0.06836
/*24  */     uint16_t *p_codes = (uint16_t *)ff_aac_spectral_codes[cb-1];                                      // (7) 0.0625
/*26  */     float    *p_vec   = (float    *)ff_aac_codebook_vectors[cb-1];                                    // 0.0
/*30  */     abs_pow34_v(s->scoefs, in, size);                                                                 // 0.0
/*32  */     scaled = s->scoefs;                                                                               // 0.0
/*34  */     for (i = 0; i < size; i += 4) {                                                                   // 0.0
/*36  */         int curidx, curidx2;                                                                          // 0.0
/*38  */         int *in_int = (int *)&in[i];                                                                  // 0.0
/*40  */         uint8_t v_bits;                                                                               // 0.0
/*42  */         unsigned int v_codes;                                                                         // 0.0
/*44  */         int t0, t1, t2, t3, t4, t5, t6, t7;                                                           // 0.0
/*46  */         const float *vec1, *vec2;                                                                     // 0.0
/*50  */         qc1 = scaled[i  ] * Q34 + ROUND_STANDARD;                                                     // 0.0
/*52  */         qc2 = scaled[i+1] * Q34 + ROUND_STANDARD;                                                     // 0.0
/*54  */         qc3 = scaled[i+2] * Q34 + ROUND_STANDARD;                                                     // 0.0
/*56  */         qc4 = scaled[i+3] * Q34 + ROUND_STANDARD;                                                     // 0.0
/*60  */         __asm__ volatile (                                                                            // 0.0
/*62  */             ".set push                      \n\t"                                                     // 0.0
/*64  */             ".set noreorder                 \n\t"                                                     // 0.0
/*68  */             "ori    %[t4],  $zero,  4       \n\t"                                                     // 0.0
/*70  */             "slt    %[t0],  %[t4],  %[qc1]  \n\t"                                                     // 0.0
/*72  */             "slt    %[t1],  %[t4],  %[qc2]  \n\t"                                                     // 0.0
/*74  */             "slt    %[t2],  %[t4],  %[qc3]  \n\t"                                                     // 0.0
/*76  */             "slt    %[t3],  %[t4],  %[qc4]  \n\t"                                                     // 0.0
/*78  */             "movn   %[qc1], %[t4],  %[t0]   \n\t"                                                     // 0.0
/*80  */             "movn   %[qc2], %[t4],  %[t1]   \n\t"                                                     // 0.0
/*82  */             "movn   %[qc3], %[t4],  %[t2]   \n\t"                                                     // 0.0
/*84  */             "movn   %[qc4], %[t4],  %[t3]   \n\t"                                                     // 0.0
/*86  */             "lw     %[t0],  0(%[in_int])    \n\t"                                                     // 0.0
/*88  */             "lw     %[t1],  4(%[in_int])    \n\t"                                                     // 0.0
/*90  */             "lw     %[t2],  8(%[in_int])    \n\t"                                                     // 0.0
/*92  */             "lw     %[t3],  12(%[in_int])   \n\t"                                                     // 0.0
/*94  */             "srl    %[t0],  %[t0],  31      \n\t"                                                     // 0.0
/*96  */             "srl    %[t1],  %[t1],  31      \n\t"                                                     // 0.0
/*98  */             "srl    %[t2],  %[t2],  31      \n\t"                                                     // 0.0
/*100 */             "srl    %[t3],  %[t3],  31      \n\t"                                                     // 0.0
/*102 */             "subu   %[t4],  $zero,  %[qc1]  \n\t"                                                     // 0.0
/*104 */             "subu   %[t5],  $zero,  %[qc2]  \n\t"                                                     // 0.0
/*106 */             "subu   %[t6],  $zero,  %[qc3]  \n\t"                                                     // 0.0
/*108 */             "subu   %[t7],  $zero,  %[qc4]  \n\t"                                                     // 0.0
/*110 */             "movn   %[qc1], %[t4],  %[t0]   \n\t"                                                     // 0.0
/*112 */             "movn   %[qc2], %[t5],  %[t1]   \n\t"                                                     // 0.0
/*114 */             "movn   %[qc3], %[t6],  %[t2]   \n\t"                                                     // 0.0
/*116 */             "movn   %[qc4], %[t7],  %[t3]   \n\t"                                                     // 0.0
/*120 */             ".set pop                       \n\t"                                                     // 0.0
/*124 */             : [qc1]"+r"(qc1), [qc2]"+r"(qc2),                                                         // 0.0
/*126 */               [qc3]"+r"(qc3), [qc4]"+r"(qc4),                                                         // 0.0
/*128 */               [t0]"=&r"(t0), [t1]"=&r"(t1), [t2]"=&r"(t2), [t3]"=&r"(t3),                             // 0.0
/*130 */               [t4]"=&r"(t4), [t5]"=&r"(t5), [t6]"=&r"(t6), [t7]"=&r"(t7)                              // 0.0
/*132 */             : [in_int]"r"(in_int)                                                                     // 0.0
/*134 */             : "memory"                                                                                // 0.0
/*136 */         );                                                                                            // 0.0
/*140 */         curidx = 9 * qc1;                                                                             // 0.0
/*142 */         curidx += qc2 + 40;                                                                           // 0.0
/*146 */         curidx2 = 9 * qc3;                                                                            // 0.0
/*148 */         curidx2 += qc4 + 40;                                                                          // 0.0
/*152 */         v_codes = (p_codes[curidx] << p_bits[curidx2]) | (p_codes[curidx2]);                          // 0.0
/*154 */         v_bits  = p_bits[curidx] + p_bits[curidx2];                                                   // 0.0
/*156 */         put_bits(pb, v_bits, v_codes);                                                                // 0.0
/*160 */         if (out) {                                                                                    // 0.0
/*162 */            vec1 = &p_vec[curidx*2 ];                                                                  // 0.0
/*164 */            vec2 = &p_vec[curidx2*2];                                                                  // 0.0
/*166 */            out[i+0] = vec1[0] * IQ;                                                                   // 0.0
/*168 */            out[i+1] = vec1[1] * IQ;                                                                   // 0.0
/*170 */            out[i+2] = vec2[0] * IQ;                                                                   // 0.0
/*172 */            out[i+3] = vec2[1] * IQ;                                                                   // 0.0
/*174 */         }                                                                                             // 0.0
/*176 */     }                                                                                                 // 0.0
/*178 */ }                                                                                                     // 0.0
