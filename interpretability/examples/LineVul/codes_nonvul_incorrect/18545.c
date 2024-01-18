// commit message FFmpeg@fa30a0a548 (target=0, prob=0.6728752, correct=False): avcodec/x86/mpegenc: check IDCT permutation type is a valid value
/*0   */ static int RENAME(dct_quantize)(MpegEncContext *s,                                                                           // (12) 0.03711
/*2   */                             int16_t *block, int n,                                                                           // (0) 0.07226
/*4   */                             int qscale, int *overflow)                                                                       // (1) 0.0703
/*6   */ {                                                                                                                            // (22) 0.001968
/*8   */     x86_reg last_non_zero_p1;                                                                                                // (14) 0.03125
/*10  */     int level=0, q; //=0 is because gcc says uninitialized ...                                                               // (11) 0.03906
/*12  */     const uint16_t *qmat, *bias;                                                                                             // (15) 0.03125
/*14  */     LOCAL_ALIGNED_16(int16_t, temp_block, [64]);                                                                             // (7) 0.04687
/*18  */     av_assert2((7&(int)(&temp_block[0])) == 0); //did gcc align it correctly?                                                // (4) 0.06054
/*22  */     //s->fdct (block);                                                                                                       // (19) 0.02148
/*24  */     RENAME_FDCT(ff_fdct)(block); // cannot be anything else ...                                                              // (8) 0.04492
/*28  */     if(s->dct_error_sum)                                                                                                     // (16) 0.02734
/*30  */         s->denoise_dct(s, block);                                                                                            // (13) 0.0371
/*34  */     if (s->mb_intra) {                                                                                                       // (17) 0.02539
/*36  */         int dummy;                                                                                                           // (21) 0.01953
/*38  */         if (n < 4){                                                                                                          // (18) 0.02539
/*40  */             q = s->y_dc_scale;                                                                                               // (9) 0.04104
/*42  */             bias = s->q_intra_matrix16[qscale][1];                                                                           // (6) 0.05663
/*44  */             qmat = s->q_intra_matrix16[qscale][0];                                                                           // (5) 0.05859
/*46  */         }else{                                                                                                               // (20) 0.01953
/*48  */             q = s->c_dc_scale;                                                                                               // (10) 0.04101
/*50  */             bias = s->q_chroma_intra_matrix16[qscale][1];                                                                    // (3) 0.06249
/*52  */             qmat = s->q_chroma_intra_matrix16[qscale][0];                                                                    // (2) 0.06445
/*54  */         }                                                                                                                    // 0.0
/*56  */         /* note: block[0] is assumed to be positive */                                                                       // 0.0
/*58  */         if (!s->h263_aic) {                                                                                                  // 0.0
/*60  */         __asm__ volatile (                                                                                                   // 0.0
/*62  */                 "mul %%ecx                \n\t"                                                                              // 0.0
/*64  */                 : "=d" (level), "=a"(dummy)                                                                                  // 0.0
/*66  */                 : "a" ((block[0]>>2) + q), "c" (ff_inverse[q<<1])                                                            // 0.0
/*68  */         );                                                                                                                   // 0.0
/*70  */         } else                                                                                                               // 0.0
/*72  */             /* For AIC we skip quant/dequant of INTRADC */                                                                   // 0.0
/*74  */             level = (block[0] + 4)>>3;                                                                                       // 0.0
/*78  */         block[0]=0; //avoid fake overflow                                                                                    // 0.0
/*80  */ //        temp_block[0] = (block[0] + (q >> 1)) / q;                                                                         // 0.0
/*82  */         last_non_zero_p1 = 1;                                                                                                // 0.0
/*84  */     } else {                                                                                                                 // 0.0
/*86  */         last_non_zero_p1 = 0;                                                                                                // 0.0
/*88  */         bias = s->q_inter_matrix16[qscale][1];                                                                               // 0.0
/*90  */         qmat = s->q_inter_matrix16[qscale][0];                                                                               // 0.0
/*92  */     }                                                                                                                        // 0.0
/*96  */     if((s->out_format == FMT_H263 || s->out_format == FMT_H261) && s->mpeg_quant==0){                                        // 0.0
/*100 */         __asm__ volatile(                                                                                                    // 0.0
/*102 */             "movd %%"FF_REG_a", "MM"3           \n\t" // last_non_zero_p1                                                    // 0.0
/*104 */             SPREADW(MM"3")                                                                                                   // 0.0
/*106 */             "pxor "MM"7, "MM"7                  \n\t" // 0                                                                   // 0.0
/*108 */             "pxor "MM"4, "MM"4                  \n\t" // 0                                                                   // 0.0
/*110 */             MOVQ" (%2), "MM"5                   \n\t" // qmat[0]                                                             // 0.0
/*112 */             "pxor "MM"6, "MM"6                  \n\t"                                                                        // 0.0
/*114 */             "psubw (%3), "MM"6                  \n\t" // -bias[0]                                                            // 0.0
/*116 */             "mov $-128, %%"FF_REG_a"            \n\t"                                                                        // 0.0
/*118 */             ".p2align 4                         \n\t"                                                                        // 0.0
/*120 */             "1:                                 \n\t"                                                                        // 0.0
/*122 */             MOVQ" (%1, %%"FF_REG_a"), "MM"0     \n\t" // block[i]                                                            // 0.0
/*124 */             SAVE_SIGN(MM"1", MM"0")                   // ABS(block[i])                                                       // 0.0
/*126 */             "psubusw "MM"6, "MM"0               \n\t" // ABS(block[i]) + bias[0]                                             // 0.0
/*128 */             "pmulhw "MM"5, "MM"0                \n\t" // (ABS(block[i])*qmat[0] - bias[0]*qmat[0])>>16                       // 0.0
/*130 */             "por "MM"0, "MM"4                   \n\t"                                                                        // 0.0
/*132 */             RESTORE_SIGN(MM"1", MM"0")                // out=((ABS(block[i])*qmat[0] - bias[0]*qmat[0])>>16)*sign(block[i])  // 0.0
/*134 */             MOVQ" "MM"0, (%5, %%"FF_REG_a")     \n\t"                                                                        // 0.0
/*136 */             "pcmpeqw "MM"7, "MM"0               \n\t" // out==0 ? 0xFF : 0x00                                                // 0.0
/*138 */             MOVQ" (%4, %%"FF_REG_a"), "MM"1     \n\t"                                                                        // 0.0
/*140 */             MOVQ" "MM"7, (%1, %%"FF_REG_a")     \n\t" // 0                                                                   // 0.0
/*142 */             "pandn "MM"1, "MM"0                 \n\t"                                                                        // 0.0
/*144 */             PMAXW(MM"0", MM"3")                                                                                              // 0.0
/*146 */             "add $"MMREG_WIDTH", %%"FF_REG_a"   \n\t"                                                                        // 0.0
/*148 */             " js 1b                             \n\t"                                                                        // 0.0
/*150 */             PMAX(MM"3", MM"0")                                                                                               // 0.0
/*152 */             "movd "MM"3, %%"FF_REG_a"           \n\t"                                                                        // 0.0
/*154 */             "movzbl %%al, %%eax                 \n\t" // last_non_zero_p1                                                    // 0.0
/*156 */             : "+a" (last_non_zero_p1)                                                                                        // 0.0
/*158 */             : "r" (block+64), "r" (qmat), "r" (bias),                                                                        // 0.0
/*160 */               "r" (inv_zigzag_direct16 + 64), "r" (temp_block + 64)                                                          // 0.0
/*162 */               XMM_CLOBBERS_ONLY("%xmm0", "%xmm1", "%xmm2", "%xmm3",                                                          // 0.0
/*164 */                                 "%xmm4", "%xmm5", "%xmm6", "%xmm7")                                                          // 0.0
/*166 */         );                                                                                                                   // 0.0
/*168 */     }else{ // FMT_H263                                                                                                       // 0.0
/*170 */         __asm__ volatile(                                                                                                    // 0.0
/*172 */             "movd %%"FF_REG_a", "MM"3           \n\t" // last_non_zero_p1                                                    // 0.0
/*174 */             SPREADW(MM"3")                                                                                                   // 0.0
/*176 */             "pxor "MM"7, "MM"7                  \n\t" // 0                                                                   // 0.0
/*178 */             "pxor "MM"4, "MM"4                  \n\t" // 0                                                                   // 0.0
/*180 */             "mov $-128, %%"FF_REG_a"            \n\t"                                                                        // 0.0
/*182 */             ".p2align 4                         \n\t"                                                                        // 0.0
/*184 */             "1:                                 \n\t"                                                                        // 0.0
/*186 */             MOVQ" (%1, %%"FF_REG_a"), "MM"0     \n\t" // block[i]                                                            // 0.0
/*188 */             SAVE_SIGN(MM"1", MM"0")                   // ABS(block[i])                                                       // 0.0
/*190 */             MOVQ" (%3, %%"FF_REG_a"), "MM"6     \n\t" // bias[0]                                                             // 0.0
/*192 */             "paddusw "MM"6, "MM"0               \n\t" // ABS(block[i]) + bias[0]                                             // 0.0
/*194 */             MOVQ" (%2, %%"FF_REG_a"), "MM"5     \n\t" // qmat[i]                                                             // 0.0
/*196 */             "pmulhw "MM"5, "MM"0                \n\t" // (ABS(block[i])*qmat[0] + bias[0]*qmat[0])>>16                       // 0.0
/*198 */             "por "MM"0, "MM"4                   \n\t"                                                                        // 0.0
/*200 */             RESTORE_SIGN(MM"1", MM"0")                // out=((ABS(block[i])*qmat[0] - bias[0]*qmat[0])>>16)*sign(block[i])  // 0.0
/*202 */             MOVQ" "MM"0, (%5, %%"FF_REG_a")     \n\t"                                                                        // 0.0
/*204 */             "pcmpeqw "MM"7, "MM"0               \n\t" // out==0 ? 0xFF : 0x00                                                // 0.0
/*206 */             MOVQ" (%4, %%"FF_REG_a"), "MM"1     \n\t"                                                                        // 0.0
/*208 */             MOVQ" "MM"7, (%1, %%"FF_REG_a")     \n\t" // 0                                                                   // 0.0
/*210 */             "pandn "MM"1, "MM"0                 \n\t"                                                                        // 0.0
/*212 */             PMAXW(MM"0", MM"3")                                                                                              // 0.0
/*214 */             "add $"MMREG_WIDTH", %%"FF_REG_a"   \n\t"                                                                        // 0.0
/*216 */             " js 1b                             \n\t"                                                                        // 0.0
/*218 */             PMAX(MM"3", MM"0")                                                                                               // 0.0
/*220 */             "movd "MM"3, %%"FF_REG_a"           \n\t"                                                                        // 0.0
/*222 */             "movzbl %%al, %%eax                 \n\t" // last_non_zero_p1                                                    // 0.0
/*224 */             : "+a" (last_non_zero_p1)                                                                                        // 0.0
/*226 */             : "r" (block+64), "r" (qmat+64), "r" (bias+64),                                                                  // 0.0
/*228 */               "r" (inv_zigzag_direct16 + 64), "r" (temp_block + 64)                                                          // 0.0
/*230 */               XMM_CLOBBERS_ONLY("%xmm0", "%xmm1", "%xmm2", "%xmm3",                                                          // 0.0
/*232 */                                 "%xmm4", "%xmm5", "%xmm6", "%xmm7")                                                          // 0.0
/*234 */         );                                                                                                                   // 0.0
/*236 */     }                                                                                                                        // 0.0
/*238 */     __asm__ volatile(                                                                                                        // 0.0
/*240 */         "movd %1, "MM"1                     \n\t" // max_qcoeff                                                              // 0.0
/*242 */         SPREADW(MM"1")                                                                                                       // 0.0
/*244 */         "psubusw "MM"1, "MM"4               \n\t"                                                                            // 0.0
/*246 */         "packuswb "MM"4, "MM"4              \n\t"                                                                            // 0.0
/*248 */ #if COMPILE_TEMPLATE_SSE2                                                                                                    // 0.0
/*250 */         "packsswb "MM"4, "MM"4              \n\t"                                                                            // 0.0
/*252 */ #endif                                                                                                                       // 0.0
/*254 */         "movd "MM"4, %0                     \n\t" // *overflow                                                               // 0.0
/*256 */         : "=g" (*overflow)                                                                                                   // 0.0
/*258 */         : "g" (s->max_qcoeff)                                                                                                // 0.0
/*260 */     );                                                                                                                       // 0.0
/*264 */     if(s->mb_intra) block[0]= level;                                                                                         // 0.0
/*266 */     else            block[0]= temp_block[0];                                                                                 // 0.0
/*270 */     if (s->idsp.perm_type == FF_IDCT_PERM_SIMPLE) {                                                                          // 0.0
/*272 */         if(last_non_zero_p1 <= 1) goto end;                                                                                  // 0.0
/*274 */         block[0x08] = temp_block[0x01]; block[0x10] = temp_block[0x08];                                                      // 0.0
/*276 */         block[0x20] = temp_block[0x10];                                                                                      // 0.0
/*278 */         if(last_non_zero_p1 <= 4) goto end;                                                                                  // 0.0
/*280 */         block[0x18] = temp_block[0x09]; block[0x04] = temp_block[0x02];                                                      // 0.0
/*282 */         block[0x09] = temp_block[0x03];                                                                                      // 0.0
/*284 */         if(last_non_zero_p1 <= 7) goto end;                                                                                  // 0.0
/*286 */         block[0x14] = temp_block[0x0A]; block[0x28] = temp_block[0x11];                                                      // 0.0
/*288 */         block[0x12] = temp_block[0x18]; block[0x02] = temp_block[0x20];                                                      // 0.0
/*290 */         if(last_non_zero_p1 <= 11) goto end;                                                                                 // 0.0
/*292 */         block[0x1A] = temp_block[0x19]; block[0x24] = temp_block[0x12];                                                      // 0.0
/*294 */         block[0x19] = temp_block[0x0B]; block[0x01] = temp_block[0x04];                                                      // 0.0
/*296 */         block[0x0C] = temp_block[0x05];                                                                                      // 0.0
/*298 */         if(last_non_zero_p1 <= 16) goto end;                                                                                 // 0.0
/*300 */         block[0x11] = temp_block[0x0C]; block[0x29] = temp_block[0x13];                                                      // 0.0
/*302 */         block[0x16] = temp_block[0x1A]; block[0x0A] = temp_block[0x21];                                                      // 0.0
/*304 */         block[0x30] = temp_block[0x28]; block[0x22] = temp_block[0x30];                                                      // 0.0
/*306 */         block[0x38] = temp_block[0x29]; block[0x06] = temp_block[0x22];                                                      // 0.0
/*308 */         if(last_non_zero_p1 <= 24) goto end;                                                                                 // 0.0
/*310 */         block[0x1B] = temp_block[0x1B]; block[0x21] = temp_block[0x14];                                                      // 0.0
/*312 */         block[0x1C] = temp_block[0x0D]; block[0x05] = temp_block[0x06];                                                      // 0.0
/*314 */         block[0x0D] = temp_block[0x07]; block[0x15] = temp_block[0x0E];                                                      // 0.0
/*316 */         block[0x2C] = temp_block[0x15]; block[0x13] = temp_block[0x1C];                                                      // 0.0
/*318 */         if(last_non_zero_p1 <= 32) goto end;                                                                                 // 0.0
/*320 */         block[0x0B] = temp_block[0x23]; block[0x34] = temp_block[0x2A];                                                      // 0.0
/*322 */         block[0x2A] = temp_block[0x31]; block[0x32] = temp_block[0x38];                                                      // 0.0
/*324 */         block[0x3A] = temp_block[0x39]; block[0x26] = temp_block[0x32];                                                      // 0.0
/*326 */         block[0x39] = temp_block[0x2B]; block[0x03] = temp_block[0x24];                                                      // 0.0
/*328 */         if(last_non_zero_p1 <= 40) goto end;                                                                                 // 0.0
/*330 */         block[0x1E] = temp_block[0x1D]; block[0x25] = temp_block[0x16];                                                      // 0.0
/*332 */         block[0x1D] = temp_block[0x0F]; block[0x2D] = temp_block[0x17];                                                      // 0.0
/*334 */         block[0x17] = temp_block[0x1E]; block[0x0E] = temp_block[0x25];                                                      // 0.0
/*336 */         block[0x31] = temp_block[0x2C]; block[0x2B] = temp_block[0x33];                                                      // 0.0
/*338 */         if(last_non_zero_p1 <= 48) goto end;                                                                                 // 0.0
/*340 */         block[0x36] = temp_block[0x3A]; block[0x3B] = temp_block[0x3B];                                                      // 0.0
/*342 */         block[0x23] = temp_block[0x34]; block[0x3C] = temp_block[0x2D];                                                      // 0.0
/*344 */         block[0x07] = temp_block[0x26]; block[0x1F] = temp_block[0x1F];                                                      // 0.0
/*346 */         block[0x0F] = temp_block[0x27]; block[0x35] = temp_block[0x2E];                                                      // 0.0
/*348 */         if(last_non_zero_p1 <= 56) goto end;                                                                                 // 0.0
/*350 */         block[0x2E] = temp_block[0x35]; block[0x33] = temp_block[0x3C];                                                      // 0.0
/*352 */         block[0x3E] = temp_block[0x3D]; block[0x27] = temp_block[0x36];                                                      // 0.0
/*354 */         block[0x3D] = temp_block[0x2F]; block[0x2F] = temp_block[0x37];                                                      // 0.0
/*356 */         block[0x37] = temp_block[0x3E]; block[0x3F] = temp_block[0x3F];                                                      // 0.0
/*358 */     }else if(s->idsp.perm_type == FF_IDCT_PERM_LIBMPEG2){                                                                    // 0.0
/*360 */         if(last_non_zero_p1 <= 1) goto end;                                                                                  // 0.0
/*362 */         block[0x04] = temp_block[0x01];                                                                                      // 0.0
/*364 */         block[0x08] = temp_block[0x08]; block[0x10] = temp_block[0x10];                                                      // 0.0
/*366 */         if(last_non_zero_p1 <= 4) goto end;                                                                                  // 0.0
/*368 */         block[0x0C] = temp_block[0x09]; block[0x01] = temp_block[0x02];                                                      // 0.0
/*370 */         block[0x05] = temp_block[0x03];                                                                                      // 0.0
/*372 */         if(last_non_zero_p1 <= 7) goto end;                                                                                  // 0.0
/*374 */         block[0x09] = temp_block[0x0A]; block[0x14] = temp_block[0x11];                                                      // 0.0
/*376 */         block[0x18] = temp_block[0x18]; block[0x20] = temp_block[0x20];                                                      // 0.0
/*378 */         if(last_non_zero_p1 <= 11) goto end;                                                                                 // 0.0
/*380 */         block[0x1C] = temp_block[0x19];                                                                                      // 0.0
/*382 */         block[0x11] = temp_block[0x12]; block[0x0D] = temp_block[0x0B];                                                      // 0.0
/*384 */         block[0x02] = temp_block[0x04]; block[0x06] = temp_block[0x05];                                                      // 0.0
/*386 */         if(last_non_zero_p1 <= 16) goto end;                                                                                 // 0.0
/*388 */         block[0x0A] = temp_block[0x0C]; block[0x15] = temp_block[0x13];                                                      // 0.0
/*390 */         block[0x19] = temp_block[0x1A]; block[0x24] = temp_block[0x21];                                                      // 0.0
/*392 */         block[0x28] = temp_block[0x28]; block[0x30] = temp_block[0x30];                                                      // 0.0
/*394 */         block[0x2C] = temp_block[0x29]; block[0x21] = temp_block[0x22];                                                      // 0.0
/*396 */         if(last_non_zero_p1 <= 24) goto end;                                                                                 // 0.0
/*398 */         block[0x1D] = temp_block[0x1B]; block[0x12] = temp_block[0x14];                                                      // 0.0
/*400 */         block[0x0E] = temp_block[0x0D]; block[0x03] = temp_block[0x06];                                                      // 0.0
/*402 */         block[0x07] = temp_block[0x07]; block[0x0B] = temp_block[0x0E];                                                      // 0.0
/*404 */         block[0x16] = temp_block[0x15]; block[0x1A] = temp_block[0x1C];                                                      // 0.0
/*406 */         if(last_non_zero_p1 <= 32) goto end;                                                                                 // 0.0
/*408 */         block[0x25] = temp_block[0x23]; block[0x29] = temp_block[0x2A];                                                      // 0.0
/*410 */         block[0x34] = temp_block[0x31]; block[0x38] = temp_block[0x38];                                                      // 0.0
/*412 */         block[0x3C] = temp_block[0x39]; block[0x31] = temp_block[0x32];                                                      // 0.0
/*414 */         block[0x2D] = temp_block[0x2B]; block[0x22] = temp_block[0x24];                                                      // 0.0
/*416 */         if(last_non_zero_p1 <= 40) goto end;                                                                                 // 0.0
/*418 */         block[0x1E] = temp_block[0x1D]; block[0x13] = temp_block[0x16];                                                      // 0.0
/*420 */         block[0x0F] = temp_block[0x0F]; block[0x17] = temp_block[0x17];                                                      // 0.0
/*422 */         block[0x1B] = temp_block[0x1E]; block[0x26] = temp_block[0x25];                                                      // 0.0
/*424 */         block[0x2A] = temp_block[0x2C]; block[0x35] = temp_block[0x33];                                                      // 0.0
/*426 */         if(last_non_zero_p1 <= 48) goto end;                                                                                 // 0.0
/*428 */         block[0x39] = temp_block[0x3A]; block[0x3D] = temp_block[0x3B];                                                      // 0.0
/*430 */         block[0x32] = temp_block[0x34]; block[0x2E] = temp_block[0x2D];                                                      // 0.0
/*432 */             block[0x23] = temp_block[0x26]; block[0x1F] = temp_block[0x1F];                                                  // 0.0
/*434 */         block[0x27] = temp_block[0x27]; block[0x2B] = temp_block[0x2E];                                                      // 0.0
/*436 */         if(last_non_zero_p1 <= 56) goto end;                                                                                 // 0.0
/*438 */         block[0x36] = temp_block[0x35]; block[0x3A] = temp_block[0x3C];                                                      // 0.0
/*440 */         block[0x3E] = temp_block[0x3D]; block[0x33] = temp_block[0x36];                                                      // 0.0
/*442 */         block[0x2F] = temp_block[0x2F]; block[0x37] = temp_block[0x37];                                                      // 0.0
/*444 */         block[0x3B] = temp_block[0x3E]; block[0x3F] = temp_block[0x3F];                                                      // 0.0
/*446 */     }else{                                                                                                                   // 0.0
/*448 */         if(last_non_zero_p1 <= 1) goto end;                                                                                  // 0.0
/*450 */         block[0x01] = temp_block[0x01];                                                                                      // 0.0
/*452 */         block[0x08] = temp_block[0x08]; block[0x10] = temp_block[0x10];                                                      // 0.0
/*454 */         if(last_non_zero_p1 <= 4) goto end;                                                                                  // 0.0
/*456 */         block[0x09] = temp_block[0x09]; block[0x02] = temp_block[0x02];                                                      // 0.0
/*458 */         block[0x03] = temp_block[0x03];                                                                                      // 0.0
/*460 */         if(last_non_zero_p1 <= 7) goto end;                                                                                  // 0.0
/*462 */         block[0x0A] = temp_block[0x0A]; block[0x11] = temp_block[0x11];                                                      // 0.0
/*464 */         block[0x18] = temp_block[0x18]; block[0x20] = temp_block[0x20];                                                      // 0.0
/*466 */         if(last_non_zero_p1 <= 11) goto end;                                                                                 // 0.0
/*468 */         block[0x19] = temp_block[0x19];                                                                                      // 0.0
/*470 */         block[0x12] = temp_block[0x12]; block[0x0B] = temp_block[0x0B];                                                      // 0.0
/*472 */         block[0x04] = temp_block[0x04]; block[0x05] = temp_block[0x05];                                                      // 0.0
/*474 */         if(last_non_zero_p1 <= 16) goto end;                                                                                 // 0.0
/*476 */         block[0x0C] = temp_block[0x0C]; block[0x13] = temp_block[0x13];                                                      // 0.0
/*478 */         block[0x1A] = temp_block[0x1A]; block[0x21] = temp_block[0x21];                                                      // 0.0
/*480 */         block[0x28] = temp_block[0x28]; block[0x30] = temp_block[0x30];                                                      // 0.0
/*482 */         block[0x29] = temp_block[0x29]; block[0x22] = temp_block[0x22];                                                      // 0.0
/*484 */         if(last_non_zero_p1 <= 24) goto end;                                                                                 // 0.0
/*486 */         block[0x1B] = temp_block[0x1B]; block[0x14] = temp_block[0x14];                                                      // 0.0
/*488 */         block[0x0D] = temp_block[0x0D]; block[0x06] = temp_block[0x06];                                                      // 0.0
/*490 */         block[0x07] = temp_block[0x07]; block[0x0E] = temp_block[0x0E];                                                      // 0.0
/*492 */         block[0x15] = temp_block[0x15]; block[0x1C] = temp_block[0x1C];                                                      // 0.0
/*494 */         if(last_non_zero_p1 <= 32) goto end;                                                                                 // 0.0
/*496 */         block[0x23] = temp_block[0x23]; block[0x2A] = temp_block[0x2A];                                                      // 0.0
/*498 */         block[0x31] = temp_block[0x31]; block[0x38] = temp_block[0x38];                                                      // 0.0
/*500 */         block[0x39] = temp_block[0x39]; block[0x32] = temp_block[0x32];                                                      // 0.0
/*502 */         block[0x2B] = temp_block[0x2B]; block[0x24] = temp_block[0x24];                                                      // 0.0
/*504 */         if(last_non_zero_p1 <= 40) goto end;                                                                                 // 0.0
/*506 */         block[0x1D] = temp_block[0x1D]; block[0x16] = temp_block[0x16];                                                      // 0.0
/*508 */         block[0x0F] = temp_block[0x0F]; block[0x17] = temp_block[0x17];                                                      // 0.0
/*510 */         block[0x1E] = temp_block[0x1E]; block[0x25] = temp_block[0x25];                                                      // 0.0
/*512 */         block[0x2C] = temp_block[0x2C]; block[0x33] = temp_block[0x33];                                                      // 0.0
/*514 */         if(last_non_zero_p1 <= 48) goto end;                                                                                 // 0.0
/*516 */         block[0x3A] = temp_block[0x3A]; block[0x3B] = temp_block[0x3B];                                                      // 0.0
/*518 */         block[0x34] = temp_block[0x34]; block[0x2D] = temp_block[0x2D];                                                      // 0.0
/*520 */         block[0x26] = temp_block[0x26]; block[0x1F] = temp_block[0x1F];                                                      // 0.0
/*522 */         block[0x27] = temp_block[0x27]; block[0x2E] = temp_block[0x2E];                                                      // 0.0
/*524 */         if(last_non_zero_p1 <= 56) goto end;                                                                                 // 0.0
/*526 */         block[0x35] = temp_block[0x35]; block[0x3C] = temp_block[0x3C];                                                      // 0.0
/*528 */         block[0x3D] = temp_block[0x3D]; block[0x36] = temp_block[0x36];                                                      // 0.0
/*530 */         block[0x2F] = temp_block[0x2F]; block[0x37] = temp_block[0x37];                                                      // 0.0
/*532 */         block[0x3E] = temp_block[0x3E]; block[0x3F] = temp_block[0x3F];                                                      // 0.0
/*534 */     }                                                                                                                        // 0.0
/*536 */     end:                                                                                                                     // 0.0
/*538 */     return last_non_zero_p1 - 1;                                                                                             // 0.0
/*540 */ }                                                                                                                            // 0.0
