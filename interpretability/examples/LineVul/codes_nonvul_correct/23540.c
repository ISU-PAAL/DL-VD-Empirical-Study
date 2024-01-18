// commit message qemu@10ee2aaa41 (target=0, prob=0.004914916, correct=True): Remove unneded ac97 indirection accessing its state
/*0  */ static void nam_writeb (void *opaque, uint32_t addr, uint32_t val)  // (0) 0.2475
/*2  */ {                                                                   // (5) 0.009901
/*4  */     PCIAC97LinkState *d = opaque;                                   // (3) 0.1287
/*6  */     AC97LinkState *s = &d->ac97;                                    // (2) 0.1584
/*8  */     dolog ("U nam writeb %#x <- %#x\n", addr, val);                 // (1) 0.2475
/*10 */     s->cas = 0;                                                     // (4) 0.08911
/*12 */ }                                                                   // (6) 0.009901
