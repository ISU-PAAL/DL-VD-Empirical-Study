// commit message qemu@b36d24b6c3 (target=1, prob=0.2946282, correct=False): Fix cpuid KVM crash on i386 (Lubomir Rintel)
/*0  */ static void host_cpuid(uint32_t function, uint32_t count,  // (13) 0.03711
/*2  */                        uint32_t *eax, uint32_t *ebx,       // (0) 0.07422
/*4  */                        uint32_t *ecx, uint32_t *edx)       // (1) 0.07422
/*6  */ {                                                          // (20) 0.001953
/*8  */ #if defined(CONFIG_KVM)                                    // (16) 0.01953
/*10 */     uint32_t vec[4];                                       // (15) 0.02148
/*14 */ #ifdef __x86_64__                                          // (18) 0.01758
/*16 */     asm volatile("cpuid"                                   // (17) 0.01953
/*18 */                  : "=a"(vec[0]), "=b"(vec[1]),             // (3) 0.06445
/*20 */                    "=c"(vec[2]), "=d"(vec[3])              // (2) 0.06641
/*22 */                  : "0"(function), "c"(count) : "cc");      // (9) 0.06055
/*24 */ #else                                                      // (19) 0.003906
/*26 */     asm volatile("pusha \n\t"                              // (14) 0.02734
/*28 */                  "cpuid \n\t"                              // (10) 0.04688
/*30 */                  "mov %%eax, 0(%1) \n\t"                   // (4) 0.06445
/*32 */                  "mov %%ebx, 4(%1) \n\t"                   // (5) 0.06445
/*34 */                  "mov %%ecx, 8(%1) \n\t"                   // (6) 0.06445
/*36 */                  "mov %%edx, 12(%1) \n\t"                  // (7) 0.06445
/*38 */                  "popa"                                    // (12) 0.03906
/*40 */                  : : "a"(function), "c"(count), "S"(vec)   // (8) 0.06445
/*42 */                  : "memory", "cc");                        // (11) 0.04492
/*44 */ #endif                                                     // 0.0
/*48 */     if (eax)                                               // 0.0
/*50 */ 	*eax = vec[0];                                            // 0.0
/*52 */     if (ebx)                                               // 0.0
/*54 */ 	*ebx = vec[1];                                            // 0.0
/*56 */     if (ecx)                                               // 0.0
/*58 */ 	*ecx = vec[2];                                            // 0.0
/*60 */     if (edx)                                               // 0.0
/*62 */ 	*edx = vec[3];                                            // 0.0
/*64 */ #endif                                                     // 0.0
/*66 */ }                                                          // 0.0
