// commit message qemu@c508277335 (target=1, prob=0.72623485, correct=True): vmxnet3: Fix reading/writing guest memory specially when behind an IOMMU
/*0  */ static void vmxnet3_update_vlan_filters(VMXNET3State *s)       // (9) 0.05679
/*2  */ {                                                              // (18) 0.002469
/*4  */     int i;                                                     // (15) 0.01481
/*8  */     /* Copy configuration from shared memory */                // (13) 0.02469
/*10 */     VMXNET3_READ_DRV_SHARED(s->drv_shmem,                      // (8) 0.06173
/*12 */                             devRead.rxFilterConf.vfTable,      // (0) 0.09383
/*14 */                             s->vlan_table,                     // (3) 0.08395
/*16 */                             sizeof(s->vlan_table));            // (1) 0.08889
/*20 */     /* Invert byte order when needed */                        // (11) 0.02716
/*22 */     for (i = 0; i < ARRAY_SIZE(s->vlan_table); i++) {          // (6) 0.0642
/*24 */         s->vlan_table[i] = le32_to_cpu(s->vlan_table[i]);      // (4) 0.08148
/*26 */     }                                                          // (16) 0.009877
/*30 */     /* Dump configuration for debugging purposes */            // (12) 0.02716
/*32 */     VMW_CFPRN("Configured VLANs:");                            // (10) 0.04198
/*34 */     for (i = 0; i < sizeof(s->vlan_table) * 8; i++) {          // (7) 0.0642
/*36 */         if (VMXNET3_VFTABLE_ENTRY_IS_SET(s->vlan_table, i)) {  // (2) 0.08642
/*38 */             VMW_CFPRN("\tVLAN %d is present", i);              // (5) 0.0716
/*40 */         }                                                      // (14) 0.01975
/*42 */     }                                                          // (17) 0.009877
/*44 */ }                                                              // (19) 0.002469
