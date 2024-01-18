// commit message qemu@10a412dab3 (target=0, prob=0.6921513, correct=False): hw/sd.c: Correct handling of type B SD status bits
/*0  */ static void sd_response_r1_make(SDState *sd,                              // (8) 0.06926
/*2  */                                 uint8_t *response, uint32_t last_status)  // (0) 0.1991
/*4  */ {                                                                         // (10) 0.004329
/*6  */     uint32_t mask = CARD_STATUS_B ^ ILLEGAL_COMMAND;                      // (1) 0.1082
/*8  */     uint32_t status;                                                      // (9) 0.03896
/*12 */     status = (sd->card_status & ~mask) | (last_status & mask);            // (3) 0.09957
/*14 */     sd->card_status &= ~CARD_STATUS_C | APP_CMD;                          // (2) 0.1039
/*18 */     response[0] = (status >> 24) & 0xff;                                  // (4) 0.07359
/*20 */     response[1] = (status >> 16) & 0xff;                                  // (5) 0.07359
/*22 */     response[2] = (status >> 8) & 0xff;                                   // (6) 0.07359
/*24 */     response[3] = (status >> 0) & 0xff;                                   // (7) 0.07359
/*26 */ }                                                                         // (11) 0.004329
