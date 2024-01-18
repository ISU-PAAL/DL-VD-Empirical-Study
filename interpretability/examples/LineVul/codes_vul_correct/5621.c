// commit message FFmpeg@01ecb7172b (target=1, prob=0.9561709, correct=True): AAC encoder: Extensive improvements
/*0   */ static float get_band_cost_UPAIR7_mips(struct AACEncContext *s,                                      // (9) 0.04492
/*2   */                                        PutBitContext *pb, const float *in,                           // (2) 0.0957
/*4   */                                        const float *scaled, int size, int scale_idx,                 // (0) 0.1035
/*6   */                                        int cb, const float lambda, const float uplim,                // (1) 0.09961
/*8   */                                        int *bits)                                                    // (5) 0.08203
/*10  */ {                                                                                                    // (16) 0.001953
/*12  */     const float Q34 = ff_aac_pow34sf_tab[POW_SF2_ZERO - scale_idx + SCALE_ONE_POS - SCALE_DIV_512];  // (3) 0.09375
/*14  */     const float IQ  = ff_aac_pow2sf_tab [POW_SF2_ZERO + scale_idx - SCALE_ONE_POS + SCALE_DIV_512];  // (4) 0.09375
/*16  */     int i;                                                                                           // (15) 0.01172
/*18  */     float cost = 0;                                                                                  // (14) 0.01563
/*20  */     int qc1, qc2, qc3, qc4;                                                                          // (10) 0.03906
/*22  */     int curbits = 0;                                                                                 // (13) 0.01758
/*26  */     uint8_t *p_bits  = (uint8_t *)ff_aac_spectral_bits[cb-1];                                        // (6) 0.06445
/*28  */     float   *p_codes = (float   *)ff_aac_codebook_vectors[cb-1];                                     // (7) 0.06055
/*32  */     for (i = 0; i < size; i += 4) {                                                                  // (11) 0.03516
/*34  */         const float *vec, *vec2;                                                                     // (12) 0.03125
/*36  */         int curidx, curidx2, sign1, count1, sign2, count2;                                           // (8) 0.05664
/*38  */         int   *in_int = (int   *)&in[i];                                                             // 0.0
/*40  */         float *in_pos = (float *)&in[i];                                                             // 0.0
/*42  */         float di0, di1, di2, di3;                                                                    // 0.0
/*44  */         int t0, t1, t2, t3, t4;                                                                      // 0.0
/*48  */         qc1 = scaled[i  ] * Q34 + ROUND_STANDARD;                                                    // 0.0
/*50  */         qc2 = scaled[i+1] * Q34 + ROUND_STANDARD;                                                    // 0.0
/*52  */         qc3 = scaled[i+2] * Q34 + ROUND_STANDARD;                                                    // 0.0
/*54  */         qc4 = scaled[i+3] * Q34 + ROUND_STANDARD;                                                    // 0.0
/*58  */         __asm__ volatile (                                                                           // 0.0
/*60  */             ".set push                                          \n\t"                                // 0.0
/*62  */             ".set noreorder                                     \n\t"                                // 0.0
/*66  */             "ori        %[t4],      $zero,      7               \n\t"                                // 0.0
/*68  */             "ori        %[sign1],   $zero,      0               \n\t"                                // 0.0
/*70  */             "ori        %[sign2],   $zero,      0               \n\t"                                // 0.0
/*72  */             "slt        %[t0],      %[t4],      %[qc1]          \n\t"                                // 0.0
/*74  */             "slt        %[t1],      %[t4],      %[qc2]          \n\t"                                // 0.0
/*76  */             "slt        %[t2],      %[t4],      %[qc3]          \n\t"                                // 0.0
/*78  */             "slt        %[t3],      %[t4],      %[qc4]          \n\t"                                // 0.0
/*80  */             "movn       %[qc1],     %[t4],      %[t0]           \n\t"                                // 0.0
/*82  */             "movn       %[qc2],     %[t4],      %[t1]           \n\t"                                // 0.0
/*84  */             "movn       %[qc3],     %[t4],      %[t2]           \n\t"                                // 0.0
/*86  */             "movn       %[qc4],     %[t4],      %[t3]           \n\t"                                // 0.0
/*88  */             "lw         %[t0],      0(%[in_int])                \n\t"                                // 0.0
/*90  */             "lw         %[t1],      4(%[in_int])                \n\t"                                // 0.0
/*92  */             "lw         %[t2],      8(%[in_int])                \n\t"                                // 0.0
/*94  */             "lw         %[t3],      12(%[in_int])               \n\t"                                // 0.0
/*96  */             "slt        %[t0],      %[t0],      $zero           \n\t"                                // 0.0
/*98  */             "movn       %[sign1],   %[t0],      %[qc1]          \n\t"                                // 0.0
/*100 */             "slt        %[t2],      %[t2],      $zero           \n\t"                                // 0.0
/*102 */             "movn       %[sign2],   %[t2],      %[qc3]          \n\t"                                // 0.0
/*104 */             "slt        %[t1],      %[t1],      $zero           \n\t"                                // 0.0
/*106 */             "sll        %[t0],      %[sign1],   1               \n\t"                                // 0.0
/*108 */             "or         %[t0],      %[t0],      %[t1]           \n\t"                                // 0.0
/*110 */             "movn       %[sign1],   %[t0],      %[qc2]          \n\t"                                // 0.0
/*112 */             "slt        %[t3],      %[t3],      $zero           \n\t"                                // 0.0
/*114 */             "sll        %[t0],      %[sign2],   1               \n\t"                                // 0.0
/*116 */             "or         %[t0],      %[t0],      %[t3]           \n\t"                                // 0.0
/*118 */             "movn       %[sign2],   %[t0],      %[qc4]          \n\t"                                // 0.0
/*120 */             "slt        %[count1],  $zero,      %[qc1]          \n\t"                                // 0.0
/*122 */             "slt        %[t1],      $zero,      %[qc2]          \n\t"                                // 0.0
/*124 */             "slt        %[count2],  $zero,      %[qc3]          \n\t"                                // 0.0
/*126 */             "slt        %[t2],      $zero,      %[qc4]          \n\t"                                // 0.0
/*128 */             "addu       %[count1],  %[count1],  %[t1]           \n\t"                                // 0.0
/*130 */             "addu       %[count2],  %[count2],  %[t2]           \n\t"                                // 0.0
/*134 */             ".set pop                                           \n\t"                                // 0.0
/*138 */             : [qc1]"+r"(qc1), [qc2]"+r"(qc2),                                                        // 0.0
/*140 */               [qc3]"+r"(qc3), [qc4]"+r"(qc4),                                                        // 0.0
/*142 */               [sign1]"=&r"(sign1), [count1]"=&r"(count1),                                            // 0.0
/*144 */               [sign2]"=&r"(sign2), [count2]"=&r"(count2),                                            // 0.0
/*146 */               [t0]"=&r"(t0), [t1]"=&r"(t1), [t2]"=&r"(t2), [t3]"=&r"(t3),                            // 0.0
/*148 */               [t4]"=&r"(t4)                                                                          // 0.0
/*150 */             : [in_int]"r"(in_int)                                                                    // 0.0
/*152 */             : "memory"                                                                               // 0.0
/*154 */         );                                                                                           // 0.0
/*158 */         curidx = 8 * qc1;                                                                            // 0.0
/*160 */         curidx += qc2;                                                                               // 0.0
/*164 */         curidx2 = 8 * qc3;                                                                           // 0.0
/*166 */         curidx2 += qc4;                                                                              // 0.0
/*170 */         curbits += p_bits[curidx];                                                                   // 0.0
/*172 */         curbits += upair7_sign_bits[curidx];                                                         // 0.0
/*174 */         vec     = &p_codes[curidx*2];                                                                // 0.0
/*178 */         curbits += p_bits[curidx2];                                                                  // 0.0
/*180 */         curbits += upair7_sign_bits[curidx2];                                                        // 0.0
/*182 */         vec2    = &p_codes[curidx2*2];                                                               // 0.0
/*186 */         __asm__ volatile (                                                                           // 0.0
/*188 */             ".set push                                          \n\t"                                // 0.0
/*190 */             ".set noreorder                                     \n\t"                                // 0.0
/*194 */             "lwc1       %[di0],     0(%[in_pos])                \n\t"                                // 0.0
/*196 */             "lwc1       %[di1],     4(%[in_pos])                \n\t"                                // 0.0
/*198 */             "lwc1       %[di2],     8(%[in_pos])                \n\t"                                // 0.0
/*200 */             "lwc1       %[di3],     12(%[in_pos])               \n\t"                                // 0.0
/*202 */             "abs.s      %[di0],     %[di0]                      \n\t"                                // 0.0
/*204 */             "abs.s      %[di1],     %[di1]                      \n\t"                                // 0.0
/*206 */             "abs.s      %[di2],     %[di2]                      \n\t"                                // 0.0
/*208 */             "abs.s      %[di3],     %[di3]                      \n\t"                                // 0.0
/*210 */             "lwc1       $f0,        0(%[vec])                   \n\t"                                // 0.0
/*212 */             "lwc1       $f1,        4(%[vec])                   \n\t"                                // 0.0
/*214 */             "lwc1       $f2,        0(%[vec2])                  \n\t"                                // 0.0
/*216 */             "lwc1       $f3,        4(%[vec2])                  \n\t"                                // 0.0
/*218 */             "nmsub.s    %[di0],     %[di0],     $f0,    %[IQ]   \n\t"                                // 0.0
/*220 */             "nmsub.s    %[di1],     %[di1],     $f1,    %[IQ]   \n\t"                                // 0.0
/*222 */             "nmsub.s    %[di2],     %[di2],     $f2,    %[IQ]   \n\t"                                // 0.0
/*224 */             "nmsub.s    %[di3],     %[di3],     $f3,    %[IQ]   \n\t"                                // 0.0
/*228 */             ".set pop                                           \n\t"                                // 0.0
/*232 */             : [di0]"=&f"(di0), [di1]"=&f"(di1),                                                      // 0.0
/*234 */               [di2]"=&f"(di2), [di3]"=&f"(di3)                                                       // 0.0
/*236 */             : [in_pos]"r"(in_pos), [vec]"r"(vec),                                                    // 0.0
/*238 */               [vec2]"r"(vec2), [IQ]"f"(IQ)                                                           // 0.0
/*240 */             : "$f0", "$f1", "$f2", "$f3",                                                            // 0.0
/*242 */               "memory"                                                                               // 0.0
/*244 */         );                                                                                           // 0.0
/*248 */         cost += di0 * di0 + di1 * di1                                                                // 0.0
/*250 */                 + di2 * di2 + di3 * di3;                                                             // 0.0
/*252 */     }                                                                                                // 0.0
/*256 */     if (bits)                                                                                        // 0.0
/*258 */         *bits = curbits;                                                                             // 0.0
/*260 */     return cost * lambda + curbits;                                                                  // 0.0
/*262 */ }                                                                                                    // 0.0
