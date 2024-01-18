// commit message qemu@9fbf0fa81f (target=1, prob=0.57470816, correct=True): ide: remove hardcoded 2GiB transactional limit
/*0   */ static int ahci_populate_sglist(AHCIDevice *ad, QEMUSGList *sglist,              // (1) 0.05859
/*2   */                                 AHCICmdHdr *cmd, int64_t limit, int32_t offset)  // (0) 0.1016
/*4   */ {                                                                                // (25) 0.001953
/*6   */     uint16_t opts = le16_to_cpu(cmd->opts);                                      // (7) 0.04297
/*8   */     uint16_t prdtl = le16_to_cpu(cmd->prdtl);                                    // (6) 0.04687
/*10  */     uint64_t cfis_addr = le64_to_cpu(cmd->tbl_addr);                             // (4) 0.05078
/*12  */     uint64_t prdt_addr = cfis_addr + 0x80;                                       // (9) 0.04102
/*14  */     dma_addr_t prdt_len = (prdtl * sizeof(AHCI_SG));                             // (3) 0.05273
/*16  */     dma_addr_t real_prdt_len = prdt_len;                                         // (8) 0.04102
/*18  */     uint8_t *prdt;                                                               // (18) 0.02148
/*20  */     int i;                                                                       // (22) 0.01172
/*22  */     int r = 0;                                                                   // (21) 0.01562
/*24  */     uint64_t sum = 0;                                                            // (19) 0.02148
/*26  */     int off_idx = -1;                                                            // (16) 0.02344
/*28  */     int64_t off_pos = -1;                                                        // (13) 0.02734
/*30  */     int tbl_entry_size;                                                          // (17) 0.02148
/*32  */     IDEBus *bus = &ad->port;                                                     // (15) 0.02539
/*34  */     BusState *qbus = BUS(bus);                                                   // (14) 0.02539
/*38  */     /*                                                                           // (24) 0.007813
/*40  */      * Note: AHCI PRDT can describe up to 256GiB. SATA/ATA only support          // (5) 0.04883
/*42  */      * transactions of up to 32MiB as of ATA8-ACS3 rev 1b, assuming a            // (2) 0.05273
/*44  */      * 512 byte sector size. We limit the PRDT in this implementation to         // (10) 0.03711
/*46  */      * a reasonably large 2GiB, which can accommodate the maximum transfer       // (11) 0.03516
/*48  */      * request for sector sizes up to 32K.                                       // (12) 0.02734
/*50  */      */                                                                          // (23) 0.009766
/*54  */     if (!prdtl) {                                                                // (20) 0.01953
/*56  */         DPRINTF(ad->port_no, "no sg list given by guest: 0x%08x\n", opts);       // 0.0
/*58  */         return -1;                                                               // 0.0
/*60  */     }                                                                            // 0.0
/*64  */     /* map PRDT */                                                               // 0.0
/*66  */     if (!(prdt = dma_memory_map(ad->hba->as, prdt_addr, &prdt_len,               // 0.0
/*68  */                                 DMA_DIRECTION_TO_DEVICE))){                      // 0.0
/*70  */         DPRINTF(ad->port_no, "map failed\n");                                    // 0.0
/*72  */         return -1;                                                               // 0.0
/*74  */     }                                                                            // 0.0
/*78  */     if (prdt_len < real_prdt_len) {                                              // 0.0
/*80  */         DPRINTF(ad->port_no, "mapped less than expected\n");                     // 0.0
/*82  */         r = -1;                                                                  // 0.0
/*84  */         goto out;                                                                // 0.0
/*86  */     }                                                                            // 0.0
/*90  */     /* Get entries in the PRDT, init a qemu sglist accordingly */                // 0.0
/*92  */     if (prdtl > 0) {                                                             // 0.0
/*94  */         AHCI_SG *tbl = (AHCI_SG *)prdt;                                          // 0.0
/*96  */         sum = 0;                                                                 // 0.0
/*98  */         for (i = 0; i < prdtl; i++) {                                            // 0.0
/*100 */             tbl_entry_size = prdt_tbl_entry_size(&tbl[i]);                       // 0.0
/*102 */             if (offset < (sum + tbl_entry_size)) {                               // 0.0
/*104 */                 off_idx = i;                                                     // 0.0
/*106 */                 off_pos = offset - sum;                                          // 0.0
/*108 */                 break;                                                           // 0.0
/*110 */             }                                                                    // 0.0
/*112 */             sum += tbl_entry_size;                                               // 0.0
/*114 */         }                                                                        // 0.0
/*116 */         if ((off_idx == -1) || (off_pos < 0) || (off_pos > tbl_entry_size)) {    // 0.0
/*118 */             DPRINTF(ad->port_no, "%s: Incorrect offset! "                        // 0.0
/*120 */                             "off_idx: %d, off_pos: %"PRId64"\n",                 // 0.0
/*122 */                             __func__, off_idx, off_pos);                         // 0.0
/*124 */             r = -1;                                                              // 0.0
/*126 */             goto out;                                                            // 0.0
/*128 */         }                                                                        // 0.0
/*132 */         qemu_sglist_init(sglist, qbus->parent, (prdtl - off_idx),                // 0.0
/*134 */                          ad->hba->as);                                           // 0.0
/*136 */         qemu_sglist_add(sglist, le64_to_cpu(tbl[off_idx].addr) + off_pos,        // 0.0
/*138 */                         MIN(prdt_tbl_entry_size(&tbl[off_idx]) - off_pos,        // 0.0
/*140 */                             limit));                                             // 0.0
/*144 */         for (i = off_idx + 1; i < prdtl && sglist->size < limit; i++) {          // 0.0
/*146 */             qemu_sglist_add(sglist, le64_to_cpu(tbl[i].addr),                    // 0.0
/*148 */                             MIN(prdt_tbl_entry_size(&tbl[i]),                    // 0.0
/*150 */                                 limit - sglist->size));                          // 0.0
/*152 */             if (sglist->size > INT32_MAX) {                                      // 0.0
/*154 */                 error_report("AHCI Physical Region Descriptor Table describes "  // 0.0
/*156 */                              "more than 2 GiB.");                                // 0.0
/*158 */                 qemu_sglist_destroy(sglist);                                     // 0.0
/*160 */                 r = -1;                                                          // 0.0
/*162 */                 goto out;                                                        // 0.0
/*164 */             }                                                                    // 0.0
/*166 */         }                                                                        // 0.0
/*168 */     }                                                                            // 0.0
/*172 */ out:                                                                             // 0.0
/*174 */     dma_memory_unmap(ad->hba->as, prdt, prdt_len,                                // 0.0
/*176 */                      DMA_DIRECTION_TO_DEVICE, prdt_len);                         // 0.0
/*178 */     return r;                                                                    // 0.0
/*180 */ }                                                                                // 0.0
