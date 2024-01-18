// commit message qemu@4f4321c11f (target=1, prob=0.7931638, correct=True): usb: use iovecs in USBPacket
/*0  */ static void usbredir_bulk_packet(void *priv, uint32_t id,                     // (8) 0.04297
/*2  */     struct usb_redir_bulk_packet_header *bulk_packet,                         // (7) 0.04492
/*4  */     uint8_t *data, int data_len)                                              // (13) 0.0293
/*6  */ {                                                                             // (26) 0.001953
/*8  */     USBRedirDevice *dev = priv;                                               // (18) 0.02344
/*10 */     uint8_t ep = bulk_packet->endpoint;                                       // (11) 0.0332
/*12 */     int len = bulk_packet->length;                                            // (17) 0.02539
/*14 */     AsyncURB *aurb;                                                           // (20) 0.02148
/*18 */     DPRINTF("bulk-in status %d ep %02X len %d id %u\n", bulk_packet->status,  // (0) 0.06641
/*20 */             ep, len, id);                                                     // (10) 0.0332
/*24 */     aurb = async_find(dev, id);                                               // (14) 0.02734
/*26 */     if (!aurb) {                                                              // (22) 0.01758
/*28 */         free(data);                                                           // (21) 0.02148
/*30 */         return;                                                               // (23) 0.01758
/*32 */     }                                                                         // (24) 0.007812
/*36 */     if (aurb->bulk_packet.endpoint != bulk_packet->endpoint ||                // (6) 0.04883
/*38 */             aurb->bulk_packet.stream_id != bulk_packet->stream_id) {          // (2) 0.06641
/*40 */         ERROR("return bulk packet mismatch, please report this!\n");          // (9) 0.04102
/*42 */         len = USB_RET_NAK;                                                    // (12) 0.03125
/*44 */     }                                                                         // (25) 0.007812
/*48 */     if (aurb->packet) {                                                       // (19) 0.02344
/*50 */         len = usbredir_handle_status(dev, bulk_packet->status, len);          // (4) 0.05469
/*52 */         if (len > 0) {                                                        // (15) 0.02734
/*54 */             usbredir_log_data(dev, "bulk data in:", data, data_len);          // (1) 0.06641
/*56 */             if (data_len <= aurb->packet->len) {                              // (5) 0.05078
/*58 */                 memcpy(aurb->packet->data, data, data_len);                   // (3) 0.06445
/*60 */             } else {                                                          // (16) 0.02734
/*62 */                 ERROR("bulk buffer too small (%d > %d)\n", data_len,          // 0.0
/*64 */                       aurb->packet->len);                                     // 0.0
/*66 */                 len = USB_RET_STALL;                                          // 0.0
/*68 */             }                                                                 // 0.0
/*70 */         }                                                                     // 0.0
/*72 */         aurb->packet->len = len;                                              // 0.0
/*74 */         usb_packet_complete(&dev->dev, aurb->packet);                         // 0.0
/*76 */     }                                                                         // 0.0
/*78 */     async_free(dev, aurb);                                                    // 0.0
/*80 */     free(data);                                                               // 0.0
/*82 */ }                                                                             // 0.0
