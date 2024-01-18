// commit message qemu@4105de6732 (target=1, prob=0.015928948, correct=False): only check RCTL_EN in e1000_can_receive()
/*0  */ e1000_can_receive(void *opaque)                     // (2) 0.1383
/*2  */ {                                                   // (4) 0.01064
/*4  */     E1000State *s = opaque;                         // (3) 0.117
/*8  */     return (!(s->mac_reg[RCTL] & E1000_RCTL_EN) ||  // (1) 0.2872
/*10 */             s->mac_reg[RDH] != s->mac_reg[RDT]);    // (0) 0.3191
/*12 */ }                                                   // (5) 0.01064
