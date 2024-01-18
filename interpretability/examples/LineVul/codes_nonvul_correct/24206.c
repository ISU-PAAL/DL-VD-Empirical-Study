// commit message qemu@4be746345f (target=0, prob=0.21834499, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0   */ uint8_t sd_read_data(SDState *sd)                                      // (16) 0.0293
/*2   */ {                                                                      // (27) 0.001953
/*4   */     /* TODO: Append CRCs */                                            // (18) 0.02344
/*6   */     uint8_t ret;                                                       // (22) 0.01758
/*8   */     int io_len;                                                        // (25) 0.01562
/*12  */     if (!sd->bdrv || !bdrv_is_inserted(sd->bdrv) || !sd->enable)       // (0) 0.06445
/*14  */         return 0x00;                                                   // (19) 0.02344
/*18  */     if (sd->state != sd_sendingdata_state) {                           // (12) 0.03516
/*20  */         fprintf(stderr, "sd_read_data: not in Sending-Data state\n");  // (1) 0.05859
/*22  */         return 0x00;                                                   // (20) 0.02344
/*24  */     }                                                                  // (26) 0.007812
/*28  */     if (sd->card_status & (ADDRESS_ERROR | WP_VIOLATION))              // (4) 0.04688
/*30  */         return 0x00;                                                   // (21) 0.02344
/*34  */     io_len = (sd->ocr & (1 << 30)) ? 512 : sd->blk_len;                // (2) 0.05273
/*38  */     switch (sd->current_cmd) {                                         // (17) 0.02344
/*40  */     case 6:	/* CMD6:   SWITCH_FUNCTION */                              // (6) 0.04102
/*42  */         ret = sd->data[sd->data_offset ++];                            // (9) 0.03906
/*46  */         if (sd->data_offset >= 64)                                     // (14) 0.0332
/*48  */             sd->state = sd_transfer_state;                             // (7) 0.04102
/*50  */         break;                                                         // (23) 0.01758
/*54  */     case 9:	/* CMD9:   SEND_CSD */                                     // (10) 0.03906
/*56  */     case 10:	/* CMD10:  SEND_CID */                                    // (11) 0.03711
/*58  */         ret = sd->data[sd->data_offset ++];                            // (8) 0.03906
/*62  */         if (sd->data_offset >= 16)                                     // (15) 0.0332
/*64  */             sd->state = sd_transfer_state;                             // (5) 0.04102
/*66  */         break;                                                         // (24) 0.01758
/*70  */     case 11:	/* CMD11:  READ_DAT_UNTIL_STOP */                         // (3) 0.04883
/*72  */         if (sd->data_offset == 0)                                      // (13) 0.0332
/*74  */             BLK_READ_BLOCK(sd->data_start, io_len);                    // 0.0
/*76  */         ret = sd->data[sd->data_offset ++];                            // 0.0
/*80  */         if (sd->data_offset >= io_len) {                               // 0.0
/*82  */             sd->data_start += io_len;                                  // 0.0
/*84  */             sd->data_offset = 0;                                       // 0.0
/*86  */             if (sd->data_start + io_len > sd->size) {                  // 0.0
/*88  */                 sd->card_status |= ADDRESS_ERROR;                      // 0.0
/*90  */                 break;                                                 // 0.0
/*92  */             }                                                          // 0.0
/*94  */         }                                                              // 0.0
/*96  */         break;                                                         // 0.0
/*100 */     case 13:	/* ACMD13: SD_STATUS */                                   // 0.0
/*102 */         ret = sd->sd_status[sd->data_offset ++];                       // 0.0
/*106 */         if (sd->data_offset >= sizeof(sd->sd_status))                  // 0.0
/*108 */             sd->state = sd_transfer_state;                             // 0.0
/*110 */         break;                                                         // 0.0
/*114 */     case 17:	/* CMD17:  READ_SINGLE_BLOCK */                           // 0.0
/*116 */         if (sd->data_offset == 0)                                      // 0.0
/*118 */             BLK_READ_BLOCK(sd->data_start, io_len);                    // 0.0
/*120 */         ret = sd->data[sd->data_offset ++];                            // 0.0
/*124 */         if (sd->data_offset >= io_len)                                 // 0.0
/*126 */             sd->state = sd_transfer_state;                             // 0.0
/*128 */         break;                                                         // 0.0
/*132 */     case 18:	/* CMD18:  READ_MULTIPLE_BLOCK */                         // 0.0
/*134 */         if (sd->data_offset == 0)                                      // 0.0
/*136 */             BLK_READ_BLOCK(sd->data_start, io_len);                    // 0.0
/*138 */         ret = sd->data[sd->data_offset ++];                            // 0.0
/*142 */         if (sd->data_offset >= io_len) {                               // 0.0
/*144 */             sd->data_start += io_len;                                  // 0.0
/*146 */             sd->data_offset = 0;                                       // 0.0
/*148 */             if (sd->data_start + io_len > sd->size) {                  // 0.0
/*150 */                 sd->card_status |= ADDRESS_ERROR;                      // 0.0
/*152 */                 break;                                                 // 0.0
/*154 */             }                                                          // 0.0
/*156 */         }                                                              // 0.0
/*158 */         break;                                                         // 0.0
/*162 */     case 22:	/* ACMD22: SEND_NUM_WR_BLOCKS */                          // 0.0
/*164 */         ret = sd->data[sd->data_offset ++];                            // 0.0
/*168 */         if (sd->data_offset >= 4)                                      // 0.0
/*170 */             sd->state = sd_transfer_state;                             // 0.0
/*172 */         break;                                                         // 0.0
/*176 */     case 30:	/* CMD30:  SEND_WRITE_PROT */                             // 0.0
/*178 */         ret = sd->data[sd->data_offset ++];                            // 0.0
/*182 */         if (sd->data_offset >= 4)                                      // 0.0
/*184 */             sd->state = sd_transfer_state;                             // 0.0
/*186 */         break;                                                         // 0.0
/*190 */     case 51:	/* ACMD51: SEND_SCR */                                    // 0.0
/*192 */         ret = sd->scr[sd->data_offset ++];                             // 0.0
/*196 */         if (sd->data_offset >= sizeof(sd->scr))                        // 0.0
/*198 */             sd->state = sd_transfer_state;                             // 0.0
/*200 */         break;                                                         // 0.0
/*204 */     case 56:	/* CMD56:  GEN_CMD */                                     // 0.0
/*206 */         if (sd->data_offset == 0)                                      // 0.0
/*208 */             APP_READ_BLOCK(sd->data_start, sd->blk_len);               // 0.0
/*210 */         ret = sd->data[sd->data_offset ++];                            // 0.0
/*214 */         if (sd->data_offset >= sd->blk_len)                            // 0.0
/*216 */             sd->state = sd_transfer_state;                             // 0.0
/*218 */         break;                                                         // 0.0
/*222 */     default:                                                           // 0.0
/*224 */         fprintf(stderr, "sd_read_data: unknown command\n");            // 0.0
/*226 */         return 0x00;                                                   // 0.0
/*228 */     }                                                                  // 0.0
/*232 */     return ret;                                                        // 0.0
/*234 */ }                                                                      // 0.0
