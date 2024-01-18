// commit message qemu@abda1f37ee (target=1, prob=0.2390847, correct=False): hw/sd.c: On CRC error, set CRC error status bit rather than clearing it
/*0   */ int sd_do_command(SDState *sd, SDRequest *req,                      // (11) 0.0332
/*2   */                   uint8_t *response) {                              // (3) 0.04883
/*4   */     uint32_t last_status = sd->card_status;                         // (13) 0.0332
/*6   */     sd_rsp_type_t rtype;                                            // (15) 0.02734
/*8   */     int rsplen;                                                     // (24) 0.01563
/*12  */     if (!sd->bdrv || !bdrv_is_inserted(sd->bdrv) || !sd->enable) {  // (0) 0.06641
/*14  */         return 0;                                                   // (20) 0.01953
/*16  */     }                                                               // (28) 0.007812
/*20  */     if (sd_req_crc_validate(req)) {                                 // (10) 0.03516
/*22  */         sd->card_status &= ~COM_CRC_ERROR;                          // (5) 0.04297
/*24  */         return 0;                                                   // (21) 0.01953
/*26  */     }                                                               // (29) 0.007812
/*30  */     sd->card_status &= ~CARD_STATUS_B;                              // (9) 0.03711
/*32  */     sd_set_status(sd);                                              // (18) 0.02148
/*36  */     if (last_status & CARD_IS_LOCKED) {                             // (12) 0.0332
/*38  */         if (!cmd_valid_while_locked(sd, req)) {                     // (4) 0.04297
/*40  */             sd->card_status |= ILLEGAL_COMMAND;                     // (2) 0.05273
/*42  */             fprintf(stderr, "SD: Card is locked\n");                // (1) 0.05273
/*44  */             return 0;                                               // (16) 0.02734
/*46  */         }                                                           // (25) 0.01562
/*48  */     }                                                               // (27) 0.007812
/*52  */     if (last_status & APP_CMD) {                                    // (14) 0.0293
/*54  */         rtype = sd_app_command(sd, *req);                           // (7) 0.04102
/*56  */         sd->card_status &= ~APP_CMD;                                // (8) 0.03906
/*58  */     } else                                                          // (26) 0.009766
/*60  */         rtype = sd_normal_command(sd, *req);                        // (6) 0.04102
/*64  */     sd->current_cmd = req->cmd;                                     // (17) 0.02539
/*68  */     switch (rtype) {                                                // (23) 0.01758
/*70  */     case sd_r1:                                                     // (22) 0.01758
/*72  */     case sd_r1b:                                                    // (19) 0.01953
/*74  */         sd_response_r1_make(sd, response, last_status);             // 0.0
/*76  */         rsplen = 4;                                                 // 0.0
/*78  */         break;                                                      // 0.0
/*82  */     case sd_r2_i:                                                   // 0.0
/*84  */         memcpy(response, sd->cid, sizeof(sd->cid));                 // 0.0
/*86  */         rsplen = 16;                                                // 0.0
/*88  */         break;                                                      // 0.0
/*92  */     case sd_r2_s:                                                   // 0.0
/*94  */         memcpy(response, sd->csd, sizeof(sd->csd));                 // 0.0
/*96  */         rsplen = 16;                                                // 0.0
/*98  */         break;                                                      // 0.0
/*102 */     case sd_r3:                                                     // 0.0
/*104 */         sd_response_r3_make(sd, response);                          // 0.0
/*106 */         rsplen = 4;                                                 // 0.0
/*108 */         break;                                                      // 0.0
/*112 */     case sd_r6:                                                     // 0.0
/*114 */         sd_response_r6_make(sd, response);                          // 0.0
/*116 */         rsplen = 4;                                                 // 0.0
/*118 */         break;                                                      // 0.0
/*122 */     case sd_r7:                                                     // 0.0
/*124 */         sd_response_r7_make(sd, response);                          // 0.0
/*126 */         rsplen = 4;                                                 // 0.0
/*128 */         break;                                                      // 0.0
/*132 */     case sd_r0:                                                     // 0.0
/*134 */     default:                                                        // 0.0
/*136 */         rsplen = 0;                                                 // 0.0
/*138 */         break;                                                      // 0.0
/*140 */     }                                                               // 0.0
/*144 */     if (sd->card_status & ILLEGAL_COMMAND)                          // 0.0
/*146 */         rsplen = 0;                                                 // 0.0
/*150 */ #ifdef DEBUG_SD                                                     // 0.0
/*152 */     if (rsplen) {                                                   // 0.0
/*154 */         int i;                                                      // 0.0
/*156 */         DPRINTF("Response:");                                       // 0.0
/*158 */         for (i = 0; i < rsplen; i++)                                // 0.0
/*160 */             printf(" %02x", response[i]);                           // 0.0
/*162 */         printf(" state %d\n", sd->state);                           // 0.0
/*164 */     } else {                                                        // 0.0
/*166 */         DPRINTF("No response %d\n", sd->state);                     // 0.0
/*168 */     }                                                               // 0.0
/*170 */ #endif                                                              // 0.0
/*174 */     return rsplen;                                                  // 0.0
/*176 */ }                                                                   // 0.0
