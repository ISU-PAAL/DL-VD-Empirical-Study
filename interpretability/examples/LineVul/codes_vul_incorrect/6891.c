// commit message qemu@8be487d8f1 (target=1, prob=0.4280702, correct=False): sdhci: convert the DPRINT() calls into trace events
/*0   */ static void sdhci_send_command(SDHCIState *s)                                     // (10) 0.0332
/*2   */ {                                                                                 // (20) 0.001953
/*4   */     SDRequest request;                                                            // (18) 0.01367
/*6   */     uint8_t response[16];                                                         // (16) 0.02148
/*8   */     int rlen;                                                                     // (19) 0.01367
/*12  */     s->errintsts = 0;                                                             // (17) 0.02148
/*14  */     s->acmd12errsts = 0;                                                          // (14) 0.02539
/*16  */     request.cmd = s->cmdreg >> 8;                                                 // (13) 0.02734
/*18  */     request.arg = s->argument;                                                    // (15) 0.02148
/*20  */     DPRINT_L1("sending CMD%u ARG[0x%08x]\n", request.cmd, request.arg);           // (7) 0.06836
/*22  */     rlen = sdbus_do_command(&s->sdbus, &request, response);                       // (8) 0.04883
/*26  */     if (s->cmdreg & SDHC_CMD_RESPONSE) {                                          // (9) 0.04297
/*28  */         if (rlen == 4) {                                                          // (12) 0.0293
/*30  */             s->rspreg[0] = (response[0] << 24) | (response[1] << 16) |            // (4) 0.07422
/*32  */                            (response[2] << 8)  |  response[3];                    // (1) 0.08008
/*34  */             s->rspreg[1] = s->rspreg[2] = s->rspreg[3] = 0;                       // (3) 0.07812
/*36  */             DPRINT_L1("Response: RSPREG[31..0]=0x%08x\n", s->rspreg[0]);          // (0) 0.08398
/*38  */         } else if (rlen == 16) {                                                  // (11) 0.0332
/*40  */             s->rspreg[0] = (response[11] << 24) | (response[12] << 16) |          // (5) 0.07422
/*42  */                            (response[13] << 8) |  response[14];                   // (2) 0.07812
/*44  */             s->rspreg[1] = (response[7] << 24) | (response[8] << 16) |            // (6) 0.07422
/*46  */                            (response[9] << 8)  |  response[10];                   // 0.0
/*48  */             s->rspreg[2] = (response[3] << 24) | (response[4] << 16) |            // 0.0
/*50  */                            (response[5] << 8)  |  response[6];                    // 0.0
/*52  */             s->rspreg[3] = (response[0] << 16) | (response[1] << 8) |             // 0.0
/*54  */                             response[2];                                          // 0.0
/*56  */             DPRINT_L1("Response received:\n RSPREG[127..96]=0x%08x, RSPREG[95.."  // 0.0
/*58  */                   "64]=0x%08x,\n RSPREG[63..32]=0x%08x, RSPREG[31..0]=0x%08x\n",  // 0.0
/*60  */                   s->rspreg[3], s->rspreg[2], s->rspreg[1], s->rspreg[0]);        // 0.0
/*62  */         } else {                                                                  // 0.0
/*64  */             ERRPRINT("Timeout waiting for command response\n");                   // 0.0
/*66  */             if (s->errintstsen & SDHC_EISEN_CMDTIMEOUT) {                         // 0.0
/*68  */                 s->errintsts |= SDHC_EIS_CMDTIMEOUT;                              // 0.0
/*70  */                 s->norintsts |= SDHC_NIS_ERR;                                     // 0.0
/*72  */             }                                                                     // 0.0
/*74  */         }                                                                         // 0.0
/*78  */         if ((s->norintstsen & SDHC_NISEN_TRSCMP) &&                               // 0.0
/*80  */             (s->cmdreg & SDHC_CMD_RESPONSE) == SDHC_CMD_RSP_WITH_BUSY) {          // 0.0
/*82  */             s->norintsts |= SDHC_NIS_TRSCMP;                                      // 0.0
/*84  */         }                                                                         // 0.0
/*86  */     }                                                                             // 0.0
/*90  */     if (s->norintstsen & SDHC_NISEN_CMDCMP) {                                     // 0.0
/*92  */         s->norintsts |= SDHC_NIS_CMDCMP;                                          // 0.0
/*94  */     }                                                                             // 0.0
/*98  */     sdhci_update_irq(s);                                                          // 0.0
/*102 */     if (s->blksize && (s->cmdreg & SDHC_CMD_DATA_PRESENT)) {                      // 0.0
/*104 */         s->data_count = 0;                                                        // 0.0
/*106 */         sdhci_data_transfer(s);                                                   // 0.0
/*108 */     }                                                                             // 0.0
/*110 */ }                                                                                 // 0.0
