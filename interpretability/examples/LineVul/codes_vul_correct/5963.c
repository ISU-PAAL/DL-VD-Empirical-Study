// commit message qemu@b4ba67d9a7 (target=1, prob=0.8943022, correct=True): libqos: Change PCI accessors to take opaque BAR handle
/*0   */ static void test_bmdma_simple_rw(void)                                            // (12) 0.02734
/*2   */ {                                                                                 // (28) 0.001953
/*4   */     QPCIDevice *dev;                                                              // (20) 0.02148
/*6   */     void *bmdma_base, *ide_base;                                                  // (9) 0.03125
/*8   */     uint8_t status;                                                               // (24) 0.01758
/*10  */     uint8_t *buf;                                                                 // (22) 0.01953
/*12  */     uint8_t *cmpbuf;                                                              // (21) 0.02148
/*14  */     size_t len = 512;                                                             // (23) 0.01953
/*16  */     uintptr_t guest_buf = guest_alloc(guest_malloc, len);                         // (7) 0.04492
/*20  */     PrdtEntry prdt[] = {                                                          // (19) 0.02148
/*22  */         {                                                                         // (26) 0.01562
/*24  */             .addr = cpu_to_le32(guest_buf),                                       // (5) 0.05078
/*26  */             .size = cpu_to_le32(len | PRDT_EOT),                                  // (2) 0.05664
/*28  */         },                                                                        // (25) 0.01563
/*30  */     };                                                                            // (27) 0.007813
/*34  */     dev = get_pci_device(&bmdma_base, &ide_base);                                 // (6) 0.04492
/*38  */     buf = g_malloc(len);                                                          // (18) 0.02344
/*40  */     cmpbuf = g_malloc(len);                                                       // (13) 0.02734
/*44  */     /* Write 0x55 pattern to sector 0 */                                          // (16) 0.02539
/*46  */     memset(buf, 0x55, len);                                                       // (14) 0.02734
/*48  */     memwrite(guest_buf, buf, len);                                                // (10) 0.0293
/*52  */     status = send_dma_request(CMD_WRITE_DMA, 0, 1, prdt,                          // (3) 0.05469
/*54  */                               ARRAY_SIZE(prdt), NULL);                            // (0) 0.07617
/*56  */     g_assert_cmphex(status, ==, BM_STS_INTR);                                     // (8) 0.04297
/*58  */     assert_bit_clear(qpci_io_readb(dev, ide_base + reg_status), DF | ERR);        // (1) 0.06445
/*62  */     /* Write 0xaa pattern to sector 1 */                                          // (17) 0.02539
/*64  */     memset(buf, 0xaa, len);                                                       // (15) 0.02734
/*66  */     memwrite(guest_buf, buf, len);                                                // (11) 0.0293
/*70  */     status = send_dma_request(CMD_WRITE_DMA, 1, 1, prdt,                          // (4) 0.05469
/*72  */                               ARRAY_SIZE(prdt), NULL);                            // 0.0
/*74  */     g_assert_cmphex(status, ==, BM_STS_INTR);                                     // 0.0
/*76  */     assert_bit_clear(qpci_io_readb(dev, ide_base + reg_status), DF | ERR);        // 0.0
/*80  */     /* Read and verify 0x55 pattern in sector 0 */                                // 0.0
/*82  */     memset(cmpbuf, 0x55, len);                                                    // 0.0
/*86  */     status = send_dma_request(CMD_READ_DMA, 0, 1, prdt, ARRAY_SIZE(prdt), NULL);  // 0.0
/*88  */     g_assert_cmphex(status, ==, BM_STS_INTR);                                     // 0.0
/*90  */     assert_bit_clear(qpci_io_readb(dev, ide_base + reg_status), DF | ERR);        // 0.0
/*94  */     memread(guest_buf, buf, len);                                                 // 0.0
/*96  */     g_assert(memcmp(buf, cmpbuf, len) == 0);                                      // 0.0
/*100 */     /* Read and verify 0xaa pattern in sector 1 */                                // 0.0
/*102 */     memset(cmpbuf, 0xaa, len);                                                    // 0.0
/*106 */     status = send_dma_request(CMD_READ_DMA, 1, 1, prdt, ARRAY_SIZE(prdt), NULL);  // 0.0
/*108 */     g_assert_cmphex(status, ==, BM_STS_INTR);                                     // 0.0
/*110 */     assert_bit_clear(qpci_io_readb(dev, ide_base + reg_status), DF | ERR);        // 0.0
/*114 */     memread(guest_buf, buf, len);                                                 // 0.0
/*116 */     g_assert(memcmp(buf, cmpbuf, len) == 0);                                      // 0.0
/*122 */     g_free(buf);                                                                  // 0.0
/*124 */     g_free(cmpbuf);                                                               // 0.0
/*126 */ }                                                                                 // 0.0
