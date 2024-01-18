// commit message FFmpeg@04dcdc4640 (target=1, prob=0.63062257, correct=True): lavc/avfft: init context to 0.
/*0  */ FFTContext *av_fft_init(int nbits, int inverse)  // (2) 0.1935
/*2  */ {                                                // (5) 0.01075
/*4  */     FFTContext *s = av_malloc(sizeof(*s));       // (1) 0.2043
/*8  */     if (s && ff_fft_init(s, nbits, inverse))     // (0) 0.2258
/*10 */         av_freep(&s);                            // (3) 0.1505
/*14 */     return s;                                    // (4) 0.06452
/*16 */ }                                                // (6) 0.01075
