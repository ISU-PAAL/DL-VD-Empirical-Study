// commit message qemu@4871b51b92 (target=1, prob=0.9173861, correct=True): vmgenid-test: use boot-sector infrastructure
/*0  */ static void vmgenid_query_monitor_test(void)                                     // (5) 0.05738
/*2  */ {                                                                                // (12) 0.004098
/*4  */     QemuUUID expected, measured;                                                 // (7) 0.04918
/*6  */     gchar *cmd;                                                                  // (11) 0.03279
/*10 */     g_assert(qemu_uuid_parse(VGID_GUID, &expected) == 0);                        // (3) 0.1148
/*14 */     cmd = g_strdup_printf("-machine accel=tcg -device vmgenid,id=testvgid,"      // (1) 0.1311
/*16 */                           "guid=%s", VGID_GUID);                                 // (0) 0.1557
/*18 */     qtest_start(cmd);                                                            // (9) 0.04098
/*22 */     /* Read the GUID via the monitor */                                          // (8) 0.04918
/*24 */     read_guid_from_monitor(&measured);                                           // (4) 0.06148
/*26 */     g_assert(memcmp(measured.data, expected.data, sizeof(measured.data)) == 0);  // (2) 0.1189
/*30 */     qtest_quit(global_qtest);                                                    // (6) 0.05328
/*32 */     g_free(cmd);                                                                 // (10) 0.03689
/*34 */ }                                                                                // (13) 0.004098
