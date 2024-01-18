// commit message qemu@4f4321c11f (target=1, prob=0.80786085, correct=True): usb: use iovecs in USBPacket
/*0  */ static void usbredir_interrupt_packet(void *priv, uint32_t id,                  // (9) 0.04297
/*2  */     struct usb_redir_interrupt_packet_header *interrupt_packet,                 // (7) 0.04492
/*4  */     uint8_t *data, int data_len)                                                // (13) 0.0293
/*6  */ {                                                                               // (26) 0.001953
/*8  */     USBRedirDevice *dev = priv;                                                 // (19) 0.02344
/*10 */     uint8_t ep = interrupt_packet->endpoint;                                    // (11) 0.0332
/*14 */     DPRINTF("interrupt-in status %d ep %02X len %d id %u\n",                    // (4) 0.05273
/*16 */             interrupt_packet->status, ep, data_len, id);                        // (5) 0.05078
/*20 */     if (dev->endpoint[EP2I(ep)].type != USB_ENDPOINT_XFER_INT) {                // (0) 0.06055
/*22 */         ERROR("received int packet for non interrupt endpoint %02X\n", ep);     // (6) 0.04688
/*24 */         free(data);                                                             // (20) 0.02148
/*26 */         return;                                                                 // (21) 0.01758
/*28 */     }                                                                           // (25) 0.007812
/*32 */     if (ep & USB_DIR_IN) {                                                      // (15) 0.02734
/*34 */         if (dev->endpoint[EP2I(ep)].interrupt_started == 0) {                   // (3) 0.05469
/*36 */             DPRINTF("received int packet while not started ep %02X\n", ep);     // (1) 0.05859
/*38 */             free(data);                                                         // (14) 0.0293
/*40 */             return;                                                             // (16) 0.02539
/*42 */         }                                                                       // (22) 0.01562
/*46 */         /* bufp_alloc also adds the packet to the ep queue */                   // (10) 0.04102
/*48 */         bufp_alloc(dev, data, data_len, interrupt_packet->status, ep);          // (2) 0.05664
/*50 */     } else {                                                                    // (24) 0.01172
/*52 */         int len = interrupt_packet->length;                                     // (12) 0.0332
/*56 */         AsyncURB *aurb = async_find(dev, id);                                   // (8) 0.04492
/*58 */         if (!aurb) {                                                            // (17) 0.02539
/*60 */             return;                                                             // (18) 0.02539
/*62 */         }                                                                       // (23) 0.01562
/*66 */         if (aurb->interrupt_packet.endpoint != interrupt_packet->endpoint) {    // 0.0
/*68 */             ERROR("return int packet mismatch, please report this!\n");         // 0.0
/*70 */             len = USB_RET_NAK;                                                  // 0.0
/*72 */         }                                                                       // 0.0
/*76 */         if (aurb->packet) {                                                     // 0.0
/*78 */             aurb->packet->len = usbredir_handle_status(dev,                     // 0.0
/*80 */                                                interrupt_packet->status, len);  // 0.0
/*82 */             usb_packet_complete(&dev->dev, aurb->packet);                       // 0.0
/*84 */         }                                                                       // 0.0
/*86 */         async_free(dev, aurb);                                                  // 0.0
/*88 */     }                                                                           // 0.0
/*90 */ }                                                                               // 0.0
