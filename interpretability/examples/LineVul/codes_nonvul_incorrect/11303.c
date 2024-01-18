// commit message qemu@b9c532903f (target=0, prob=0.53281933, correct=False): rbd: always set out parameter in qemu_rbd_snap_list
/*0  */ static int qemu_rbd_snap_list(BlockDriverState *bs,                    // (9) 0.03711
/*2  */                               QEMUSnapshotInfo **psn_tab)              // (0) 0.08203
/*4  */ {                                                                      // (25) 0.001953
/*6  */     BDRVRBDState *s = bs->opaque;                                      // (12) 0.0332
/*8  */     QEMUSnapshotInfo *sn_info, *sn_tab = NULL;                         // (7) 0.04297
/*10 */     int i, snap_count;                                                 // (21) 0.01953
/*12 */     rbd_snap_info_t *snaps;                                            // (17) 0.0293
/*14 */     int max_snaps = RBD_MAX_SNAPS;                                     // (13) 0.0332
/*18 */     do {                                                               // (23) 0.009766
/*20 */         snaps = g_malloc(sizeof(*snaps) * max_snaps);                  // (5) 0.05078
/*22 */         snap_count = rbd_snap_list(s->image, snaps, &max_snaps);       // (2) 0.05859
/*24 */         if (snap_count < 0) {                                          // (16) 0.03125
/*26 */             g_free(snaps);                                             // (10) 0.03516
/*28 */         }                                                              // (22) 0.01562
/*30 */     } while (snap_count == -ERANGE);                                   // (18) 0.02734
/*34 */     if (snap_count <= 0) {                                             // (19) 0.02344
/*36 */         return snap_count;                                             // (20) 0.02344
/*38 */     }                                                                  // (24) 0.007812
/*42 */     sn_tab = g_malloc0(snap_count * sizeof(QEMUSnapshotInfo));         // (4) 0.05273
/*46 */     for (i = 0; i < snap_count; i++) {                                 // (11) 0.03516
/*48 */         const char *snap_name = snaps[i].name;                         // (8) 0.03906
/*52 */         sn_info = sn_tab + i;                                          // (14) 0.0332
/*54 */         pstrcpy(sn_info->id_str, sizeof(sn_info->id_str), snap_name);  // (1) 0.06641
/*56 */         pstrcpy(sn_info->name, sizeof(sn_info->name), snap_name);      // (3) 0.05859
/*60 */         sn_info->vm_state_size = snaps[i].size;                        // (6) 0.04492
/*62 */         sn_info->date_sec = 0;                                         // (15) 0.0332
/*64 */         sn_info->date_nsec = 0;                                        // 0.0
/*66 */         sn_info->vm_clock_nsec = 0;                                    // 0.0
/*68 */     }                                                                  // 0.0
/*70 */     rbd_snap_list_end(snaps);                                          // 0.0
/*74 */     *psn_tab = sn_tab;                                                 // 0.0
/*76 */     return snap_count;                                                 // 0.0
/*78 */ }                                                                      // 0.0
