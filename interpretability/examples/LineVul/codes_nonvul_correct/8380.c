// commit message qemu@a8170e5e97 (target=0, prob=0.014033324, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t nand_read(void *opaque, target_phys_addr_t addr, unsigned size)  // (1) 0.172
/*2  */ {                                                                                // (9) 0.006369
/*4  */     struct nand_state_t *s = opaque;                                             // (4) 0.09554
/*6  */     uint32_t r;                                                                  // (6) 0.05732
/*8  */     int rdy;                                                                     // (7) 0.04459
/*12 */     r = nand_getio(s->nand);                                                     // (3) 0.1019
/*14 */     nand_getpins(s->nand, &rdy);                                                 // (2) 0.1146
/*16 */     s->rdy = rdy;                                                                // (5) 0.07006
/*20 */     DNAND(printf("%s addr=%x r=%x\n", __func__, addr, r));                       // (0) 0.1847
/*22 */     return r;                                                                    // (8) 0.03822
/*24 */ }                                                                                // (10) 0.006369
