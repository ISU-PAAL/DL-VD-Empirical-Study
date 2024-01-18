// commit message qemu@e98768d437 (target=1, prob=0.4273909, correct=False): vmdk: use unsigned values for on disk header fields
/*0   */ static int vmdk_open_vmdk4(BlockDriverState *bs,                                 // (11) 0.03711
/*2   */                            BlockDriverState *file,                               // (0) 0.0625
/*4   */                            int flags)                                            // (3) 0.05664
/*6   */ {                                                                                // (28) 0.001953
/*8   */     int ret;                                                                     // (25) 0.01172
/*10  */     uint32_t magic;                                                              // (20) 0.01758
/*12  */     uint32_t l1_size, l1_entry_sectors;                                          // (10) 0.03906
/*14  */     VMDK4Header header;                                                          // (17) 0.01953
/*16  */     VmdkExtent *extent;                                                          // (16) 0.02344
/*18  */     int64_t l1_backup_offset = 0;                                                // (12) 0.0332
/*22  */     ret = bdrv_pread(file, sizeof(magic), &header, sizeof(header));              // (7) 0.04688
/*24  */     if (ret < 0) {                                                               // (18) 0.01953
/*26  */         return ret;                                                              // (19) 0.01953
/*28  */     }                                                                            // (27) 0.007812
/*30  */     if (header.capacity == 0) {                                                  // (15) 0.02344
/*32  */         int64_t desc_offset = le64_to_cpu(header.desc_offset);                   // (4) 0.05469
/*34  */         if (desc_offset) {                                                       // (13) 0.02734
/*36  */             return vmdk_open_desc_file(bs, flags, desc_offset << 9);             // (1) 0.0625
/*38  */         }                                                                        // (24) 0.01562
/*40  */     }                                                                            // (26) 0.007813
/*44  */     if (le64_to_cpu(header.gd_offset) == VMDK4_GD_AT_END) {                      // (2) 0.06055
/*46  */         /*                                                                       // (23) 0.01563
/*48  */          * The footer takes precedence over the header, so read it in. The       // (5) 0.04688
/*50  */          * footer starts at offset -1024 from the end: One sector for the        // (6) 0.04688
/*52  */          * footer, and another one for the end-of-stream marker.                 // (8) 0.04688
/*54  */          */                                                                      // (21) 0.01758
/*56  */         struct {                                                                 // (22) 0.01758
/*58  */             struct {                                                             // (14) 0.02539
/*60  */                 uint64_t val;                                                    // (9) 0.04102
/*62  */                 uint32_t size;                                                   // 0.0
/*64  */                 uint32_t type;                                                   // 0.0
/*66  */                 uint8_t pad[512 - 16];                                           // 0.0
/*68  */             } QEMU_PACKED footer_marker;                                         // 0.0
/*72  */             uint32_t magic;                                                      // 0.0
/*74  */             VMDK4Header header;                                                  // 0.0
/*76  */             uint8_t pad[512 - 4 - sizeof(VMDK4Header)];                          // 0.0
/*80  */             struct {                                                             // 0.0
/*82  */                 uint64_t val;                                                    // 0.0
/*84  */                 uint32_t size;                                                   // 0.0
/*86  */                 uint32_t type;                                                   // 0.0
/*88  */                 uint8_t pad[512 - 16];                                           // 0.0
/*90  */             } QEMU_PACKED eos_marker;                                            // 0.0
/*92  */         } QEMU_PACKED footer;                                                    // 0.0
/*96  */         ret = bdrv_pread(file,                                                   // 0.0
/*98  */             bs->file->total_sectors * 512 - 1536,                                // 0.0
/*100 */             &footer, sizeof(footer));                                            // 0.0
/*102 */         if (ret < 0) {                                                           // 0.0
/*104 */             return ret;                                                          // 0.0
/*106 */         }                                                                        // 0.0
/*110 */         /* Some sanity checks for the footer */                                  // 0.0
/*112 */         if (be32_to_cpu(footer.magic) != VMDK4_MAGIC ||                          // 0.0
/*114 */             le32_to_cpu(footer.footer_marker.size) != 0  ||                      // 0.0
/*116 */             le32_to_cpu(footer.footer_marker.type) != MARKER_FOOTER ||           // 0.0
/*118 */             le64_to_cpu(footer.eos_marker.val) != 0  ||                          // 0.0
/*120 */             le32_to_cpu(footer.eos_marker.size) != 0  ||                         // 0.0
/*122 */             le32_to_cpu(footer.eos_marker.type) != MARKER_END_OF_STREAM)         // 0.0
/*124 */         {                                                                        // 0.0
/*126 */             return -EINVAL;                                                      // 0.0
/*128 */         }                                                                        // 0.0
/*132 */         header = footer.header;                                                  // 0.0
/*134 */     }                                                                            // 0.0
/*138 */     if (le32_to_cpu(header.version) >= 3) {                                      // 0.0
/*140 */         char buf[64];                                                            // 0.0
/*142 */         snprintf(buf, sizeof(buf), "VMDK version %d",                            // 0.0
/*144 */                  le32_to_cpu(header.version));                                   // 0.0
/*146 */         qerror_report(QERR_UNKNOWN_BLOCK_FORMAT_FEATURE,                         // 0.0
/*148 */                 bs->device_name, "vmdk", buf);                                   // 0.0
/*150 */         return -ENOTSUP;                                                         // 0.0
/*152 */     }                                                                            // 0.0
/*156 */     l1_entry_sectors = le32_to_cpu(header.num_gtes_per_gte)                      // 0.0
/*158 */                         * le64_to_cpu(header.granularity);                       // 0.0
/*160 */     if (l1_entry_sectors == 0) {                                                 // 0.0
/*162 */         return -EINVAL;                                                          // 0.0
/*164 */     }                                                                            // 0.0
/*166 */     l1_size = (le64_to_cpu(header.capacity) + l1_entry_sectors - 1)              // 0.0
/*168 */                 / l1_entry_sectors;                                              // 0.0
/*170 */     if (le32_to_cpu(header.flags) & VMDK4_FLAG_RGD) {                            // 0.0
/*172 */         l1_backup_offset = le64_to_cpu(header.rgd_offset) << 9;                  // 0.0
/*174 */     }                                                                            // 0.0
/*176 */     extent = vmdk_add_extent(bs, file, false,                                    // 0.0
/*178 */                           le64_to_cpu(header.capacity),                          // 0.0
/*180 */                           le64_to_cpu(header.gd_offset) << 9,                    // 0.0
/*182 */                           l1_backup_offset,                                      // 0.0
/*184 */                           l1_size,                                               // 0.0
/*186 */                           le32_to_cpu(header.num_gtes_per_gte),                  // 0.0
/*188 */                           le64_to_cpu(header.granularity));                      // 0.0
/*190 */     extent->compressed =                                                         // 0.0
/*192 */         le16_to_cpu(header.compressAlgorithm) == VMDK4_COMPRESSION_DEFLATE;      // 0.0
/*194 */     extent->has_marker = le32_to_cpu(header.flags) & VMDK4_FLAG_MARKER;          // 0.0
/*196 */     extent->version = le32_to_cpu(header.version);                               // 0.0
/*198 */     extent->has_zero_grain = le32_to_cpu(header.flags) & VMDK4_FLAG_ZERO_GRAIN;  // 0.0
/*200 */     ret = vmdk_init_tables(bs, extent);                                          // 0.0
/*202 */     if (ret) {                                                                   // 0.0
/*204 */         /* free extent allocated by vmdk_add_extent */                           // 0.0
/*206 */         vmdk_free_last_extent(bs);                                               // 0.0
/*208 */     }                                                                            // 0.0
/*210 */     return ret;                                                                  // 0.0
/*212 */ }                                                                                // 0.0
