// commit message qemu@cf29a570a7 (target=1, prob=0.5440772, correct=True): quorum: Add the rewrite-corrupted parameter to quorum
/*0   */ static void quorum_vote(QuorumAIOCB *acb)                                      // (8) 0.03125
/*2   */ {                                                                              // (34) 0.001953
/*4   */     bool quorum = true;                                                        // (21) 0.01758
/*6   */     int i, j, ret;                                                             // (18) 0.01953
/*8   */     QuorumVoteValue hash;                                                      // (20) 0.01758
/*10  */     BDRVQuorumState *s = acb->common.bs->opaque;                               // (2) 0.04297
/*12  */     QuorumVoteVersion *winner;                                                 // (17) 0.01953
/*16  */     if (quorum_has_too_much_io_failed(acb)) {                                  // (3) 0.04297
/*18  */         return;                                                                // (22) 0.01758
/*20  */     }                                                                          // (32) 0.007812
/*24  */     /* get the index of the first successful read */                           // (12) 0.02539
/*26  */     for (i = 0; i < s->num_children; i++) {                                    // (7) 0.03906
/*28  */         if (!acb->qcrs[i].ret) {                                               // (5) 0.04102
/*30  */             break;                                                             // (13) 0.02539
/*32  */         }                                                                      // (25) 0.01562
/*34  */     }                                                                          // (30) 0.007813
/*38  */     assert(i < s->num_children);                                               // (11) 0.02539
/*42  */     /* compare this read with all other successful reads stopping at quorum    // (9) 0.03125
/*44  */      * failure                                                                 // (28) 0.01172
/*46  */      */                                                                        // (29) 0.009766
/*48  */     for (j = i + 1; j < s->num_children; j++) {                                // (4) 0.04297
/*50  */         if (acb->qcrs[j].ret) {                                                // (6) 0.04102
/*52  */             continue;                                                          // (14) 0.02539
/*54  */         }                                                                      // (26) 0.01562
/*56  */         quorum = quorum_compare(acb, &acb->qcrs[i].qiov, &acb->qcrs[j].qiov);  // (0) 0.08789
/*58  */         if (!quorum) {                                                         // (15) 0.02539
/*60  */             break;                                                             // (16) 0.02539
/*62  */        }                                                                       // (27) 0.01367
/*64  */     }                                                                          // (33) 0.007812
/*68  */     /* Every successful read agrees */                                         // (19) 0.01758
/*70  */     if (quorum) {                                                              // (23) 0.01758
/*72  */         quorum_copy_qiov(acb->qiov, &acb->qcrs[i].qiov);                       // (1) 0.06641
/*74  */         return;                                                                // (24) 0.01758
/*76  */     }                                                                          // (31) 0.007813
/*80  */     /* compute hashes for each successful read, also store indexes */          // (10) 0.0293
/*82  */     for (i = 0; i < s->num_children; i++) {                                    // 0.0
/*84  */         if (acb->qcrs[i].ret) {                                                // 0.0
/*86  */             continue;                                                          // 0.0
/*88  */         }                                                                      // 0.0
/*90  */         ret = quorum_compute_hash(acb, i, &hash);                              // 0.0
/*92  */         /* if ever the hash computation failed */                              // 0.0
/*94  */         if (ret < 0) {                                                         // 0.0
/*96  */             acb->vote_ret = ret;                                               // 0.0
/*98  */             goto free_exit;                                                    // 0.0
/*100 */         }                                                                      // 0.0
/*102 */         quorum_count_vote(&acb->votes, &hash, i);                              // 0.0
/*104 */     }                                                                          // 0.0
/*108 */     /* vote to select the most represented version */                          // 0.0
/*110 */     winner = quorum_get_vote_winner(&acb->votes);                              // 0.0
/*114 */     /* if the winner count is smaller than threshold the read fails */         // 0.0
/*116 */     if (winner->vote_count < s->threshold) {                                   // 0.0
/*118 */         quorum_report_failure(acb);                                            // 0.0
/*120 */         acb->vote_ret = -EIO;                                                  // 0.0
/*122 */         goto free_exit;                                                        // 0.0
/*124 */     }                                                                          // 0.0
/*128 */     /* we have a winner: copy it */                                            // 0.0
/*130 */     quorum_copy_qiov(acb->qiov, &acb->qcrs[winner->index].qiov);               // 0.0
/*134 */     /* some versions are bad print them */                                     // 0.0
/*136 */     quorum_report_bad_versions(s, acb, &winner->value);                        // 0.0
/*140 */ free_exit:                                                                     // 0.0
/*142 */     /* free lists */                                                           // 0.0
/*144 */     quorum_free_vote_list(&acb->votes);                                        // 0.0
/*146 */ }                                                                              // 0.0
