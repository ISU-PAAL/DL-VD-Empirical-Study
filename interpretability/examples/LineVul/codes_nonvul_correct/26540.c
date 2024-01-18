// commit message qemu@abd696e4f7 (target=0, prob=0.058192678, correct=True): pc-bios/s390-ccw: make checkpatch happy
/*0  */ static void sclp_set_write_mask(void)                    // (8) 0.06087
/*2  */ {                                                        // (10) 0.004348
/*4  */     WriteEventMask *sccb = (void*)_sccb;                 // (5) 0.08261
/*8  */     sccb->h.length = sizeof(WriteEventMask);             // (6) 0.07391
/*10 */     sccb->mask_length = sizeof(unsigned int);            // (7) 0.06956
/*12 */     sccb->receive_mask = SCLP_EVENT_MASK_MSG_ASCII;      // (3) 0.1217
/*14 */     sccb->cp_receive_mask = SCLP_EVENT_MASK_MSG_ASCII;   // (1) 0.1304
/*16 */     sccb->send_mask = SCLP_EVENT_MASK_MSG_ASCII;         // (4) 0.1174
/*18 */     sccb->cp_send_mask = SCLP_EVENT_MASK_MSG_ASCII;      // (2) 0.1261
/*22 */     sclp_service_call(SCLP_CMD_WRITE_EVENT_MASK, sccb);  // (0) 0.1348
/*24 */ }                                                        // (9) 0.004348
