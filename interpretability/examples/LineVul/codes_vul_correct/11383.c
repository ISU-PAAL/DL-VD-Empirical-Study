// commit message FFmpeg@3df2be9fa7 (target=1, prob=0.7612424, correct=True): matroskadec: ass events lines must end with a DOS style EOL
/*0  */ static void matroska_fix_ass_packet(MatroskaDemuxContext *matroska,               // (8) 0.04688
/*2  */                                     AVPacket *pkt, uint64_t display_duration)     // (0) 0.09766
/*4  */ {                                                                                 // (21) 0.001953
/*6  */     char *line, *layer, *ptr = pkt->data, *end = ptr+pkt->size;                   // (2) 0.05469
/*8  */     for (; *ptr!=',' && ptr<end-1; ptr++);                                        // (15) 0.04102
/*10 */     if (*ptr == ',')                                                              // (20) 0.01953
/*12 */         layer = ++ptr;                                                            // (18) 0.02344
/*14 */     for (; *ptr!=',' && ptr<end-1; ptr++);                                        // (14) 0.04102
/*16 */     if (*ptr == ',') {                                                            // (19) 0.02148
/*18 */         int64_t end_pts = pkt->pts + display_duration;                            // (5) 0.05078
/*20 */         int sc = matroska->time_scale * pkt->pts / 10000000;                      // (3) 0.05273
/*22 */         int ec = matroska->time_scale * end_pts  / 10000000;                      // (4) 0.05273
/*24 */         int sh, sm, ss, eh, em, es, len;                                          // (12) 0.04297
/*26 */         sh = sc/360000;  sc -= 360000*sh;                                         // (13) 0.04297
/*28 */         sm = sc/  6000;  sc -=   6000*sm;                                         // (9) 0.04492
/*30 */         ss = sc/   100;  sc -=    100*ss;                                         // (7) 0.04883
/*32 */         eh = ec/360000;  ec -= 360000*eh;                                         // (11) 0.04297
/*34 */         em = ec/  6000;  ec -=   6000*em;                                         // (10) 0.04492
/*36 */         es = ec/   100;  ec -=    100*es;                                         // (6) 0.04883
/*38 */         *ptr++ = '\0';                                                            // (17) 0.0293
/*40 */         len = 50 + end-ptr + FF_INPUT_BUFFER_PADDING_SIZE;                        // (1) 0.05664
/*42 */         if (!(line = av_malloc(len)))                                             // (16) 0.03711
/*44 */             return;                                                               // 0.0
/*46 */         snprintf(line,len,"Dialogue: %s,%d:%02d:%02d.%02d,%d:%02d:%02d.%02d,%s",  // 0.0
/*48 */                  layer, sh, sm, ss, sc, eh, em, es, ec, ptr);                     // 0.0
/*50 */         av_free(pkt->data);                                                       // 0.0
/*52 */         pkt->data = line;                                                         // 0.0
/*54 */         pkt->size = strlen(line);                                                 // 0.0
/*56 */     }                                                                             // 0.0
/*58 */ }                                                                                 // 0.0
