// commit message qemu@913440249e (target=0, prob=0.015300662, correct=True): usbnet: Drop usbnet_can_receive
/*0  */ static int usbnet_can_receive(NetClientState *nc)                   // (2) 0.1111
/*2  */ {                                                                   // (10) 0.006944
/*4  */     USBNetState *s = qemu_get_nic_opaque(nc);                       // (1) 0.1528
/*8  */     if (!s->dev.config) {                                           // (3) 0.08333
/*10 */         return 0;                                                   // (5) 0.06944
/*12 */     }                                                               // (7) 0.02778
/*16 */     if (is_rndis(s) && s->rndis_state != RNDIS_DATA_INITIALIZED) {  // (0) 0.2431
/*18 */         return 1;                                                   // (6) 0.06944
/*20 */     }                                                               // (8) 0.02778
/*24 */     return !s->in_len;                                              // (4) 0.07639
/*26 */ }                                                                   // (9) 0.006944
