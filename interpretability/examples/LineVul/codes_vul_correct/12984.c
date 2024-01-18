// commit message qemu@65f82df0d7 (target=1, prob=0.5697037, correct=True): e1000: bounds packet size against buffer size
/*0   */ process_tx_desc(E1000State *s, struct e1000_tx_desc *dp)                        // (13) 0.04297
/*2   */ {                                                                               // (18) 0.001955
/*4   */     uint32_t txd_lower = le32_to_cpu(dp->lower.data);                           // (9) 0.04883
/*6   */     uint32_t dtype = txd_lower & (E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D);       // (0) 0.07812
/*8   */     unsigned int split_size = txd_lower & 0xffff, bytes, sz, op;                // (8) 0.04884
/*10  */     unsigned int msh = 0xfffff, hdr = 0;                                        // (15) 0.03516
/*12  */     uint64_t addr;                                                              // (17) 0.01758
/*14  */     struct e1000_context_desc *xp = (struct e1000_context_desc *)dp;            // (11) 0.04687
/*16  */     struct e1000_tx *tp = &s->tx;                                               // (16) 0.03125
/*20  */     if (dtype == E1000_TXD_CMD_DEXT) {	// context descriptor                    // (10) 0.04883
/*22  */         op = le32_to_cpu(xp->cmd_and_length);                                   // (12) 0.04687
/*24  */         tp->ipcss = xp->lower_setup.ip_fields.ipcss;                            // (7) 0.05078
/*26  */         tp->ipcso = xp->lower_setup.ip_fields.ipcso;                            // (6) 0.05469
/*28  */         tp->ipcse = le16_to_cpu(xp->lower_setup.ip_fields.ipcse);               // (2) 0.06836
/*30  */         tp->tucss = xp->upper_setup.tcp_fields.tucss;                           // (4) 0.05664
/*32  */         tp->tucso = xp->upper_setup.tcp_fields.tucso;                           // (5) 0.05664
/*34  */         tp->tucse = le16_to_cpu(xp->upper_setup.tcp_fields.tucse);              // (1) 0.07031
/*36  */         tp->paylen = op & 0xfffff;                                              // (14) 0.03906
/*38  */         tp->hdr_len = xp->tcp_seg_setup.fields.hdr_len;                         // (3) 0.0625
/*40  */         tp->mss = le16_to_cpu(xp->tcp_seg_setup.fields.mss);                    // 0.0
/*42  */         tp->ip = (op & E1000_TXD_CMD_IP) ? 1 : 0;                               // 0.0
/*44  */         tp->tcp = (op & E1000_TXD_CMD_TCP) ? 1 : 0;                             // 0.0
/*46  */         tp->tse = (op & E1000_TXD_CMD_TSE) ? 1 : 0;                             // 0.0
/*48  */         tp->tso_frames = 0;                                                     // 0.0
/*50  */         if (tp->tucso == 0) {	// this is probably wrong                         // 0.0
/*52  */             DBGOUT(TXSUM, "TCP/UDP: cso 0!\n");                                 // 0.0
/*54  */             tp->tucso = tp->tucss + (tp->tcp ? 16 : 6);                         // 0.0
/*56  */         }                                                                       // 0.0
/*58  */         return;                                                                 // 0.0
/*60  */     } else if (dtype == (E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D)) {              // 0.0
/*62  */         // data descriptor                                                      // 0.0
/*64  */         if (tp->size == 0) {                                                    // 0.0
/*66  */             tp->sum_needed = le32_to_cpu(dp->upper.data) >> 8;                  // 0.0
/*68  */         }                                                                       // 0.0
/*70  */         tp->cptse = ( txd_lower & E1000_TXD_CMD_TSE ) ? 1 : 0;                  // 0.0
/*72  */     } else {                                                                    // 0.0
/*74  */         // legacy descriptor                                                    // 0.0
/*76  */         tp->cptse = 0;                                                          // 0.0
/*78  */     }                                                                           // 0.0
/*82  */     if (vlan_enabled(s) && is_vlan_txd(txd_lower) &&                            // 0.0
/*84  */         (tp->cptse || txd_lower & E1000_TXD_CMD_EOP)) {                         // 0.0
/*86  */         tp->vlan_needed = 1;                                                    // 0.0
/*88  */         cpu_to_be16wu((uint16_t *)(tp->vlan_header),                            // 0.0
/*90  */                       le16_to_cpup((uint16_t *)(s->mac_reg + VET)));            // 0.0
/*92  */         cpu_to_be16wu((uint16_t *)(tp->vlan_header + 2),                        // 0.0
/*94  */                       le16_to_cpu(dp->upper.fields.special));                   // 0.0
/*96  */     }                                                                           // 0.0
/*98  */                                                                                 // 0.0
/*100 */     addr = le64_to_cpu(dp->buffer_addr);                                        // 0.0
/*102 */     if (tp->tse && tp->cptse) {                                                 // 0.0
/*104 */         hdr = tp->hdr_len;                                                      // 0.0
/*106 */         msh = hdr + tp->mss;                                                    // 0.0
/*108 */         do {                                                                    // 0.0
/*110 */             bytes = split_size;                                                 // 0.0
/*112 */             if (tp->size + bytes > msh)                                         // 0.0
/*114 */                 bytes = msh - tp->size;                                         // 0.0
/*118 */             bytes = MIN(sizeof(tp->data) - tp->size, bytes);                    // 0.0
/*120 */             pci_dma_read(&s->dev, addr, tp->data + tp->size, bytes);            // 0.0
/*122 */             if ((sz = tp->size + bytes) >= hdr && tp->size < hdr)               // 0.0
/*124 */                 memmove(tp->header, tp->data, hdr);                             // 0.0
/*126 */             tp->size = sz;                                                      // 0.0
/*128 */             addr += bytes;                                                      // 0.0
/*130 */             if (sz == msh) {                                                    // 0.0
/*132 */                 xmit_seg(s);                                                    // 0.0
/*134 */                 memmove(tp->data, tp->header, hdr);                             // 0.0
/*136 */                 tp->size = hdr;                                                 // 0.0
/*138 */             }                                                                   // 0.0
/*140 */         } while (split_size -= bytes);                                          // 0.0
/*142 */     } else if (!tp->tse && tp->cptse) {                                         // 0.0
/*144 */         // context descriptor TSE is not set, while data descriptor TSE is set  // 0.0
/*146 */         DBGOUT(TXERR, "TCP segmentaion Error\n");                               // 0.0
/*148 */     } else {                                                                    // 0.0
/*151 */         pci_dma_read(&s->dev, addr, tp->data + tp->size, split_size);           // 0.0
/*153 */         tp->size += split_size;                                                 // 0.0
/*155 */     }                                                                           // 0.0
/*159 */     if (!(txd_lower & E1000_TXD_CMD_EOP))                                       // 0.0
/*161 */         return;                                                                 // 0.0
/*163 */     if (!(tp->tse && tp->cptse && tp->size < hdr))                              // 0.0
/*165 */         xmit_seg(s);                                                            // 0.0
/*167 */     tp->tso_frames = 0;                                                         // 0.0
/*169 */     tp->sum_needed = 0;                                                         // 0.0
/*171 */     tp->vlan_needed = 0;                                                        // 0.0
/*173 */     tp->size = 0;                                                               // 0.0
/*175 */     tp->cptse = 0;                                                              // 0.0
/*177 */ }                                                                               // 0.0
