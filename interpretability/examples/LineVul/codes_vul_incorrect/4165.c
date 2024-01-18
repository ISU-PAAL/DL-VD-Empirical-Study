// commit message qemu@d3ac1a87b2 (target=1, prob=0.19224487, correct=False): usb-storage: fix NULL pointer dereference.
/*0 */ static void usb_msd_cancel_io(USBDevice *dev, USBPacket *p)  // (0) 0.3194
/*2 */ {                                                            // (4) 0.01389
/*4 */     MSDState *s = DO_UPCAST(MSDState, dev, dev);             // (1) 0.3194
/*6 */     scsi_req_cancel(s->req);                                 // (2) 0.2083
/*8 */ }                                                            // (3) 0.01389
