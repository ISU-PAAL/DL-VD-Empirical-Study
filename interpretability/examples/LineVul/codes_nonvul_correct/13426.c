// commit message qemu@079d0b7f1e (target=0, prob=0.35359168, correct=True): usb: Set USBEndpoint in usb_packet_setup().
/*0   */ static int usb_host_handle_control(USBDevice *dev, USBPacket *p,               // (7) 0.04102
/*2   */                int request, int value, int index, int length, uint8_t *data)   // (0) 0.06445
/*4   */ {                                                                              // (31) 0.001953
/*6   */     USBHostDevice *s = DO_UPCAST(USBHostDevice, dev, dev);                     // (4) 0.04492
/*8   */     struct usbdevfs_urb *urb;                                                  // (16) 0.02344
/*10  */     AsyncURB *aurb;                                                            // (18) 0.02148
/*12  */     int ret;                                                                   // (24) 0.01172
/*16  */     /*                                                                         // (27) 0.007813
/*18  */      * Process certain standard device requests.                               // (20) 0.02148
/*20  */      * These are infrequent and are processed synchronously.                   // (14) 0.0293
/*22  */      */                                                                        // (25) 0.009766
/*26  */     /* Note request is (bRequestType << 8) | bRequest */                       // (11) 0.03516
/*28  */     trace_usb_host_req_control(s->bus_num, s->addr, request, value, index);    // (2) 0.05664
/*32  */     switch (request) {                                                         // (23) 0.01562
/*34  */     case DeviceOutRequest | USB_REQ_SET_ADDRESS:                               // (10) 0.03711
/*36  */         return usb_host_set_address(s, value);                                 // (8) 0.03906
/*40  */     case DeviceOutRequest | USB_REQ_SET_CONFIGURATION:                         // (9) 0.03906
/*42  */         return usb_host_set_config(s, value & 0xff);                           // (5) 0.04492
/*46  */     case InterfaceOutRequest | USB_REQ_SET_INTERFACE:                          // (12) 0.03516
/*48  */         return usb_host_set_interface(s, index, value);                        // (6) 0.04297
/*50  */     }                                                                          // (28) 0.007812
/*54  */     /* The rest are asynchronous */                                            // (22) 0.01758
/*58  */     if (length > sizeof(dev->data_buf)) {                                      // (13) 0.03125
/*60  */         fprintf(stderr, "husb: ctrl buffer too small (%d > %zu)\n",            // (1) 0.06055
/*62  */                 length, sizeof(dev->data_buf));                                // (3) 0.04883
/*64  */         return USB_RET_STALL;                                                  // (15) 0.0293
/*66  */     }                                                                          // (29) 0.007812
/*70  */     aurb = async_alloc(s);                                                     // (17) 0.02344
/*72  */     aurb->packet = p;                                                          // (19) 0.02148
/*76  */     /*                                                                         // (30) 0.007812
/*78  */      * Setup ctrl transfer.                                                    // (21) 0.01953
/*80  */      *                                                                         // (26) 0.009766
/*82  */      * s->ctrl is laid out such that data buffer immediately follows           // 0.0
/*84  */      * 'req' struct which is exactly what usbdevfs expects.                    // 0.0
/*86  */      */                                                                        // 0.0
/*88  */     urb = &aurb->urb;                                                          // 0.0
/*92  */     urb->type     = USBDEVFS_URB_TYPE_CONTROL;                                 // 0.0
/*94  */     urb->endpoint = p->devep;                                                  // 0.0
/*98  */     urb->buffer        = &dev->setup_buf;                                      // 0.0
/*100 */     urb->buffer_length = length + 8;                                           // 0.0
/*104 */     urb->usercontext = s;                                                      // 0.0
/*108 */     trace_usb_host_urb_submit(s->bus_num, s->addr, aurb,                       // 0.0
/*110 */                               urb->buffer_length, aurb->more);                 // 0.0
/*112 */     ret = ioctl(s->fd, USBDEVFS_SUBMITURB, urb);                               // 0.0
/*116 */     DPRINTF("husb: submit ctrl. len %u aurb %p\n", urb->buffer_length, aurb);  // 0.0
/*120 */     if (ret < 0) {                                                             // 0.0
/*122 */         DPRINTF("husb: submit failed. errno %d\n", errno);                     // 0.0
/*124 */         async_free(aurb);                                                      // 0.0
/*128 */         switch(errno) {                                                        // 0.0
/*130 */         case ETIMEDOUT:                                                        // 0.0
/*132 */             return USB_RET_NAK;                                                // 0.0
/*134 */         case EPIPE:                                                            // 0.0
/*136 */         default:                                                               // 0.0
/*138 */             return USB_RET_STALL;                                              // 0.0
/*140 */         }                                                                      // 0.0
/*142 */     }                                                                          // 0.0
/*146 */     return USB_RET_ASYNC;                                                      // 0.0
/*148 */ }                                                                              // 0.0
