// commit message qemu@7e2515e87c (target=0, prob=0.037982475, correct=True): separated readline from monitor code - added password input support - added output buffer
/*0  */ static void term_down_char(void)                                        // (5) 0.05747
/*2  */ {                                                                       // (10) 0.005747
/*4  */     if (term_hist_entry == TERM_MAX_CMDS - 1 || term_hist_entry == -1)  // (0) 0.1724
/*6  */ 	return;                                                                // (9) 0.01724
/*8  */     if (term_history[++term_hist_entry] != NULL) {                      // (3) 0.1149
/*10 */ 	pstrcpy(term_cmd_buf, sizeof(term_cmd_buf),                            // (4) 0.1149
/*12 */                 term_history[term_hist_entry]);                         // (2) 0.1437
/*14 */     } else {                                                            // (7) 0.03448
/*16 */ 	term_hist_entry = -1;                                                  // (6) 0.05747
/*18 */     }                                                                   // (8) 0.02299
/*20 */     term_cmd_buf_index = term_cmd_buf_size = strlen(term_cmd_buf);      // (1) 0.1609
/*22 */ }                                                                       // (11) 0.005747
