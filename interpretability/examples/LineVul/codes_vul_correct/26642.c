// commit message qemu@4f4321c11f (target=1, prob=0.55345076, correct=True): usb: use iovecs in USBPacket
/*0  */ static int bt_hid_in(struct bt_hid_device_s *s)                   // (1) 0.1479
/*2  */ {                                                                 // (8) 0.007042
/*4  */     USBPacket p;                                                  // (7) 0.05634
/*8  */     p.pid = USB_TOKEN_IN;                                         // (3) 0.09859
/*10 */     p.devep = 1;                                                  // (5) 0.07746
/*12 */     p.data = s->datain.buffer;                                    // (4) 0.09859
/*14 */     p.len = sizeof(s->datain.buffer);                             // (2) 0.1127
/*16 */     s->datain.len = s->usbdev->info->handle_data(s->usbdev, &p);  // (0) 0.2042
/*20 */     return s->datain.len;                                         // (6) 0.07746
/*22 */ }                                                                 // (9) 0.007042
