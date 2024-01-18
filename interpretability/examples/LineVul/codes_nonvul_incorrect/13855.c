// commit message FFmpeg@9b2c28e6ed (target=0, prob=0.9921704, correct=False): faster 15to16 bit rgb (the mmx routine is limited by memory speed so there is no difference ): but the c routine is faster
/*0  */ void rgb15to16(const uint8_t *src,uint8_t *dst,uint32_t src_size)  // (0) 0.05859
/*2  */ {                                                                  // (32) 0.001953
/*4  */ #ifdef HAVE_MMX                                                    // (26) 0.01367
/*6  */   register const char* s=src+src_size;                             // (20) 0.02539
/*8  */   register char* d=dst+src_size;                                   // (19) 0.02539
/*10 */   register int offs=-src_size;                                     // (24) 0.01953
/*12 */   __asm __volatile(PREFETCH"	%0"::"m"(*(s+offs)):"memory");        // (1) 0.05664
/*14 */   __asm __volatile(                                                // (27) 0.01367
/*16 */ 	"movq	%0, %%mm4\n\t"                                              // (14) 0.0332
/*18 */ 	"movq	%1, %%mm5"                                                  // (21) 0.02539
/*20 */ 	::"m"(mask15b), "m"(mask15rg):"memory");                          // (2) 0.03711
/*22 */   while(offs<0)                                                    // (25) 0.01367
/*24 */   {                                                                // (31) 0.003906
/*26 */ 	__asm __volatile(                                                 // (28) 0.01367
/*28 */ 		PREFETCH"	32%1\n\t"                                              // (17) 0.03125
/*30 */ 		"movq	%1, %%mm0\n\t"                                             // (7) 0.03516
/*32 */ 		"movq	8%1, %%mm2\n\t"                                            // (3) 0.03711
/*34 */ 		"movq	%%mm0, %%mm1\n\t"                                          // (4) 0.03711
/*36 */ 		"movq	%%mm2, %%mm3\n\t"                                          // (5) 0.03711
/*38 */ 		"pand	%%mm4, %%mm0\n\t"                                          // (8) 0.03516
/*40 */ 		"pand	%%mm5, %%mm1\n\t"                                          // (9) 0.03516
/*42 */ 		"pand	%%mm4, %%mm2\n\t"                                          // (10) 0.03516
/*44 */ 		"pand	%%mm5, %%mm3\n\t"                                          // (11) 0.03516
/*46 */ 		"psllq	$1, %%mm1\n\t"                                            // (12) 0.03516
/*48 */ 		"psllq	$1, %%mm3\n\t"                                            // (13) 0.03516
/*50 */ 		"por	%%mm1, %%mm0\n\t"                                           // (15) 0.0332
/*52 */ 		"por	%%mm3, %%mm2\n\t"                                           // (16) 0.0332
/*54 */ 		MOVNTQ"	%%mm0, %0\n\t"                                           // (6) 0.03711
/*56 */ 		MOVNTQ"	%%mm2, 8%0"                                              // (18) 0.03125
/*58 */ 		:"=m"(*(d+offs))                                                 // (22) 0.02344
/*60 */ 		:"m"(*(s+offs))                                                  // (23) 0.02148
/*62 */ 		:"memory");                                                      // (29) 0.009766
/*64 */ 	offs+=16;                                                         // (30) 0.009766
/*66 */   }                                                                // 0.0
/*68 */   __asm __volatile(SFENCE:::"memory");                             // 0.0
/*70 */   __asm __volatile(EMMS:::"memory");                               // 0.0
/*72 */ #else                                                              // 0.0
/*74 */    const uint16_t *s1=( uint16_t * )src;                           // 0.0
/*76 */    uint16_t *d1=( uint16_t * )dst;                                 // 0.0
/*78 */    uint16_t *e=((uint8_t *)s1)+src_size;                           // 0.0
/*80 */    while( s1<e ){                                                  // 0.0
/*82 */      register int x=*( s1++ );                                     // 0.0
/*84 */      /* rrrrrggggggbbbbb                                           // 0.0
/*86 */         0rrrrrgggggbbbbb                                           // 0.0
/*88 */         0111 1111 1110 0000=0x7FE0                                 // 0.0
/*90 */         00000000000001 1111=0x001F */                              // 0.0
/*92 */      *( d1++ )=( x&0x001F )|( ( x&0x7FE0 )<<1 );                   // 0.0
/*94 */    }                                                               // 0.0
/*96 */ #endif                                                             // 0.0
/*98 */ }                                                                  // 0.0
