// commit message qemu@aedbe19297 (target=1, prob=0.26018766, correct=False): shutdown: Prepare for use of an enum in reset/shutdown_request
/*0  */ static void cpu_handle_ioreq(void *opaque)                                   // (14) 0.0293
/*2  */ {                                                                            // (23) 0.001953
/*4  */     XenIOState *state = opaque;                                              // (19) 0.02148
/*6  */     ioreq_t *req = cpu_get_ioreq(state);                                     // (8) 0.04102
/*10 */     handle_buffered_iopage(state);                                           // (16) 0.02539
/*12 */     if (req) {                                                               // (20) 0.01562
/*14 */         ioreq_t copy = *req;                                                 // (13) 0.0332
/*18 */         xen_rmb();                                                           // (18) 0.02344
/*20 */         handle_ioreq(state, &copy);                                          // (12) 0.03516
/*22 */         req->data = copy.data;                                               // (15) 0.0293
/*26 */         if (req->state != STATE_IOREQ_INPROCESS) {                           // (6) 0.04883
/*28 */             fprintf(stderr, "Badness in I/O request ... not in service?!: "  // (4) 0.06445
/*30 */                     "%x, ptr: %x, port: %"PRIx64", "                         // (1) 0.07227
/*32 */                     "data: %"PRIx64", count: %u, size: %u, type: %u\n",      // (0) 0.08984
/*34 */                     req->state, req->data_is_ptr, req->addr,                 // (2) 0.06836
/*36 */                     req->data, req->count, req->size, req->type);            // (3) 0.06836
/*38 */             destroy_hvm_domain(false);                                       // (11) 0.03906
/*40 */             return;                                                          // (17) 0.02539
/*42 */         }                                                                    // (22) 0.01562
/*46 */         xen_wmb(); /* Update ioreq contents /then/ update state. */          // (5) 0.04883
/*50 */         /*                                                                   // (21) 0.01562
/*52 */          * We do this before we send the response so that the tools          // (7) 0.04102
/*54 */          * have the opportunity to pick up on the reset before the           // (10) 0.03906
/*56 */          * guest resumes and does a hlt with interrupts disabled which       // (9) 0.03906
/*58 */          * causes Xen to powerdown the domain.                               // 0.0
/*60 */          */                                                                  // 0.0
/*62 */         if (runstate_is_running()) {                                         // 0.0
/*64 */             if (qemu_shutdown_requested_get()) {                             // 0.0
/*66 */                 destroy_hvm_domain(false);                                   // 0.0
/*68 */             }                                                                // 0.0
/*70 */             if (qemu_reset_requested_get()) {                                // 0.0
/*72 */                 qemu_system_reset(VMRESET_REPORT);                           // 0.0
/*74 */                 destroy_hvm_domain(true);                                    // 0.0
/*76 */             }                                                                // 0.0
/*78 */         }                                                                    // 0.0
/*82 */         req->state = STATE_IORESP_READY;                                     // 0.0
/*84 */         xenevtchn_notify(state->xce_handle,                                  // 0.0
/*86 */                          state->ioreq_local_port[state->send_vcpu]);         // 0.0
/*88 */     }                                                                        // 0.0
/*90 */ }                                                                            // 0.0
