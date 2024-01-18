// commit message qemu@10a412dab3 (target=0, prob=0.22944622, correct=True): hw/sd.c: Correct handling of type B SD status bits
/*0   */ int sd_do_command(SDState *sd, SDRequest *req,                      // (12) 0.0332
/*2   */                   uint8_t *response) {                              // (3) 0.04883
/*4   */     uint32_t last_status = sd->card_status;                         // (14) 0.0332
/*6   */     sd_rsp_type_t rtype;                                            // (17) 0.02734
/*8   */     int rsplen;                                                     // (23) 0.01563
/*12  */     if (!sd->bdrv || !bdrv_is_inserted(sd->bdrv) || !sd->enable) {  // (0) 0.06641
/*14  */         return 0;                                                   // (22) 0.01953
/*16  */     }                                                               // (28) 0.007812
/*20  */     if (sd_req_crc_validate(req)) {                                 // (10) 0.03516
/*22  */         sd->card_status |= COM_CRC_ERROR;                           // (7) 0.04102
/*24  */         rtype = sd_illegal;                                         // (18) 0.02734
/*26  */         goto send_response;                                         // (20) 0.02344
/*28  */     }                                                               // (26) 0.007813
/*32  */     sd->card_status &= ~CARD_STATUS_B;                              // (9) 0.03711
/*34  */     sd_set_status(sd);                                              // (21) 0.02148
/*38  */     if (last_status & CARD_IS_LOCKED) {                             // (13) 0.0332
/*40  */         if (!cmd_valid_while_locked(sd, req)) {                     // (4) 0.04297
/*42  */             sd->card_status |= ILLEGAL_COMMAND;                     // (2) 0.05273
/*44  */             fprintf(stderr, "SD: Card is locked\n");                // (1) 0.05273
/*46  */             rtype = sd_illegal;                                     // (11) 0.03516
/*48  */             goto send_response;                                     // (15) 0.03125
/*50  */         }                                                           // (24) 0.01562
/*52  */     }                                                               // (27) 0.007813
/*56  */     if (last_status & APP_CMD) {                                    // (16) 0.0293
/*58  */         rtype = sd_app_command(sd, *req);                           // (6) 0.04102
/*60  */         sd->card_status &= ~APP_CMD;                                // (8) 0.03906
/*62  */     } else                                                          // (25) 0.009766
/*64  */         rtype = sd_normal_command(sd, *req);                        // (5) 0.04102
/*68  */     if (rtype == sd_illegal) {                                      // (19) 0.02539
/*70  */         sd->card_status |= ILLEGAL_COMMAND;                         // 0.0
/*72  */     }                                                               // 0.0
/*76  */     sd->current_cmd = req->cmd;                                     // 0.0
/*80  */ send_response:                                                      // 0.0
/*82  */     switch (rtype) {                                                // 0.0
/*84  */     case sd_r1:                                                     // 0.0
/*86  */     case sd_r1b:                                                    // 0.0
/*88  */         sd_response_r1_make(sd, response, last_status);             // 0.0
/*90  */         rsplen = 4;                                                 // 0.0
/*92  */         break;                                                      // 0.0
/*96  */     case sd_r2_i:                                                   // 0.0
/*98  */         memcpy(response, sd->cid, sizeof(sd->cid));                 // 0.0
/*100 */         rsplen = 16;                                                // 0.0
/*102 */         break;                                                      // 0.0
/*106 */     case sd_r2_s:                                                   // 0.0
/*108 */         memcpy(response, sd->csd, sizeof(sd->csd));                 // 0.0
/*110 */         rsplen = 16;                                                // 0.0
/*112 */         break;                                                      // 0.0
/*116 */     case sd_r3:                                                     // 0.0
/*118 */         sd_response_r3_make(sd, response);                          // 0.0
/*120 */         rsplen = 4;                                                 // 0.0
/*122 */         break;                                                      // 0.0
/*126 */     case sd_r6:                                                     // 0.0
/*128 */         sd_response_r6_make(sd, response);                          // 0.0
/*130 */         rsplen = 4;                                                 // 0.0
/*132 */         break;                                                      // 0.0
/*136 */     case sd_r7:                                                     // 0.0
/*138 */         sd_response_r7_make(sd, response);                          // 0.0
/*140 */         rsplen = 4;                                                 // 0.0
/*142 */         break;                                                      // 0.0
/*146 */     case sd_r0:                                                     // 0.0
/*148 */     case sd_illegal:                                                // 0.0
/*150 */     default:                                                        // 0.0
/*152 */         rsplen = 0;                                                 // 0.0
/*154 */         break;                                                      // 0.0
/*156 */     }                                                               // 0.0
/*160 */ #ifdef DEBUG_SD                                                     // 0.0
/*162 */     if (rsplen) {                                                   // 0.0
/*164 */         int i;                                                      // 0.0
/*166 */         DPRINTF("Response:");                                       // 0.0
/*168 */         for (i = 0; i < rsplen; i++)                                // 0.0
/*170 */             printf(" %02x", response[i]);                           // 0.0
/*172 */         printf(" state %d\n", sd->state);                           // 0.0
/*174 */     } else {                                                        // 0.0
/*176 */         DPRINTF("No response %d\n", sd->state);                     // 0.0
/*178 */     }                                                               // 0.0
/*180 */ #endif                                                              // 0.0
/*184 */     return rsplen;                                                  // 0.0
/*186 */ }                                                                   // 0.0
