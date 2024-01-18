// commit message qemu@9be385980d (target=0, prob=0.66478354, correct=False): coccinelle: Remove unnecessary variables for function return value
/*0  */ static uint64_t megasas_fw_time(void)                     // (7) 0.06122
/*2  */ {                                                         // (11) 0.004082
/*4  */     struct tm curtime;                                    // (9) 0.03673
/*6  */     uint64_t bcd_time;                                    // (8) 0.04898
/*10 */     qemu_get_timedate(&curtime, 0);                       // (6) 0.07347
/*12 */     bcd_time = ((uint64_t)curtime.tm_sec & 0xff) << 48 |  // (0) 0.1102
/*14 */         ((uint64_t)curtime.tm_min & 0xff)  << 40 |        // (1) 0.1102
/*16 */         ((uint64_t)curtime.tm_hour & 0xff) << 32 |        // (5) 0.1061
/*18 */         ((uint64_t)curtime.tm_mday & 0xff) << 24 |        // (2) 0.1102
/*20 */         ((uint64_t)curtime.tm_mon & 0xff)  << 16 |        // (3) 0.1102
/*22 */         ((uint64_t)(curtime.tm_year + 1900) & 0xffff);    // (4) 0.1102
/*26 */     return bcd_time;                                      // (10) 0.03673
/*28 */ }                                                         // (12) 0.004082
