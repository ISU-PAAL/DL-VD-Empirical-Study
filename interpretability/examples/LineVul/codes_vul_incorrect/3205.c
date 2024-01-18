// commit message qemu@95ce326e5b (target=1, prob=0.14730166, correct=False): buffer overflow fix - printf format fix
/*0  */ static void term_down_char(void)                                        // (5) 0.0565
/*2  */ {                                                                       // (11) 0.00565
/*4  */     if (term_hist_entry == TERM_MAX_CMDS - 1 || term_hist_entry == -1)  // (0) 0.1695
/*6  */ 	return;                                                                // (10) 0.01695
/*8  */     if (term_history[++term_hist_entry] != NULL) {                      // (3) 0.113
/*10 */ 	strcpy(term_cmd_buf, term_history[term_hist_entry]);                   // (2) 0.1186
/*12 */     } else {                                                            // (8) 0.0339
/*14 */ 	term_hist_entry = -1;                                                  // (6) 0.0565
/*16 */     }                                                                   // (9) 0.0226
/*18 */     term_printf("\n");                                                  // (7) 0.0565
/*20 */     term_print_cmdline(term_cmd_buf);                                   // (4) 0.0904
/*22 */     term_cmd_buf_index = term_cmd_buf_size = strlen(term_cmd_buf);      // (1) 0.1582
/*24 */ }                                                                       // (12) 0.00565
