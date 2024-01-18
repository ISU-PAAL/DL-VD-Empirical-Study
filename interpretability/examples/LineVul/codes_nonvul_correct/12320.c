// commit message qemu@a980a065fb (target=0, prob=0.1372322, correct=True): usb: move USB_REQ_{GET,SET}_CONFIGURATION handling to common code
/*0  */ static int usbnet_can_receive(VLANClientState *nc)              // (2) 0.1491
/*2  */ {                                                               // (5) 0.008772
/*4  */     USBNetState *s = DO_UPCAST(NICState, nc, nc)->opaque;       // (1) 0.2544
/*8  */     if (s->rndis && !s->rndis_state == RNDIS_DATA_INITIALIZED)  // (0) 0.2807
/*10 */         return 1;                                               // (4) 0.08772
/*14 */     return !s->in_len;                                          // (3) 0.09649
/*16 */ }                                                               // (6) 0.008772
