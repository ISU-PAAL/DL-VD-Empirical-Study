// commit message qemu@8e65b7c049 (target=0, prob=0.21787298, correct=True): audio streaming from usb devices
/*0  */ static void uhci_async_complete(USBPacket *packet, void *opaque)                     // (1) 0.176
/*2  */ {                                                                                    // (6) 0.008
/*4  */     UHCIState *s = opaque;                                                           // (4) 0.096
/*6  */     UHCIAsync *async = (UHCIAsync *) packet;                                         // (2) 0.152
/*10 */     DPRINTF("uhci: async complete. td 0x%x token 0x%x\n", async->td, async->token);  // (0) 0.272
/*14 */     async->done = 1;                                                                 // (5) 0.072
/*18 */     uhci_process_frame(s);                                                           // (3) 0.096
/*20 */ }                                                                                    // (7) 0.008
