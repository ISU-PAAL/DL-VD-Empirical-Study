// commit message qemu@788cf9f8c8 (target=1, prob=0.30394614, correct=False): block: rip out all traces of password prompting
/*0  */ void hmp_cont(Monitor *mon, const QDict *qdict)                      // (4) 0.0636
/*2  */ {                                                                    // (16) 0.003534
/*4  */     BlockInfoList *bdev_list, *bdev;                                 // (7) 0.05654
/*6  */     Error *err = NULL;                                               // (11) 0.0318
/*10 */     bdev_list = qmp_query_block(NULL);                               // (5) 0.06007
/*12 */     for (bdev = bdev_list; bdev; bdev = bdev->next) {                // (2) 0.08834
/*14 */         if (key_is_missing(bdev->value)) {                           // (3) 0.0742
/*16 */             monitor_read_block_device_key(mon, bdev->value->device,  // (1) 0.106
/*18 */                                           hmp_cont_cb, NULL);        // (0) 0.1767
/*20 */             goto out;                                                // (9) 0.04947
/*22 */         }                                                            // (12) 0.02827
/*24 */     }                                                                // (13) 0.01413
/*28 */     qmp_cont(&err);                                                  // (10) 0.03534
/*30 */     hmp_handle_error(mon, &err);                                     // (8) 0.053
/*34 */ out:                                                                 // (14) 0.007067
/*36 */     qapi_free_BlockInfoList(bdev_list);                              // (6) 0.06007
/*38 */ }                                                                    // (15) 0.003534
