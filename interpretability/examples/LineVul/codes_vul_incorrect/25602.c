// commit message qemu@4f4321c11f (target=1, prob=0.42949602, correct=False): usb: use iovecs in USBPacket
/*0   */ static int usb_bt_handle_data(USBDevice *dev, USBPacket *p)             // (6) 0.04102
/*2   */ {                                                                       // (27) 0.001954
/*4   */     struct USBBtState *s = (struct USBBtState *) dev->opaque;           // (5) 0.04492
/*6   */     int ret = 0;                                                        // (25) 0.01562
/*10  */     if (!s->config)                                                     // (22) 0.01758
/*12  */         goto fail;                                                      // (21) 0.01953
/*16  */     switch (p->pid) {                                                   // (20) 0.01953
/*18  */     case USB_TOKEN_IN:                                                  // (18) 0.02148
/*20  */         switch (p->devep & 0xf) {                                       // (7) 0.03711
/*22  */         case USB_EVT_EP:                                                // (9) 0.0293
/*24  */             ret = usb_bt_fifo_dequeue(&s->evt, p);                      // (2) 0.05859
/*26  */             break;                                                      // (16) 0.02539
/*30  */         case USB_ACL_EP:                                                // (10) 0.0293
/*32  */             ret = usb_bt_fifo_dequeue(&s->acl, p);                      // (4) 0.05664
/*34  */             break;                                                      // (14) 0.02539
/*38  */         case USB_SCO_EP:                                                // (12) 0.0293
/*40  */             ret = usb_bt_fifo_dequeue(&s->sco, p);                      // (3) 0.05859
/*42  */             break;                                                      // (17) 0.02539
/*46  */         default:                                                        // (24) 0.01758
/*48  */             goto fail;                                                  // (13) 0.02734
/*50  */         }                                                               // (26) 0.01562
/*52  */         break;                                                          // (23) 0.01758
/*56  */     case USB_TOKEN_OUT:                                                 // (19) 0.02148
/*58  */         switch (p->devep & 0xf) {                                       // (8) 0.03711
/*60  */         case USB_ACL_EP:                                                // (11) 0.0293
/*62  */             usb_bt_fifo_out_enqueue(s, &s->outacl, s->hci->acl_send,    // (1) 0.07812
/*64  */                             usb_bt_hci_acl_complete, p->data, p->len);  // (0) 0.08984
/*66  */             break;                                                      // (15) 0.02539
/*70  */         case USB_SCO_EP:                                                // 0.0
/*72  */             usb_bt_fifo_out_enqueue(s, &s->outsco, s->hci->sco_send,    // 0.0
/*74  */                             usb_bt_hci_sco_complete, p->data, p->len);  // 0.0
/*76  */             break;                                                      // 0.0
/*80  */         default:                                                        // 0.0
/*82  */             goto fail;                                                  // 0.0
/*84  */         }                                                               // 0.0
/*86  */         break;                                                          // 0.0
/*90  */     default:                                                            // 0.0
/*92  */     fail:                                                               // 0.0
/*94  */         ret = USB_RET_STALL;                                            // 0.0
/*96  */         break;                                                          // 0.0
/*98  */     }                                                                   // 0.0
/*102 */     return ret;                                                         // 0.0
/*104 */ }                                                                       // 0.0
