// commit message qemu@c508277335 (target=1, prob=0.935563, correct=True): vmxnet3: Fix reading/writing guest memory specially when behind an IOMMU
/*0  */ static void vmxnet3_update_mcast_filters(VMXNET3State *s)                       // (10) 0.04492
/*2  */ {                                                                               // (20) 0.001953
/*4  */     uint16_t list_bytes =                                                       // (15) 0.02148
/*6  */         VMXNET3_READ_DRV_SHARED16(s->drv_shmem,                                 // (4) 0.05859
/*8  */                                   devRead.rxFilterConf.mfTableLen);             // (1) 0.08789
/*12 */     s->mcast_list_len = list_bytes / sizeof(s->mcast_list[0]);                  // (7) 0.05273
/*16 */     s->mcast_list = g_realloc(s->mcast_list, list_bytes);                       // (8) 0.05078
/*18 */     if (!s->mcast_list) {                                                       // (14) 0.02539
/*20 */         if (s->mcast_list_len == 0) {                                           // (11) 0.04102
/*22 */             VMW_CFPRN("Current multicast list is empty");                       // (9) 0.04883
/*24 */         } else {                                                                // (16) 0.01953
/*26 */             VMW_ERPRN("Failed to allocate multicast list of %d elements",       // (5) 0.05859
/*28 */                       s->mcast_list_len);                                       // (6) 0.05859
/*30 */         }                                                                       // (18) 0.01562
/*32 */         s->mcast_list_len = 0;                                                  // (12) 0.03516
/*34 */     } else {                                                                    // (19) 0.01172
/*36 */         int i;                                                                  // (17) 0.01953
/*38 */         hwaddr mcast_list_pa =                                                  // (13) 0.0332
/*40 */             VMXNET3_READ_DRV_SHARED64(s->drv_shmem,                             // (3) 0.06641
/*42 */                                       devRead.rxFilterConf.mfTablePA);          // (0) 0.0957
/*46 */         pci_dma_read(PCI_DEVICE(s), mcast_list_pa, s->mcast_list, list_bytes);  // (2) 0.07813
/*50 */         VMW_CFPRN("Current multicast list len is %d:", s->mcast_list_len);      // 0.0
/*52 */         for (i = 0; i < s->mcast_list_len; i++) {                               // 0.0
/*54 */             VMW_CFPRN("\t" MAC_FMT, MAC_ARG(s->mcast_list[i].a));               // 0.0
/*56 */         }                                                                       // 0.0
/*58 */     }                                                                           // 0.0
/*60 */ }                                                                               // 0.0
