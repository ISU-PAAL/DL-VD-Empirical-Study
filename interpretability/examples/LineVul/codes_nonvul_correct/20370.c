// commit message qemu@a89f364ae8 (target=0, prob=0.05033918, correct=True): Replace all occurances of __FUNCTION__ with __func__
/*0   */ static void bt_submit_acl(struct HCIInfo *info,                                 // (13) 0.03125
/*2   */                 const uint8_t *data, int length)                                // (5) 0.05078
/*4   */ {                                                                               // (25) 0.001953
/*6   */     struct bt_hci_s *hci = hci_from_info(info);                                 // (6) 0.04687
/*8   */     uint16_t handle;                                                            // (20) 0.01758
/*10  */     int datalen, flags;                                                         // (19) 0.01953
/*12  */     struct bt_link_s *link;                                                     // (17) 0.02539
/*16  */     if (length < HCI_ACL_HDR_SIZE) {                                            // (11) 0.03711
/*18  */         fprintf(stderr, "%s: ACL packet too short (%iB)\n",                     // (3) 0.05273
/*20  */                         __FUNCTION__, length);                                  // (1) 0.06055
/*22  */         return;                                                                 // (21) 0.01758
/*24  */     }                                                                           // (23) 0.007812
/*28  */     handle = acl_handle((data[1] << 8) | data[0]);                              // (8) 0.04297
/*30  */     flags = acl_flags((data[1] << 8) | data[0]);                                // (7) 0.04297
/*32  */     datalen = (data[3] << 8) | data[2];                                         // (10) 0.03906
/*34  */     data += HCI_ACL_HDR_SIZE;                                                   // (14) 0.03125
/*36  */     length -= HCI_ACL_HDR_SIZE;                                                 // (15) 0.03125
/*40  */     if (bt_hci_handle_bad(hci, handle)) {                                       // (9) 0.03906
/*42  */         fprintf(stderr, "%s: invalid ACL handle %03x\n",                        // (4) 0.05078
/*44  */                         __FUNCTION__, handle);                                  // (2) 0.06055
/*46  */         /* TODO: signal an error */                                             // (16) 0.0293
/*48  */         return;                                                                 // (22) 0.01758
/*50  */     }                                                                           // (24) 0.007812
/*52  */     handle &= ~HCI_HANDLE_OFFSET;                                               // (12) 0.0332
/*56  */     if (datalen > length) {                                                     // (18) 0.02344
/*58  */         fprintf(stderr, "%s: ACL packet too short (%iB < %iB)\n",               // (0) 0.06055
/*60  */                         __FUNCTION__, length, datalen);                         // 0.0
/*62  */         return;                                                                 // 0.0
/*64  */     }                                                                           // 0.0
/*68  */     link = hci->lm.handle[handle].link;                                         // 0.0
/*72  */     if ((flags & ~3) == ACL_ACTIVE_BCAST) {                                     // 0.0
/*74  */         if (!hci->asb_handle)                                                   // 0.0
/*76  */             hci->asb_handle = handle;                                           // 0.0
/*78  */         else if (handle != hci->asb_handle) {                                   // 0.0
/*80  */             fprintf(stderr, "%s: Bad handle %03x in Active Slave Broadcast\n",  // 0.0
/*82  */                             __FUNCTION__, handle);                              // 0.0
/*84  */             /* TODO: signal an error */                                         // 0.0
/*86  */             return;                                                             // 0.0
/*88  */         }                                                                       // 0.0
/*92  */         /* TODO */                                                              // 0.0
/*94  */     }                                                                           // 0.0
/*98  */     if ((flags & ~3) == ACL_PICO_BCAST) {                                       // 0.0
/*100 */         if (!hci->psb_handle)                                                   // 0.0
/*102 */             hci->psb_handle = handle;                                           // 0.0
/*104 */         else if (handle != hci->psb_handle) {                                   // 0.0
/*106 */             fprintf(stderr, "%s: Bad handle %03x in Parked Slave Broadcast\n",  // 0.0
/*108 */                             __FUNCTION__, handle);                              // 0.0
/*110 */             /* TODO: signal an error */                                         // 0.0
/*112 */             return;                                                             // 0.0
/*114 */         }                                                                       // 0.0
/*118 */         /* TODO */                                                              // 0.0
/*120 */     }                                                                           // 0.0
/*124 */     /* TODO: increase counter and send EVT_NUM_COMP_PKTS */                     // 0.0
/*126 */     bt_hci_event_num_comp_pkts(hci, handle | HCI_HANDLE_OFFSET, 1);             // 0.0
/*130 */     /* Do this last as it can trigger further events even in this HCI */        // 0.0
/*132 */     hci->lm.handle[handle].lmp_acl_data(link, data,                             // 0.0
/*134 */                     (flags & 3) == ACL_START, length);                          // 0.0
/*136 */ }                                                                               // 0.0
