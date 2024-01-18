// commit message qemu@926cde5f3e (target=0, prob=0.5935402, correct=False): scsi: esp: make cmdbuf big enough for maximum CDB size
/*0  */ static void handle_ti(ESPState *s)                               // (20) 0.02344
/*2  */ {                                                                // (30) 0.001953
/*4  */     uint32_t dmalen, minlen;                                     // (14) 0.02734
/*8  */     if (s->dma && !s->dma_enabled) {                             // (8) 0.03711
/*10 */         s->dma_cb = handle_ti;                                   // (9) 0.03516
/*12 */         return;                                                  // (25) 0.01758
/*14 */     }                                                            // (26) 0.007813
/*18 */     dmalen = s->rregs[ESP_TCLO];                                 // (7) 0.03711
/*20 */     dmalen |= s->rregs[ESP_TCMID] << 8;                          // (3) 0.04688
/*22 */     dmalen |= s->rregs[ESP_TCHI] << 16;                          // (4) 0.04688
/*24 */     if (dmalen==0) {                                             // (21) 0.02344
/*26 */       dmalen=0x10000;                                            // (19) 0.02539
/*28 */     }                                                            // (27) 0.007812
/*30 */     s->dma_counter = dmalen;                                     // (15) 0.02734
/*34 */     if (s->do_cmd)                                               // (23) 0.02148
/*36 */         minlen = (dmalen < 32) ? dmalen : 32;                    // (5) 0.04688
/*38 */     else if (s->ti_size < 0)                                     // (16) 0.02734
/*40 */         minlen = (dmalen < -s->ti_size) ? dmalen : -s->ti_size;  // (0) 0.06641
/*42 */     else                                                         // (28) 0.007812
/*44 */         minlen = (dmalen < s->ti_size) ? dmalen : s->ti_size;    // (1) 0.0625
/*46 */     trace_esp_handle_ti(minlen);                                 // (17) 0.02734
/*48 */     if (s->dma) {                                                // (24) 0.02148
/*50 */         s->dma_left = minlen;                                    // (10) 0.0332
/*52 */         s->rregs[ESP_RSTAT] &= ~STAT_TC;                         // (2) 0.05078
/*54 */         esp_do_dma(s);                                           // (11) 0.03125
/*56 */     }                                                            // (29) 0.007812
/*58 */     if (s->do_cmd) {                                             // (22) 0.02344
/*60 */         trace_esp_handle_ti_cmd(s->cmdlen);                      // (6) 0.04297
/*62 */         s->ti_size = 0;                                          // (12) 0.0293
/*64 */         s->cmdlen = 0;                                           // (18) 0.02734
/*66 */         s->do_cmd = 0;                                           // (13) 0.0293
/*68 */         do_cmd(s, s->cmdbuf);                                    // 0.0
/*70 */     }                                                            // 0.0
/*72 */ }                                                                // 0.0
