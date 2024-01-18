// commit message qemu@6c1fef6b59 (target=1, prob=0.58894956, correct=True): esp: check dma length before reading scsi command(CVE-2016-4441)
/*0  */ static void handle_satn(ESPState *s)  // (3) 0.0963
/*2  */ {                                     // (10) 0.007407
/*4  */     uint8_t buf[32];                  // (5) 0.08148
/*6  */     int len;                          // (8) 0.04444
/*10 */     if (s->dma && !s->dma_enabled) {  // (1) 0.1407
/*12 */         s->dma_cb = handle_satn;      // (0) 0.1407
/*14 */         return;                       // (6) 0.06667
/*16 */     }                                 // (9) 0.02963
/*18 */     len = get_cmd(s, buf);            // (4) 0.0963
/*20 */     if (len)                          // (7) 0.05185
/*22 */         do_cmd(s, buf);               // (2) 0.1111
/*24 */ }                                     // (11) 0.007407
