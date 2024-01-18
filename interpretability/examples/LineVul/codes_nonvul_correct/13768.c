// commit message qemu@a8170e5e97 (target=0, prob=0.0071031577, correct=True): Rename target_phys_addr_t to hwaddr
/*0 */ static bool fw_cfg_comb_valid(void *opaque, target_phys_addr_t addr,  // (1) 0.2604
/*2 */                                   unsigned size, bool is_write)       // (0) 0.4271
/*4 */ {                                                                     // (3) 0.01042
/*6 */     return (size == 1) || (is_write && size == 2);                    // (2) 0.1979
/*8 */ }                                                                     // (4) 0.01042
