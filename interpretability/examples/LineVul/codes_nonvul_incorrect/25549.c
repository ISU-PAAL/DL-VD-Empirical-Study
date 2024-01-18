// commit message qemu@e1f8c729fa (target=0, prob=0.9291978, correct=False): pxa2xx_pic: update to use qdev
/*0  */ qemu_irq *pxa2xx_pic_init(target_phys_addr_t base, CPUState *env)           // (5) 0.05859
/*2  */ {                                                                           // (23) 0.001953
/*4  */     PXA2xxPICState *s;                                                      // (14) 0.02734
/*6  */     int iomemtype;                                                          // (21) 0.01758
/*8  */     qemu_irq *qi;                                                           // (18) 0.02344
/*12 */     s = (PXA2xxPICState *)                                                  // (8) 0.0293
/*14 */             qemu_mallocz(sizeof(PXA2xxPICState));                           // (3) 0.06055
/*16 */     if (!s)                                                                 // (22) 0.01367
/*18 */         return NULL;                                                        // (20) 0.01953
/*22 */     s->cpu_env = env;                                                       // (19) 0.02148
/*26 */     s->int_pending[0] = 0;                                                  // (9) 0.0293
/*28 */     s->int_pending[1] = 0;                                                  // (10) 0.0293
/*30 */     s->int_enabled[0] = 0;                                                  // (15) 0.02734
/*32 */     s->int_enabled[1] = 0;                                                  // (16) 0.02734
/*34 */     s->is_fiq[0] = 0;                                                       // (11) 0.0293
/*36 */     s->is_fiq[1] = 0;                                                       // (12) 0.0293
/*40 */     qi = qemu_allocate_irqs(pxa2xx_pic_set_irq, s, PXA2XX_PIC_SRCS);        // (0) 0.08398
/*44 */     /* Enable IC memory-mapped registers access.  */                        // (13) 0.0293
/*46 */     iomemtype = cpu_register_io_memory(pxa2xx_pic_readfn,                   // (6) 0.05078
/*48 */                     pxa2xx_pic_writefn, s, DEVICE_NATIVE_ENDIAN);           // (2) 0.07812
/*50 */     cpu_register_physical_memory(base, 0x00100000, iomemtype);              // (7) 0.04688
/*54 */     /* Enable IC coprocessor access.  */                                    // (17) 0.02734
/*56 */     cpu_arm_set_cp_io(env, 6, pxa2xx_pic_cp_read, pxa2xx_pic_cp_write, s);  // (1) 0.08008
/*60 */     register_savevm(NULL, "pxa2xx_pic", 0, 0, pxa2xx_pic_save,              // (4) 0.06055
/*62 */                     pxa2xx_pic_load, s);                                    // 0.0
/*66 */     return qi;                                                              // 0.0
/*68 */ }                                                                           // 0.0
