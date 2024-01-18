// commit message qemu@a718978ed5 (target=1, prob=0.48264807, correct=False): ide: add limit to .prepare_buf()
/*0   */ static int32_t bmdma_prepare_buf(IDEDMA *dma, int is_write)             // (6) 0.05078
/*2   */ {                                                                       // (23) 0.001953
/*4   */     BMDMAState *bm = DO_UPCAST(BMDMAState, dma, dma);                   // (5) 0.05273
/*6   */     IDEState *s = bmdma_active_if(bm);                                  // (14) 0.03516
/*8   */     PCIDevice *pci_dev = PCI_DEVICE(bm->pci_dev);                       // (7) 0.04883
/*10  */     struct {                                                            // (22) 0.009766
/*12  */         uint32_t addr;                                                  // (16) 0.02539
/*14  */         uint32_t size;                                                  // (17) 0.02539
/*16  */     } prd;                                                              // (21) 0.01367
/*18  */     int l, len;                                                         // (19) 0.01563
/*22  */     pci_dma_sglist_init(&s->sg, pci_dev,                                // (10) 0.04297
/*24  */                         s->nsector / (BMDMA_PAGE_SIZE / 512) + 1);      // (0) 0.08398
/*26  */     s->io_buffer_size = 0;                                              // (15) 0.02539
/*28  */     for(;;) {                                                           // (20) 0.01562
/*30  */         if (bm->cur_prd_len == 0) {                                     // (12) 0.04102
/*32  */             /* end of table (with a fail safe of one page) */           // (8) 0.04883
/*34  */             if (bm->cur_prd_last ||                                     // (11) 0.04297
/*36  */                 (bm->cur_addr - bm->addr) >= BMDMA_PAGE_SIZE) {         // (1) 0.07422
/*38  */                 return s->io_buffer_size;                               // (9) 0.04688
/*40  */             }                                                           // (18) 0.02344
/*42  */             pci_dma_read(pci_dev, bm->cur_addr, &prd, 8);               // (2) 0.07031
/*44  */             bm->cur_addr += 8;                                          // (13) 0.03906
/*46  */             prd.addr = le32_to_cpu(prd.addr);                           // (3) 0.05469
/*48  */             prd.size = le32_to_cpu(prd.size);                           // (4) 0.05469
/*50  */             len = prd.size & 0xfffe;                                    // 0.0
/*52  */             if (len == 0)                                               // 0.0
/*54  */                 len = 0x10000;                                          // 0.0
/*56  */             bm->cur_prd_len = len;                                      // 0.0
/*58  */             bm->cur_prd_addr = prd.addr;                                // 0.0
/*60  */             bm->cur_prd_last = (prd.size & 0x80000000);                 // 0.0
/*62  */         }                                                               // 0.0
/*64  */         l = bm->cur_prd_len;                                            // 0.0
/*66  */         if (l > 0) {                                                    // 0.0
/*68  */             qemu_sglist_add(&s->sg, bm->cur_prd_addr, l);               // 0.0
/*72  */             /* Note: We limit the max transfer to be 2GiB.              // 0.0
/*74  */              * This should accommodate the largest ATA transaction      // 0.0
/*76  */              * for LBA48 (65,536 sectors) and 32K sector sizes. */      // 0.0
/*78  */             if (s->sg.size > INT32_MAX) {                               // 0.0
/*80  */                 error_report("IDE: sglist describes more than 2GiB.");  // 0.0
/*82  */                 break;                                                  // 0.0
/*84  */             }                                                           // 0.0
/*86  */             bm->cur_prd_addr += l;                                      // 0.0
/*88  */             bm->cur_prd_len -= l;                                       // 0.0
/*90  */             s->io_buffer_size += l;                                     // 0.0
/*92  */         }                                                               // 0.0
/*94  */     }                                                                   // 0.0
/*98  */     qemu_sglist_destroy(&s->sg);                                        // 0.0
/*100 */     s->io_buffer_size = 0;                                              // 0.0
/*102 */     return -1;                                                          // 0.0
/*104 */ }                                                                       // 0.0
