// commit message qemu@5ac2731cf8 (target=1, prob=0.57295805, correct=True): usb: improve packet state sanity checks
/*0  */ void usb_packet_complete(USBDevice *dev, USBPacket *p)  // (10) 0.04185
/*2  */ {                                                       // (24) 0.002203
/*4  */     USBEndpoint *ep = p->ep;                            // (16) 0.02863
/*6  */     int ret;                                            // (22) 0.01322
/*10 */     assert(p->state == USB_PACKET_ASYNC);               // (12) 0.03965
/*12 */     assert(QTAILQ_FIRST(&ep->queue) == p);              // (8) 0.04405
/*14 */     usb_packet_set_state(p, USB_PACKET_COMPLETE);       // (4) 0.05066
/*16 */     QTAILQ_REMOVE(&ep->queue, p, queue);                // (9) 0.04405
/*18 */     dev->port->ops->complete(dev->port, p);             // (14) 0.03744
/*22 */     while (!QTAILQ_EMPTY(&ep->queue)) {                 // (13) 0.03965
/*24 */         p = QTAILQ_FIRST(&ep->queue);                   // (6) 0.04626
/*26 */         if (p->state == USB_PACKET_ASYNC) {             // (5) 0.05066
/*28 */             break;                                      // (17) 0.02863
/*30 */         }                                               // (20) 0.01762
/*32 */         assert(p->state == USB_PACKET_QUEUED);          // (2) 0.05286
/*34 */         ret = usb_process_one(p);                       // (15) 0.03744
/*36 */         if (ret == USB_RET_ASYNC) {                     // (11) 0.04185
/*38 */             usb_packet_set_state(p, USB_PACKET_ASYNC);  // (0) 0.06828
/*40 */             break;                                      // (18) 0.02863
/*42 */         }                                               // (21) 0.01762
/*44 */         p->result = ret;                                // (19) 0.02863
/*46 */         usb_packet_set_state(p, USB_PACKET_COMPLETE);   // (1) 0.05947
/*48 */         QTAILQ_REMOVE(&ep->queue, p, queue);            // (3) 0.05286
/*50 */         dev->port->ops->complete(dev->port, p);         // (7) 0.04626
/*52 */     }                                                   // (23) 0.008811
/*54 */ }                                                       // (25) 0.002203
