// commit message qemu@92c0bba9a9 (target=0, prob=0.004701486, correct=True): omap: remove L4_MUX_HACK
/*0  */ static void omap_l4_io_writeb(void *opaque, target_phys_addr_t addr,    // (2) 0.2126
/*2  */                 uint32_t value)                                         // (3) 0.1654
/*4  */ {                                                                       // (4) 0.007874
/*6  */     unsigned int i = (addr - OMAP2_L4_BASE) >> TARGET_PAGE_BITS;        // (1) 0.2362
/*10 */     return omap_l4_io_writeb_fn[i](omap_l4_io_opaque[i], addr, value);  // (0) 0.2835
/*12 */ }                                                                       // (5) 0.007874
