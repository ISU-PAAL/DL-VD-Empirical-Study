// commit message qemu@4be746345f (target=0, prob=0.23636666, correct=True): hw: Convert from BlockDriverState to BlockBackend, mostly
/*0   */ void ide_atapi_cmd(IDEState *s)                                                   // (14) 0.02539
/*2   */ {                                                                                 // (32) 0.001953
/*4   */     uint8_t *buf;                                                                 // (18) 0.01953
/*8   */     buf = s->io_buffer;                                                           // (17) 0.02148
/*10  */ #ifdef DEBUG_IDE_ATAPI                                                            // (21) 0.01758
/*12  */     {                                                                             // (29) 0.007812
/*14  */         int i;                                                                    // (19) 0.01953
/*16  */         printf("ATAPI limit=0x%x packet:", s->lcyl | (s->hcyl << 8));             // (0) 0.06445
/*18  */         for(i = 0; i < ATAPI_PACKET_SIZE; i++) {                                  // (3) 0.05273
/*20  */             printf(" %02x", buf[i]);                                              // (7) 0.04102
/*22  */         }                                                                         // (23) 0.01562
/*24  */         printf("\n");                                                             // (15) 0.02344
/*26  */     }                                                                             // (26) 0.007813
/*28  */ #endif                                                                            // (31) 0.003906
/*30  */     /*                                                                            // (27) 0.007813
/*32  */      * If there's a UNIT_ATTENTION condition pending, only command flagged with   // (6) 0.04102
/*34  */      * ALLOW_UA are allowed to complete. with other commands getting a CHECK      // (5) 0.04102
/*36  */      * condition response unless a higher priority status, defined by the drive   // (11) 0.0332
/*38  */      * here, is pending.                                                          // (20) 0.01953
/*40  */      */                                                                           // (25) 0.009766
/*42  */     if (s->sense_key == UNIT_ATTENTION &&                                         // (12) 0.0332
/*44  */         !(atapi_cmd_table[s->io_buffer[0]].flags & ALLOW_UA)) {                   // (1) 0.06445
/*46  */         ide_atapi_cmd_check_status(s);                                            // (8) 0.03906
/*48  */         return;                                                                   // (22) 0.01758
/*50  */     }                                                                             // (30) 0.007812
/*52  */     /*                                                                            // (28) 0.007813
/*54  */      * When a CD gets changed, we have to report an ejected state and             // (9) 0.03711
/*56  */      * then a loaded state to guests so that they detect tray                     // (13) 0.03125
/*58  */      * open/close and media change events.  Guests that do not use                // (10) 0.03711
/*60  */      * GET_EVENT_STATUS_NOTIFICATION to detect such tray open/close               // (4) 0.04492
/*62  */      * states rely on this behavior.                                              // (16) 0.02148
/*64  */      */                                                                           // (24) 0.009766
/*66  */     if (!(atapi_cmd_table[s->io_buffer[0]].flags & ALLOW_UA) &&                   // (2) 0.05859
/*68  */         !s->tray_open && bdrv_is_inserted(s->bs) && s->cdrom_changed) {           // 0.0
/*72  */         if (s->cdrom_changed == 1) {                                              // 0.0
/*74  */             ide_atapi_cmd_error(s, NOT_READY, ASC_MEDIUM_NOT_PRESENT);            // 0.0
/*76  */             s->cdrom_changed = 2;                                                 // 0.0
/*78  */         } else {                                                                  // 0.0
/*80  */             ide_atapi_cmd_error(s, UNIT_ATTENTION, ASC_MEDIUM_MAY_HAVE_CHANGED);  // 0.0
/*82  */             s->cdrom_changed = 0;                                                 // 0.0
/*84  */         }                                                                         // 0.0
/*88  */         return;                                                                   // 0.0
/*90  */     }                                                                             // 0.0
/*94  */     /* Report a Not Ready condition if appropriate for the command */             // 0.0
/*96  */     if ((atapi_cmd_table[s->io_buffer[0]].flags & CHECK_READY) &&                 // 0.0
/*98  */         (!media_present(s) || !bdrv_is_inserted(s->bs)))                          // 0.0
/*100 */     {                                                                             // 0.0
/*102 */         ide_atapi_cmd_error(s, NOT_READY, ASC_MEDIUM_NOT_PRESENT);                // 0.0
/*104 */         return;                                                                   // 0.0
/*106 */     }                                                                             // 0.0
/*110 */     /* Execute the command */                                                     // 0.0
/*112 */     if (atapi_cmd_table[s->io_buffer[0]].handler) {                               // 0.0
/*114 */         atapi_cmd_table[s->io_buffer[0]].handler(s, buf);                         // 0.0
/*116 */         return;                                                                   // 0.0
/*118 */     }                                                                             // 0.0
/*122 */     ide_atapi_cmd_error(s, ILLEGAL_REQUEST, ASC_ILLEGAL_OPCODE);                  // 0.0
/*124 */ }                                                                                 // 0.0
