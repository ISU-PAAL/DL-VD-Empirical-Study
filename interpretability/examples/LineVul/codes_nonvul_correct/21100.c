// commit message qemu@ac4b0d0c4f (target=0, prob=0.16549264, correct=True): Add qemu_strndup: qemu_strdup with length limit.
/*0    */ static void bt_submit_hci(struct HCIInfo *info,                                  // (13) 0.0332
/*2    */                 const uint8_t *data, int length)                                 // (4) 0.05078
/*4    */ {                                                                                // (25) 0.001953
/*6    */     struct bt_hci_s *hci = hci_from_info(info);                                  // (6) 0.04687
/*8    */     uint16_t cmd;                                                                // (22) 0.01758
/*10   */     int paramlen, i;                                                             // (21) 0.01758
/*14   */     if (length < HCI_COMMAND_HDR_SIZE)                                           // (10) 0.03711
/*16   */         goto short_hci;                                                          // (17) 0.02539
/*20   */     memcpy(&hci->last_cmd, data, 2);                                             // (11) 0.03516
/*24   */     cmd = (data[1] << 8) | data[0];                                              // (12) 0.03516
/*26   */     paramlen = data[2];                                                          // (19) 0.01953
/*28   */     if (cmd_opcode_ogf(cmd) == 0 || cmd_opcode_ocf(cmd) == 0)	/* NOP */          // (0) 0.07031
/*30   */         return;                                                                  // (23) 0.01758
/*34   */     data += HCI_COMMAND_HDR_SIZE;                                                // (14) 0.0332
/*36   */     length -= HCI_COMMAND_HDR_SIZE;                                              // (15) 0.0332
/*40   */     if (paramlen > length)                                                       // (18) 0.01953
/*42   */         return;                                                                  // (20) 0.01758
/*46   */ #define PARAM(cmd, param)	(((cmd##_cp *) data)->param)                           // (7) 0.04297
/*48   */ #define PARAM16(cmd, param)	le16_to_cpup(&PARAM(cmd, param))                     // (5) 0.05078
/*50   */ #define PARAMHANDLE(cmd)	HNDL(PARAM(cmd, handle))                                // (8) 0.04297
/*52   */ #define LENGTH_CHECK(cmd)	if (length < sizeof(cmd##_cp)) goto short_hci          // (3) 0.05078
/*54   */     /* Note: the supported commands bitmask in bt_hci_read_local_commands_rp     // (2) 0.05273
/*56   */      * needs to be updated every time a command is implemented here!  */         // (9) 0.03711
/*58   */     switch (cmd) {                                                               // (24) 0.01562
/*60   */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_INQUIRY):                             // (1) 0.05469
/*62   */         LENGTH_CHECK(inquiry);                                                   // (16) 0.0293
/*66   */         if (PARAM(inquiry, length) < 1) {                                        // 0.0
/*68   */             bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);           // 0.0
/*70   */             break;                                                               // 0.0
/*72   */         }                                                                        // 0.0
/*76   */         hci->lm.inquire = 1;                                                     // 0.0
/*78   */         hci->lm.periodic = 0;                                                    // 0.0
/*80   */         hci->lm.responses_left = PARAM(inquiry, num_rsp) ?: INT_MAX;             // 0.0
/*82   */         hci->lm.responses = 0;                                                   // 0.0
/*84   */         bt_hci_event_status(hci, HCI_SUCCESS);                                   // 0.0
/*86   */         bt_hci_inquiry_start(hci, PARAM(inquiry, length));                       // 0.0
/*88   */         break;                                                                   // 0.0
/*92   */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_INQUIRY_CANCEL):                      // 0.0
/*94   */         if (!hci->lm.inquire || hci->lm.periodic) {                              // 0.0
/*96   */             fprintf(stderr, "%s: Inquiry Cancel should only be issued after "    // 0.0
/*98   */                             "the Inquiry command has been issued, a Command "    // 0.0
/*100  */                             "Status event has been received for the Inquiry "    // 0.0
/*102  */                             "command, and before the Inquiry Complete event "    // 0.0
/*104  */                             "occurs", __FUNCTION__);                             // 0.0
/*106  */             bt_hci_event_complete_status(hci, HCI_COMMAND_DISALLOWED);           // 0.0
/*108  */             break;                                                               // 0.0
/*110  */         }                                                                        // 0.0
/*114  */         hci->lm.inquire = 0;                                                     // 0.0
/*116  */         qemu_del_timer(hci->lm.inquiry_done);                                    // 0.0
/*118  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*120  */         break;                                                                   // 0.0
/*124  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_PERIODIC_INQUIRY):                    // 0.0
/*126  */         LENGTH_CHECK(periodic_inquiry);                                          // 0.0
/*130  */         if (!(PARAM(periodic_inquiry, length) <                                  // 0.0
/*132  */                                 PARAM16(periodic_inquiry, min_period) &&         // 0.0
/*134  */                                 PARAM16(periodic_inquiry, min_period) <          // 0.0
/*136  */                                 PARAM16(periodic_inquiry, max_period)) ||        // 0.0
/*138  */                         PARAM(periodic_inquiry, length) < 1 ||                   // 0.0
/*140  */                         PARAM16(periodic_inquiry, min_period) < 2 ||             // 0.0
/*142  */                         PARAM16(periodic_inquiry, max_period) < 3) {             // 0.0
/*144  */             bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);           // 0.0
/*146  */             break;                                                               // 0.0
/*148  */         }                                                                        // 0.0
/*152  */         hci->lm.inquire = 1;                                                     // 0.0
/*154  */         hci->lm.periodic = 1;                                                    // 0.0
/*156  */         hci->lm.responses_left = PARAM(periodic_inquiry, num_rsp);               // 0.0
/*158  */         hci->lm.responses = 0;                                                   // 0.0
/*160  */         hci->lm.inquiry_period = PARAM16(periodic_inquiry, max_period);          // 0.0
/*162  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*164  */         bt_hci_inquiry_start(hci, PARAM(periodic_inquiry, length));              // 0.0
/*166  */         break;                                                                   // 0.0
/*170  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_EXIT_PERIODIC_INQUIRY):               // 0.0
/*172  */         if (!hci->lm.inquire || !hci->lm.periodic) {                             // 0.0
/*174  */             fprintf(stderr, "%s: Inquiry Cancel should only be issued after "    // 0.0
/*176  */                             "the Inquiry command has been issued, a Command "    // 0.0
/*178  */                             "Status event has been received for the Inquiry "    // 0.0
/*180  */                             "command, and before the Inquiry Complete event "    // 0.0
/*182  */                             "occurs", __FUNCTION__);                             // 0.0
/*184  */             bt_hci_event_complete_status(hci, HCI_COMMAND_DISALLOWED);           // 0.0
/*186  */             break;                                                               // 0.0
/*188  */         }                                                                        // 0.0
/*190  */         hci->lm.inquire = 0;                                                     // 0.0
/*192  */         qemu_del_timer(hci->lm.inquiry_done);                                    // 0.0
/*194  */         qemu_del_timer(hci->lm.inquiry_next);                                    // 0.0
/*196  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*198  */         break;                                                                   // 0.0
/*202  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_CREATE_CONN):                         // 0.0
/*204  */         LENGTH_CHECK(create_conn);                                               // 0.0
/*208  */         if (hci->lm.connecting >= HCI_HANDLES_MAX) {                             // 0.0
/*210  */             bt_hci_event_status(hci, HCI_REJECTED_LIMITED_RESOURCES);            // 0.0
/*212  */             break;                                                               // 0.0
/*214  */         }                                                                        // 0.0
/*216  */         bt_hci_event_status(hci, HCI_SUCCESS);                                   // 0.0
/*220  */         if (bt_hci_connect(hci, &PARAM(create_conn, bdaddr)))                    // 0.0
/*222  */             bt_hci_connection_reject_event(hci, &PARAM(create_conn, bdaddr));    // 0.0
/*224  */         break;                                                                   // 0.0
/*228  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_DISCONNECT):                          // 0.0
/*230  */         LENGTH_CHECK(disconnect);                                                // 0.0
/*234  */         if (bt_hci_handle_bad(hci, PARAMHANDLE(disconnect))) {                   // 0.0
/*236  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*238  */             break;                                                               // 0.0
/*240  */         }                                                                        // 0.0
/*244  */         bt_hci_event_status(hci, HCI_SUCCESS);                                   // 0.0
/*246  */         bt_hci_disconnect(hci, PARAMHANDLE(disconnect),                          // 0.0
/*248  */                         PARAM(disconnect, reason));                              // 0.0
/*250  */         break;                                                                   // 0.0
/*254  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_CREATE_CONN_CANCEL):                  // 0.0
/*256  */         LENGTH_CHECK(create_conn_cancel);                                        // 0.0
/*260  */         if (bt_hci_lmp_connection_ready(hci,                                     // 0.0
/*262  */                                 &PARAM(create_conn_cancel, bdaddr))) {           // 0.0
/*264  */             for (i = 0; i < HCI_HANDLES_MAX; i ++)                               // 0.0
/*266  */                 if (bt_hci_role_master(hci, i) && hci->lm.handle[i].link &&      // 0.0
/*268  */                                 !bacmp(&hci->lm.handle[i].link->slave->bd_addr,  // 0.0
/*270  */                                         &PARAM(create_conn_cancel, bdaddr)))     // 0.0
/*272  */                    break;                                                        // 0.0
/*276  */             bt_hci_event_complete_conn_cancel(hci, i < HCI_HANDLES_MAX ?         // 0.0
/*278  */                             HCI_ACL_CONNECTION_EXISTS : HCI_NO_CONNECTION,       // 0.0
/*280  */                             &PARAM(create_conn_cancel, bdaddr));                 // 0.0
/*282  */         } else                                                                   // 0.0
/*284  */             bt_hci_event_complete_conn_cancel(hci, HCI_SUCCESS,                  // 0.0
/*286  */                             &PARAM(create_conn_cancel, bdaddr));                 // 0.0
/*288  */         break;                                                                   // 0.0
/*292  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_ACCEPT_CONN_REQ):                     // 0.0
/*294  */         LENGTH_CHECK(accept_conn_req);                                           // 0.0
/*298  */         if (!hci->conn_req_host ||                                               // 0.0
/*300  */                         bacmp(&PARAM(accept_conn_req, bdaddr),                   // 0.0
/*302  */                                 &hci->conn_req_host->bd_addr)) {                 // 0.0
/*304  */             bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);                    // 0.0
/*306  */             break;                                                               // 0.0
/*308  */         }                                                                        // 0.0
/*312  */         bt_hci_event_status(hci, HCI_SUCCESS);                                   // 0.0
/*314  */         bt_hci_connection_accept(hci, hci->conn_req_host);                       // 0.0
/*316  */         hci->conn_req_host = 0;                                                  // 0.0
/*318  */         break;                                                                   // 0.0
/*322  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_REJECT_CONN_REQ):                     // 0.0
/*324  */         LENGTH_CHECK(reject_conn_req);                                           // 0.0
/*328  */         if (!hci->conn_req_host ||                                               // 0.0
/*330  */                         bacmp(&PARAM(reject_conn_req, bdaddr),                   // 0.0
/*332  */                                 &hci->conn_req_host->bd_addr)) {                 // 0.0
/*334  */             bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);                    // 0.0
/*336  */             break;                                                               // 0.0
/*338  */         }                                                                        // 0.0
/*342  */         bt_hci_event_status(hci, HCI_SUCCESS);                                   // 0.0
/*344  */         bt_hci_connection_reject(hci, hci->conn_req_host,                        // 0.0
/*346  */                         PARAM(reject_conn_req, reason));                         // 0.0
/*348  */         bt_hci_connection_reject_event(hci, &hci->conn_req_host->bd_addr);       // 0.0
/*350  */         hci->conn_req_host = 0;                                                  // 0.0
/*352  */         break;                                                                   // 0.0
/*356  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_AUTH_REQUESTED):                      // 0.0
/*358  */         LENGTH_CHECK(auth_requested);                                            // 0.0
/*362  */         if (bt_hci_handle_bad(hci, PARAMHANDLE(auth_requested)))                 // 0.0
/*364  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*366  */         else {                                                                   // 0.0
/*368  */             bt_hci_event_status(hci, HCI_SUCCESS);                               // 0.0
/*370  */             bt_hci_event_auth_complete(hci, PARAMHANDLE(auth_requested));        // 0.0
/*372  */         }                                                                        // 0.0
/*374  */         break;                                                                   // 0.0
/*378  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_SET_CONN_ENCRYPT):                    // 0.0
/*380  */         LENGTH_CHECK(set_conn_encrypt);                                          // 0.0
/*384  */         if (bt_hci_handle_bad(hci, PARAMHANDLE(set_conn_encrypt)))               // 0.0
/*386  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*388  */         else {                                                                   // 0.0
/*390  */             bt_hci_event_status(hci, HCI_SUCCESS);                               // 0.0
/*392  */             bt_hci_event_encrypt_change(hci,                                     // 0.0
/*394  */                             PARAMHANDLE(set_conn_encrypt),                       // 0.0
/*396  */                             PARAM(set_conn_encrypt, encrypt));                   // 0.0
/*398  */         }                                                                        // 0.0
/*400  */         break;                                                                   // 0.0
/*404  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_REMOTE_NAME_REQ):                     // 0.0
/*406  */         LENGTH_CHECK(remote_name_req);                                           // 0.0
/*410  */         if (bt_hci_name_req(hci, &PARAM(remote_name_req, bdaddr)))               // 0.0
/*412  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*414  */         break;                                                                   // 0.0
/*418  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_REMOTE_NAME_REQ_CANCEL):              // 0.0
/*420  */         LENGTH_CHECK(remote_name_req_cancel);                                    // 0.0
/*424  */         bt_hci_event_complete_name_cancel(hci,                                   // 0.0
/*426  */                         &PARAM(remote_name_req_cancel, bdaddr));                 // 0.0
/*428  */         break;                                                                   // 0.0
/*432  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_REMOTE_FEATURES):                // 0.0
/*434  */         LENGTH_CHECK(read_remote_features);                                      // 0.0
/*438  */         if (bt_hci_features_req(hci, PARAMHANDLE(read_remote_features)))         // 0.0
/*440  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*442  */         break;                                                                   // 0.0
/*446  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_REMOTE_EXT_FEATURES):            // 0.0
/*448  */         LENGTH_CHECK(read_remote_ext_features);                                  // 0.0
/*452  */         if (bt_hci_handle_bad(hci, PARAMHANDLE(read_remote_ext_features)))       // 0.0
/*454  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*456  */         else {                                                                   // 0.0
/*458  */             bt_hci_event_status(hci, HCI_SUCCESS);                               // 0.0
/*460  */             bt_hci_event_read_remote_ext_features(hci,                           // 0.0
/*462  */                             PARAMHANDLE(read_remote_ext_features));              // 0.0
/*464  */         }                                                                        // 0.0
/*466  */         break;                                                                   // 0.0
/*470  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_REMOTE_VERSION):                 // 0.0
/*472  */         LENGTH_CHECK(read_remote_version);                                       // 0.0
/*476  */         if (bt_hci_version_req(hci, PARAMHANDLE(read_remote_version)))           // 0.0
/*478  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*480  */         break;                                                                   // 0.0
/*484  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_CLOCK_OFFSET):                   // 0.0
/*486  */         LENGTH_CHECK(read_clock_offset);                                         // 0.0
/*490  */         if (bt_hci_clkoffset_req(hci, PARAMHANDLE(read_clock_offset)))           // 0.0
/*492  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*494  */         break;                                                                   // 0.0
/*498  */     case cmd_opcode_pack(OGF_LINK_CTL, OCF_READ_LMP_HANDLE):                     // 0.0
/*500  */         LENGTH_CHECK(read_lmp_handle);                                           // 0.0
/*504  */         /* TODO: */                                                              // 0.0
/*506  */         bt_hci_event_complete_lmp_handle(hci, PARAMHANDLE(read_lmp_handle));     // 0.0
/*508  */         break;                                                                   // 0.0
/*512  */     case cmd_opcode_pack(OGF_LINK_POLICY, OCF_HOLD_MODE):                        // 0.0
/*514  */         LENGTH_CHECK(hold_mode);                                                 // 0.0
/*518  */         if (PARAM16(hold_mode, min_interval) >                                   // 0.0
/*520  */                         PARAM16(hold_mode, max_interval) ||                      // 0.0
/*522  */                         PARAM16(hold_mode, min_interval) < 0x0002 ||             // 0.0
/*524  */                         PARAM16(hold_mode, max_interval) > 0xff00 ||             // 0.0
/*526  */                         (PARAM16(hold_mode, min_interval) & 1) ||                // 0.0
/*528  */                         (PARAM16(hold_mode, max_interval) & 1)) {                // 0.0
/*530  */             bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);                    // 0.0
/*532  */             break;                                                               // 0.0
/*534  */         }                                                                        // 0.0
/*538  */         if (bt_hci_mode_change(hci, PARAMHANDLE(hold_mode),                      // 0.0
/*540  */                                 PARAM16(hold_mode, max_interval),                // 0.0
/*542  */                                 acl_hold))                                       // 0.0
/*544  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*546  */         break;                                                                   // 0.0
/*550  */     case cmd_opcode_pack(OGF_LINK_POLICY, OCF_PARK_MODE):                        // 0.0
/*552  */         LENGTH_CHECK(park_mode);                                                 // 0.0
/*556  */         if (PARAM16(park_mode, min_interval) >                                   // 0.0
/*558  */                         PARAM16(park_mode, max_interval) ||                      // 0.0
/*560  */                         PARAM16(park_mode, min_interval) < 0x000e ||             // 0.0
/*562  */                         (PARAM16(park_mode, min_interval) & 1) ||                // 0.0
/*564  */                         (PARAM16(park_mode, max_interval) & 1)) {                // 0.0
/*566  */             bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);                    // 0.0
/*568  */             break;                                                               // 0.0
/*570  */         }                                                                        // 0.0
/*574  */         if (bt_hci_mode_change(hci, PARAMHANDLE(park_mode),                      // 0.0
/*576  */                                 PARAM16(park_mode, max_interval),                // 0.0
/*578  */                                 acl_parked))                                     // 0.0
/*580  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*582  */         break;                                                                   // 0.0
/*586  */     case cmd_opcode_pack(OGF_LINK_POLICY, OCF_EXIT_PARK_MODE):                   // 0.0
/*588  */         LENGTH_CHECK(exit_park_mode);                                            // 0.0
/*592  */         if (bt_hci_mode_cancel(hci, PARAMHANDLE(exit_park_mode),                 // 0.0
/*594  */                                 acl_parked))                                     // 0.0
/*596  */             bt_hci_event_status(hci, HCI_NO_CONNECTION);                         // 0.0
/*598  */         break;                                                                   // 0.0
/*602  */     case cmd_opcode_pack(OGF_LINK_POLICY, OCF_ROLE_DISCOVERY):                   // 0.0
/*604  */         LENGTH_CHECK(role_discovery);                                            // 0.0
/*608  */         if (bt_hci_handle_bad(hci, PARAMHANDLE(role_discovery)))                 // 0.0
/*610  */             bt_hci_event_complete_role_discovery(hci,                            // 0.0
/*612  */                             HCI_NO_CONNECTION, PARAMHANDLE(role_discovery), 0);  // 0.0
/*614  */         else                                                                     // 0.0
/*616  */             bt_hci_event_complete_role_discovery(hci,                            // 0.0
/*618  */                             HCI_SUCCESS, PARAMHANDLE(role_discovery),            // 0.0
/*620  */                             bt_hci_role_master(hci,                              // 0.0
/*622  */                                     PARAMHANDLE(role_discovery)));               // 0.0
/*624  */         break;                                                                   // 0.0
/*628  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_SET_EVENT_MASK):                      // 0.0
/*630  */         LENGTH_CHECK(set_event_mask);                                            // 0.0
/*634  */         memcpy(hci->event_mask, PARAM(set_event_mask, mask), 8);                 // 0.0
/*636  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*638  */         break;                                                                   // 0.0
/*642  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_RESET):                               // 0.0
/*644  */         bt_hci_reset(hci);                                                       // 0.0
/*646  */         bt_hci_event_status(hci, HCI_SUCCESS);                                   // 0.0
/*648  */         break;                                                                   // 0.0
/*652  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_SET_EVENT_FLT):                       // 0.0
/*654  */         if (length >= 1 && PARAM(set_event_flt, flt_type) == FLT_CLEAR_ALL)      // 0.0
/*656  */             /* No length check */;                                               // 0.0
/*658  */         else                                                                     // 0.0
/*660  */             LENGTH_CHECK(set_event_flt);                                         // 0.0
/*664  */         /* Filters are not implemented */                                        // 0.0
/*666  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*668  */         break;                                                                   // 0.0
/*672  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_FLUSH):                               // 0.0
/*674  */         LENGTH_CHECK(flush);                                                     // 0.0
/*678  */         if (bt_hci_handle_bad(hci, PARAMHANDLE(flush)))                          // 0.0
/*680  */             bt_hci_event_complete_flush(hci,                                     // 0.0
/*682  */                             HCI_NO_CONNECTION, PARAMHANDLE(flush));              // 0.0
/*684  */         else {                                                                   // 0.0
/*686  */             /* TODO: ordering? */                                                // 0.0
/*688  */             bt_hci_event(hci, EVT_FLUSH_OCCURRED,                                // 0.0
/*690  */                             &PARAM(flush, handle),                               // 0.0
/*692  */                             EVT_FLUSH_OCCURRED_SIZE);                            // 0.0
/*694  */             bt_hci_event_complete_flush(hci,                                     // 0.0
/*696  */                             HCI_SUCCESS, PARAMHANDLE(flush));                    // 0.0
/*698  */         }                                                                        // 0.0
/*700  */         break;                                                                   // 0.0
/*704  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_CHANGE_LOCAL_NAME):                   // 0.0
/*706  */         LENGTH_CHECK(change_local_name);                                         // 0.0
/*710  */         if (hci->device.lmp_name)                                                // 0.0
/*712  */             free((void *) hci->device.lmp_name);                                 // 0.0
/*714  */         hci->device.lmp_name = strndup(PARAM(change_local_name, name),           // 0.0
/*716  */                         sizeof(PARAM(change_local_name, name)));                 // 0.0
/*718  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*720  */         break;                                                                   // 0.0
/*724  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_LOCAL_NAME):                     // 0.0
/*726  */         bt_hci_event_complete_read_local_name(hci);                              // 0.0
/*728  */         break;                                                                   // 0.0
/*732  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_CONN_ACCEPT_TIMEOUT):            // 0.0
/*734  */         bt_hci_event_complete_read_conn_accept_timeout(hci);                     // 0.0
/*736  */         break;                                                                   // 0.0
/*740  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_CONN_ACCEPT_TIMEOUT):           // 0.0
/*742  */         /* TODO */                                                               // 0.0
/*744  */         LENGTH_CHECK(write_conn_accept_timeout);                                 // 0.0
/*748  */         if (PARAM16(write_conn_accept_timeout, timeout) < 0x0001 ||              // 0.0
/*750  */                         PARAM16(write_conn_accept_timeout, timeout) > 0xb540) {  // 0.0
/*752  */             bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);           // 0.0
/*754  */             break;                                                               // 0.0
/*756  */         }                                                                        // 0.0
/*760  */         hci->conn_accept_tout = PARAM16(write_conn_accept_timeout, timeout);     // 0.0
/*762  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*764  */         break;                                                                   // 0.0
/*768  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_SCAN_ENABLE):                    // 0.0
/*770  */         bt_hci_event_complete_read_scan_enable(hci);                             // 0.0
/*772  */         break;                                                                   // 0.0
/*776  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_SCAN_ENABLE):                   // 0.0
/*778  */         LENGTH_CHECK(write_scan_enable);                                         // 0.0
/*782  */         /* TODO: check that the remaining bits are all 0 */                      // 0.0
/*784  */         hci->device.inquiry_scan =                                               // 0.0
/*786  */                 !!(PARAM(write_scan_enable, scan_enable) & SCAN_INQUIRY);        // 0.0
/*788  */         hci->device.page_scan =                                                  // 0.0
/*790  */                 !!(PARAM(write_scan_enable, scan_enable) & SCAN_PAGE);           // 0.0
/*792  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*794  */         break;                                                                   // 0.0
/*798  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_CLASS_OF_DEV):                   // 0.0
/*800  */         bt_hci_event_complete_read_local_class(hci);                             // 0.0
/*802  */         break;                                                                   // 0.0
/*806  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_CLASS_OF_DEV):                  // 0.0
/*808  */         LENGTH_CHECK(write_class_of_dev);                                        // 0.0
/*812  */         memcpy(hci->device.class, PARAM(write_class_of_dev, dev_class),          // 0.0
/*814  */                         sizeof(PARAM(write_class_of_dev, dev_class)));           // 0.0
/*816  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*818  */         break;                                                                   // 0.0
/*822  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_VOICE_SETTING):                  // 0.0
/*824  */         bt_hci_event_complete_voice_setting(hci);                                // 0.0
/*826  */         break;                                                                   // 0.0
/*830  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_VOICE_SETTING):                 // 0.0
/*832  */         LENGTH_CHECK(write_voice_setting);                                       // 0.0
/*836  */         hci->voice_setting = PARAM(write_voice_setting, voice_setting);          // 0.0
/*838  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*840  */         break;                                                                   // 0.0
/*844  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_HOST_NUMBER_OF_COMPLETED_PACKETS):    // 0.0
/*846  */         if (length < data[0] * 2 + 1)                                            // 0.0
/*848  */             goto short_hci;                                                      // 0.0
/*852  */         for (i = 0; i < data[0]; i ++)                                           // 0.0
/*854  */             if (bt_hci_handle_bad(hci,                                           // 0.0
/*856  */                                     data[i * 2 + 1] | (data[i * 2 + 2] << 8)))   // 0.0
/*858  */                 bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);       // 0.0
/*860  */         break;                                                                   // 0.0
/*864  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_READ_INQUIRY_MODE):                   // 0.0
/*866  */         /* Only if (local_features[3] & 0x40) && (local_commands[12] & 0x40)     // 0.0
/*868  */          * else                                                                  // 0.0
/*870  */          *     goto unknown_command */                                           // 0.0
/*872  */         bt_hci_event_complete_read_inquiry_mode(hci);                            // 0.0
/*874  */         break;                                                                   // 0.0
/*878  */     case cmd_opcode_pack(OGF_HOST_CTL, OCF_WRITE_INQUIRY_MODE):                  // 0.0
/*880  */         /* Only if (local_features[3] & 0x40) && (local_commands[12] & 0x80)     // 0.0
/*882  */          * else                                                                  // 0.0
/*884  */          *     goto unknown_command */                                           // 0.0
/*886  */         LENGTH_CHECK(write_inquiry_mode);                                        // 0.0
/*890  */         if (PARAM(write_inquiry_mode, mode) > 0x01) {                            // 0.0
/*892  */             bt_hci_event_complete_status(hci, HCI_INVALID_PARAMETERS);           // 0.0
/*894  */             break;                                                               // 0.0
/*896  */         }                                                                        // 0.0
/*900  */         hci->lm.inquiry_mode = PARAM(write_inquiry_mode, mode);                  // 0.0
/*902  */         bt_hci_event_complete_status(hci, HCI_SUCCESS);                          // 0.0
/*904  */         break;                                                                   // 0.0
/*908  */     case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_VERSION):                // 0.0
/*910  */         bt_hci_read_local_version_rp(hci);                                       // 0.0
/*912  */         break;                                                                   // 0.0
/*916  */     case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_COMMANDS):               // 0.0
/*918  */         bt_hci_read_local_commands_rp(hci);                                      // 0.0
/*920  */         break;                                                                   // 0.0
/*924  */     case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_FEATURES):               // 0.0
/*926  */         bt_hci_read_local_features_rp(hci);                                      // 0.0
/*928  */         break;                                                                   // 0.0
/*932  */     case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_LOCAL_EXT_FEATURES):           // 0.0
/*934  */         LENGTH_CHECK(read_local_ext_features);                                   // 0.0
/*938  */         bt_hci_read_local_ext_features_rp(hci,                                   // 0.0
/*940  */                         PARAM(read_local_ext_features, page_num));               // 0.0
/*942  */         break;                                                                   // 0.0
/*946  */     case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_BUFFER_SIZE):                  // 0.0
/*948  */         bt_hci_read_buffer_size_rp(hci);                                         // 0.0
/*950  */         break;                                                                   // 0.0
/*954  */     case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_COUNTRY_CODE):                 // 0.0
/*956  */         bt_hci_read_country_code_rp(hci);                                        // 0.0
/*958  */         break;                                                                   // 0.0
/*962  */     case cmd_opcode_pack(OGF_INFO_PARAM, OCF_READ_BD_ADDR):                      // 0.0
/*964  */         bt_hci_read_bd_addr_rp(hci);                                             // 0.0
/*966  */         break;                                                                   // 0.0
/*970  */     case cmd_opcode_pack(OGF_STATUS_PARAM, OCF_READ_LINK_QUALITY):               // 0.0
/*972  */         LENGTH_CHECK(read_link_quality);                                         // 0.0
/*976  */         bt_hci_link_quality_rp(hci, PARAMHANDLE(read_link_quality));             // 0.0
/*978  */         break;                                                                   // 0.0
/*982  */     default:                                                                     // 0.0
/*984  */         bt_hci_event_status(hci, HCI_UNKNOWN_COMMAND);                           // 0.0
/*986  */         break;                                                                   // 0.0
/*990  */     short_hci:                                                                   // 0.0
/*992  */         fprintf(stderr, "%s: HCI packet too short (%iB)\n",                      // 0.0
/*994  */                         __FUNCTION__, length);                                   // 0.0
/*996  */         bt_hci_event_status(hci, HCI_INVALID_PARAMETERS);                        // 0.0
/*998  */         break;                                                                   // 0.0
/*1000 */     }                                                                            // 0.0
/*1002 */ }                                                                                // 0.0
