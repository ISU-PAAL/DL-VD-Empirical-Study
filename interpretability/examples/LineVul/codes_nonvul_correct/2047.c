// commit message qemu@64c9bc181f (target=0, prob=0.46427044, correct=True): usb: check RNDIS message length
/*0  */ static void do_token_in(USBDevice *s, USBPacket *p)                 // (12) 0.03711
/*2  */ {                                                                   // (23) 0.001953
/*4  */     int request, value, index;                                      // (20) 0.01953
/*8  */     assert(p->ep->nr == 0);                                         // (15) 0.02539
/*12 */     request = (s->setup_buf[0] << 8) | s->setup_buf[1];             // (5) 0.05078
/*14 */     value   = (s->setup_buf[3] << 8) | s->setup_buf[2];             // (3) 0.05469
/*16 */     index   = (s->setup_buf[5] << 8) | s->setup_buf[4];             // (2) 0.05469
/*18 */                                                                     // (24) 0.001953
/*20 */     switch(s->setup_state) {                                        // (16) 0.02344
/*22 */     case SETUP_STATE_ACK:                                           // (18) 0.02148
/*24 */         if (!(s->setup_buf[0] & USB_DIR_IN)) {                      // (4) 0.05078
/*26 */             usb_device_handle_control(s, p, request, value, index,  // (1) 0.05664
/*28 */                                       s->setup_len, s->data_buf);   // (0) 0.0957
/*30 */             if (p->status == USB_RET_ASYNC) {                       // (8) 0.04883
/*32 */                 return;                                             // (14) 0.0332
/*34 */             }                                                       // (17) 0.02344
/*36 */             s->setup_state = SETUP_STATE_IDLE;                      // (9) 0.04883
/*38 */             p->actual_length = 0;                                   // (13) 0.03711
/*40 */         }                                                           // (22) 0.01562
/*42 */         break;                                                      // (21) 0.01758
/*46 */     case SETUP_STATE_DATA:                                          // (19) 0.02148
/*48 */         if (s->setup_buf[0] & USB_DIR_IN) {                         // (7) 0.04883
/*50 */             int len = s->setup_len - s->setup_index;                // (6) 0.05078
/*52 */             if (len > p->iov.size) {                                // (11) 0.04297
/*54 */                 len = p->iov.size;                                  // (10) 0.04492
/*56 */             }                                                       // 0.0
/*58 */             usb_packet_copy(p, s->data_buf + s->setup_index, len);  // 0.0
/*60 */             s->setup_index += len;                                  // 0.0
/*62 */             if (s->setup_index >= s->setup_len) {                   // 0.0
/*64 */                 s->setup_state = SETUP_STATE_ACK;                   // 0.0
/*66 */             }                                                       // 0.0
/*68 */             return;                                                 // 0.0
/*70 */         }                                                           // 0.0
/*72 */         s->setup_state = SETUP_STATE_IDLE;                          // 0.0
/*74 */         p->status = USB_RET_STALL;                                  // 0.0
/*76 */         break;                                                      // 0.0
/*80 */     default:                                                        // 0.0
/*82 */         p->status = USB_RET_STALL;                                  // 0.0
/*84 */     }                                                               // 0.0
/*86 */ }                                                                   // 0.0
