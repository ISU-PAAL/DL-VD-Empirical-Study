// commit message qemu@df8ad9f128 (target=1, prob=0.014433988, correct=False): nbd: Fully initialize client in case of failed negotiation
/*0 */ static int nbd_can_accept(void)  // (1) 0.3333
/*2 */ {                                // (2) 0.0303
/*4 */     return nb_fds < shared;      // (0) 0.3636
/*6 */ }                                // (3) 0.0303
