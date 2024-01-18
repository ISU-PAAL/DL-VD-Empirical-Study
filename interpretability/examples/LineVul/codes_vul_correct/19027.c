// commit message qemu@187337f8b0 (target=1, prob=0.9551498, correct=True): Fix off-by-one memory region sizes.
/*0  */ qemu_irq *pxa2xx_pic_init(target_phys_addr_t base, CPUState *env)              // (4) 0.05859
/*2  */ {                                                                              // (23) 0.001953
/*4  */     struct pxa2xx_pic_state_s *s;                                              // (8) 0.0332
/*6  */     int iomemtype;                                                             // (21) 0.01758
/*8  */     qemu_irq *qi;                                                              // (17) 0.02344
/*12 */     s = (struct pxa2xx_pic_state_s *)                                          // (7) 0.03516
/*14 */             qemu_mallocz(sizeof(struct pxa2xx_pic_state_s));                   // (2) 0.06641
/*16 */     if (!s)                                                                    // (22) 0.01367
/*18 */         return NULL;                                                           // (19) 0.01953
/*22 */     s->cpu_env = env;                                                          // (18) 0.02148
/*24 */     s->base = base;                                                            // (20) 0.01758
/*28 */     s->int_pending[0] = 0;                                                     // (10) 0.0293
/*30 */     s->int_pending[1] = 0;                                                     // (11) 0.0293
/*32 */     s->int_enabled[0] = 0;                                                     // (15) 0.02734
/*34 */     s->int_enabled[1] = 0;                                                     // (16) 0.02734
/*36 */     s->is_fiq[0] = 0;                                                          // (12) 0.0293
/*38 */     s->is_fiq[1] = 0;                                                          // (13) 0.0293
/*42 */     qi = qemu_allocate_irqs(pxa2xx_pic_set_irq, s, PXA2XX_PIC_SRCS);           // (0) 0.08398
/*46 */     /* Enable IC memory-mapped registers access.  */                           // (9) 0.0293
/*48 */     iomemtype = cpu_register_io_memory(0, pxa2xx_pic_readfn,                   // (5) 0.05469
/*50 */                     pxa2xx_pic_writefn, s);                                    // (3) 0.06055
/*52 */     cpu_register_physical_memory(base, 0x000fffff, iomemtype);                 // (6) 0.04688
/*56 */     /* Enable IC coprocessor access.  */                                       // (14) 0.02734
/*58 */     cpu_arm_set_cp_io(env, 6, pxa2xx_pic_cp_read, pxa2xx_pic_cp_write, s);     // (1) 0.08008
/*62 */     register_savevm("pxa2xx_pic", 0, 0, pxa2xx_pic_save, pxa2xx_pic_load, s);  // 0.0
/*66 */     return qi;                                                                 // 0.0
/*68 */ }                                                                              // 0.0
