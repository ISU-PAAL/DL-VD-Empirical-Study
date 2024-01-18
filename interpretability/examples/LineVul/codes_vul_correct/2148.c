// commit message qemu@93bb131525 (target=1, prob=0.999038, correct=True): hmp: fix memory leak at hmp_info_block_jobs()
/*0  */ void hmp_info_block_jobs(Monitor *mon, const QDict *qdict)                 // (10) 0.04297
/*1  */ {                                                                          // (21) 0.001953
/*2  */     BlockJobInfoList *list;                                                // (13) 0.01953
/*3  */     Error *err = NULL;                                                     // (15) 0.01758
/*4  */     list = qmp_query_block_jobs(&err);                                     // (12) 0.03125
/*5  */     assert(!err);                                                          // (18) 0.01563
/*6  */     if (!list) {                                                           // (19) 0.01562
/*7  */         monitor_printf(mon, "No active jobs\n");                           // (11) 0.03906
/*8  */         return;                                                            // (16) 0.01758
/*9  */     }                                                                      // (20) 0.007813
/*10 */     while (list) {                                                         // (17) 0.01563
/*11 */         if (strcmp(list->value->type, "stream") == 0) {                    // (9) 0.04883
/*12 */             monitor_printf(mon, "Streaming device %s: Completed %" PRId64  // (8) 0.05859
/*13 */                            " of %" PRId64 " bytes, speed limit %" PRId64   // (1) 0.08398
/*14 */                            " bytes/s\n",                                   // (2) 0.06445
/*15 */                            list->value->device,                            // (3) 0.0625
/*16 */                            list->value->offset,                            // (5) 0.0625
/*17 */                            list->value->len,                               // (6) 0.0625
/*18 */                            list->value->speed);                            // (7) 0.0625
/*19 */         } else {                                                           // (14) 0.01953
/*20 */             monitor_printf(mon, "Type %s, device %s: Completed %" PRId64   // (4) 0.0625
/*21 */                            " of %" PRId64 " bytes, speed limit %" PRId64   // (0) 0.08398
/*22 */                            " bytes/s\n",                                   // 0.0
/*23 */                            list->value->type,                              // 0.0
/*24 */                            list->value->device,                            // 0.0
/*25 */                            list->value->offset,                            // 0.0
/*26 */                            list->value->len,                               // 0.0
/*27 */                            list->value->speed);                            // 0.0
/*28 */         }                                                                  // 0.0
/*29 */         list = list->next;                                                 // 0.0
/*30 */     }                                                                      // 0.0
/*31 */ }                                                                          // 0.0
