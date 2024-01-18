// commit message qemu@42bb9c9178 (target=0, prob=0.19418801, correct=True): stream: Remove app argument hack
/*0   */ static void stream_process_mem2s(struct Stream *s,                    // (13) 0.0293
/*2   */                                  StreamSlave *tx_dev)                 // (0) 0.07813
/*4   */ {                                                                     // (25) 0.001953
/*6   */     uint32_t prev_d;                                                  // (16) 0.02148
/*8   */     unsigned char txbuf[16 * 1024];                                   // (15) 0.02344
/*10  */     unsigned int txlen;                                               // (20) 0.01563
/*12  */     uint32_t app[6];                                                  // (17) 0.02148
/*16  */     if (!stream_running(s) || stream_idle(s)) {                       // (11) 0.03906
/*18  */         return;                                                       // (18) 0.01758
/*20  */     }                                                                 // (24) 0.007812
/*24  */     while (1) {                                                       // (19) 0.01563
/*26  */         stream_desc_load(s, s->regs[R_CURDESC]);                      // (4) 0.05273
/*30  */         if (s->desc.status & SDESC_STATUS_COMPLETE) {                 // (6) 0.05078
/*32  */             s->regs[R_DMASR] |= DMASR_HALTED;                         // (2) 0.0625
/*34  */             break;                                                    // (14) 0.02539
/*36  */         }                                                             // (21) 0.01562
/*40  */         if (stream_desc_sof(&s->desc)) {                              // (10) 0.04102
/*42  */             s->pos = 0;                                               // (12) 0.0332
/*44  */             memcpy(app, s->desc.app, sizeof app);                     // (7) 0.05078
/*46  */         }                                                             // (22) 0.01562
/*50  */         txlen = s->desc.control & SDESC_CTRL_LEN_MASK;                // (3) 0.05664
/*52  */         if ((txlen + s->pos) > sizeof txbuf) {                        // (9) 0.04297
/*54  */             hw_error("%s: too small internal txbuf! %d\n", __func__,  // (1) 0.06641
/*56  */                      txlen + s->pos);                                 // (5) 0.05273
/*58  */         }                                                             // (23) 0.01562
/*62  */         cpu_physical_memory_read(s->desc.buffer_address,              // (8) 0.04492
/*64  */                                  txbuf + s->pos, txlen);              // 0.0
/*66  */         s->pos += txlen;                                              // 0.0
/*70  */         if (stream_desc_eof(&s->desc)) {                              // 0.0
/*72  */             stream_push(tx_dev, txbuf, s->pos, app);                  // 0.0
/*74  */             s->pos = 0;                                               // 0.0
/*76  */             stream_complete(s);                                       // 0.0
/*78  */         }                                                             // 0.0
/*82  */         /* Update the descriptor.  */                                 // 0.0
/*84  */         s->desc.status = txlen | SDESC_STATUS_COMPLETE;               // 0.0
/*86  */         stream_desc_store(s, s->regs[R_CURDESC]);                     // 0.0
/*90  */         /* Advance.  */                                               // 0.0
/*92  */         prev_d = s->regs[R_CURDESC];                                  // 0.0
/*94  */         s->regs[R_CURDESC] = s->desc.nxtdesc;                         // 0.0
/*96  */         if (prev_d == s->regs[R_TAILDESC]) {                          // 0.0
/*98  */             s->regs[R_DMASR] |= DMASR_IDLE;                           // 0.0
/*100 */             break;                                                    // 0.0
/*102 */         }                                                             // 0.0
/*104 */     }                                                                 // 0.0
/*106 */ }                                                                     // 0.0
