// commit message FFmpeg@0de1319ee0 (target=0, prob=0.5293691, correct=False): avserver: check return value of ftruncate()
/*0  */ static int http_start_receive_data(HTTPContext *c)                                        // (9) 0.03125
/*2  */ {                                                                                         // (28) 0.001953
/*4  */     int fd;                                                                               // (24) 0.01367
/*8  */     if (c->stream->feed_opened)                                                           // (13) 0.02539
/*10 */         return -1;                                                                        // (18) 0.02148
/*14 */     /* Don't permit writing to this one */                                                // (15) 0.02344
/*16 */     if (c->stream->readonly)                                                              // (16) 0.02344
/*18 */         return -1;                                                                        // (19) 0.02148
/*22 */     /* open feed */                                                                       // (23) 0.01367
/*24 */     fd = open(c->stream->feed_filename, O_RDWR);                                          // (8) 0.04102
/*26 */     if (fd < 0) {                                                                         // (21) 0.01953
/*28 */         http_log("Error opening feeder file: %s\n", strerror(errno));                     // (5) 0.05664
/*30 */         return -1;                                                                        // (20) 0.02148
/*32 */     }                                                                                     // (26) 0.007812
/*34 */     c->feed_fd = fd;                                                                      // (17) 0.02344
/*38 */     if (c->stream->truncate) {                                                            // (12) 0.02734
/*40 */         /* truncate feed file */                                                          // (14) 0.02539
/*42 */         ffm_write_write_index(c->feed_fd, FFM_PACKET_SIZE);                               // (4) 0.06055
/*44 */         ftruncate(c->feed_fd, FFM_PACKET_SIZE);                                           // (6) 0.05273
/*46 */         http_log("Truncating feed file '%s'\n", c->stream->feed_filename);                // (3) 0.06055
/*48 */     } else {                                                                              // (25) 0.01172
/*50 */         if ((c->stream->feed_write_index = ffm_read_write_index(fd)) < 0) {               // (2) 0.06641
/*52 */             http_log("Error reading write index from feed file: %s\n", strerror(errno));  // (1) 0.06836
/*54 */             return -1;                                                                    // (11) 0.0293
/*56 */         }                                                                                 // (22) 0.01562
/*58 */     }                                                                                     // (27) 0.007812
/*62 */     c->stream->feed_write_index = FFMAX(ffm_read_write_index(fd), FFM_PACKET_SIZE);       // (0) 0.07031
/*64 */     c->stream->feed_size = lseek(fd, 0, SEEK_END);                                        // (7) 0.04492
/*66 */     lseek(fd, 0, SEEK_SET);                                                               // (10) 0.0293
/*70 */     /* init buffer input */                                                               // 0.0
/*72 */     c->buffer_ptr = c->buffer;                                                            // 0.0
/*74 */     c->buffer_end = c->buffer + FFM_PACKET_SIZE;                                          // 0.0
/*76 */     c->stream->feed_opened = 1;                                                           // 0.0
/*78 */     c->chunked_encoding = !!av_stristr(c->buffer, "Transfer-Encoding: chunked");          // 0.0
/*80 */     return 0;                                                                             // 0.0
/*82 */ }                                                                                         // 0.0
