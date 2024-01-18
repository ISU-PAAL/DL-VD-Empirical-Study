// commit message qemu@b93c94f7ec (target=1, prob=0.4818841, correct=False): iscsi: do not leak initiator_name
/*0   */ static int iscsi_open(BlockDriverState *bs, const char *filename, int flags)     // (8) 0.04297
/*2   */ {                                                                                // (26) 0.001953
/*4   */     IscsiLun *iscsilun = bs->opaque;                                             // (12) 0.03711
/*6   */     struct iscsi_context *iscsi = NULL;                                          // (14) 0.0293
/*8   */     struct iscsi_url *iscsi_url = NULL;                                          // (13) 0.0332
/*10  */     struct IscsiTask task;                                                       // (21) 0.01953
/*12  */     char *initiator_name = NULL;                                                 // (17) 0.02539
/*14  */     int ret;                                                                     // (23) 0.01172
/*18  */     if ((BDRV_SECTOR_SIZE % 512) != 0) {                                         // (9) 0.04102
/*20  */         error_report("iSCSI: Invalid BDRV_SECTOR_SIZE. "                         // (3) 0.05273
/*22  */                      "BDRV_SECTOR_SIZE(%lld) is not a multiple "                 // (0) 0.07812
/*24  */                      "of 512", BDRV_SECTOR_SIZE);                                // (1) 0.06641
/*26  */         return -EINVAL;                                                          // (19) 0.02539
/*28  */     }                                                                            // (25) 0.007812
/*32  */     iscsi_url = iscsi_parse_full_url(iscsi, filename);                           // (4) 0.04687
/*34  */     if (iscsi_url == NULL) {                                                     // (18) 0.02539
/*36  */         error_report("Failed to parse URL : %s %s", filename,                    // (6) 0.04687
/*38  */                      iscsi_get_error(iscsi));                                    // (2) 0.06055
/*40  */         ret = -EINVAL;                                                           // (16) 0.02734
/*42  */         goto failed;                                                             // (22) 0.01953
/*44  */     }                                                                            // (24) 0.007812
/*48  */     memset(iscsilun, 0, sizeof(IscsiLun));                                       // (11) 0.03906
/*52  */     initiator_name = parse_initiator_name(iscsi_url->target);                    // (7) 0.04492
/*56  */     iscsi = iscsi_create_context(initiator_name);                                // (10) 0.04102
/*58  */     if (iscsi == NULL) {                                                         // (20) 0.02148
/*60  */         error_report("iSCSI: Failed to create iSCSI context.");                  // (5) 0.04687
/*62  */         ret = -ENOMEM;                                                           // (15) 0.02734
/*64  */         goto failed;                                                             // 0.0
/*66  */     }                                                                            // 0.0
/*70  */     if (iscsi_set_targetname(iscsi, iscsi_url->target)) {                        // 0.0
/*72  */         error_report("iSCSI: Failed to set target name.");                       // 0.0
/*74  */         ret = -EINVAL;                                                           // 0.0
/*76  */         goto failed;                                                             // 0.0
/*78  */     }                                                                            // 0.0
/*82  */     if (iscsi_url->user != NULL) {                                               // 0.0
/*84  */         ret = iscsi_set_initiator_username_pwd(iscsi, iscsi_url->user,           // 0.0
/*86  */                                               iscsi_url->passwd);                // 0.0
/*88  */         if (ret != 0) {                                                          // 0.0
/*90  */             error_report("Failed to set initiator username and password");       // 0.0
/*92  */             ret = -EINVAL;                                                       // 0.0
/*94  */             goto failed;                                                         // 0.0
/*96  */         }                                                                        // 0.0
/*98  */     }                                                                            // 0.0
/*102 */     /* check if we got CHAP username/password via the options */                 // 0.0
/*104 */     if (parse_chap(iscsi, iscsi_url->target) != 0) {                             // 0.0
/*106 */         error_report("iSCSI: Failed to set CHAP user/password");                 // 0.0
/*108 */         ret = -EINVAL;                                                           // 0.0
/*110 */         goto failed;                                                             // 0.0
/*112 */     }                                                                            // 0.0
/*116 */     if (iscsi_set_session_type(iscsi, ISCSI_SESSION_NORMAL) != 0) {              // 0.0
/*118 */         error_report("iSCSI: Failed to set session type to normal.");            // 0.0
/*120 */         ret = -EINVAL;                                                           // 0.0
/*122 */         goto failed;                                                             // 0.0
/*124 */     }                                                                            // 0.0
/*128 */     iscsi_set_header_digest(iscsi, ISCSI_HEADER_DIGEST_NONE_CRC32C);             // 0.0
/*132 */     /* check if we got HEADER_DIGEST via the options */                          // 0.0
/*134 */     parse_header_digest(iscsi, iscsi_url->target);                               // 0.0
/*138 */     task.iscsilun = iscsilun;                                                    // 0.0
/*140 */     task.status = 0;                                                             // 0.0
/*142 */     task.complete = 0;                                                           // 0.0
/*144 */     task.bs = bs;                                                                // 0.0
/*148 */     iscsilun->iscsi = iscsi;                                                     // 0.0
/*150 */     iscsilun->lun   = iscsi_url->lun;                                            // 0.0
/*154 */     if (iscsi_full_connect_async(iscsi, iscsi_url->portal, iscsi_url->lun,       // 0.0
/*156 */                                  iscsi_connect_cb, &task)                        // 0.0
/*158 */         != 0) {                                                                  // 0.0
/*160 */         error_report("iSCSI: Failed to start async connect.");                   // 0.0
/*162 */         ret = -EINVAL;                                                           // 0.0
/*164 */         goto failed;                                                             // 0.0
/*166 */     }                                                                            // 0.0
/*170 */     while (!task.complete) {                                                     // 0.0
/*172 */         iscsi_set_events(iscsilun);                                              // 0.0
/*174 */         qemu_aio_wait();                                                         // 0.0
/*176 */     }                                                                            // 0.0
/*178 */     if (task.status != 0) {                                                      // 0.0
/*180 */         error_report("iSCSI: Failed to connect to LUN : %s",                     // 0.0
/*182 */                      iscsi_get_error(iscsi));                                    // 0.0
/*184 */         ret = -EINVAL;                                                           // 0.0
/*186 */         goto failed;                                                             // 0.0
/*188 */     }                                                                            // 0.0
/*192 */     if (iscsi_url != NULL) {                                                     // 0.0
/*194 */         iscsi_destroy_url(iscsi_url);                                            // 0.0
/*196 */     }                                                                            // 0.0
/*200 */     /* Medium changer or tape. We dont have any emulation for this so this must  // 0.0
/*202 */      * be sg ioctl compatible. We force it to be sg, otherwise qemu will try     // 0.0
/*204 */      * to read from the device to guess the image format.                        // 0.0
/*206 */      */                                                                          // 0.0
/*208 */     if (iscsilun->type == TYPE_MEDIUM_CHANGER ||                                 // 0.0
/*210 */         iscsilun->type == TYPE_TAPE) {                                           // 0.0
/*212 */         bs->sg = 1;                                                              // 0.0
/*214 */     }                                                                            // 0.0
/*218 */     return 0;                                                                    // 0.0
/*222 */ failed:                                                                          // 0.0
/*224 */     if (initiator_name != NULL) {                                                // 0.0
/*226 */         g_free(initiator_name);                                                  // 0.0
/*228 */     }                                                                            // 0.0
/*230 */     if (iscsi_url != NULL) {                                                     // 0.0
/*232 */         iscsi_destroy_url(iscsi_url);                                            // 0.0
/*234 */     }                                                                            // 0.0
/*236 */     if (iscsi != NULL) {                                                         // 0.0
/*238 */         iscsi_destroy_context(iscsi);                                            // 0.0
/*240 */     }                                                                            // 0.0
/*242 */     memset(iscsilun, 0, sizeof(IscsiLun));                                       // 0.0
/*244 */     return ret;                                                                  // 0.0
/*246 */ }                                                                                // 0.0
