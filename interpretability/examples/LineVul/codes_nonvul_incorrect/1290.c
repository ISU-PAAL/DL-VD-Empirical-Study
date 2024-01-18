// commit message qemu@e0891bd8bf (target=0, prob=0.6498703, correct=False): xilinx_spips: Fix bus setup conditional check
/*0 */ static inline int num_effective_busses(XilinxSPIPS *s)                      // (2) 0.1638
/*2 */ {                                                                           // (3) 0.008621
/*4 */     return (s->regs[R_LQSPI_STS] & LQSPI_CFG_SEP_BUS &&                     // (1) 0.2931
/*6 */             s->regs[R_LQSPI_STS] & LQSPI_CFG_TWO_MEM) ? s->num_busses : 1;  // (0) 0.4483
/*8 */ }                                                                           // (4) 0.008621
