// commit message qemu@debaaa114a (target=0, prob=0.6413716, correct=False): qtest/ahci: Allow override of default CLI options
/*0  */ static AHCIQState *ahci_boot(void)                                      // (9) 0.04943
/*2  */ {                                                                       // (14) 0.003802
/*4  */     AHCIQState *s;                                                      // (11) 0.03802
/*6  */     const char *cli;                                                    // (12) 0.03042
/*10 */     s = g_malloc0(sizeof(AHCIQState));                                  // (3) 0.07224
/*14 */     cli = "-drive if=none,id=drive0,file=%s,cache=writeback,serial=%s"  // (0) 0.1217
/*16 */         ",format=qcow2"                                                 // (8) 0.05323
/*18 */         " -M q35 "                                                      // (10) 0.04943
/*20 */         "-device ide-hd,drive=drive0 "                                  // (5) 0.06844
/*22 */         "-global ide-hd.ver=%s";                                        // (6) 0.06844
/*24 */     s->parent = qtest_pc_boot(cli, tmp_path, "testdisk", "version");    // (1) 0.1027
/*26 */     alloc_set_flags(s->parent->alloc, ALLOC_LEAK_ASSERT);               // (2) 0.09125
/*30 */     /* Verify that we have an AHCI device present. */                   // (7) 0.06084
/*32 */     s->dev = get_ahci_device(&s->fingerprint);                          // (4) 0.07224
/*36 */     return s;                                                           // (13) 0.02281
/*38 */ }                                                                       // (15) 0.003802
