// commit message qemu@67251a3113 (target=0, prob=0.446466, correct=True): block: Fix reopen flag inheritance
/*0  */ static int vmdk_reopen_prepare(BDRVReopenState *state,                 // (3) 0.06069
/*2  */                                BlockReopenQueue *queue, Error **errp)  // (0) 0.1214
/*4  */ {                                                                      // (23) 0.00289
/*6  */     BDRVVmdkState *s;                                                  // (7) 0.03757
/*8  */     int ret = -1;                                                      // (13) 0.02601
/*10 */     int i;                                                             // (18) 0.01734
/*12 */     VmdkExtent *e;                                                     // (9) 0.03179
/*16 */     assert(state != NULL);                                             // (14) 0.02601
/*18 */     assert(state->bs != NULL);                                         // (10) 0.03179
/*22 */     if (queue == NULL) {                                               // (11) 0.0289
/*24 */         error_setg(errp, "No reopen queue for VMDK extents");          // (2) 0.07514
/*26 */         goto exit;                                                     // (12) 0.0289
/*28 */     }                                                                  // (20) 0.01156
/*32 */     s = state->bs->opaque;                                             // (8) 0.03468
/*36 */     assert(s != NULL);                                                 // (15) 0.02601
/*40 */     for (i = 0; i < s->num_extents; i++) {                             // (4) 0.06069
/*42 */         e = &s->extents[i];                                            // (6) 0.04913
/*44 */         if (e->file != state->bs->file) {                              // (5) 0.0578
/*46 */             bdrv_reopen_queue(queue, e->file, state->flags);           // (1) 0.08671
/*48 */         }                                                              // (16) 0.02312
/*50 */     }                                                                  // (21) 0.01156
/*52 */     ret = 0;                                                           // (17) 0.02023
/*56 */ exit:                                                                  // (22) 0.00578
/*58 */     return ret;                                                        // (19) 0.01734
/*60 */ }                                                                      // (24) 0.00289
