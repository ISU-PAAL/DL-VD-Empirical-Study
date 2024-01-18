// commit message qemu@ddca7f86ac (target=0, prob=0.21108578, correct=True): hw/9pfs: Add validation to {un}marshal code
/*0  */ static void v9fs_link(void *opaque)                               // (14) 0.03002
/*2  */ {                                                                 // (29) 0.002309
/*4  */     V9fsPDU *pdu = opaque;                                        // (9) 0.03233
/*6  */     V9fsState *s = pdu->s;                                        // (6) 0.03464
/*8  */     int32_t dfid, oldfid;                                         // (10) 0.03233
/*10 */     V9fsFidState *dfidp, *oldfidp;                                // (3) 0.04619
/*12 */     V9fsString name;                                              // (21) 0.02079
/*14 */     size_t offset = 7;                                            // (20) 0.02309
/*16 */     int err = 0;                                                  // (22) 0.01848
/*20 */     pdu_unmarshal(pdu, offset, "dds", &dfid, &oldfid, &name);     // (1) 0.07159
/*22 */     trace_v9fs_link(pdu->tag, pdu->id, dfid, oldfid, name.data);  // (0) 0.0739
/*26 */     dfidp = get_fid(pdu, dfid);                                   // (5) 0.04157
/*28 */     if (dfidp == NULL) {                                          // (17) 0.02771
/*30 */         err = -ENOENT;                                            // (12) 0.03233
/*32 */         goto out_nofid;                                           // (11) 0.03233
/*34 */     }                                                             // (25) 0.009238
/*38 */     oldfidp = get_fid(pdu, oldfid);                               // (4) 0.04619
/*40 */     if (oldfidp == NULL) {                                        // (16) 0.03002
/*42 */         err = -ENOENT;                                            // (13) 0.03233
/*44 */         goto out;                                                 // (19) 0.02309
/*46 */     }                                                             // (26) 0.009238
/*48 */     err = v9fs_co_link(pdu, oldfidp, dfidp, &name);               // (2) 0.06467
/*50 */     if (!err) {                                                   // (23) 0.01848
/*52 */         err = offset;                                             // (18) 0.0254
/*54 */     }                                                             // (27) 0.009238
/*56 */ out:                                                              // (28) 0.004619
/*58 */     put_fid(pdu, dfidp);                                          // (8) 0.03464
/*60 */ out_nofid:                                                        // (24) 0.01386
/*62 */     v9fs_string_free(&name);                                      // (15) 0.03002
/*64 */     complete_pdu(s, pdu, err);                                    // (7) 0.03464
/*66 */ }                                                                 // (30) 0.002309
