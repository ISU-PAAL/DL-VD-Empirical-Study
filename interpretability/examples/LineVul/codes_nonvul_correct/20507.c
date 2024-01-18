// commit message qemu@a9c0183059 (target=0, prob=0.012399505, correct=True): hw/sd.c: convert wp_groups in SDState to bitfield
/*0 */ static inline int sd_wp_addr(SDState *sd, uint32_t addr)      // (1) 0.2532
/*2 */ {                                                             // (3) 0.01266
/*4 */     return sd->wp_groups[addr >>                              // (2) 0.1519
/*6 */             (HWBLOCK_SHIFT + SECTOR_SHIFT + WPGROUP_SHIFT)];  // (0) 0.4557
/*8 */ }                                                             // (4) 0.01266
