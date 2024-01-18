// commit message qemu@7e2515e87c (target=0, prob=0.101757705, correct=True): separated readline from monitor code - added password input support - added output buffer
/*0   */ static void term_handle_byte(int ch)                            // (21) 0.02148
/*2   */ {                                                               // (35) 0.001953
/*4   */     switch(term_esc_state) {                                    // (20) 0.02344
/*6   */     case IS_NORM:                                               // (31) 0.01758
/*8   */         switch(ch) {                                            // (19) 0.02344
/*10  */         case 1:                                                 // (23) 0.01953
/*12  */             term_bol();                                         // (11) 0.0293
/*14  */             break;                                              // (12) 0.02539
/*16  */         case 4:                                                 // (24) 0.01953
/*18  */             term_delete_char();                                 // (6) 0.0332
/*20  */             break;                                              // (13) 0.02539
/*22  */         case 5:                                                 // (25) 0.01953
/*24  */             term_eol();                                         // (7) 0.03125
/*26  */             break;                                              // (14) 0.02539
/*28  */         case 9:                                                 // (26) 0.01953
/*30  */             term_completion();                                  // (9) 0.03125
/*32  */             break;                                              // (15) 0.02539
/*34  */         case 10:                                                // (22) 0.01953
/*36  */         case 13:                                                // (27) 0.01953
/*38  */             term_cmd_buf[term_cmd_buf_size] = '\0';             // (0) 0.05859
/*40  */ 	    term_hist_add(term_cmd_buf);                               // (10) 0.03125
/*42  */             term_printf("\n");                                  // (5) 0.03516
/*44  */             term_handle_command(term_cmd_buf);                  // (1) 0.04492
/*46  */             term_show_prompt();                                 // (4) 0.03516
/*48  */             break;                                              // (16) 0.02539
/*50  */         case 27:                                                // (28) 0.01953
/*52  */             term_esc_state = IS_ESC;                            // (2) 0.04297
/*54  */             break;                                              // (17) 0.02539
/*56  */         case 127:                                               // (29) 0.01953
/*58  */         case 8:                                                 // (30) 0.01953
/*60  */             term_backspace();                                   // (8) 0.03125
/*62  */             break;                                              // (18) 0.02539
/*64  */ 	case 155:                                                      // (34) 0.007812
/*66  */             term_esc_state = IS_CSI;                            // (3) 0.04297
/*68  */ 	    break;                                                     // (33) 0.01172
/*70  */         default:                                                // (32) 0.01758
/*72  */             if (ch >= 32) {                                     // 0.0
/*74  */                 term_insert_char(ch);                           // 0.0
/*76  */             }                                                   // 0.0
/*78  */             break;                                              // 0.0
/*80  */         }                                                       // 0.0
/*82  */         break;                                                  // 0.0
/*84  */     case IS_ESC:                                                // 0.0
/*86  */         if (ch == '[') {                                        // 0.0
/*88  */             term_esc_state = IS_CSI;                            // 0.0
/*90  */             term_esc_param = 0;                                 // 0.0
/*92  */         } else {                                                // 0.0
/*94  */             term_esc_state = IS_NORM;                           // 0.0
/*96  */         }                                                       // 0.0
/*98  */         break;                                                  // 0.0
/*100 */     case IS_CSI:                                                // 0.0
/*102 */         switch(ch) {                                            // 0.0
/*104 */ 	case 'A':                                                      // 0.0
/*106 */ 	case 'F':                                                      // 0.0
/*108 */ 	    term_up_char();                                            // 0.0
/*110 */ 	    break;                                                     // 0.0
/*112 */ 	case 'B':                                                      // 0.0
/*114 */ 	case 'E':                                                      // 0.0
/*116 */ 	    term_down_char();                                          // 0.0
/*118 */ 	    break;                                                     // 0.0
/*120 */         case 'D':                                               // 0.0
/*122 */             term_backward_char();                               // 0.0
/*124 */             break;                                              // 0.0
/*126 */         case 'C':                                               // 0.0
/*128 */             term_forward_char();                                // 0.0
/*130 */             break;                                              // 0.0
/*132 */         case '0' ... '9':                                       // 0.0
/*134 */             term_esc_param = term_esc_param * 10 + (ch - '0');  // 0.0
/*136 */             goto the_end;                                       // 0.0
/*138 */         case '~':                                               // 0.0
/*140 */             switch(term_esc_param) {                            // 0.0
/*142 */             case 1:                                             // 0.0
/*144 */                 term_bol();                                     // 0.0
/*146 */                 break;                                          // 0.0
/*148 */             case 3:                                             // 0.0
/*150 */                 term_delete_char();                             // 0.0
/*152 */                 break;                                          // 0.0
/*154 */             case 4:                                             // 0.0
/*156 */                 term_eol();                                     // 0.0
/*158 */                 break;                                          // 0.0
/*160 */             }                                                   // 0.0
/*162 */             break;                                              // 0.0
/*164 */         default:                                                // 0.0
/*166 */             break;                                              // 0.0
/*168 */         }                                                       // 0.0
/*170 */         term_esc_state = IS_NORM;                               // 0.0
/*172 */     the_end:                                                    // 0.0
/*174 */         break;                                                  // 0.0
/*176 */     }                                                           // 0.0
/*178 */     term_update();                                              // 0.0
/*180 */ }                                                               // 0.0
