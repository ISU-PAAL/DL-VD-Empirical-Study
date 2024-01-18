// commit message qemu@e0dadc1e9e (target=1, prob=0.9336662, correct=True): aux: Rename aux.[ch] to auxbus.[ch] for the benefit of Windows
/*0  */ static void aux_bridge_init(Object *obj)                // (2) 0.1558
/*2  */ {                                                       // (3) 0.01299
/*4  */     AUXTOI2CState *s = AUXTOI2C(obj);                   // (1) 0.2857
/*8  */     s->i2c_bus = i2c_init_bus(DEVICE(obj), "aux-i2c");  // (0) 0.4026
/*10 */ }                                                       // (4) 0.01299
