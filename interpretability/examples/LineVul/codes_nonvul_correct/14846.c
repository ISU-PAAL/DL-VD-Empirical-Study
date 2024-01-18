// commit message qemu@541dc0d47f (target=0, prob=0.19426322, correct=True): Use new macro QEMU_PACKED for packed structures
/*0   */ static void cmd_get_event_status_notification(IDEState *s,                      // (3) 0.04124
/*2   */                                               uint8_t *buf)                     // (1) 0.07497
/*4   */ {                                                                               // (28) 0.003782
/*6   */     const uint8_t *packet = buf;                                                // (5) 0.03339
/*10  */     struct {                                                                    // (25) 0.01068
/*12  */         uint8_t opcode;                                                         // (0) 0.2227
/*14  */         uint8_t polled;        /* lsb bit is polled; others are reserved */     // (2) 0.05254
/*16  */         uint8_t reserved2[2];                                                   // (18) 0.02188
/*18  */         uint8_t class;                                                          // (4) 0.03529
/*20  */         uint8_t reserved3[2];                                                   // (19) 0.02151
/*22  */         uint16_t len;                                                           // (24) 0.01751
/*24  */         uint8_t control;                                                        // (22) 0.01797
/*26  */     } __attribute__((packed)) *gesn_cdb;                                        // (15) 0.02478
/*30  */     struct {                                                                    // (26) 0.007693
/*32  */         uint16_t len;                                                           // (23) 0.0177
/*34  */         uint8_t notification_class;                                             // (11) 0.02576
/*36  */         uint8_t supported_events;                                               // (21) 0.02087
/*38  */     } __attribute((packed)) *gesn_event_header;                                 // (6) 0.02744
/*42  */     enum notification_class_request_type {                                      // (20) 0.02119
/*44  */         NCR_RESERVED1 = 1 << 0,                                                 // (14) 0.02509
/*46  */         NCR_OPERATIONAL_CHANGE = 1 << 1,                                        // (12) 0.02574
/*48  */         NCR_POWER_MANAGEMENT = 1 << 2,                                          // (8) 0.02675
/*50  */         NCR_EXTERNAL_REQUEST = 1 << 3,                                          // (9) 0.0267
/*52  */         NCR_MEDIA = 1 << 4,                                                     // (17) 0.0221
/*54  */         NCR_MULTI_HOST = 1 << 5,                                                // (7) 0.02725
/*56  */         NCR_DEVICE_BUSY = 1 << 6,                                               // (10) 0.026
/*58  */         NCR_RESERVED2 = 1 << 7,                                                 // (13) 0.02517
/*60  */     };                                                                          // (27) 0.005366
/*62  */     enum event_notification_class_field {                                       // (16) 0.02318
/*64  */         ENC_NO_EVENTS = 0,                                                      // 0.0
/*66  */         ENC_OPERATIONAL_CHANGE,                                                 // 0.0
/*68  */         ENC_POWER_MANAGEMENT,                                                   // 0.0
/*70  */         ENC_EXTERNAL_REQUEST,                                                   // 0.0
/*72  */         ENC_MEDIA,                                                              // 0.0
/*74  */         ENC_MULTIPLE_HOSTS,                                                     // 0.0
/*76  */         ENC_DEVICE_BUSY,                                                        // 0.0
/*78  */         ENC_RESERVED,                                                           // 0.0
/*80  */     };                                                                          // 0.0
/*82  */     unsigned int max_len, used_len;                                             // 0.0
/*86  */     gesn_cdb = (void *)packet;                                                  // 0.0
/*88  */     gesn_event_header = (void *)buf;                                            // 0.0
/*92  */     max_len = be16_to_cpu(gesn_cdb->len);                                       // 0.0
/*96  */     /* It is fine by the MMC spec to not support async mode operations */       // 0.0
/*98  */     if (!(gesn_cdb->polled & 0x01)) { /* asynchronous mode */                   // 0.0
/*100 */         /* Only polling is supported, asynchronous mode is not. */              // 0.0
/*102 */         ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST,                           // 0.0
/*104 */                             ASC_INV_FIELD_IN_CMD_PACKET);                       // 0.0
/*106 */         return;                                                                 // 0.0
/*108 */     }                                                                           // 0.0
/*112 */     /* polling mode operation */                                                // 0.0
/*116 */     /*                                                                          // 0.0
/*118 */      * These are the supported events.                                          // 0.0
/*120 */      *                                                                          // 0.0
/*122 */      * We currently only support requests of the 'media' type.                  // 0.0
/*124 */      */                                                                         // 0.0
/*126 */     gesn_event_header->supported_events = NCR_MEDIA;                            // 0.0
/*130 */     /*                                                                          // 0.0
/*132 */      * We use |= below to set the class field; other bits in this byte          // 0.0
/*134 */      * are reserved now but this is useful to do if we have to use the          // 0.0
/*136 */      * reserved fields later.                                                   // 0.0
/*138 */      */                                                                         // 0.0
/*140 */     gesn_event_header->notification_class = 0;                                  // 0.0
/*144 */     /*                                                                          // 0.0
/*146 */      * Responses to requests are to be based on request priority.  The          // 0.0
/*148 */      * notification_class_request_type enum above specifies the                 // 0.0
/*150 */      * priority: upper elements are higher prio than lower ones.                // 0.0
/*152 */      */                                                                         // 0.0
/*154 */     if (gesn_cdb->class & NCR_MEDIA) {                                          // 0.0
/*156 */         gesn_event_header->notification_class |= ENC_MEDIA;                     // 0.0
/*158 */         used_len = event_status_media(s, buf);                                  // 0.0
/*160 */     } else {                                                                    // 0.0
/*162 */         gesn_event_header->notification_class = 0x80; /* No event available */  // 0.0
/*164 */         used_len = sizeof(*gesn_event_header);                                  // 0.0
/*166 */     }                                                                           // 0.0
/*168 */     gesn_event_header->len = cpu_to_be16(used_len                               // 0.0
/*170 */                                          - sizeof(*gesn_event_header));         // 0.0
/*172 */     ide_atapi_cmd_reply(s, used_len, max_len);                                  // 0.0
/*174 */ }                                                                               // 0.0
