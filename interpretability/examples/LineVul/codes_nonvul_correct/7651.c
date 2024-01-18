// commit message FFmpeg@4b1f5e5090 (target=0, prob=0.12308052, correct=True): cosmetics: Write NULL pointer inequality checks more compactly
/*0  */ void av_register_output_format(AVOutputFormat *format)  // (2) 0.1705
/*2  */ {                                                       // (6) 0.01136
/*4  */     AVOutputFormat **p = &first_oformat;                // (1) 0.1705
/*8  */     while (*p != NULL)                                  // (4) 0.1023
/*10 */         p = &(*p)->next;                                // (0) 0.1818
/*14 */     *p = format;                                        // (5) 0.09091
/*16 */     format->next = NULL;                                // (3) 0.1023
/*18 */ }                                                       // (7) 0.01136
