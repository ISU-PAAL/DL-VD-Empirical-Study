// commit message qemu@9eca6cc643 (target=0, prob=0.11057759, correct=True): slirp: Remove unused code for bad sprintf
/*0  */ sprintf_len(char *string, const char *format, ...)  // (0) 0.1088
/*2  */ #else                                               // (12) 0.01361
/*4  */ sprintf_len(va_alist) va_dcl                        // (1) 0.08844
/*6  */ #endif                                              // (13) 0.01361
/*8  */ {                                                   // (16) 0.006803
/*10 */ 	va_list args;                                      // (9) 0.04082
/*12 */ #ifdef __STDC__                                     // (6) 0.04762
/*14 */ 	va_start(args, format);                            // (5) 0.06122
/*16 */ #else                                               // (14) 0.01361
/*18 */ 	char *string;                                      // (10) 0.03401
/*20 */ 	char *format;                                      // (11) 0.03401
/*22 */ 	va_start(args);                                    // (7) 0.04762
/*24 */ 	string = va_arg(args, char *);                     // (2) 0.08163
/*26 */ 	format = va_arg(args, char *);                     // (3) 0.08163
/*28 */ #endif                                              // (15) 0.01361
/*30 */ 	vsprintf(string, format, args);                    // (4) 0.06803
/*32 */ 	return strlen(string);                             // (8) 0.04762
/*34 */ }                                                   // (17) 0.006803
