// commit message qemu@778358d0a8 (target=1, prob=0.82776946, correct=True): rocker: Use g_new() & friends where that makes obvious sense
/*0   */ static int of_dpa_cmd_add_l2_flood(OfDpa *of_dpa, OfDpaGroup *group,         // (2) 0.06445
/*2   */                                    RockerTlv **group_tlvs)                   // (0) 0.08789
/*4   */ {                                                                            // (24) 0.001953
/*6   */     OfDpaGroup *l2_group;                                                    // (15) 0.02539
/*8   */     RockerTlv **tlvs;                                                        // (17) 0.02344
/*10  */     int err;                                                                 // (19) 0.01172
/*12  */     int i;                                                                   // (20) 0.01172
/*16  */     if (!group_tlvs[ROCKER_TLV_OF_DPA_GROUP_COUNT] ||                        // (5) 0.05664
/*18  */         !group_tlvs[ROCKER_TLV_OF_DPA_GROUP_IDS]) {                          // (4) 0.06055
/*20  */         return -ROCKER_EINVAL;                                               // (11) 0.0332
/*22  */     }                                                                        // (21) 0.007812
/*26  */     group->l2_flood.group_count =                                            // (13) 0.0293
/*28  */         rocker_tlv_get_le16(group_tlvs[ROCKER_TLV_OF_DPA_GROUP_COUNT]);      // (1) 0.08008
/*32  */     tlvs = g_malloc0((group->l2_flood.group_count + 1) *                     // (7) 0.05469
/*34  */                      sizeof(RockerTlv *));                                   // (6) 0.05469
/*36  */     if (!tlvs) {                                                             // (18) 0.01953
/*38  */         return -ROCKER_ENOMEM;                                               // (12) 0.0332
/*40  */     }                                                                        // (22) 0.007812
/*44  */     g_free(group->l2_flood.group_ids);                                       // (8) 0.03711
/*46  */     group->l2_flood.group_ids =                                              // (14) 0.0293
/*48  */         g_malloc0(group->l2_flood.group_count * sizeof(uint32_t));           // (3) 0.0625
/*50  */     if (!group->l2_flood.group_ids) {                                        // (10) 0.03516
/*52  */         err = -ROCKER_ENOMEM;                                                // (9) 0.03516
/*54  */         goto err_out;                                                        // (16) 0.02344
/*56  */     }                                                                        // (23) 0.007812
/*60  */     rocker_tlv_parse_nested(tlvs, group->l2_flood.group_count,               // 0.0
/*62  */                             group_tlvs[ROCKER_TLV_OF_DPA_GROUP_IDS]);        // 0.0
/*66  */     for (i = 0; i < group->l2_flood.group_count; i++) {                      // 0.0
/*68  */         group->l2_flood.group_ids[i] = rocker_tlv_get_le32(tlvs[i + 1]);     // 0.0
/*70  */     }                                                                        // 0.0
/*74  */     /* All of the L2 interface groups referenced by the L2 flood             // 0.0
/*76  */      * must have same VLAN                                                   // 0.0
/*78  */      */                                                                      // 0.0
/*82  */     for (i = 0; i < group->l2_flood.group_count; i++) {                      // 0.0
/*84  */         l2_group = of_dpa_group_find(of_dpa, group->l2_flood.group_ids[i]);  // 0.0
/*86  */         if (!l2_group) {                                                     // 0.0
/*88  */             continue;                                                        // 0.0
/*90  */         }                                                                    // 0.0
/*92  */         if ((ROCKER_GROUP_TYPE_GET(l2_group->id) ==                          // 0.0
/*94  */              ROCKER_OF_DPA_GROUP_TYPE_L2_INTERFACE) &&                       // 0.0
/*96  */             (ROCKER_GROUP_VLAN_GET(l2_group->id) !=                          // 0.0
/*98  */              ROCKER_GROUP_VLAN_GET(group->id))) {                            // 0.0
/*100 */             DPRINTF("l2 interface group 0x%08x VLAN doesn't match l2 "       // 0.0
/*102 */                     "flood group 0x%08x\n",                                  // 0.0
/*104 */                     group->l2_flood.group_ids[i], group->id);                // 0.0
/*106 */             err = -ROCKER_EINVAL;                                            // 0.0
/*108 */             goto err_out;                                                    // 0.0
/*110 */         }                                                                    // 0.0
/*112 */     }                                                                        // 0.0
/*116 */     g_free(tlvs);                                                            // 0.0
/*118 */     return ROCKER_OK;                                                        // 0.0
/*122 */ err_out:                                                                     // 0.0
/*124 */     group->l2_flood.group_count = 0;                                         // 0.0
/*126 */     g_free(group->l2_flood.group_ids);                                       // 0.0
/*128 */     g_free(tlvs);                                                            // 0.0
/*132 */     return err;                                                              // 0.0
/*134 */ }                                                                            // 0.0
