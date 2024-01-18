// commit message qemu@c60bf3391b (target=0, prob=0.10008331, correct=True): readline: decouple readline from the monitor
/*0  */ void readline_show_prompt(ReadLineState *rs)    // (1) 0.1456
/*2  */ {                                               // (6) 0.009709
/*4  */     monitor_printf(rs->mon, "%s", rs->prompt);  // (0) 0.1845
/*6  */     monitor_flush(rs->mon);                     // (5) 0.1068
/*8  */     rs->last_cmd_buf_index = 0;                 // (2) 0.1456
/*10 */     rs->last_cmd_buf_size = 0;                  // (3) 0.1456
/*12 */     rs->esc_state = IS_NORM;                    // (4) 0.1359
/*14 */ }                                               // (7) 0.009709
