// commit message qemu@57ef3f1278 (target=0, prob=0.44916195, correct=True): block: Don't try to set *errp directly
/*0  */ bool bdrv_op_is_blocked(BlockDriverState *bs, BlockOpType op, Error **errp)  // (2) 0.1057
/*2  */ {                                                                            // (13) 0.003774
/*4  */     BdrvOpBlocker *blocker;                                                  // (7) 0.04906
/*6  */     assert((int) op >= 0 && op < BLOCK_OP_TYPE_MAX);                         // (5) 0.08302
/*8  */     if (!QLIST_EMPTY(&bs->op_blockers[op])) {                                // (6) 0.08302
/*10 */         blocker = QLIST_FIRST(&bs->op_blockers[op]);                         // (3) 0.09057
/*12 */         if (errp) {                                                          // (8) 0.04906
/*14 */             *errp = error_copy(blocker->reason);                             // (4) 0.09057
/*16 */             error_prepend(errp, "Node '%s' is busy: ",                       // (1) 0.1094
/*18 */                           bdrv_get_device_or_node_name(bs));                 // (0) 0.1547
/*20 */         }                                                                    // (10) 0.03019
/*22 */         return true;                                                         // (9) 0.03774
/*24 */     }                                                                        // (12) 0.01509
/*26 */     return false;                                                            // (11) 0.02264
/*28 */ }                                                                            // (14) 0.003774
