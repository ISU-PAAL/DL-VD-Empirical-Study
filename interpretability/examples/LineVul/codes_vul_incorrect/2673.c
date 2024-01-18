// commit message qemu@615220ddaf (target=1, prob=0.18508288, correct=False): ui/curses: Fix monitor color with -curses when 256 colors
/*0  */ static void curses_setup(void)                                        // (10) 0.03306
/*2  */ {                                                                     // (12) 0.004132
/*4  */     int i, colour_default[8] = {                                      // (8) 0.05785
/*6  */         COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,             // (1) 0.1281
/*8  */         COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE,          // (0) 0.1322
/*10 */     };                                                                // (11) 0.01653
/*14 */     /* input as raw as possible, let everything be interpreted        // (7) 0.05785
/*16 */      * by the guest system */                                         // (9) 0.04132
/*18 */     initscr(); noecho(); intrflush(stdscr, FALSE);                    // (4) 0.07851
/*20 */     nodelay(stdscr, TRUE); nonl(); keypad(stdscr, TRUE);              // (3) 0.1033
/*22 */     start_color(); raw(); scrollok(stdscr, FALSE);                    // (5) 0.07438
/*26 */     for (i = 0; i < 64; i ++)                                         // (6) 0.06612
/*28 */         init_pair(i, colour_default[i & 7], colour_default[i >> 3]);  // (2) 0.1198
/*30 */ }                                                                     // (13) 0.004132
