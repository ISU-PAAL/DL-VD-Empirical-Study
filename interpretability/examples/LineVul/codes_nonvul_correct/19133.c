// commit message qemu@079d0b7f1e (target=0, prob=0.4638698, correct=True): usb: Set USBEndpoint in usb_packet_setup().
/*0  */ static int do_token_in(USBDevice *s, USBPacket *p)                        // (10) 0.03711
/*2  */ {                                                                         // (24) 0.001953
/*4  */     int request, value, index;                                            // (20) 0.01953
/*6  */     int ret = 0;                                                          // (22) 0.01563
/*10 */     assert(p->devep == 0);                                                // (14) 0.02539
/*14 */     request = (s->setup_buf[0] << 8) | s->setup_buf[1];                   // (5) 0.05078
/*16 */     value   = (s->setup_buf[3] << 8) | s->setup_buf[2];                   // (2) 0.05469
/*18 */     index   = (s->setup_buf[5] << 8) | s->setup_buf[4];                   // (3) 0.05469
/*20 */                                                                           // (25) 0.001953
/*22 */     switch(s->setup_state) {                                              // (15) 0.02344
/*24 */     case SETUP_STATE_ACK:                                                 // (18) 0.02148
/*26 */         if (!(s->setup_buf[0] & USB_DIR_IN)) {                            // (4) 0.05078
/*28 */             ret = usb_device_handle_control(s, p, request, value, index,  // (1) 0.06055
/*30 */                                             s->setup_len, s->data_buf);   // (0) 0.1074
/*32 */             if (ret == USB_RET_ASYNC) {                                   // (8) 0.04492
/*34 */                 return USB_RET_ASYNC;                                     // (9) 0.04492
/*36 */             }                                                             // (16) 0.02344
/*38 */             s->setup_state = SETUP_STATE_IDLE;                            // (7) 0.04883
/*40 */             if (ret > 0)                                                  // (12) 0.0332
/*42 */                 return 0;                                                 // (11) 0.03516
/*44 */             return ret;                                                   // (13) 0.02734
/*46 */         }                                                                 // (23) 0.01562
/*50 */         /* return 0 byte */                                               // (17) 0.02344
/*52 */         return 0;                                                         // (21) 0.01953
/*56 */     case SETUP_STATE_DATA:                                                // (19) 0.02148
/*58 */         if (s->setup_buf[0] & USB_DIR_IN) {                               // (6) 0.04883
/*60 */             int len = s->setup_len - s->setup_index;                      // 0.0
/*62 */             if (len > p->iov.size) {                                      // 0.0
/*64 */                 len = p->iov.size;                                        // 0.0
/*66 */             }                                                             // 0.0
/*68 */             usb_packet_copy(p, s->data_buf + s->setup_index, len);        // 0.0
/*70 */             s->setup_index += len;                                        // 0.0
/*72 */             if (s->setup_index >= s->setup_len)                           // 0.0
/*74 */                 s->setup_state = SETUP_STATE_ACK;                         // 0.0
/*76 */             return len;                                                   // 0.0
/*78 */         }                                                                 // 0.0
/*82 */         s->setup_state = SETUP_STATE_IDLE;                                // 0.0
/*84 */         return USB_RET_STALL;                                             // 0.0
/*88 */     default:                                                              // 0.0
/*90 */         return USB_RET_STALL;                                             // 0.0
/*92 */     }                                                                     // 0.0
/*94 */ }                                                                         // 0.0
