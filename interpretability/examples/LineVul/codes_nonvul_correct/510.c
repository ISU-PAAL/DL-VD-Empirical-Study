// commit message qemu@a35faa94c8 (target=0, prob=0.29365614, correct=True): hw/pl061: Convert to VMState
/*0  */ static void pl061_register_devices(void)                        // (4) 0.08759
/*2  */ {                                                               // (5) 0.007299
/*4  */     sysbus_register_dev("pl061", sizeof(pl061_state),           // (3) 0.1606
/*6  */                         pl061_init_arm);                        // (1) 0.2263
/*8  */     sysbus_register_dev("pl061_luminary", sizeof(pl061_state),  // (2) 0.1898
/*10 */                         pl061_init_luminary);                   // (0) 0.2409
/*12 */ }                                                               // (6) 0.007299
