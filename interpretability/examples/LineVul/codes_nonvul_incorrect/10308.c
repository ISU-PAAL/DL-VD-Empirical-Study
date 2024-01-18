// commit message FFmpeg@53e5462040 (target=0, prob=0.82385236, correct=False): Replace manual gcc version check by AV_GCC_VERSION_AT_LEAST macro.
/*0   */ inline static void RENAME(hcscale)(SwsContext *c, uint16_t *dst, long dstWidth, const uint8_t *src1, const uint8_t *src2,  // (2) 0.09488
/*2   */                                    int srcW, int xInc, int flags, const int16_t *hChrFilter,                               // (0) 0.1082
/*4   */                                    const int16_t *hChrFilterPos, int hChrFilterSize,                                       // (1) 0.1024
/*6   */                                    int srcFormat, uint8_t *formatConvBuffer,                                               // (3) 0.09271
/*8   */                                    uint32_t *pal)                                                                          // (4) 0.07933
/*10  */ {                                                                                                                          // (15) 0.003489
/*12  */     int32_t av_unused *mmx2FilterPos = c->chrMmx2FilterPos;                                                                // (10) 0.0541
/*14  */     int16_t av_unused *mmx2Filter    = c->chrMmx2Filter;                                                                   // (8) 0.05602
/*16  */     int     av_unused canMMX2BeUsed  = c->canMMX2BeUsed;                                                                   // (7) 0.05604
/*18  */     void    av_unused *mmx2FilterCode= c->chrMmx2FilterCode;                                                               // (9) 0.05416
/*22  */     if (isGray(srcFormat) || srcFormat==PIX_FMT_MONOBLACK || srcFormat==PIX_FMT_MONOWHITE)                                 // (5) 0.07773
/*24  */         return;                                                                                                            // (13) 0.01739
/*28  */     if (srcFormat==PIX_FMT_RGB32_1 || srcFormat==PIX_FMT_BGR32_1) {                                                        // (6) 0.06761
/*30  */         src1 += ALT32_CORR;                                                                                                // (12) 0.03283
/*32  */         src2 += ALT32_CORR;                                                                                                // (11) 0.03283
/*34  */     }                                                                                                                      // (14) 0.007763
/*38  */     if (srcFormat==PIX_FMT_RGB48LE) {                                                                                      // 0.0
/*40  */         src1++;                                                                                                            // 0.0
/*42  */         src2++;                                                                                                            // 0.0
/*44  */     }                                                                                                                      // 0.0
/*48  */     if (c->hcscale_internal) {                                                                                             // 0.0
/*50  */         c->hcscale_internal(formatConvBuffer, formatConvBuffer+VOFW, src1, src2, srcW, pal);                               // 0.0
/*52  */         src1= formatConvBuffer;                                                                                            // 0.0
/*54  */         src2= formatConvBuffer+VOFW;                                                                                       // 0.0
/*56  */     }                                                                                                                      // 0.0
/*60  */ #if COMPILE_TEMPLATE_MMX                                                                                                   // 0.0
/*62  */     // Use the new MMX scaler if the MMX2 one can't be used (it is faster than the x86 ASM one).                           // 0.0
/*64  */     if (!(flags&SWS_FAST_BILINEAR) || (!canMMX2BeUsed))                                                                    // 0.0
/*66  */ #else                                                                                                                      // 0.0
/*68  */     if (!(flags&SWS_FAST_BILINEAR))                                                                                        // 0.0
/*70  */ #endif                                                                                                                     // 0.0
/*72  */     {                                                                                                                      // 0.0
/*74  */         c->hScale(dst     , dstWidth, src1, srcW, xInc, hChrFilter, hChrFilterPos, hChrFilterSize);                        // 0.0
/*76  */         c->hScale(dst+VOFW, dstWidth, src2, srcW, xInc, hChrFilter, hChrFilterPos, hChrFilterSize);                        // 0.0
/*78  */     } else { // fast bilinear upscale / crap downscale                                                                     // 0.0
/*80  */ #if ARCH_X86 && CONFIG_GPL                                                                                                 // 0.0
/*82  */ #if COMPILE_TEMPLATE_MMX2                                                                                                  // 0.0
/*84  */         int i;                                                                                                             // 0.0
/*86  */ #if defined(PIC)                                                                                                           // 0.0
/*88  */         DECLARE_ALIGNED(8, uint64_t, ebxsave);                                                                             // 0.0
/*90  */ #endif                                                                                                                     // 0.0
/*92  */         if (canMMX2BeUsed) {                                                                                               // 0.0
/*94  */             __asm__ volatile(                                                                                              // 0.0
/*96  */ #if defined(PIC)                                                                                                           // 0.0
/*98  */                 "mov          %%"REG_b", %6         \n\t"                                                                  // 0.0
/*100 */ #endif                                                                                                                     // 0.0
/*102 */                 "pxor             %%mm7, %%mm7      \n\t"                                                                  // 0.0
/*104 */                 "mov                 %0, %%"REG_c"  \n\t"                                                                  // 0.0
/*106 */                 "mov                 %1, %%"REG_D"  \n\t"                                                                  // 0.0
/*108 */                 "mov                 %2, %%"REG_d"  \n\t"                                                                  // 0.0
/*110 */                 "mov                 %3, %%"REG_b"  \n\t"                                                                  // 0.0
/*112 */                 "xor          %%"REG_a", %%"REG_a"  \n\t" // i                                                             // 0.0
/*114 */                 PREFETCH"   (%%"REG_c")             \n\t"                                                                  // 0.0
/*116 */                 PREFETCH" 32(%%"REG_c")             \n\t"                                                                  // 0.0
/*118 */                 PREFETCH" 64(%%"REG_c")             \n\t"                                                                  // 0.0
/*122 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*124 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*126 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*128 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*130 */                 "xor          %%"REG_a", %%"REG_a"  \n\t" // i                                                             // 0.0
/*132 */                 "mov                 %5, %%"REG_c"  \n\t" // src                                                           // 0.0
/*134 */                 "mov                 %1, %%"REG_D"  \n\t" // buf1                                                          // 0.0
/*136 */                 "add              $"AV_STRINGIFY(VOF)", %%"REG_D"  \n\t"                                                   // 0.0
/*138 */                 PREFETCH"   (%%"REG_c")             \n\t"                                                                  // 0.0
/*140 */                 PREFETCH" 32(%%"REG_c")             \n\t"                                                                  // 0.0
/*142 */                 PREFETCH" 64(%%"REG_c")             \n\t"                                                                  // 0.0
/*146 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*148 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*150 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*152 */                 CALL_MMX2_FILTER_CODE                                                                                      // 0.0
/*156 */ #if defined(PIC)                                                                                                           // 0.0
/*158 */                 "mov %6, %%"REG_b"    \n\t"                                                                                // 0.0
/*160 */ #endif                                                                                                                     // 0.0
/*162 */                 :: "m" (src1), "m" (dst), "m" (mmx2Filter), "m" (mmx2FilterPos),                                           // 0.0
/*164 */                 "m" (mmx2FilterCode), "m" (src2)                                                                           // 0.0
/*166 */ #if defined(PIC)                                                                                                           // 0.0
/*168 */                 ,"m" (ebxsave)                                                                                             // 0.0
/*170 */ #endif                                                                                                                     // 0.0
/*172 */                 : "%"REG_a, "%"REG_c, "%"REG_d, "%"REG_S, "%"REG_D                                                         // 0.0
/*174 */ #if !defined(PIC)                                                                                                          // 0.0
/*176 */                 ,"%"REG_b                                                                                                  // 0.0
/*178 */ #endif                                                                                                                     // 0.0
/*180 */             );                                                                                                             // 0.0
/*182 */             for (i=dstWidth-1; (i*xInc)>>16 >=srcW-1; i--) {                                                               // 0.0
/*184 */                 //printf("%d %d %d\n", dstWidth, i, srcW);                                                                 // 0.0
/*186 */                 dst[i] = src1[srcW-1]*128;                                                                                 // 0.0
/*188 */                 dst[i+VOFW] = src2[srcW-1]*128;                                                                            // 0.0
/*190 */             }                                                                                                              // 0.0
/*192 */         } else {                                                                                                           // 0.0
/*194 */ #endif /* COMPILE_TEMPLATE_MMX2 */                                                                                         // 0.0
/*196 */             x86_reg xInc_shr16 = (x86_reg) (xInc >> 16);                                                                   // 0.0
/*198 */             uint16_t xInc_mask = xInc & 0xffff;                                                                            // 0.0
/*200 */             __asm__ volatile(                                                                                              // 0.0
/*202 */                 "xor %%"REG_a", %%"REG_a"               \n\t" // i                                                         // 0.0
/*204 */                 "xor %%"REG_d", %%"REG_d"               \n\t" // xx                                                        // 0.0
/*206 */                 "xorl    %%ecx, %%ecx                   \n\t" // xalpha                                                    // 0.0
/*208 */                 ASMALIGN(4)                                                                                                // 0.0
/*210 */                 "1:                                     \n\t"                                                              // 0.0
/*212 */                 "mov        %0, %%"REG_S"               \n\t"                                                              // 0.0
/*214 */                 "movzbl  (%%"REG_S", %%"REG_d"), %%edi  \n\t" //src[xx]                                                    // 0.0
/*216 */                 "movzbl 1(%%"REG_S", %%"REG_d"), %%esi  \n\t" //src[xx+1]                                                  // 0.0
/*218 */                 FAST_BILINEAR_X86                                                                                          // 0.0
/*220 */                 "movw     %%si, (%%"REG_D", %%"REG_a", 2)   \n\t"                                                          // 0.0
/*224 */                 "movzbl    (%5, %%"REG_d"), %%edi       \n\t" //src[xx]                                                    // 0.0
/*226 */                 "movzbl   1(%5, %%"REG_d"), %%esi       \n\t" //src[xx+1]                                                  // 0.0
/*228 */                 FAST_BILINEAR_X86                                                                                          // 0.0
/*230 */                 "movw     %%si, "AV_STRINGIFY(VOF)"(%%"REG_D", %%"REG_a", 2)   \n\t"                                       // 0.0
/*234 */                 "addw       %4, %%cx                    \n\t" //xalpha += xInc&0xFFFF                                      // 0.0
/*236 */                 "adc        %3, %%"REG_d"               \n\t" //xx+= xInc>>16 + carry                                      // 0.0
/*238 */                 "add        $1, %%"REG_a"               \n\t"                                                              // 0.0
/*240 */                 "cmp        %2, %%"REG_a"               \n\t"                                                              // 0.0
/*242 */                 " jb        1b                          \n\t"                                                              // 0.0
/*246 */ /* GCC 3.3 makes MPlayer crash on IA-32 machines when using "g" operand here,                                              // 0.0
/*248 */    which is needed to support GCC 4.0. */                                                                                  // 0.0
/*250 */ #if ARCH_X86_64 && ((__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))                                              // 0.0
/*252 */                 :: "m" (src1), "m" (dst), "g" (dstWidth), "m" (xInc_shr16), "m" (xInc_mask),                               // 0.0
/*254 */ #else                                                                                                                      // 0.0
/*256 */                 :: "m" (src1), "m" (dst), "m" (dstWidth), "m" (xInc_shr16), "m" (xInc_mask),                               // 0.0
/*258 */ #endif                                                                                                                     // 0.0
/*260 */                 "r" (src2)                                                                                                 // 0.0
/*262 */                 : "%"REG_a, "%"REG_d, "%ecx", "%"REG_D, "%esi"                                                             // 0.0
/*264 */             );                                                                                                             // 0.0
/*266 */ #if COMPILE_TEMPLATE_MMX2                                                                                                  // 0.0
/*268 */         } //if MMX2 can't be used                                                                                          // 0.0
/*270 */ #endif                                                                                                                     // 0.0
/*272 */ #else                                                                                                                      // 0.0
/*274 */         c->hcscale_fast(c, dst, dstWidth, src1, src2, srcW, xInc);                                                         // 0.0
/*276 */ #endif /* ARCH_X86 */                                                                                                      // 0.0
/*278 */     }                                                                                                                      // 0.0
/*280 */     if(c->srcRange != c->dstRange && !(isRGB(c->dstFormat) || isBGR(c->dstFormat))) {                                      // 0.0
/*282 */         int i;                                                                                                             // 0.0
/*284 */         //FIXME all pal and rgb srcFormats could do this convertion as well                                                // 0.0
/*286 */         //FIXME all scalers more complex than bilinear could do half of this transform                                     // 0.0
/*288 */         if(c->srcRange) {                                                                                                  // 0.0
/*290 */             for (i=0; i<dstWidth; i++) {                                                                                   // 0.0
/*292 */                 dst[i     ]= (dst[i     ]*1799 + 4081085)>>11; //1469                                                      // 0.0
/*294 */                 dst[i+VOFW]= (dst[i+VOFW]*1799 + 4081085)>>11; //1469                                                      // 0.0
/*296 */             }                                                                                                              // 0.0
/*298 */         } else {                                                                                                           // 0.0
/*300 */             for (i=0; i<dstWidth; i++) {                                                                                   // 0.0
/*302 */                 dst[i     ]= (FFMIN(dst[i     ],30775)*4663 - 9289992)>>12; //-264                                         // 0.0
/*304 */                 dst[i+VOFW]= (FFMIN(dst[i+VOFW],30775)*4663 - 9289992)>>12; //-264                                         // 0.0
/*306 */             }                                                                                                              // 0.0
/*308 */         }                                                                                                                  // 0.0
/*310 */     }                                                                                                                      // 0.0
/*312 */ }                                                                                                                          // 0.0
