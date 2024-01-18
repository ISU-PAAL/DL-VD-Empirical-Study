// commit message qemu@af95738754 (target=0, prob=0.35943413, correct=True): snapshot: fix referencing wrong variable in while loop in do_delvm
/*0  */ void do_delvm(Monitor *mon, const QDict *qdict)                                 // (10) 0.03797
/*2  */ {                                                                               // (23) 0.00211
/*4  */     BlockDriverState *bs, *bs1;                                                 // (13) 0.02743
/*6  */     Error *err = NULL;                                                          // (16) 0.01899
/*8  */     const char *name = qdict_get_str(qdict, "name");                            // (7) 0.0443
/*12 */     bs = find_vmstate_bs();                                                     // (14) 0.02743
/*14 */     if (!bs) {                                                                  // (19) 0.01688
/*16 */         monitor_printf(mon, "No block device supports snapshots\n");            // (5) 0.04641
/*18 */         return;                                                                 // (17) 0.01899
/*20 */     }                                                                           // (21) 0.008439
/*24 */     bs1 = NULL;                                                                 // (18) 0.01899
/*26 */     while ((bs1 = bdrv_next(bs1))) {                                            // (11) 0.03797
/*28 */         if (bdrv_can_snapshot(bs1)) {                                           // (6) 0.04641
/*30 */             bdrv_snapshot_delete_by_id_or_name(bs, name, &err);                 // (4) 0.07384
/*32 */             if (err) {                                                          // (12) 0.03376
/*34 */                 monitor_printf(mon,                                             // (8) 0.0443
/*36 */                                "Error while deleting snapshot on device '%s':"  // (0) 0.08861
/*38 */                                " %s\n",                                         // (3) 0.07595
/*40 */                                bdrv_get_device_name(bs),                        // (1) 0.08861
/*42 */                                error_get_pretty(err));                          // (2) 0.08017
/*44 */                 error_free(err);                                                // (9) 0.0443
/*46 */             }                                                                   // (15) 0.02532
/*48 */         }                                                                       // (20) 0.01688
/*50 */     }                                                                           // (22) 0.008439
/*52 */ }                                                                               // (24) 0.00211
