// commit message qemu@73d60fa5fa (target=1, prob=0.9745666, correct=True): ipmi: sensor number should not exceed MAX_SENSORS
/*0  */ static void get_sensor_evt_enable(IPMIBmcSim *ibs,                      // (10) 0.04688
/*2  */                                   uint8_t *cmd, unsigned int cmd_len,   // (1) 0.1027
/*4  */                                   uint8_t *rsp, unsigned int *rsp_len,  // (0) 0.1094
/*6  */                                   unsigned int max_rsp_len)             // (2) 0.09375
/*8  */ {                                                                       // (17) 0.002232
/*10 */     IPMISensor *sens;                                                   // (14) 0.02232
/*14 */     IPMI_CHECK_CMD_LEN(3);                                              // (12) 0.03571
/*16 */     if ((cmd[2] > MAX_SENSORS) ||                                       // (11) 0.03795
/*18 */         !IPMI_SENSOR_GET_PRESENT(ibs->sensors + cmd[2])) {              // (3) 0.07366
/*20 */         rsp[2] = IPMI_CC_REQ_ENTRY_NOT_PRESENT;                         // (5) 0.06473
/*22 */         return;                                                         // (15) 0.02009
/*24 */     }                                                                   // (16) 0.008929
/*26 */     sens = ibs->sensors + cmd[2];                                       // (13) 0.03571
/*28 */     IPMI_ADD_RSP_DATA(IPMI_SENSOR_GET_RET_STATUS(sens));                // (4) 0.06696
/*30 */     IPMI_ADD_RSP_DATA(sens->assert_enable & 0xff);                      // (9) 0.05134
/*32 */     IPMI_ADD_RSP_DATA((sens->assert_enable >> 8) & 0xff);               // (7) 0.05804
/*34 */     IPMI_ADD_RSP_DATA(sens->deassert_enable & 0xff);                    // (8) 0.05357
/*36 */     IPMI_ADD_RSP_DATA((sens->deassert_enable >> 8) & 0xff);             // (6) 0.06027
/*38 */ }                                                                       // (18) 0.002232
