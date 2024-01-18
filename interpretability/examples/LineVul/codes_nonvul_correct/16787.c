// commit message qemu@a980a065fb (target=0, prob=0.034358904, correct=True): usb: move USB_REQ_{GET,SET}_CONFIGURATION handling to common code
/*0  */ int usb_desc_get_descriptor(USBDevice *dev, int value, uint8_t *dest, size_t len)  // (2) 0.06055
/*2  */ {                                                                                  // (29) 0.001953
/*4  */     const USBDesc *desc = dev->info->usb_desc;                                     // (10) 0.0332
/*6  */     uint8_t buf[256];                                                              // (16) 0.02148
/*8  */     uint8_t type = value >> 8;                                                     // (14) 0.02539
/*10 */     uint8_t index = value & 0xff;                                                  // (12) 0.02734
/*12 */     int ret = -1;                                                                  // (20) 0.01758
/*16 */     switch(type) {                                                                 // (25) 0.01562
/*18 */     case USB_DT_DEVICE:                                                            // (15) 0.02148
/*20 */         ret = usb_desc_device(&desc->id, desc->full, buf, sizeof(buf));            // (3) 0.05664
/*22 */         trace_usb_desc_device(dev->addr, len, ret);                                // (7) 0.04492
/*24 */         break;                                                                     // (21) 0.01758
/*26 */     case USB_DT_CONFIG:                                                            // (17) 0.02148
/*28 */         if (index < desc->full->bNumConfigurations) {                              // (9) 0.04102
/*30 */             ret = usb_desc_config(desc->full->confs + index, buf, sizeof(buf));    // (1) 0.06641
/*32 */         }                                                                          // (26) 0.01562
/*34 */         trace_usb_desc_config(dev->addr, index, len, ret);                         // (4) 0.04883
/*36 */         break;                                                                     // (22) 0.01758
/*38 */     case USB_DT_STRING:                                                            // (18) 0.02148
/*40 */         ret = usb_desc_string(dev, index, buf, sizeof(buf));                       // (5) 0.04883
/*42 */         trace_usb_desc_string(dev->addr, index, len, ret);                         // (6) 0.04883
/*44 */         break;                                                                     // (23) 0.01758
/*46 */     default:                                                                       // (27) 0.009766
/*48 */         fprintf(stderr, "%s: %d unknown type %d (len %zd)\n", __FUNCTION__,        // (0) 0.07227
/*50 */                 dev->addr, type, len);                                             // (8) 0.04492
/*52 */         break;                                                                     // (24) 0.01758
/*54 */     }                                                                              // (28) 0.007812
/*58 */     if (ret > 0) {                                                                 // (19) 0.01953
/*60 */         if (ret > len) {                                                           // (13) 0.02734
/*62 */             ret = len;                                                             // (11) 0.0293
/*64 */         }                                                                          // 0.0
/*66 */         memcpy(dest, buf, ret);                                                    // 0.0
/*68 */     }                                                                              // 0.0
/*70 */     return ret;                                                                    // 0.0
/*72 */ }                                                                                  // 0.0
