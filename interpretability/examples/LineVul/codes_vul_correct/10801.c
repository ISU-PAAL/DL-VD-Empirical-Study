// commit message qemu@d02f8adc6d (target=1, prob=0.6707666, correct=True): ahci.c: mask unused flags when reading size PRDT DBC
/*0   */ static int ahci_populate_sglist(AHCIDevice *ad, QEMUSGList *sglist, int offset)  // (3) 0.06445
/*2   */ {                                                                                // (26) 0.001953
/*4   */     AHCICmdHdr *cmd = ad->cur_cmd;                                               // (10) 0.03516
/*6   */     uint32_t opts = le32_to_cpu(cmd->opts);                                      // (8) 0.04297
/*8   */     uint64_t prdt_addr = le64_to_cpu(cmd->tbl_addr) + 0x80;                      // (6) 0.06055
/*10  */     int sglist_alloc_hint = opts >> AHCI_CMD_HDR_PRDT_LEN;                       // (4) 0.0625
/*12  */     dma_addr_t prdt_len = (sglist_alloc_hint * sizeof(AHCI_SG));                 // (5) 0.0625
/*14  */     dma_addr_t real_prdt_len = prdt_len;                                         // (9) 0.04102
/*16  */     uint8_t *prdt;                                                               // (15) 0.02148
/*18  */     int i;                                                                       // (23) 0.01172
/*20  */     int r = 0;                                                                   // (20) 0.01562
/*22  */     int sum = 0;                                                                 // (21) 0.01562
/*24  */     int off_idx = -1;                                                            // (14) 0.02344
/*26  */     int off_pos = -1;                                                            // (16) 0.02148
/*28  */     int tbl_entry_size;                                                          // (17) 0.02148
/*30  */     IDEBus *bus = &ad->port;                                                     // (12) 0.02539
/*32  */     BusState *qbus = BUS(bus);                                                   // (13) 0.02539
/*36  */     if (!sglist_alloc_hint) {                                                    // (11) 0.0293
/*38  */         DPRINTF(ad->port_no, "no sg list given by guest: 0x%08x\n", opts);       // (1) 0.07227
/*40  */         return -1;                                                               // (18) 0.02148
/*42  */     }                                                                            // (24) 0.007812
/*46  */     /* map PRDT */                                                               // (22) 0.01562
/*48  */     if (!(prdt = dma_memory_map(ad->hba->as, prdt_addr, &prdt_len,               // (2) 0.06641
/*50  */                                 DMA_DIRECTION_TO_DEVICE))){                      // (0) 0.08594
/*52  */         DPRINTF(ad->port_no, "map failed\n");                                    // (7) 0.04492
/*54  */         return -1;                                                               // (19) 0.02148
/*56  */     }                                                                            // (25) 0.007812
/*60  */     if (prdt_len < real_prdt_len) {                                              // 0.0
/*62  */         DPRINTF(ad->port_no, "mapped less than expected\n");                     // 0.0
/*64  */         r = -1;                                                                  // 0.0
/*66  */         goto out;                                                                // 0.0
/*68  */     }                                                                            // 0.0
/*72  */     /* Get entries in the PRDT, init a qemu sglist accordingly */                // 0.0
/*74  */     if (sglist_alloc_hint > 0) {                                                 // 0.0
/*76  */         AHCI_SG *tbl = (AHCI_SG *)prdt;                                          // 0.0
/*78  */         sum = 0;                                                                 // 0.0
/*80  */         for (i = 0; i < sglist_alloc_hint; i++) {                                // 0.0
/*82  */             /* flags_size is zero-based */                                       // 0.0
/*84  */             tbl_entry_size = (le32_to_cpu(tbl[i].flags_size) + 1);               // 0.0
/*86  */             if (offset <= (sum + tbl_entry_size)) {                              // 0.0
/*88  */                 off_idx = i;                                                     // 0.0
/*90  */                 off_pos = offset - sum;                                          // 0.0
/*92  */                 break;                                                           // 0.0
/*94  */             }                                                                    // 0.0
/*96  */             sum += tbl_entry_size;                                               // 0.0
/*98  */         }                                                                        // 0.0
/*100 */         if ((off_idx == -1) || (off_pos < 0) || (off_pos > tbl_entry_size)) {    // 0.0
/*102 */             DPRINTF(ad->port_no, "%s: Incorrect offset! "                        // 0.0
/*104 */                             "off_idx: %d, off_pos: %d\n",                        // 0.0
/*106 */                             __func__, off_idx, off_pos);                         // 0.0
/*108 */             r = -1;                                                              // 0.0
/*110 */             goto out;                                                            // 0.0
/*112 */         }                                                                        // 0.0
/*116 */         qemu_sglist_init(sglist, qbus->parent, (sglist_alloc_hint - off_idx),    // 0.0
/*118 */                          ad->hba->as);                                           // 0.0
/*120 */         qemu_sglist_add(sglist, le64_to_cpu(tbl[off_idx].addr + off_pos),        // 0.0
/*122 */                         le32_to_cpu(tbl[off_idx].flags_size) + 1 - off_pos);     // 0.0
/*126 */         for (i = off_idx + 1; i < sglist_alloc_hint; i++) {                      // 0.0
/*128 */             /* flags_size is zero-based */                                       // 0.0
/*130 */             qemu_sglist_add(sglist, le64_to_cpu(tbl[i].addr),                    // 0.0
/*132 */                             le32_to_cpu(tbl[i].flags_size) + 1);                 // 0.0
/*134 */         }                                                                        // 0.0
/*136 */     }                                                                            // 0.0
/*140 */ out:                                                                             // 0.0
/*142 */     dma_memory_unmap(ad->hba->as, prdt, prdt_len,                                // 0.0
/*144 */                      DMA_DIRECTION_TO_DEVICE, prdt_len);                         // 0.0
/*146 */     return r;                                                                    // 0.0
/*148 */ }                                                                                // 0.0
