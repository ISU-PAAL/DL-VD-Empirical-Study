// commit message qemu@c7dfbf3225 (target=1, prob=0.31914335, correct=False): usb: ccid: check ccid apdu length
/*0  */ static void ccid_on_apdu_from_guest(USBCCIDState *s, CCID_XferBlock *recv)     // (2) 0.088
/*2  */ {                                                                              // (17) 0.002667
/*4  */     uint32_t len;                                                              // (12) 0.024
/*8  */     if (ccid_card_status(s) != ICC_STATUS_PRESENT_ACTIVE) {                    // (5) 0.072
/*10 */         DPRINTF(s, 1,                                                          // (10) 0.04
/*12 */                 "usb-ccid: not sending apdu to client, no card connected\n");  // (1) 0.09067
/*14 */         ccid_write_data_block_error(s, recv->hdr.bSlot, recv->hdr.bSeq);       // (0) 0.104
/*16 */         return;                                                                // (13) 0.024
/*18 */     }                                                                          // (15) 0.01067
/*20 */     len = le32_to_cpu(recv->hdr.dwLength);                                     // (9) 0.05867
/*22 */     DPRINTF(s, 1, "%s: seq %d, len %d\n", __func__,                            // (4) 0.07467
/*24 */                 recv->hdr.bSeq, len);                                          // (6) 0.072
/*26 */     ccid_add_pending_answer(s, (CCID_Header *)recv);                           // (8) 0.064
/*28 */     if (s->card) {                                                             // (11) 0.02667
/*30 */         ccid_card_apdu_from_guest(s->card, recv->abData, len);                 // (3) 0.08533
/*32 */     } else {                                                                   // (14) 0.016
/*34 */         DPRINTF(s, D_WARN, "warning: discarded apdu\n");                       // (7) 0.06933
/*36 */     }                                                                          // (16) 0.01067
/*38 */ }                                                                              // (18) 0.002667
