// commit message qemu@b4ba67d9a7 (target=1, prob=0.98094845, correct=True): libqos: Change PCI accessors to take opaque BAR handle
/*0  */ static void test_tco1_status_bits(void)                                      // (7) 0.03233
/*2  */ {                                                                            // (23) 0.002309
/*4  */     TestData d;                                                              // (21) 0.01617
/*6  */     uint16_t ticks = 8;                                                      // (11) 0.0254
/*8  */     uint16_t val;                                                            // (17) 0.02079
/*10 */     int ret;                                                                 // (22) 0.01386
/*14 */     d.args = NULL;                                                           // (18) 0.02079
/*16 */     d.noreboot = true;                                                       // (12) 0.0254
/*18 */     test_init(&d);                                                           // (19) 0.02079
/*22 */     stop_tco(&d);                                                            // (14) 0.02309
/*24 */     clear_tco_status(&d);                                                    // (10) 0.02771
/*26 */     reset_on_second_timeout(false);                                          // (9) 0.03002
/*28 */     set_tco_timeout(&d, ticks);                                              // (8) 0.03233
/*30 */     load_tco(&d);                                                            // (15) 0.02309
/*32 */     start_tco(&d);                                                           // (16) 0.02309
/*34 */     clock_step(ticks * TCO_TICK_NSEC);                                       // (6) 0.04388
/*38 */     qpci_io_writeb(d.dev, d.tco_io_base + TCO_DAT_IN, 0);                    // (1) 0.08083
/*40 */     qpci_io_writeb(d.dev, d.tco_io_base + TCO_DAT_OUT, 0);                   // (2) 0.08083
/*42 */     val = qpci_io_readw(d.dev, d.tco_io_base + TCO1_STS);                    // (4) 0.07852
/*44 */     ret = val & (TCO_TIMEOUT | SW_TCO_SMI | TCO_INT_STS) ? 1 : 0;            // (3) 0.08083
/*46 */     g_assert(ret == 1);                                                      // (13) 0.0254
/*48 */     qpci_io_writew(d.dev, d.tco_io_base + TCO1_STS, val);                    // (5) 0.07852
/*50 */     g_assert_cmpint(qpci_io_readw(d.dev, d.tco_io_base + TCO1_STS), ==, 0);  // (0) 0.09931
/*52 */     qtest_end();                                                             // (20) 0.01848
/*54 */ }                                                                            // (24) 0.002309
