// commit message qemu@73d60fa5fa (target=1, prob=0.97323555, correct=True): ipmi: sensor number should not exceed MAX_SENSORS
/*0  */ static void get_sensor_evt_status(IPMIBmcSim *ibs,                      // (10) 0.04497
/*2  */                                   uint8_t *cmd, unsigned int cmd_len,   // (1) 0.0985
/*4  */                                   uint8_t *rsp, unsigned int *rsp_len,  // (0) 0.1049
/*6  */                                   unsigned int max_rsp_len)             // (2) 0.08994
/*8  */ {                                                                       // (18) 0.002141
/*10 */     IPMISensor *sens;                                                   // (15) 0.02141
/*14 */     IPMI_CHECK_CMD_LEN(3);                                              // (13) 0.03426
/*16 */     if ((cmd[2] > MAX_SENSORS) ||                                       // (12) 0.0364
/*18 */         !IPMI_SENSOR_GET_PRESENT(ibs->sensors + cmd[2])) {              // (3) 0.07066
/*20 */         rsp[2] = IPMI_CC_REQ_ENTRY_NOT_PRESENT;                         // (5) 0.0621
/*22 */         return;                                                         // (16) 0.01927
/*24 */     }                                                                   // (17) 0.008565
/*26 */     sens = ibs->sensors + cmd[2];                                       // (14) 0.03426
/*28 */     IPMI_ADD_RSP_DATA(sens->reading);                                   // (11) 0.03854
/*30 */     IPMI_ADD_RSP_DATA(IPMI_SENSOR_GET_RET_STATUS(sens));                // (4) 0.06424
/*32 */     IPMI_ADD_RSP_DATA(sens->assert_states & 0xff);                      // (9) 0.04925
/*34 */     IPMI_ADD_RSP_DATA((sens->assert_states >> 8) & 0xff);               // (7) 0.05567
/*36 */     IPMI_ADD_RSP_DATA(sens->deassert_states & 0xff);                    // (8) 0.05139
/*38 */     IPMI_ADD_RSP_DATA((sens->deassert_states >> 8) & 0xff);             // (6) 0.05782
/*40 */ }                                                                       // (19) 0.002141
