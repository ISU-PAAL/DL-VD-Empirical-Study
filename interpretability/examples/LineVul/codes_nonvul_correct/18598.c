// commit message qemu@22156ab498 (target=0, prob=0.020348174, correct=True): net: Remove unused net-checksum.c file
/*0  */ uint16_t net_checksum_tcpudp(uint16_t length, uint16_t proto,           // (3) 0.1268
/*2  */                              uint8_t *addrs, uint8_t *buf)              // (0) 0.2098
/*4  */ {                                                                       // (7) 0.004878
/*6  */     uint32_t sum = 0;                                                   // (6) 0.05366
/*10 */     sum += net_checksum_add(length, buf);         // payload            // (4) 0.1268
/*12 */     sum += net_checksum_add(8, addrs);            // src + dst address  // (2) 0.161
/*14 */     sum += proto + length;                        // protocol & length  // (1) 0.1756
/*16 */     return net_checksum_finish(sum);                                    // (5) 0.06829
/*18 */ }                                                                       // (8) 0.004878
