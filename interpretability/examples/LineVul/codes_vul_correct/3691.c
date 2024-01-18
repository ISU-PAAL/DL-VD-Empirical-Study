// commit message qemu@4f4321c11f (target=1, prob=0.67419094, correct=True): usb: use iovecs in USBPacket
/*0  */ static int ccid_bulk_in_copy_to_guest(USBCCIDState *s, uint8_t *data, int len)  // (3) 0.07261
/*2  */ {                                                                               // (24) 0.002075
/*4  */     int ret = 0;                                                                // (17) 0.0166
/*8  */     assert(len > 0);                                                            // (16) 0.01867
/*10 */     ccid_bulk_in_get(s);                                                        // (13) 0.03112
/*12 */     if (s->current_bulk_in != NULL) {                                           // (11) 0.03527
/*14 */         ret = MIN(s->current_bulk_in->len - s->current_bulk_in->pos, len);      // (4) 0.07261
/*16 */         memcpy(data, s->current_bulk_in->data + s->current_bulk_in->pos, ret);  // (1) 0.07676
/*18 */         s->current_bulk_in->pos += ret;                                         // (8) 0.04149
/*20 */         if (s->current_bulk_in->pos == s->current_bulk_in->len) {               // (5) 0.06639
/*22 */             ccid_bulk_in_release(s);                                            // (7) 0.04772
/*24 */         }                                                                       // (18) 0.0166
/*26 */     } else {                                                                    // (19) 0.01245
/*28 */         /* return when device has no data - usb 2.0 spec Table 8-4 */           // (6) 0.05187
/*30 */         ret = USB_RET_NAK;                                                      // (12) 0.0332
/*32 */     }                                                                           // (21) 0.008299
/*34 */     if (ret > 0) {                                                              // (15) 0.02075
/*36 */         DPRINTF(s, D_MORE_INFO,                                                 // (9) 0.03942
/*38 */                 "%s: %d/%d req/act to guest (BULK_IN)\n", __func__, len, ret);  // (0) 0.09336
/*40 */     }                                                                           // (22) 0.008299
/*42 */     if (ret != USB_RET_NAK && ret < len) {                                      // (10) 0.03942
/*44 */         DPRINTF(s, 1,                                                           // (14) 0.03112
/*46 */             "%s: returning short (EREMOTEIO) %d < %d\n", __func__, ret, len);   // (2) 0.07676
/*48 */     }                                                                           // (23) 0.008299
/*50 */     return ret;                                                                 // (20) 0.01245
/*52 */ }                                                                               // (25) 0.002075
