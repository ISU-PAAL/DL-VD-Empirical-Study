// commit message qemu@2c8f86961b (target=1, prob=0.54364026, correct=True): tests: fix hd-geo-test leaks
/*0  */ static void test_ide_drive_cd_0(void)                       // (7) 0.05405
/*2  */ {                                                           // (14) 0.003861
/*4  */     char *argv[256];                                        // (9) 0.03861
/*6  */     int argc, ide_idx;                                      // (8) 0.04633
/*8  */     Backend i;                                              // (12) 0.02703
/*12 */     argc = setup_common(argv, ARRAY_SIZE(argv));            // (3) 0.08108
/*14 */     for (i = 0; i <= backend_empty; i++) {                  // (4) 0.0695
/*16 */         ide_idx = backend_empty - i;                        // (5) 0.0695
/*18 */         cur_ide[ide_idx] = &hd_chst[i][mbr_blank];          // (1) 0.1158
/*20 */         argc = setup_ide(argc, argv, ARRAY_SIZE(argv),      // (2) 0.1081
/*22 */                          ide_idx, NULL, i, mbr_blank, "");  // (0) 0.1544
/*24 */     }                                                       // (13) 0.01544
/*26 */     qtest_start(g_strjoinv(" ", argv));                     // (6) 0.0695
/*28 */     test_cmos();                                            // (10) 0.03089
/*30 */     qtest_end();                                            // (11) 0.03089
/*32 */ }                                                           // (15) 0.003861
