// commit message qemu@e5fda03839 (target=1, prob=0.12135865, correct=False): bt: replace fragile snprintf use and unwarranted strncpy
/*0  */ static inline void bt_hci_event_complete_read_local_name(struct bt_hci_s *hci)  // (0) 0.1845
/*2  */ {                                                                               // (7) 0.005952
/*4  */     read_local_name_rp params;                                                  // (6) 0.07738
/*6  */     params.status = HCI_SUCCESS;                                                // (5) 0.08333
/*8  */     memset(params.name, 0, sizeof(params.name));                                // (3) 0.1071
/*10 */     if (hci->device.lmp_name)                                                   // (4) 0.08929
/*12 */         strncpy(params.name, hci->device.lmp_name, sizeof(params.name));        // (1) 0.1845
/*16 */     bt_hci_event_complete(hci, &params, READ_LOCAL_NAME_RP_SIZE);               // (2) 0.1786
/*18 */ }                                                                               // (8) 0.005952
