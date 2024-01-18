// commit message qemu@87e459a810 (target=1, prob=0.6640771, correct=True): megasas: always store SCSIRequest* into MegasasCmd
/*0   */ static int megasas_pd_get_info_submit(SCSIDevice *sdev, int lun,                // (7) 0.05078
/*2   */                                       MegasasCmd *cmd)                          // (1) 0.08594
/*4   */ {                                                                               // (20) 0.001953
/*6   */     struct mfi_pd_info *info = cmd->iov_buf;                                    // (12) 0.03711
/*8   */     size_t dcmd_size = sizeof(struct mfi_pd_info);                              // (10) 0.04102
/*10  */     uint64_t pd_size;                                                           // (14) 0.02344
/*12  */     uint16_t pd_id = ((sdev->id & 0xFF) << 8) | (lun & 0xFF);                   // (3) 0.06641
/*14  */     uint8_t cmdbuf[6];                                                          // (15) 0.02344
/*16  */     SCSIRequest *req;                                                           // (19) 0.01758
/*18  */     size_t len, resid;                                                          // (18) 0.01953
/*22  */     if (!cmd->iov_buf) {                                                        // (16) 0.02344
/*24  */         cmd->iov_buf = g_malloc0(dcmd_size);                                    // (8) 0.04688
/*26  */         info = cmd->iov_buf;                                                    // (13) 0.0293
/*28  */         info->inquiry_data[0] = 0x7f; /* Force PQual 0x3, PType 0x1f */         // (2) 0.07227
/*30  */         info->vpd_page83[0] = 0x7f;                                             // (9) 0.04492
/*32  */         megasas_setup_inquiry(cmdbuf, 0, sizeof(info->inquiry_data));           // (4) 0.05859
/*34  */         req = scsi_req_new(sdev, cmd->index, lun, cmdbuf, cmd);                 // (5) 0.05859
/*36  */         if (!req) {                                                             // (17) 0.02344
/*38  */             trace_megasas_dcmd_req_alloc_failed(cmd->index,                     // (6) 0.05859
/*40  */                                                 "PD get info std inquiry");     // (0) 0.1055
/*42  */             g_free(cmd->iov_buf);                                               // (11) 0.04102
/*44  */             cmd->iov_buf = NULL;                                                // 0.0
/*46  */             return MFI_STAT_FLASH_ALLOC_FAIL;                                   // 0.0
/*48  */         }                                                                       // 0.0
/*50  */         trace_megasas_dcmd_internal_submit(cmd->index,                          // 0.0
/*52  */                                            "PD get info std inquiry", lun);     // 0.0
/*54  */         len = scsi_req_enqueue(req);                                            // 0.0
/*56  */         if (len > 0) {                                                          // 0.0
/*58  */             cmd->iov_size = len;                                                // 0.0
/*60  */             scsi_req_continue(req);                                             // 0.0
/*62  */         }                                                                       // 0.0
/*64  */         return MFI_STAT_INVALID_STATUS;                                         // 0.0
/*66  */     } else if (info->inquiry_data[0] != 0x7f && info->vpd_page83[0] == 0x7f) {  // 0.0
/*68  */         megasas_setup_inquiry(cmdbuf, 0x83, sizeof(info->vpd_page83));          // 0.0
/*70  */         req = scsi_req_new(sdev, cmd->index, lun, cmdbuf, cmd);                 // 0.0
/*72  */         if (!req) {                                                             // 0.0
/*74  */             trace_megasas_dcmd_req_alloc_failed(cmd->index,                     // 0.0
/*76  */                                                 "PD get info vpd inquiry");     // 0.0
/*78  */             return MFI_STAT_FLASH_ALLOC_FAIL;                                   // 0.0
/*80  */         }                                                                       // 0.0
/*82  */         trace_megasas_dcmd_internal_submit(cmd->index,                          // 0.0
/*84  */                                            "PD get info vpd inquiry", lun);     // 0.0
/*86  */         len = scsi_req_enqueue(req);                                            // 0.0
/*88  */         if (len > 0) {                                                          // 0.0
/*90  */             cmd->iov_size = len;                                                // 0.0
/*92  */             scsi_req_continue(req);                                             // 0.0
/*94  */         }                                                                       // 0.0
/*96  */         return MFI_STAT_INVALID_STATUS;                                         // 0.0
/*98  */     }                                                                           // 0.0
/*100 */     /* Finished, set FW state */                                                // 0.0
/*102 */     if ((info->inquiry_data[0] >> 5) == 0) {                                    // 0.0
/*104 */         if (megasas_is_jbod(cmd->state)) {                                      // 0.0
/*106 */             info->fw_state = cpu_to_le16(MFI_PD_STATE_SYSTEM);                  // 0.0
/*108 */         } else {                                                                // 0.0
/*110 */             info->fw_state = cpu_to_le16(MFI_PD_STATE_ONLINE);                  // 0.0
/*112 */         }                                                                       // 0.0
/*114 */     } else {                                                                    // 0.0
/*116 */         info->fw_state = cpu_to_le16(MFI_PD_STATE_OFFLINE);                     // 0.0
/*118 */     }                                                                           // 0.0
/*122 */     info->ref.v.device_id = cpu_to_le16(pd_id);                                 // 0.0
/*124 */     info->state.ddf.pd_type = cpu_to_le16(MFI_PD_DDF_TYPE_IN_VD|                // 0.0
/*126 */                                           MFI_PD_DDF_TYPE_INTF_SAS);            // 0.0
/*128 */     blk_get_geometry(sdev->conf.blk, &pd_size);                                 // 0.0
/*130 */     info->raw_size = cpu_to_le64(pd_size);                                      // 0.0
/*132 */     info->non_coerced_size = cpu_to_le64(pd_size);                              // 0.0
/*134 */     info->coerced_size = cpu_to_le64(pd_size);                                  // 0.0
/*136 */     info->encl_device_id = 0xFFFF;                                              // 0.0
/*138 */     info->slot_number = (sdev->id & 0xFF);                                      // 0.0
/*140 */     info->path_info.count = 1;                                                  // 0.0
/*142 */     info->path_info.sas_addr[0] =                                               // 0.0
/*144 */         cpu_to_le64(megasas_get_sata_addr(pd_id));                              // 0.0
/*146 */     info->connected_port_bitmap = 0x1;                                          // 0.0
/*148 */     info->device_speed = 1;                                                     // 0.0
/*150 */     info->link_speed = 1;                                                       // 0.0
/*152 */     resid = dma_buf_read(cmd->iov_buf, dcmd_size, &cmd->qsg);                   // 0.0
/*154 */     g_free(cmd->iov_buf);                                                       // 0.0
/*156 */     cmd->iov_size = dcmd_size - resid;                                          // 0.0
/*158 */     cmd->iov_buf = NULL;                                                        // 0.0
/*160 */     return MFI_STAT_OK;                                                         // 0.0
/*162 */ }                                                                               // 0.0
