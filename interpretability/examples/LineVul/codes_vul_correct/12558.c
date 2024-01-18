// commit message qemu@97f3ad3551 (target=1, prob=0.52779126, correct=True): migration: Use g_new() & friends where that makes obvious sense
/*0   */ void hmp_info_snapshots(Monitor *mon, const QDict *qdict)                       // (9) 0.04102
/*2   */ {                                                                               // (29) 0.001953
/*4   */     BlockDriverState *bs, *bs1;                                                 // (13) 0.02539
/*6   */     QEMUSnapshotInfo *sn_tab, *sn, s, *sn_info = &s;                            // (3) 0.05469
/*8   */     int nb_sns, i, ret, available;                                              // (11) 0.03125
/*10  */     int total;                                                                  // (25) 0.01172
/*12  */     int *available_snapshots;                                                   // (19) 0.01953
/*16  */     bs = find_vmstate_bs();                                                     // (14) 0.02539
/*18  */     if (!bs) {                                                                  // (23) 0.01562
/*20  */         monitor_printf(mon, "No available block device supports snapshots\n");  // (6) 0.04492
/*22  */         return;                                                                 // (20) 0.01758
/*24  */     }                                                                           // (26) 0.007812
/*28  */     nb_sns = bdrv_snapshot_list(bs, &sn_tab);                                   // (5) 0.04883
/*30  */     if (nb_sns < 0) {                                                           // (15) 0.02539
/*32  */         monitor_printf(mon, "bdrv_snapshot_list: error %d\n", nb_sns);          // (1) 0.06836
/*34  */         return;                                                                 // (21) 0.01758
/*36  */     }                                                                           // (27) 0.007812
/*40  */     if (nb_sns == 0) {                                                          // (16) 0.02539
/*42  */         monitor_printf(mon, "There is no snapshot available.\n");               // (7) 0.04492
/*44  */         return;                                                                 // (22) 0.01758
/*46  */     }                                                                           // (28) 0.007812
/*50  */     available_snapshots = g_malloc0(sizeof(int) * nb_sns);                      // (4) 0.05078
/*52  */     total = 0;                                                                  // (24) 0.01367
/*54  */     for (i = 0; i < nb_sns; i++) {                                              // (10) 0.03906
/*56  */         sn = &sn_tab[i];                                                        // (12) 0.03125
/*58  */         available = 1;                                                          // (18) 0.02148
/*60  */         bs1 = NULL;                                                             // (17) 0.02539
/*64  */         while ((bs1 = bdrv_next(bs1))) {                                        // (8) 0.04297
/*66  */             if (bdrv_can_snapshot(bs1) && bs1 != bs) {                          // (2) 0.06641
/*68  */                 ret = bdrv_snapshot_find(bs1, sn_info, sn->id_str);             // (0) 0.07617
/*70  */                 if (ret < 0) {                                                  // 0.0
/*72  */                     available = 0;                                              // 0.0
/*74  */                     break;                                                      // 0.0
/*76  */                 }                                                               // 0.0
/*78  */             }                                                                   // 0.0
/*80  */         }                                                                       // 0.0
/*84  */         if (available) {                                                        // 0.0
/*86  */             available_snapshots[total] = i;                                     // 0.0
/*88  */             total++;                                                            // 0.0
/*90  */         }                                                                       // 0.0
/*92  */     }                                                                           // 0.0
/*96  */     if (total > 0) {                                                            // 0.0
/*98  */         bdrv_snapshot_dump((fprintf_function)monitor_printf, mon, NULL);        // 0.0
/*100 */         monitor_printf(mon, "\n");                                              // 0.0
/*102 */         for (i = 0; i < total; i++) {                                           // 0.0
/*104 */             sn = &sn_tab[available_snapshots[i]];                               // 0.0
/*106 */             bdrv_snapshot_dump((fprintf_function)monitor_printf, mon, sn);      // 0.0
/*108 */             monitor_printf(mon, "\n");                                          // 0.0
/*110 */         }                                                                       // 0.0
/*112 */     } else {                                                                    // 0.0
/*114 */         monitor_printf(mon, "There is no suitable snapshot available\n");       // 0.0
/*116 */     }                                                                           // 0.0
/*120 */     g_free(sn_tab);                                                             // 0.0
/*122 */     g_free(available_snapshots);                                                // 0.0
/*126 */ }                                                                               // 0.0
