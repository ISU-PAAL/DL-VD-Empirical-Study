// commit message qemu@e3f5ec2b5e (target=0, prob=0.008673411, correct=True): net: pass VLANClientState* as first arg to receive handlers
/*0 */ static void rtl8139_receive(void *opaque, const uint8_t *buf, size_t size)  // (0) 0.4667
/*2 */ {                                                                           // (2) 0.01667
/*4 */     rtl8139_do_receive(opaque, buf, size, 1);                               // (1) 0.3667
/*6 */ }                                                                           // (3) 0.01667
