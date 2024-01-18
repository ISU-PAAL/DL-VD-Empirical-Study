// commit message qemu@2e29bd0478 (target=1, prob=0.048471548, correct=False): PPC: convert Uni-north to qdev: also fixes Mac99 machine crash
/*0  */ static void pci_unin_main_config_writel (void *opaque, target_phys_addr_t addr,  // (2) 0.1517
/*2  */                                          uint32_t val)                           // (0) 0.2584
/*4  */ {                                                                                // (8) 0.005618
/*6  */     UNINState *s = opaque;                                                       // (5) 0.0618
/*10 */     UNIN_DPRINTF("config_writel addr " TARGET_FMT_plx " val %x\n", addr, val);   // (1) 0.2022
/*12 */ #ifdef TARGET_WORDS_BIGENDIAN                                                    // (3) 0.07303
/*14 */     val = bswap32(val);                                                          // (4) 0.06742
/*16 */ #endif                                                                           // (7) 0.01124
/*20 */     s->config_reg = val;                                                         // (6) 0.0618
/*22 */ }                                                                                // (9) 0.005618
