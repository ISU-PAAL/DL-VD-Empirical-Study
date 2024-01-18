// commit message qemu@f57ba05823 (target=0, prob=0.45521638, correct=True): virtio-ccw: use ccw data stream
/*0   */ static int virtio_ccw_handle_set_vq(SubchDev *sch, CCW1 ccw, bool check_len,  // (4) 0.0625
/*2   */                                     bool is_legacy)                           // (2) 0.08008
/*4   */ {                                                                             // (22) 0.001953
/*6   */     int ret;                                                                  // (19) 0.01172
/*8   */     VqInfoBlock info;                                                         // (17) 0.01758
/*10  */     VqInfoBlockLegacy linfo;                                                  // (12) 0.02344
/*12  */     size_t info_len = is_legacy ? sizeof(linfo) : sizeof(info);               // (6) 0.04883
/*16  */     if (check_len) {                                                          // (16) 0.01953
/*18  */         if (ccw.count != info_len) {                                          // (7) 0.03711
/*20  */             return -EINVAL;                                                   // (8) 0.0332
/*22  */         }                                                                     // (18) 0.01562
/*24  */     } else if (ccw.count < info_len) {                                        // (9) 0.0332
/*26  */         /* Can't execute command. */                                          // (10) 0.02734
/*28  */         return -EINVAL;                                                       // (11) 0.02539
/*30  */     }                                                                         // (20) 0.007812
/*32  */     if (!ccw.cda) {                                                           // (13) 0.02344
/*34  */         return -EFAULT;                                                       // (14) 0.02344
/*36  */     }                                                                         // (21) 0.007812
/*38  */     if (is_legacy) {                                                          // (15) 0.02148
/*40  */         linfo.queue = address_space_ldq_be(&address_space_memory, ccw.cda,    // (3) 0.06445
/*42  */                                            MEMTXATTRS_UNSPECIFIED, NULL);     // (1) 0.1055
/*44  */         linfo.align = address_space_ldl_be(&address_space_memory,             // (5) 0.05273
/*46  */                                            ccw.cda + sizeof(linfo.queue),     // (0) 0.1074
/*48  */                                            MEMTXATTRS_UNSPECIFIED,            // 0.0
/*50  */                                            NULL);                             // 0.0
/*52  */         linfo.index = address_space_lduw_be(&address_space_memory,            // 0.0
/*54  */                                             ccw.cda + sizeof(linfo.queue)     // 0.0
/*56  */                                             + sizeof(linfo.align),            // 0.0
/*58  */                                             MEMTXATTRS_UNSPECIFIED,           // 0.0
/*60  */                                             NULL);                            // 0.0
/*62  */         linfo.num = address_space_lduw_be(&address_space_memory,              // 0.0
/*64  */                                           ccw.cda + sizeof(linfo.queue)       // 0.0
/*66  */                                           + sizeof(linfo.align)               // 0.0
/*68  */                                           + sizeof(linfo.index),              // 0.0
/*70  */                                           MEMTXATTRS_UNSPECIFIED,             // 0.0
/*72  */                                           NULL);                              // 0.0
/*74  */         ret = virtio_ccw_set_vqs(sch, NULL, &linfo);                          // 0.0
/*76  */     } else {                                                                  // 0.0
/*78  */         info.desc = address_space_ldq_be(&address_space_memory, ccw.cda,      // 0.0
/*80  */                                            MEMTXATTRS_UNSPECIFIED, NULL);     // 0.0
/*82  */         info.index = address_space_lduw_be(&address_space_memory,             // 0.0
/*84  */                                            ccw.cda + sizeof(info.desc)        // 0.0
/*86  */                                            + sizeof(info.res0),               // 0.0
/*88  */                                            MEMTXATTRS_UNSPECIFIED, NULL);     // 0.0
/*90  */         info.num = address_space_lduw_be(&address_space_memory,               // 0.0
/*92  */                                          ccw.cda + sizeof(info.desc)          // 0.0
/*94  */                                          + sizeof(info.res0)                  // 0.0
/*96  */                                          + sizeof(info.index),                // 0.0
/*98  */                                          MEMTXATTRS_UNSPECIFIED, NULL);       // 0.0
/*100 */         info.avail = address_space_ldq_be(&address_space_memory,              // 0.0
/*102 */                                           ccw.cda + sizeof(info.desc)         // 0.0
/*104 */                                           + sizeof(info.res0)                 // 0.0
/*106 */                                           + sizeof(info.index)                // 0.0
/*108 */                                           + sizeof(info.num),                 // 0.0
/*110 */                                           MEMTXATTRS_UNSPECIFIED, NULL);      // 0.0
/*112 */         info.used = address_space_ldq_be(&address_space_memory,               // 0.0
/*114 */                                          ccw.cda + sizeof(info.desc)          // 0.0
/*116 */                                          + sizeof(info.res0)                  // 0.0
/*118 */                                          + sizeof(info.index)                 // 0.0
/*120 */                                          + sizeof(info.num)                   // 0.0
/*122 */                                          + sizeof(info.avail),                // 0.0
/*124 */                                          MEMTXATTRS_UNSPECIFIED, NULL);       // 0.0
/*126 */         ret = virtio_ccw_set_vqs(sch, &info, NULL);                           // 0.0
/*128 */     }                                                                         // 0.0
/*130 */     sch->curr_status.scsw.count = 0;                                          // 0.0
/*132 */     return ret;                                                               // 0.0
/*134 */ }                                                                             // 0.0
