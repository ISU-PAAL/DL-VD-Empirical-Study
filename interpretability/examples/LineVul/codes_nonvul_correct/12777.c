// commit message qemu@f2001a7e05 (target=0, prob=0.009571506, correct=True): char: don't assume telnet initialization will not block
/*0  */ static void tcp_chr_telnet_init(QIOChannel *ioc)                                       // (5) 0.07364
/*2  */ {                                                                                      // (11) 0.003876
/*4  */     char buf[3];                                                                       // (10) 0.03101
/*6  */     /* Send the telnet negotion to put telnet in binary, no echo, single char mode */  // (4) 0.09302
/*8  */     IACSET(buf, 0xff, 0xfb, 0x01);  /* IAC WILL ECHO */                                // (1) 0.1085
/*10 */     qio_channel_write(ioc, buf, 3, NULL);                                              // (6) 0.07364
/*12 */     IACSET(buf, 0xff, 0xfb, 0x03);  /* IAC WILL Suppress go ahead */                   // (0) 0.1163
/*14 */     qio_channel_write(ioc, buf, 3, NULL);                                              // (7) 0.07364
/*16 */     IACSET(buf, 0xff, 0xfb, 0x00);  /* IAC WILL Binary */                              // (2) 0.1047
/*18 */     qio_channel_write(ioc, buf, 3, NULL);                                              // (8) 0.07364
/*20 */     IACSET(buf, 0xff, 0xfd, 0x00);  /* IAC DO Binary */                                // (3) 0.1047
/*22 */     qio_channel_write(ioc, buf, 3, NULL);                                              // (9) 0.07364
/*24 */ }                                                                                      // (12) 0.003876
