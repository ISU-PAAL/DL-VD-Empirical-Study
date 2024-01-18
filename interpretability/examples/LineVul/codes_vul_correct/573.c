// commit message qemu@b9f7c377df (target=1, prob=0.82031584, correct=True): net/vmxnet3: Fix incorrect debug message
/*0  */ static void vmxnet3_rx_need_csum_calculate(struct VmxnetRxPkt *pkt,             // (5) 0.05859
/*2  */                                            const void *pkt_data,                // (1) 0.09766
/*4  */                                            size_t pkt_len)                      // (0) 0.09766
/*6  */ {                                                                               // (21) 0.001953
/*8  */     struct virtio_net_hdr *vhdr;                                                // (12) 0.03125
/*10 */     bool isip4, isip6, istcp, isudp;                                            // (10) 0.03906
/*12 */     uint8_t *data;                                                              // (13) 0.01953
/*14 */     int len;                                                                    // (17) 0.01172
/*18 */     if (!vmxnet_rx_pkt_has_virt_hdr(pkt)) {                                     // (7) 0.04883
/*20 */         return;                                                                 // (14) 0.01758
/*22 */     }                                                                           // (18) 0.007812
/*26 */     vhdr = vmxnet_rx_pkt_get_vhdr(pkt);                                         // (8) 0.04883
/*28 */     if (!VMXNET_FLAG_IS_SET(vhdr->flags, VIRTIO_NET_HDR_F_NEEDS_CSUM)) {        // (2) 0.07813
/*30 */         return;                                                                 // (15) 0.01758
/*32 */     }                                                                           // (19) 0.007812
/*36 */     vmxnet_rx_pkt_get_protocols(pkt, &isip4, &isip6, &isudp, &istcp);           // (3) 0.07813
/*38 */     if (!(isip4 || isip6) || !(istcp || isudp)) {                               // (9) 0.04883
/*40 */         return;                                                                 // (16) 0.01758
/*42 */     }                                                                           // (20) 0.007812
/*46 */     vmxnet3_dump_virt_hdr(vhdr);                                                // (11) 0.03711
/*50 */     /* Validate packet len: csum_start + scum_offset + length of csum field */  // (6) 0.04883
/*52 */     if (pkt_len < (vhdr->csum_start + vhdr->csum_offset + 2)) {                 // (4) 0.0625
/*54 */         VMW_PKPRN("packet len:%d < csum_start(%d) + csum_offset(%d) + 2, "      // 0.0
/*56 */                   "cannot calculate checksum",                                  // 0.0
/*58 */                   len, vhdr->csum_start, vhdr->csum_offset);                    // 0.0
/*60 */         return;                                                                 // 0.0
/*62 */     }                                                                           // 0.0
/*66 */     data = (uint8_t *)pkt_data + vhdr->csum_start;                              // 0.0
/*68 */     len = pkt_len - vhdr->csum_start;                                           // 0.0
/*70 */     /* Put the checksum obtained into the packet */                             // 0.0
/*72 */     stw_be_p(data + vhdr->csum_offset, net_raw_checksum(data, len));            // 0.0
/*76 */     vhdr->flags &= ~VIRTIO_NET_HDR_F_NEEDS_CSUM;                                // 0.0
/*78 */     vhdr->flags |= VIRTIO_NET_HDR_F_DATA_VALID;                                 // 0.0
/*80 */ }                                                                               // 0.0
