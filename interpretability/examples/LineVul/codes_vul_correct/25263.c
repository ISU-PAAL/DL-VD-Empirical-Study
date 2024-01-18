// commit message qemu@4f4321c11f (target=1, prob=0.73067373, correct=True): usb: use iovecs in USBPacket
/*0  */ static inline void usb_bt_fifo_out_enqueue(struct USBBtState *s,       // (6) 0.0599
/*2  */                 struct usb_hci_out_fifo_s *fifo,                       // (1) 0.08073
/*4  */                 void (*send)(struct HCIInfo *, const uint8_t *, int),  // (0) 0.08854
/*6  */                 int (*complete)(const uint8_t *, int),                 // (2) 0.07292
/*8  */                 const uint8_t *data, int len)                          // (4) 0.06771
/*10 */ {                                                                      // (19) 0.002604
/*12 */     if (fifo->len) {                                                   // (15) 0.02865
/*14 */         memcpy(fifo->data + fifo->len, data, len);                     // (5) 0.0651
/*16 */         fifo->len += len;                                              // (11) 0.03646
/*18 */         if (complete(fifo->data, fifo->len)) {                         // (7) 0.05729
/*20 */             send(s->hci, fifo->data, fifo->len);                       // (3) 0.07292
/*22 */             fifo->len = 0;                                             // (9) 0.04688
/*24 */         }                                                              // (16) 0.02083
/*26 */     } else if (complete(data, len))                                    // (14) 0.03385
/*28 */         send(s->hci, data, len);                                       // (10) 0.04688
/*30 */     else {                                                             // (17) 0.01302
/*32 */         memcpy(fifo->data, data, len);                                 // (8) 0.05208
/*34 */         fifo->len = len;                                               // (12) 0.03646
/*36 */     }                                                                  // (18) 0.01042
/*40 */     /* TODO: do we need to loop? */                                    // (13) 0.03646
/*42 */ }                                                                      // (20) 0.002604
