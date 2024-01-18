// commit message qemu@edc2438512 (target=1, prob=0.71043205, correct=True): virtio-net: fix guest-triggerable buffer overrun
/*0   */ static int virtio_net_handle_mac(VirtIONet *n, uint8_t cmd,                // (6) 0.04688
/*2   */                                  struct iovec *iov, unsigned int iov_cnt)  // (0) 0.0918
/*4   */ {                                                                          // (24) 0.001953
/*6   */     struct virtio_net_ctrl_mac mac_data;                                   // (13) 0.03125
/*8   */     size_t s;                                                              // (20) 0.01562
/*10  */     NetClientState *nc = qemu_get_queue(n->nic);                           // (9) 0.04102
/*14  */     if (cmd == VIRTIO_NET_CTRL_MAC_ADDR_SET) {                             // (7) 0.04688
/*16  */         if (iov_size(iov, iov_cnt) != sizeof(n->mac)) {                    // (5) 0.05664
/*18  */             return VIRTIO_NET_ERR;                                         // (10) 0.04102
/*20  */         }                                                                  // (21) 0.01562
/*22  */         s = iov_to_buf(iov, iov_cnt, 0, &n->mac, sizeof(n->mac));          // (1) 0.07227
/*24  */         assert(s == sizeof(n->mac));                                       // (11) 0.0332
/*26  */         qemu_format_nic_info_str(qemu_get_queue(n->nic), n->mac);          // (2) 0.06836
/*28  */         rxfilter_notify(nc);                                               // (14) 0.03125
/*32  */         return VIRTIO_NET_OK;                                              // (15) 0.03125
/*34  */     }                                                                      // (23) 0.007813
/*38  */     if (cmd != VIRTIO_NET_CTRL_MAC_TABLE_SET) {                            // (8) 0.04492
/*40  */         return VIRTIO_NET_ERR;                                             // (12) 0.0332
/*42  */     }                                                                      // (22) 0.007813
/*46  */     int in_use = 0;                                                        // (19) 0.01953
/*48  */     int first_multi = 0;                                                   // (18) 0.01953
/*50  */     uint8_t uni_overflow = 0;                                              // (16) 0.0293
/*52  */     uint8_t multi_overflow = 0;                                            // (17) 0.02734
/*54  */     uint8_t *macs = g_malloc0(MAC_TABLE_ENTRIES * ETH_ALEN);               // (4) 0.05859
/*58  */     s = iov_to_buf(iov, iov_cnt, 0, &mac_data.entries,                     // (3) 0.05859
/*60  */                    sizeof(mac_data.entries));                              // 0.0
/*62  */     mac_data.entries = ldl_p(&mac_data.entries);                           // 0.0
/*64  */     if (s != sizeof(mac_data.entries)) {                                   // 0.0
/*66  */         goto error;                                                        // 0.0
/*68  */     }                                                                      // 0.0
/*70  */     iov_discard_front(&iov, &iov_cnt, s);                                  // 0.0
/*74  */     if (mac_data.entries * ETH_ALEN > iov_size(iov, iov_cnt)) {            // 0.0
/*76  */         goto error;                                                        // 0.0
/*78  */     }                                                                      // 0.0
/*82  */     if (mac_data.entries <= MAC_TABLE_ENTRIES) {                           // 0.0
/*84  */         s = iov_to_buf(iov, iov_cnt, 0, macs,                              // 0.0
/*86  */                        mac_data.entries * ETH_ALEN);                       // 0.0
/*88  */         if (s != mac_data.entries * ETH_ALEN) {                            // 0.0
/*90  */             goto error;                                                    // 0.0
/*92  */         }                                                                  // 0.0
/*94  */         in_use += mac_data.entries;                                        // 0.0
/*96  */     } else {                                                               // 0.0
/*98  */         uni_overflow = 1;                                                  // 0.0
/*100 */     }                                                                      // 0.0
/*104 */     iov_discard_front(&iov, &iov_cnt, mac_data.entries * ETH_ALEN);        // 0.0
/*108 */     first_multi = in_use;                                                  // 0.0
/*112 */     s = iov_to_buf(iov, iov_cnt, 0, &mac_data.entries,                     // 0.0
/*114 */                    sizeof(mac_data.entries));                              // 0.0
/*116 */     mac_data.entries = ldl_p(&mac_data.entries);                           // 0.0
/*118 */     if (s != sizeof(mac_data.entries)) {                                   // 0.0
/*120 */         goto error;                                                        // 0.0
/*122 */     }                                                                      // 0.0
/*126 */     iov_discard_front(&iov, &iov_cnt, s);                                  // 0.0
/*130 */     if (mac_data.entries * ETH_ALEN != iov_size(iov, iov_cnt)) {           // 0.0
/*132 */         goto error;                                                        // 0.0
/*134 */     }                                                                      // 0.0
/*138 */     if (in_use + mac_data.entries <= MAC_TABLE_ENTRIES) {                  // 0.0
/*140 */         s = iov_to_buf(iov, iov_cnt, 0, &macs[in_use * ETH_ALEN],          // 0.0
/*142 */                        mac_data.entries * ETH_ALEN);                       // 0.0
/*144 */         if (s != mac_data.entries * ETH_ALEN) {                            // 0.0
/*146 */             goto error;                                                    // 0.0
/*148 */         }                                                                  // 0.0
/*150 */         in_use += mac_data.entries;                                        // 0.0
/*152 */     } else {                                                               // 0.0
/*154 */         multi_overflow = 1;                                                // 0.0
/*156 */     }                                                                      // 0.0
/*160 */     n->mac_table.in_use = in_use;                                          // 0.0
/*162 */     n->mac_table.first_multi = first_multi;                                // 0.0
/*164 */     n->mac_table.uni_overflow = uni_overflow;                              // 0.0
/*166 */     n->mac_table.multi_overflow = multi_overflow;                          // 0.0
/*168 */     memcpy(n->mac_table.macs, macs, MAC_TABLE_ENTRIES * ETH_ALEN);         // 0.0
/*170 */     g_free(macs);                                                          // 0.0
/*172 */     rxfilter_notify(nc);                                                   // 0.0
/*176 */     return VIRTIO_NET_OK;                                                  // 0.0
/*180 */ error:                                                                     // 0.0
/*182 */     g_free(macs);                                                          // 0.0
/*184 */     return VIRTIO_NET_ERR;                                                 // 0.0
/*186 */ }                                                                          // 0.0
