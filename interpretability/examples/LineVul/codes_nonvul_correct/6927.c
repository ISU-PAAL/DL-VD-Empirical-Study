// commit message qemu@362786f14a (target=0, prob=0.07580919, correct=True): net: check packet payload length
/*0  */ void net_checksum_calculate(uint8_t *data, int length)                  // (5) 0.05464
/*2  */ {                                                                       // (25) 0.002732
/*4  */     int hlen, plen, proto, csum_offset;                                 // (9) 0.04645
/*6  */     uint16_t csum;                                                      // (12) 0.02732
/*10 */     if ((data[14] & 0xf0) != 0x40)                                      // (8) 0.05191
/*12 */ 	return; /* not IPv4 */                                                 // (16) 0.02186
/*14 */     hlen  = (data[14] & 0x0f) * 4;                                      // (4) 0.05738
/*16 */     plen  = (data[16] << 8 | data[17]) - hlen;                          // (2) 0.06284
/*18 */     proto = data[23];                                                   // (14) 0.02459
/*22 */     switch (proto) {                                                    // (15) 0.02459
/*24 */     case PROTO_TCP:                                                     // (13) 0.02732
/*26 */ 	csum_offset = 16;                                                      // (17) 0.02186
/*28 */ 	break;                                                                 // (23) 0.008197
/*30 */     case PROTO_UDP:                                                     // (11) 0.02732
/*32 */ 	csum_offset = 6;                                                       // (18) 0.02186
/*34 */ 	break;                                                                 // (24) 0.008197
/*36 */     default:                                                            // (19) 0.01366
/*38 */ 	return;                                                                // (21) 0.008197
/*40 */     }                                                                   // (20) 0.01093
/*44 */     if (plen < csum_offset+2)                                           // (10) 0.04098
/*46 */ 	return;                                                                // (22) 0.008197
/*50 */     data[14+hlen+csum_offset]   = 0;                                    // (6) 0.05464
/*52 */     data[14+hlen+csum_offset+1] = 0;                                    // (7) 0.05464
/*54 */     csum = net_checksum_tcpudp(plen, proto, data+14+12, data+14+hlen);  // (0) 0.0929
/*56 */     data[14+hlen+csum_offset]   = csum >> 8;                            // (3) 0.06284
/*58 */     data[14+hlen+csum_offset+1] = csum & 0xff;                          // (1) 0.06557
/*60 */ }                                                                       // (26) 0.002732
