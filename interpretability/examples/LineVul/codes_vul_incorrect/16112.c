// commit message qemu@36fef36b91 (target=1, prob=0.19303787, correct=False): scsi: initialise info object with appropriate size
/*0   */ static int megasas_ctrl_get_info(MegasasState *s, MegasasCmd *cmd)            // (2) 0.06067
/*2   */ {                                                                             // (22) 0.001518
/*4   */     PCIDevice *pci_dev = PCI_DEVICE(s);                                       // (5) 0.01995
/*6   */     PCIDeviceClass *pci_class = PCI_DEVICE_GET_CLASS(pci_dev);                // (3) 0.04456
/*8   */     MegasasBaseClass *base_class = MEGASAS_DEVICE_GET_CLASS(s);               // (0) 0.641
/*10  */     struct mfi_ctrl_info info;                                                // (6) 0.01595
/*12  */     size_t dcmd_size = sizeof(info);                                          // (8) 0.007479
/*14  */     BusChild *kid;                                                            // (1) 0.08331
/*16  */     int num_pd_disks = 0;                                                     // (7) 0.008674
/*20  */     memset(&info, 0x0, cmd->iov_size);                                        // (11) 0.005182
/*22  */     if (cmd->iov_size < dcmd_size) {                                          // (19) 0.002428
/*24  */         trace_megasas_dcmd_invalid_xfer_len(cmd->index, cmd->iov_size,        // (4) 0.02553
/*26  */                                             dcmd_size);                       // (21) 0.001908
/*28  */         return MFI_STAT_INVALID_PARAMETER;                                    // (16) 0.003097
/*30  */     }                                                                         // (25) 0.0006694
/*34  */     info.pci.vendor = cpu_to_le16(pci_class->vendor_id);                      // (10) 0.005553
/*36  */     info.pci.device = cpu_to_le16(pci_class->device_id);                      // (12) 0.00471
/*38  */     info.pci.subvendor = cpu_to_le16(pci_class->subsystem_vendor_id);         // (17) 0.003038
/*40  */     info.pci.subdevice = cpu_to_le16(pci_class->subsystem_id);                // (9) 0.007293
/*44  */     /*                                                                        // (20) 0.002055
/*46  */      * For some reason the firmware supports                                  // (13) 0.00427
/*48  */      * only up to 8 device ports.                                             // (23) 0.001505
/*50  */      * Despite supporting a far larger number                                 // (14) 0.003514
/*52  */      * of devices for the physical devices.                                   // (24) 0.001269
/*54  */      * So just display the first 8 devices                                    // (18) 0.00251
/*56  */      * in the device port list, independent                                   // (15) 0.00328
/*58  */      * of how many logical devices are actually                               // 0.0
/*60  */      * present.                                                               // 0.0
/*62  */      */                                                                       // 0.0
/*64  */     info.host.type = MFI_INFO_HOST_PCIE;                                      // 0.0
/*66  */     info.device.type = MFI_INFO_DEV_SAS3G;                                    // 0.0
/*68  */     info.device.port_count = 8;                                               // 0.0
/*70  */     QTAILQ_FOREACH(kid, &s->bus.qbus.children, sibling) {                     // 0.0
/*72  */         SCSIDevice *sdev = DO_UPCAST(SCSIDevice, qdev, kid->child);           // 0.0
/*74  */         uint16_t pd_id;                                                       // 0.0
/*78  */         if (num_pd_disks < 8) {                                               // 0.0
/*80  */             pd_id = ((sdev->id & 0xFF) << 8) | (sdev->lun & 0xFF);            // 0.0
/*82  */             info.device.port_addr[num_pd_disks] =                             // 0.0
/*84  */                 cpu_to_le64(megasas_get_sata_addr(pd_id));                    // 0.0
/*86  */         }                                                                     // 0.0
/*88  */         num_pd_disks++;                                                       // 0.0
/*90  */     }                                                                         // 0.0
/*94  */     memcpy(info.product_name, base_class->product_name, 24);                  // 0.0
/*96  */     snprintf(info.serial_number, 32, "%s", s->hba_serial);                    // 0.0
/*98  */     snprintf(info.package_version, 0x60, "%s-QEMU", qemu_hw_version());       // 0.0
/*100 */     memcpy(info.image_component[0].name, "APP", 3);                           // 0.0
/*102 */     snprintf(info.image_component[0].version, 10, "%s-QEMU",                  // 0.0
/*104 */              base_class->product_version);                                    // 0.0
/*106 */     memcpy(info.image_component[0].build_date, "Apr  1 2014", 11);            // 0.0
/*108 */     memcpy(info.image_component[0].build_time, "12:34:56", 8);                // 0.0
/*110 */     info.image_component_count = 1;                                           // 0.0
/*112 */     if (pci_dev->has_rom) {                                                   // 0.0
/*114 */         uint8_t biosver[32];                                                  // 0.0
/*116 */         uint8_t *ptr;                                                         // 0.0
/*120 */         ptr = memory_region_get_ram_ptr(&pci_dev->rom);                       // 0.0
/*122 */         memcpy(biosver, ptr + 0x41, 31);                                      // 0.0
/*124 */         memcpy(info.image_component[1].name, "BIOS", 4);                      // 0.0
/*126 */         memcpy(info.image_component[1].version, biosver,                      // 0.0
/*128 */                strlen((const char *)biosver));                                // 0.0
/*130 */         info.image_component_count++;                                         // 0.0
/*132 */     }                                                                         // 0.0
/*134 */     info.current_fw_time = cpu_to_le32(megasas_fw_time());                    // 0.0
/*136 */     info.max_arms = 32;                                                       // 0.0
/*138 */     info.max_spans = 8;                                                       // 0.0
/*140 */     info.max_arrays = MEGASAS_MAX_ARRAYS;                                     // 0.0
/*142 */     info.max_lds = MFI_MAX_LD;                                                // 0.0
/*144 */     info.max_cmds = cpu_to_le16(s->fw_cmds);                                  // 0.0
/*146 */     info.max_sg_elements = cpu_to_le16(s->fw_sge);                            // 0.0
/*148 */     info.max_request_size = cpu_to_le32(MEGASAS_MAX_SECTORS);                 // 0.0
/*150 */     if (!megasas_is_jbod(s))                                                  // 0.0
/*152 */         info.lds_present = cpu_to_le16(num_pd_disks);                         // 0.0
/*154 */     info.pd_present = cpu_to_le16(num_pd_disks);                              // 0.0
/*156 */     info.pd_disks_present = cpu_to_le16(num_pd_disks);                        // 0.0
/*158 */     info.hw_present = cpu_to_le32(MFI_INFO_HW_NVRAM |                         // 0.0
/*160 */                                    MFI_INFO_HW_MEM |                          // 0.0
/*162 */                                    MFI_INFO_HW_FLASH);                        // 0.0
/*164 */     info.memory_size = cpu_to_le16(512);                                      // 0.0
/*166 */     info.nvram_size = cpu_to_le16(32);                                        // 0.0
/*168 */     info.flash_size = cpu_to_le16(16);                                        // 0.0
/*170 */     info.raid_levels = cpu_to_le32(MFI_INFO_RAID_0);                          // 0.0
/*172 */     info.adapter_ops = cpu_to_le32(MFI_INFO_AOPS_RBLD_RATE |                  // 0.0
/*174 */                                     MFI_INFO_AOPS_SELF_DIAGNOSTIC |           // 0.0
/*176 */                                     MFI_INFO_AOPS_MIXED_ARRAY);               // 0.0
/*178 */     info.ld_ops = cpu_to_le32(MFI_INFO_LDOPS_DISK_CACHE_POLICY |              // 0.0
/*180 */                                MFI_INFO_LDOPS_ACCESS_POLICY |                 // 0.0
/*182 */                                MFI_INFO_LDOPS_IO_POLICY |                     // 0.0
/*184 */                                MFI_INFO_LDOPS_WRITE_POLICY |                  // 0.0
/*186 */                                MFI_INFO_LDOPS_READ_POLICY);                   // 0.0
/*188 */     info.max_strips_per_io = cpu_to_le16(s->fw_sge);                          // 0.0
/*190 */     info.stripe_sz_ops.min = 3;                                               // 0.0
/*192 */     info.stripe_sz_ops.max = ctz32(MEGASAS_MAX_SECTORS + 1);                  // 0.0
/*194 */     info.properties.pred_fail_poll_interval = cpu_to_le16(300);               // 0.0
/*196 */     info.properties.intr_throttle_cnt = cpu_to_le16(16);                      // 0.0
/*198 */     info.properties.intr_throttle_timeout = cpu_to_le16(50);                  // 0.0
/*200 */     info.properties.rebuild_rate = 30;                                        // 0.0
/*202 */     info.properties.patrol_read_rate = 30;                                    // 0.0
/*204 */     info.properties.bgi_rate = 30;                                            // 0.0
/*206 */     info.properties.cc_rate = 30;                                             // 0.0
/*208 */     info.properties.recon_rate = 30;                                          // 0.0
/*210 */     info.properties.cache_flush_interval = 4;                                 // 0.0
/*212 */     info.properties.spinup_drv_cnt = 2;                                       // 0.0
/*214 */     info.properties.spinup_delay = 6;                                         // 0.0
/*216 */     info.properties.ecc_bucket_size = 15;                                     // 0.0
/*218 */     info.properties.ecc_bucket_leak_rate = cpu_to_le16(1440);                 // 0.0
/*220 */     info.properties.expose_encl_devices = 1;                                  // 0.0
/*222 */     info.properties.OnOffProperties = cpu_to_le32(MFI_CTRL_PROP_EnableJBOD);  // 0.0
/*224 */     info.pd_ops = cpu_to_le32(MFI_INFO_PDOPS_FORCE_ONLINE |                   // 0.0
/*226 */                                MFI_INFO_PDOPS_FORCE_OFFLINE);                 // 0.0
/*228 */     info.pd_mix_support = cpu_to_le32(MFI_INFO_PDMIX_SAS |                    // 0.0
/*230 */                                        MFI_INFO_PDMIX_SATA |                  // 0.0
/*232 */                                        MFI_INFO_PDMIX_LD);                    // 0.0
/*236 */     cmd->iov_size -= dma_buf_read((uint8_t *)&info, dcmd_size, &cmd->qsg);    // 0.0
/*238 */     return MFI_STAT_OK;                                                       // 0.0
/*240 */ }                                                                             // 0.0
