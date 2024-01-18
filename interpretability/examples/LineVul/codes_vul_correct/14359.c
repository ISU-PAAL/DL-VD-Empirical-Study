// commit message FFmpeg@7da9f45231 (target=1, prob=0.8906235, correct=True): cinepakenc: fixes and improvements
/*0  */ static int write_cvid_header(CinepakEncContext *s, unsigned char *buf, int num_strips, int data_size)  // (0) 0.2292
/*2  */ {                                                                                                      // (7) 0.006944
/*4  */     buf[0] = 0;                                                                                        // (6) 0.06944
/*6  */     AV_WB24(&buf[1], data_size + CVID_HEADER_SIZE);                                                    // (1) 0.1667
/*8  */     AV_WB16(&buf[4], s->w);                                                                            // (3) 0.1111
/*10 */     AV_WB16(&buf[6], s->h);                                                                            // (4) 0.1111
/*12 */     AV_WB16(&buf[8], num_strips);                                                                      // (2) 0.1181
/*16 */     return CVID_HEADER_SIZE;                                                                           // (5) 0.08333
/*18 */ }                                                                                                      // (8) 0.006944
