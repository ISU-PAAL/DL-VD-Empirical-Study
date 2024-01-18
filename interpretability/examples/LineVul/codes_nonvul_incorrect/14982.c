// commit message qemu@190563f9a9 (target=0, prob=0.9783146, correct=False): net: fix usbnet_receive() packet drops
/*0  */ static int rndis_parse(USBNetState *s, uint8_t *data, int length)               // (8) 0.04752
/*2  */ {                                                                               // (24) 0.00198
/*4  */     uint32_t msg_type;                                                          // (20) 0.02178
/*6  */     le32 *tmp = (le32 *) data;                                                  // (14) 0.02772
/*10 */     msg_type = le32_to_cpup(tmp);                                               // (11) 0.03366
/*14 */     switch (msg_type) {                                                         // (21) 0.0198
/*16 */     case RNDIS_INITIALIZE_MSG:                                                  // (12) 0.03168
/*18 */         s->rndis_state = RNDIS_INITIALIZED;                                     // (7) 0.0495
/*20 */         return rndis_init_response(s, (rndis_init_msg_type *) data);            // (3) 0.06139
/*24 */     case RNDIS_HALT_MSG:                                                        // (15) 0.02772
/*26 */         s->rndis_state = RNDIS_UNINITIALIZED;                                   // (6) 0.05149
/*28 */         return 0;                                                               // (22) 0.0198
/*32 */     case RNDIS_QUERY_MSG:                                                       // (16) 0.02772
/*34 */         return rndis_query_response(s, (rndis_query_msg_type *) data, length);  // (1) 0.06535
/*38 */     case RNDIS_SET_MSG:                                                         // (18) 0.02574
/*40 */         return rndis_set_response(s, (rndis_set_msg_type *) data, length);      // (2) 0.06535
/*44 */     case RNDIS_RESET_MSG:                                                       // (17) 0.02772
/*46 */         rndis_clear_responsequeue(s);                                           // (10) 0.03564
/*48 */         s->out_ptr = s->in_ptr = s->in_len = 0;                                 // (5) 0.05347
/*50 */         return rndis_reset_response(s, (rndis_reset_msg_type *) data);          // (4) 0.06139
/*54 */     case RNDIS_KEEPALIVE_MSG:                                                   // (13) 0.03168
/*56 */         /* For USB: host does this every 5 seconds */                           // (9) 0.03564
/*58 */         return rndis_keepalive_response(s, (rndis_keepalive_msg_type *) data);  // (0) 0.06931
/*60 */     }                                                                           // (23) 0.007921
/*64 */     return USB_RET_STALL;                                                       // (19) 0.02178
/*66 */ }                                                                               // (25) 0.00198
