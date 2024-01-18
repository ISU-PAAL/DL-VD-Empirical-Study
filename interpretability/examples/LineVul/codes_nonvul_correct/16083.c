// commit message qemu@e3f5ec2b5e (target=0, prob=0.014906371, correct=True): net: pass VLANClientState* as first arg to receive handlers
/*0  */ static int stellaris_enet_can_receive(void *opaque)            // (2) 0.1765
/*2  */ {                                                              // (5) 0.009804
/*4  */     stellaris_enet_state *s = (stellaris_enet_state *)opaque;  // (0) 0.2451
/*8  */     if ((s->rctl & SE_RCTL_RXEN) == 0)                         // (1) 0.2255
/*10 */         return 1;                                              // (4) 0.09804
/*14 */     return (s->np < 31);                                       // (3) 0.1078
/*16 */ }                                                              // (6) 0.009804
