// commit message qemu@22156ab498 (target=0, prob=0.009233432, correct=True): net: Remove unused net-checksum.c file
/*0  */ uint16_t net_checksum_finish(uint32_t sum)  // (0) 0.2951
/*2  */ {                                           // (4) 0.01639
/*4  */     while (sum>>16)                         // (2) 0.1475
/*6  */ 	sum = (sum & 0xFFFF)+(sum >> 16);          // (1) 0.2459
/*8  */     return ~sum;                            // (3) 0.1148
/*10 */ }                                           // (5) 0.01639
