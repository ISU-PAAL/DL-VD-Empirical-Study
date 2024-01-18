// commit message qemu@7f595609b4 (target=0, prob=0.037017506, correct=True): usb-hid: simplify class initialization a bit
/*0  */ static void usb_tablet_class_initfn(ObjectClass *klass, void *data)  // (1) 0.09778
/*2  */ {                                                                    // (10) 0.004444
/*4  */     USBDeviceClass *uc = USB_DEVICE_CLASS(klass);                    // (6) 0.08444
/*8  */     uc->init           = usb_tablet_initfn;                          // (0) 0.1156
/*10 */     uc->product_desc   = "QEMU USB Tablet";                          // (7) 0.08444
/*12 */     uc->usb_desc       = &desc_tablet;                               // (2) 0.09778
/*14 */     uc->handle_packet  = usb_generic_handle_packet;                  // (3) 0.09333
/*16 */     uc->handle_reset   = usb_hid_handle_reset;                       // (5) 0.08889
/*18 */     uc->handle_control = usb_hid_handle_control;                     // (9) 0.08
/*20 */     uc->handle_data    = usb_hid_handle_data;                        // (4) 0.09333
/*22 */     uc->handle_destroy = usb_hid_handle_destroy;                     // (8) 0.08
/*24 */ }                                                                    // (11) 0.004444
