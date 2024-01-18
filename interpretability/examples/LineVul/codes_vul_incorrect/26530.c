// commit message qemu@b14ef7c9ab (target=1, prob=0.19222626, correct=False): Fix unassigned memory access handling
/*0  */ static uint32_t unassigned_mem_readl(void *opaque, target_phys_addr_t addr)       // (1) 0.1944
/*2  */ {                                                                                 // (8) 0.006944
/*4  */ #ifdef DEBUG_UNASSIGNED                                                           // (4) 0.0625
/*6  */     printf("Unassigned mem read " TARGET_FMT_plx "\n", addr);                     // (2) 0.1667
/*8  */ #endif                                                                            // (6) 0.01389
/*10 */ #if defined(TARGET_ALPHA) || defined(TARGET_SPARC) || defined(TARGET_MICROBLAZE)  // (0) 0.2222
/*12 */     do_unassigned_access(addr, 0, 0, 0, 4);                                       // (3) 0.1458
/*14 */ #endif                                                                            // (7) 0.01389
/*16 */     return 0;                                                                     // (5) 0.04167
/*18 */ }                                                                                 // (9) 0.006944
