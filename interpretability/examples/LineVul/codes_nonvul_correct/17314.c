// commit message qemu@e514fc7e12 (target=0, prob=0.49078244, correct=True): net: e1000e: fix dead code in e1000e_write_packet_to_guest
/*0   */ e1000e_write_packet_to_guest(E1000ECore *core, struct NetRxPkt *pkt,             // (3) 0.05626
/*2   */                              const E1000E_RxRing *rxr,                           // (11) 0.00772
/*4   */                              const E1000E_RSSInfo *rss_info)                     // (8) 0.01068
/*6   */ {                                                                                // (16) 0.00354
/*8   */     PCIDevice *d = core->owner;                                                  // (2) 0.05977
/*10  */     dma_addr_t base;                                                             // (0) 0.4924
/*12  */     uint8_t desc[E1000_MAX_RX_DESC_LEN];                                         // (5) 0.03245
/*14  */     size_t desc_size;                                                            // (19) 0.002943
/*16  */     size_t desc_offset = 0;                                                      // (20) 0.002773
/*18  */     size_t iov_ofs = 0;                                                          // (21) 0.002581
/*22  */     struct iovec *iov = net_rx_pkt_get_iovec(pkt);                               // (12) 0.007238
/*24  */     size_t size = net_rx_pkt_get_total_len(pkt);                                 // (13) 0.006034
/*26  */     size_t total_size = size + e1000x_fcs_len(core->mac);                        // (7) 0.01093
/*28  */     const E1000E_RingInfo *rxi;                                                  // (14) 0.005276
/*30  */     size_t ps_hdr_len = 0;                                                       // (18) 0.003148
/*32  */     bool do_ps = e1000e_do_ps(core, pkt, &ps_hdr_len);                           // (10) 0.007882
/*36  */     rxi = rxr->i;                                                                // (15) 0.004267
/*40  */     do {                                                                         // (1) 0.1464
/*42  */         hwaddr ba[MAX_PS_BUFFERS];                                               // (4) 0.0521
/*44  */         e1000e_ba_state bastate = { { 0 } };                                     // (9) 0.01026
/*46  */         bool is_last = false;                                                    // (22) 0.001534
/*48  */         bool is_first = true;                                                    // (23) 0.001317
/*52  */         desc_size = total_size - desc_offset;                                    // (17) 0.003254
/*56  */         if (desc_size > core->rx_desc_buf_size) {                                // (6) 0.01187
/*58  */             desc_size = core->rx_desc_buf_size;                                  // 0.0
/*60  */         }                                                                        // 0.0
/*64  */         base = e1000e_ring_head_descr(core, rxi);                                // 0.0
/*68  */         pci_dma_read(d, base, &desc, core->rx_desc_len);                         // 0.0
/*72  */         trace_e1000e_rx_descr(rxi->idx, base, core->rx_desc_len);                // 0.0
/*76  */         e1000e_read_rx_descr(core, desc, &ba);                                   // 0.0
/*80  */         if (ba[0]) {                                                             // 0.0
/*82  */             if (desc_offset < size) {                                            // 0.0
/*84  */                 static const uint32_t fcs_pad;                                   // 0.0
/*86  */                 size_t iov_copy;                                                 // 0.0
/*88  */                 size_t copy_size = size - desc_offset;                           // 0.0
/*90  */                 if (copy_size > core->rx_desc_buf_size) {                        // 0.0
/*92  */                     copy_size = core->rx_desc_buf_size;                          // 0.0
/*94  */                 }                                                                // 0.0
/*98  */                 /* For PS mode copy the packet header first */                   // 0.0
/*100 */                 if (do_ps) {                                                     // 0.0
/*102 */                     if (is_first) {                                              // 0.0
/*104 */                         size_t ps_hdr_copied = 0;                                // 0.0
/*106 */                         do {                                                     // 0.0
/*108 */                             iov_copy = MIN(ps_hdr_len - ps_hdr_copied,           // 0.0
/*110 */                                            iov->iov_len - iov_ofs);              // 0.0
/*114 */                             e1000e_write_hdr_to_rx_buffers(core, &ba, &bastate,  // 0.0
/*116 */                                                       iov->iov_base, iov_copy);  // 0.0
/*120 */                             copy_size -= iov_copy;                               // 0.0
/*122 */                             ps_hdr_copied += iov_copy;                           // 0.0
/*126 */                             iov_ofs += iov_copy;                                 // 0.0
/*128 */                             if (iov_ofs == iov->iov_len) {                       // 0.0
/*130 */                                 iov++;                                           // 0.0
/*132 */                                 iov_ofs = 0;                                     // 0.0
/*134 */                             }                                                    // 0.0
/*136 */                         } while (ps_hdr_copied < ps_hdr_len);                    // 0.0
/*140 */                         is_first = false;                                        // 0.0
/*142 */                     } else {                                                     // 0.0
/*144 */                         /* Leave buffer 0 of each descriptor except first */     // 0.0
/*146 */                         /* empty as per spec 7.1.5.1                      */     // 0.0
/*148 */                         e1000e_write_hdr_to_rx_buffers(core, &ba, &bastate,      // 0.0
/*150 */                                                        NULL, 0);                 // 0.0
/*152 */                     }                                                            // 0.0
/*154 */                 }                                                                // 0.0
/*158 */                 /* Copy packet payload */                                        // 0.0
/*160 */                 while (copy_size) {                                              // 0.0
/*162 */                     iov_copy = MIN(copy_size, iov->iov_len - iov_ofs);           // 0.0
/*166 */                     e1000e_write_to_rx_buffers(core, &ba, &bastate,              // 0.0
/*168 */                                             iov->iov_base + iov_ofs, iov_copy);  // 0.0
/*172 */                     copy_size -= iov_copy;                                       // 0.0
/*174 */                     iov_ofs += iov_copy;                                         // 0.0
/*176 */                     if (iov_ofs == iov->iov_len) {                               // 0.0
/*178 */                         iov++;                                                   // 0.0
/*180 */                         iov_ofs = 0;                                             // 0.0
/*182 */                     }                                                            // 0.0
/*184 */                 }                                                                // 0.0
/*188 */                 if (desc_offset + desc_size >= total_size) {                     // 0.0
/*190 */                     /* Simulate FCS checksum presence in the last descriptor */  // 0.0
/*192 */                     e1000e_write_to_rx_buffers(core, &ba, &bastate,              // 0.0
/*194 */                           (const char *) &fcs_pad, e1000x_fcs_len(core->mac));   // 0.0
/*196 */                 }                                                                // 0.0
/*198 */             }                                                                    // 0.0
/*200 */             desc_offset += desc_size;                                            // 0.0
/*202 */             if (desc_offset >= total_size) {                                     // 0.0
/*204 */                 is_last = true;                                                  // 0.0
/*206 */             }                                                                    // 0.0
/*208 */         } else { /* as per intel docs; skip descriptors with null buf addr */    // 0.0
/*210 */             trace_e1000e_rx_null_descriptor();                                   // 0.0
/*212 */         }                                                                        // 0.0
/*216 */         e1000e_write_rx_descr(core, desc, is_last ? core->rx_pkt : NULL,         // 0.0
/*218 */                            rss_info, do_ps ? ps_hdr_len : 0, &bastate.written);  // 0.0
/*220 */         pci_dma_write(d, base, &desc, core->rx_desc_len);                        // 0.0
/*224 */         e1000e_ring_advance(core, rxi,                                           // 0.0
/*226 */                             core->rx_desc_len / E1000_MIN_RX_DESC_LEN);          // 0.0
/*230 */     } while (desc_offset < total_size);                                          // 0.0
/*234 */     e1000e_update_rx_stats(core, size, total_size);                              // 0.0
/*236 */ }                                                                                // 0.0
