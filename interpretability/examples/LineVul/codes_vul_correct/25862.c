// commit message qemu@248de4a899 (target=1, prob=0.65934503, correct=True): ahci-test: fix memory leak
/*0  */ static void test_dma_fragmented(void)                                        // (20) 0.02539
/*2  */ {                                                                            // (31) 0.001953
/*4  */     AHCIQState *ahci;                                                        // (22) 0.02148
/*6  */     AHCICommand *cmd;                                                        // (23) 0.02148
/*8  */     uint8_t px;                                                              // (25) 0.01953
/*10 */     size_t bufsize = 4096;                                                   // (24) 0.02148
/*12 */     unsigned char *tx = g_malloc(bufsize);                                   // (13) 0.03125
/*14 */     unsigned char *rx = g_malloc0(bufsize);                                  // (10) 0.0332
/*16 */     uint64_t ptr;                                                            // (26) 0.01758
/*20 */     ahci = ahci_boot_and_enable(NULL);                                       // (9) 0.0332
/*22 */     px = ahci_port_select(ahci);                                             // (11) 0.03125
/*24 */     ahci_port_clear(ahci, px);                                               // (12) 0.03125
/*28 */     /* create pattern */                                                     // (30) 0.01367
/*30 */     generate_pattern(tx, bufsize, AHCI_SECTOR_SIZE);                         // (0) 0.04297
/*34 */     /* Create a DMA buffer in guest memory, and write our pattern to it. */  // (2) 0.04102
/*36 */     ptr = guest_alloc(ahci->parent->alloc, bufsize);                         // (6) 0.03711
/*38 */     g_assert(ptr);                                                           // (27) 0.01758
/*40 */     bufwrite(ptr, tx, bufsize);                                              // (21) 0.02539
/*44 */     cmd = ahci_command_create(CMD_WRITE_DMA);                                // (3) 0.04102
/*46 */     ahci_command_adjust(cmd, 0, ptr, bufsize, 32);                           // (1) 0.04102
/*48 */     ahci_command_commit(ahci, cmd, px);                                      // (7) 0.03516
/*50 */     ahci_command_issue(ahci, cmd);                                           // (17) 0.0293
/*52 */     ahci_command_verify(ahci, cmd);                                          // (15) 0.03125
/*54 */     g_free(cmd);                                                             // (28) 0.01758
/*58 */     cmd = ahci_command_create(CMD_READ_DMA);                                 // (5) 0.03906
/*60 */     ahci_command_adjust(cmd, 0, ptr, bufsize, 32);                           // (4) 0.04102
/*62 */     ahci_command_commit(ahci, cmd, px);                                      // (8) 0.03516
/*64 */     ahci_command_issue(ahci, cmd);                                           // (18) 0.0293
/*66 */     ahci_command_verify(ahci, cmd);                                          // (14) 0.03125
/*68 */     g_free(cmd);                                                             // (29) 0.01758
/*72 */     /* Read back the guest's receive buffer into local memory */             // (16) 0.0293
/*74 */     bufread(ptr, rx, bufsize);                                               // (19) 0.02734
/*76 */     guest_free(ahci->parent->alloc, ptr);                                    // 0.0
/*80 */     g_assert_cmphex(memcmp(tx, rx, bufsize), ==, 0);                         // 0.0
/*84 */     ahci_shutdown(ahci);                                                     // 0.0
/*88 */     g_free(rx);                                                              // 0.0
/*90 */     g_free(tx);                                                              // 0.0
/*92 */ }                                                                            // 0.0
