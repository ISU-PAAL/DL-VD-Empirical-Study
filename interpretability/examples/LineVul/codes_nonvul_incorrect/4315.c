// commit message qemu@45b339b18c (target=0, prob=0.53893054, correct=False): usb: controllers do not need to check for babble themselves
/*0   */ static int uhci_complete_td(UHCIState *s, UHCI_TD *td, UHCIAsync *async, uint32_t *int_mask)  // (0) 0.08008
/*2   */ {                                                                                             // (26) 0.001953
/*4   */     int len = 0, max_len, err, ret;                                                           // (14) 0.03125
/*6   */     uint8_t pid;                                                                              // (23) 0.01758
/*10  */     max_len = ((td->token >> 21) + 1) & 0x7ff;                                                // (4) 0.04492
/*12  */     pid = td->token & 0xff;                                                                   // (19) 0.02344
/*16  */     ret = async->packet.result;                                                               // (20) 0.02344
/*20  */     if (td->ctrl & TD_CTRL_IOS)                                                               // (13) 0.0332
/*22  */         td->ctrl &= ~TD_CTRL_ACTIVE;                                                          // (7) 0.04102
/*26  */     if (ret < 0)                                                                              // (24) 0.01758
/*28  */         goto out;                                                                             // (22) 0.01953
/*32  */     len = async->packet.result;                                                               // (18) 0.02344
/*34  */     td->ctrl = (td->ctrl & ~0x7ff) | ((len - 1) & 0x7ff);                                     // (1) 0.05859
/*38  */     /* The NAK bit may have been set by a previous frame, so clear it                         // (10) 0.03906
/*40  */        here.  The docs are somewhat unclear, but win2k relies on this                         // (5) 0.04297
/*42  */        behavior.  */                                                                          // (21) 0.01953
/*44  */     td->ctrl &= ~(TD_CTRL_ACTIVE | TD_CTRL_NAK);                                              // (3) 0.05078
/*46  */     if (td->ctrl & TD_CTRL_IOC)                                                               // (12) 0.0332
/*48  */         *int_mask |= 0x01;                                                                    // (11) 0.0332
/*52  */     if (pid == USB_TOKEN_IN) {                                                                // (16) 0.0293
/*54  */         if (len > max_len) {                                                                  // (15) 0.03125
/*56  */             ret = USB_RET_BABBLE;                                                             // (9) 0.04102
/*58  */             goto out;                                                                         // (17) 0.02734
/*60  */         }                                                                                     // (25) 0.01562
/*64  */         if ((td->ctrl & TD_CTRL_SPD) && len < max_len) {                                      // (2) 0.05664
/*66  */             *int_mask |= 0x02;                                                                // (8) 0.04102
/*68  */             /* short packet: do not update QH */                                              // (6) 0.04102
/*70  */             trace_usb_uhci_packet_complete_shortxfer(async->queue->token,                     // 0.0
/*72  */                                                     async->td);                               // 0.0
/*74  */             return TD_RESULT_NEXT_QH;                                                         // 0.0
/*76  */         }                                                                                     // 0.0
/*78  */     }                                                                                         // 0.0
/*82  */     /* success */                                                                             // 0.0
/*84  */     trace_usb_uhci_packet_complete_success(async->queue->token, async->td);                   // 0.0
/*86  */     return TD_RESULT_COMPLETE;                                                                // 0.0
/*90  */ out:                                                                                          // 0.0
/*92  */     /*                                                                                        // 0.0
/*94  */      * We should not do any further processing on a queue with errors!                        // 0.0
/*96  */      * This is esp. important for bulk endpoints with pipelining enabled                      // 0.0
/*98  */      * (redirection to a real USB device), where we must cancel all the                       // 0.0
/*100 */      * transfers after this one so that:                                                      // 0.0
/*102 */      * 1) If they've completed already, they are not processed further                        // 0.0
/*104 */      *    causing more stalls, originating from the same failed transfer                      // 0.0
/*106 */      * 2) If still in flight, they are cancelled before the guest does                        // 0.0
/*108 */      *    a clear stall, otherwise the guest and device can loose sync!                       // 0.0
/*110 */      */                                                                                       // 0.0
/*112 */     while (!QTAILQ_EMPTY(&async->queue->asyncs)) {                                            // 0.0
/*114 */         UHCIAsync *as = QTAILQ_FIRST(&async->queue->asyncs);                                  // 0.0
/*116 */         uhci_async_unlink(as);                                                                // 0.0
/*118 */         uhci_async_cancel(as);                                                                // 0.0
/*120 */     }                                                                                         // 0.0
/*124 */     switch(ret) {                                                                             // 0.0
/*126 */     case USB_RET_STALL:                                                                       // 0.0
/*128 */         td->ctrl |= TD_CTRL_STALL;                                                            // 0.0
/*130 */         td->ctrl &= ~TD_CTRL_ACTIVE;                                                          // 0.0
/*132 */         s->status |= UHCI_STS_USBERR;                                                         // 0.0
/*134 */         if (td->ctrl & TD_CTRL_IOC) {                                                         // 0.0
/*136 */             *int_mask |= 0x01;                                                                // 0.0
/*138 */         }                                                                                     // 0.0
/*140 */         uhci_update_irq(s);                                                                   // 0.0
/*142 */         trace_usb_uhci_packet_complete_stall(async->queue->token, async->td);                 // 0.0
/*144 */         return TD_RESULT_NEXT_QH;                                                             // 0.0
/*148 */     case USB_RET_BABBLE:                                                                      // 0.0
/*150 */         td->ctrl |= TD_CTRL_BABBLE | TD_CTRL_STALL;                                           // 0.0
/*152 */         td->ctrl &= ~TD_CTRL_ACTIVE;                                                          // 0.0
/*154 */         s->status |= UHCI_STS_USBERR;                                                         // 0.0
/*156 */         if (td->ctrl & TD_CTRL_IOC) {                                                         // 0.0
/*158 */             *int_mask |= 0x01;                                                                // 0.0
/*160 */         }                                                                                     // 0.0
/*162 */         uhci_update_irq(s);                                                                   // 0.0
/*164 */         /* frame interrupted */                                                               // 0.0
/*166 */         trace_usb_uhci_packet_complete_babble(async->queue->token, async->td);                // 0.0
/*168 */         return TD_RESULT_STOP_FRAME;                                                          // 0.0
/*172 */     case USB_RET_NAK:                                                                         // 0.0
/*174 */         td->ctrl |= TD_CTRL_NAK;                                                              // 0.0
/*176 */         if (pid == USB_TOKEN_SETUP)                                                           // 0.0
/*178 */             break;                                                                            // 0.0
/*180 */         return TD_RESULT_NEXT_QH;                                                             // 0.0
/*184 */     case USB_RET_IOERROR:                                                                     // 0.0
/*186 */     case USB_RET_NODEV:                                                                       // 0.0
/*188 */     default:                                                                                  // 0.0
/*190 */ 	break;                                                                                       // 0.0
/*192 */     }                                                                                         // 0.0
/*196 */     /* Retry the TD if error count is not zero */                                             // 0.0
/*200 */     td->ctrl |= TD_CTRL_TIMEOUT;                                                              // 0.0
/*202 */     err = (td->ctrl >> TD_CTRL_ERROR_SHIFT) & 3;                                              // 0.0
/*204 */     if (err != 0) {                                                                           // 0.0
/*206 */         err--;                                                                                // 0.0
/*208 */         if (err == 0) {                                                                       // 0.0
/*210 */             td->ctrl &= ~TD_CTRL_ACTIVE;                                                      // 0.0
/*212 */             s->status |= UHCI_STS_USBERR;                                                     // 0.0
/*214 */             if (td->ctrl & TD_CTRL_IOC)                                                       // 0.0
/*216 */                 *int_mask |= 0x01;                                                            // 0.0
/*218 */             uhci_update_irq(s);                                                               // 0.0
/*220 */             trace_usb_uhci_packet_complete_error(async->queue->token,                         // 0.0
/*222 */                                                  async->td);                                  // 0.0
/*224 */         }                                                                                     // 0.0
/*226 */     }                                                                                         // 0.0
/*228 */     td->ctrl = (td->ctrl & ~(3 << TD_CTRL_ERROR_SHIFT)) |                                     // 0.0
/*230 */         (err << TD_CTRL_ERROR_SHIFT);                                                         // 0.0
/*232 */     return TD_RESULT_NEXT_QH;                                                                 // 0.0
/*234 */ }                                                                                             // 0.0
