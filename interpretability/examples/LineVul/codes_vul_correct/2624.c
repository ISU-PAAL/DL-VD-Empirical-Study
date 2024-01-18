// commit message qemu@f8ed85ac99 (target=1, prob=0.76803917, correct=True): Fix bad error handling after memory_region_init_ram()
/*0  */ static int idreg_init1(SysBusDevice *dev)                                     // (6) 0.08
/*2  */ {                                                                             // (8) 0.005714
/*4  */     IDRegState *s = MACIO_ID_REGISTER(dev);                                   // (2) 0.1086
/*8  */     memory_region_init_ram(&s->mem, OBJECT(s),                                // (1) 0.1143
/*10 */                            "sun4m.idreg", sizeof(idreg_data), &error_abort);  // (0) 0.2686
/*12 */     vmstate_register_ram_global(&s->mem);                                     // (5) 0.09143
/*14 */     memory_region_set_readonly(&s->mem, true);                                // (4) 0.1029
/*16 */     sysbus_init_mmio(dev, &s->mem);                                           // (3) 0.1029
/*18 */     return 0;                                                                 // (7) 0.03429
/*20 */ }                                                                             // (9) 0.005714
