// commit message qemu@d6cf84e1de (target=0, prob=0.56221884, correct=False): slirp: Drop redundant checks from slirp_output
/*0 */ int slirp_can_output(void)                               // (1) 0.2245
/*2 */ {                                                        // (2) 0.02041
/*4 */     return !slirp_vc || qemu_can_send_packet(slirp_vc);  // (0) 0.5714
/*6 */ }                                                        // (3) 0.02041
