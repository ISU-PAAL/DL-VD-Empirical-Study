// commit message qemu@b074e62205 (target=1, prob=0.8946215, correct=True): s390x/sclpconsole: Fix and simplify interrupt injection
/*0  */ static void receive_from_chr_layer(SCLPConsole *scon, const uint8_t *buf,  // (1) 0.1268
/*2  */                                    int size)                               // (0) 0.1737
/*4  */ {                                                                          // (10) 0.004695
/*6  */     /* read data must fit into current buffer */                           // (8) 0.05634
/*8  */     assert(size <= SIZE_BUFFER_VT220 - scon->iov_data_len);                // (2) 0.1174
/*12 */     /* put byte-stream from character layer into buffer */                 // (6) 0.06573
/*14 */     memcpy(&scon->iov[scon->iov_bs], buf, size);                           // (3) 0.108
/*16 */     scon->iov_data_len += size;                                            // (7) 0.06573
/*18 */     scon->iov_sclp_rest += size;                                           // (4) 0.07042
/*20 */     scon->iov_bs += size;                                                  // (9) 0.05634
/*22 */     scon->event.event_pending = true;                                      // (5) 0.07042
/*24 */ }                                                                          // (11) 0.004695
