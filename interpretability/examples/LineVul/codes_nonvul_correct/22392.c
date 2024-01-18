// commit message FFmpeg@e16e49ac90 (target=0, prob=0.3381287, correct=True): Proper check for interactive support (termios and conio).
/*0  */ static void term_exit(void)           // (2) 0.1538
/*2  */ {                                     // (4) 0.01923
/*4  */ #ifndef __MINGW32__                   // (1) 0.1923
/*6  */     tcsetattr (0, TCSANOW, &oldtty);  // (0) 0.3462
/*8  */ #endif                                // (3) 0.03846
/*10 */ }                                     // (5) 0.01923
