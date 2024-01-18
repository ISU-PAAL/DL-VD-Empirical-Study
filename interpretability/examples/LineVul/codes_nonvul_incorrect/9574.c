// commit message qemu@ef1e1e0782 (target=0, prob=0.5917476, correct=False): maint: avoid useless "if (foo) free(foo)" pattern
/*0   */ static int tx_consume(Rocker *r, DescInfo *info)                                // (10) 0.0332
/*2   */ {                                                                               // (28) 0.001953
/*4   */     PCIDevice *dev = PCI_DEVICE(r);                                             // (11) 0.0332
/*6   */     char *buf = desc_get_buf(info, true);                                       // (12) 0.0332
/*8   */     RockerTlv *tlv_frag;                                                        // (17) 0.02734
/*10  */     RockerTlv *tlvs[ROCKER_TLV_TX_MAX + 1];                                     // (3) 0.04883
/*12  */     struct iovec iov[ROCKER_TX_FRAGS_MAX] = { { 0, }, };                        // (2) 0.05664
/*14  */     uint32_t pport;                                                             // (20) 0.01953
/*16  */     uint32_t port;                                                              // (21) 0.01758
/*18  */     uint16_t tx_offload = ROCKER_TX_OFFLOAD_NONE;                               // (4) 0.04687
/*20  */     uint16_t tx_l3_csum_off = 0;                                                // (9) 0.03711
/*22  */     uint16_t tx_tso_mss = 0;                                                    // (14) 0.0332
/*24  */     uint16_t tx_tso_hdr_len = 0;                                                // (8) 0.03711
/*26  */     int iovcnt = 0;                                                             // (19) 0.02148
/*28  */     int err = ROCKER_OK;                                                        // (18) 0.02148
/*30  */     int rem;                                                                    // (24) 0.01172
/*32  */     int i;                                                                      // (23) 0.01172
/*36  */     if (!buf) {                                                                 // (22) 0.01563
/*38  */         return -ROCKER_ENXIO;                                                   // (13) 0.0332
/*40  */     }                                                                           // (25) 0.007812
/*44  */     rocker_tlv_parse(tlvs, ROCKER_TLV_TX_MAX, buf, desc_tlv_size(info));        // (0) 0.07031
/*48  */     if (!tlvs[ROCKER_TLV_TX_FRAGS]) {                                           // (5) 0.04492
/*50  */         return -ROCKER_EINVAL;                                                  // (16) 0.0332
/*52  */     }                                                                           // (27) 0.007812
/*56  */     pport = rocker_get_pport_by_tx_ring(r, desc_get_ring(info));                // (1) 0.05664
/*58  */     if (!fp_port_from_pport(pport, &port)) {                                    // (7) 0.03711
/*60  */         return -ROCKER_EINVAL;                                                  // (15) 0.0332
/*62  */     }                                                                           // (26) 0.007812
/*66  */     if (tlvs[ROCKER_TLV_TX_OFFLOAD]) {                                          // (6) 0.04492
/*68  */         tx_offload = rocker_tlv_get_u8(tlvs[ROCKER_TLV_TX_OFFLOAD]);            // 0.0
/*70  */     }                                                                           // 0.0
/*74  */     switch (tx_offload) {                                                       // 0.0
/*76  */     case ROCKER_TX_OFFLOAD_L3_CSUM:                                             // 0.0
/*78  */         if (!tlvs[ROCKER_TLV_TX_L3_CSUM_OFF]) {                                 // 0.0
/*80  */             return -ROCKER_EINVAL;                                              // 0.0
/*82  */         }                                                                       // 0.0
/*84  */         break;                                                                  // 0.0
/*86  */     case ROCKER_TX_OFFLOAD_TSO:                                                 // 0.0
/*88  */         if (!tlvs[ROCKER_TLV_TX_TSO_MSS] ||                                     // 0.0
/*90  */             !tlvs[ROCKER_TLV_TX_TSO_HDR_LEN]) {                                 // 0.0
/*92  */             return -ROCKER_EINVAL;                                              // 0.0
/*94  */         }                                                                       // 0.0
/*96  */         break;                                                                  // 0.0
/*98  */     }                                                                           // 0.0
/*102 */     if (tlvs[ROCKER_TLV_TX_L3_CSUM_OFF]) {                                      // 0.0
/*104 */         tx_l3_csum_off = rocker_tlv_get_le16(tlvs[ROCKER_TLV_TX_L3_CSUM_OFF]);  // 0.0
/*106 */     }                                                                           // 0.0
/*110 */     if (tlvs[ROCKER_TLV_TX_TSO_MSS]) {                                          // 0.0
/*112 */         tx_tso_mss = rocker_tlv_get_le16(tlvs[ROCKER_TLV_TX_TSO_MSS]);          // 0.0
/*114 */     }                                                                           // 0.0
/*118 */     if (tlvs[ROCKER_TLV_TX_TSO_HDR_LEN]) {                                      // 0.0
/*120 */         tx_tso_hdr_len = rocker_tlv_get_le16(tlvs[ROCKER_TLV_TX_TSO_HDR_LEN]);  // 0.0
/*122 */     }                                                                           // 0.0
/*126 */     rocker_tlv_for_each_nested(tlv_frag, tlvs[ROCKER_TLV_TX_FRAGS], rem) {      // 0.0
/*128 */         hwaddr frag_addr;                                                       // 0.0
/*130 */         uint16_t frag_len;                                                      // 0.0
/*134 */         if (rocker_tlv_type(tlv_frag) != ROCKER_TLV_TX_FRAG) {                  // 0.0
/*136 */             err = -ROCKER_EINVAL;                                               // 0.0
/*138 */             goto err_bad_attr;                                                  // 0.0
/*140 */         }                                                                       // 0.0
/*144 */         rocker_tlv_parse_nested(tlvs, ROCKER_TLV_TX_FRAG_ATTR_MAX, tlv_frag);   // 0.0
/*148 */         if (!tlvs[ROCKER_TLV_TX_FRAG_ATTR_ADDR] ||                              // 0.0
/*150 */             !tlvs[ROCKER_TLV_TX_FRAG_ATTR_LEN]) {                               // 0.0
/*152 */             err = -ROCKER_EINVAL;                                               // 0.0
/*154 */             goto err_bad_attr;                                                  // 0.0
/*156 */         }                                                                       // 0.0
/*160 */         frag_addr = rocker_tlv_get_le64(tlvs[ROCKER_TLV_TX_FRAG_ATTR_ADDR]);    // 0.0
/*162 */         frag_len = rocker_tlv_get_le16(tlvs[ROCKER_TLV_TX_FRAG_ATTR_LEN]);      // 0.0
/*166 */         iov[iovcnt].iov_len = frag_len;                                         // 0.0
/*168 */         iov[iovcnt].iov_base = g_malloc(frag_len);                              // 0.0
/*170 */         if (!iov[iovcnt].iov_base) {                                            // 0.0
/*172 */             err = -ROCKER_ENOMEM;                                               // 0.0
/*174 */             goto err_no_mem;                                                    // 0.0
/*176 */         }                                                                       // 0.0
/*180 */         if (pci_dma_read(dev, frag_addr, iov[iovcnt].iov_base,                  // 0.0
/*182 */                      iov[iovcnt].iov_len)) {                                    // 0.0
/*184 */             err = -ROCKER_ENXIO;                                                // 0.0
/*186 */             goto err_bad_io;                                                    // 0.0
/*188 */         }                                                                       // 0.0
/*192 */         if (++iovcnt > ROCKER_TX_FRAGS_MAX) {                                   // 0.0
/*194 */             goto err_too_many_frags;                                            // 0.0
/*196 */         }                                                                       // 0.0
/*198 */     }                                                                           // 0.0
/*202 */     if (iovcnt) {                                                               // 0.0
/*204 */         /* XXX perform Tx offloads */                                           // 0.0
/*206 */         /* XXX   silence compiler for now */                                    // 0.0
/*208 */         tx_l3_csum_off += tx_tso_mss = tx_tso_hdr_len = 0;                      // 0.0
/*210 */     }                                                                           // 0.0
/*214 */     err = fp_port_eg(r->fp_port[port], iov, iovcnt);                            // 0.0
/*218 */ err_too_many_frags:                                                             // 0.0
/*220 */ err_bad_io:                                                                     // 0.0
/*222 */ err_no_mem:                                                                     // 0.0
/*224 */ err_bad_attr:                                                                   // 0.0
/*226 */     for (i = 0; i < ROCKER_TX_FRAGS_MAX; i++) {                                 // 0.0
/*228 */         if (iov[i].iov_base) {                                                  // 0.0
/*230 */             g_free(iov[i].iov_base);                                            // 0.0
/*232 */         }                                                                       // 0.0
/*234 */     }                                                                           // 0.0
/*238 */     return err;                                                                 // 0.0
/*240 */ }                                                                               // 0.0
