// commit message qemu@bc3e6a0d6c (target=1, prob=0.56888616, correct=True): pvpanic: initialization cleanup
/*0 */ int pvpanic_init(ISABus *bus)                         // (1) 0.2407
/*2 */ {                                                     // (3) 0.01852
/*4 */     isa_create_simple(bus, TYPE_ISA_PVPANIC_DEVICE);  // (0) 0.4444
/*6 */     return 0;                                         // (2) 0.1111
/*8 */ }                                                     // (4) 0.01852
