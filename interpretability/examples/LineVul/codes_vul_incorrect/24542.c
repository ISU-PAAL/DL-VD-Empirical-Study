// commit message FFmpeg@8bc80f8b24 (target=1, prob=0.43306452, correct=False): Minor bugfix to prevent segfault if a malloc fails. I have no idea what will happen, but at least this crash is gone.
/*0   */ static int http_server(void)                                                              // (29) 0.01563
/*2   */ {                                                                                         // (33) 0.001953
/*4   */     int server_fd, ret, rtsp_server_fd, delay, delay1;                                    // (2) 0.04492
/*6   */     struct pollfd poll_table[HTTP_MAX_CONNECTIONS + 2], *poll_entry;                      // (1) 0.04883
/*8   */     HTTPContext *c, *c_next;                                                              // (17) 0.02539
/*12  */     server_fd = socket_open_listen(&my_http_addr);                                        // (4) 0.03906
/*14  */     if (server_fd < 0)                                                                    // (25) 0.02148
/*16  */         return -1;                                                                        // (26) 0.02148
/*20  */     rtsp_server_fd = socket_open_listen(&my_rtsp_addr);                                   // (0) 0.05078
/*22  */     if (rtsp_server_fd < 0)                                                               // (12) 0.0293
/*24  */         return -1;                                                                        // (27) 0.02148
/*26  */                                                                                           // (32) 0.007812
/*28  */     http_log("ffserver started.\n");                                                      // (15) 0.02734
/*32  */     start_children(first_feed);                                                           // (18) 0.02148
/*36  */     first_http_ctx = NULL;                                                                // (19) 0.02148
/*38  */     nb_connections = 0;                                                                   // (22) 0.02148
/*40  */     first_http_ctx = NULL;                                                                // (21) 0.02148
/*44  */     start_multicast();                                                                    // (28) 0.01758
/*48  */     for(;;) {                                                                             // (30) 0.01562
/*50  */         poll_entry = poll_table;                                                          // (14) 0.0293
/*52  */         poll_entry->fd = server_fd;                                                       // (7) 0.0332
/*54  */         poll_entry->events = POLLIN;                                                      // (8) 0.0332
/*56  */         poll_entry++;                                                                     // (23) 0.02148
/*60  */         poll_entry->fd = rtsp_server_fd;                                                  // (3) 0.04102
/*62  */         poll_entry->events = POLLIN;                                                      // (9) 0.0332
/*64  */         poll_entry++;                                                                     // (24) 0.02148
/*68  */         /* wait for events on each HTTP handle */                                         // (10) 0.03125
/*70  */         c = first_http_ctx;                                                               // (11) 0.0293
/*72  */         delay = 1000;                                                                     // (20) 0.02148
/*74  */         while (c != NULL) {                                                               // (16) 0.02734
/*76  */             int fd;                                                                       // (13) 0.0293
/*78  */             fd = c->fd;                                                                   // (5) 0.03516
/*80  */             switch(c->state) {                                                            // (6) 0.03516
/*82  */             case HTTPSTATE_SEND_HEADER:                                                   // 0.0
/*84  */             case RTSPSTATE_SEND_REPLY:                                                    // 0.0
/*86  */             case RTSPSTATE_SEND_PACKET:                                                   // 0.0
/*88  */                 c->poll_entry = poll_entry;                                               // 0.0
/*90  */                 poll_entry->fd = fd;                                                      // 0.0
/*92  */                 poll_entry->events = POLLOUT;                                             // 0.0
/*94  */                 poll_entry++;                                                             // 0.0
/*96  */                 break;                                                                    // 0.0
/*98  */             case HTTPSTATE_SEND_DATA_HEADER:                                              // 0.0
/*100 */             case HTTPSTATE_SEND_DATA:                                                     // 0.0
/*102 */             case HTTPSTATE_SEND_DATA_TRAILER:                                             // 0.0
/*104 */                 if (!c->is_packetized) {                                                  // 0.0
/*106 */                     /* for TCP, we output as much as we can (may need to put a limit) */  // 0.0
/*108 */                     c->poll_entry = poll_entry;                                           // 0.0
/*110 */                     poll_entry->fd = fd;                                                  // 0.0
/*112 */                     poll_entry->events = POLLOUT;                                         // 0.0
/*114 */                     poll_entry++;                                                         // 0.0
/*116 */                 } else {                                                                  // 0.0
/*118 */                     /* not strictly correct, but currently cannot add                     // 0.0
/*120 */                        more than one fd in poll entry */                                  // 0.0
/*122 */                     delay = 0;                                                            // 0.0
/*124 */                 }                                                                         // 0.0
/*126 */                 break;                                                                    // 0.0
/*128 */             case HTTPSTATE_WAIT_REQUEST:                                                  // 0.0
/*130 */             case HTTPSTATE_RECEIVE_DATA:                                                  // 0.0
/*132 */             case HTTPSTATE_WAIT_FEED:                                                     // 0.0
/*134 */             case RTSPSTATE_WAIT_REQUEST:                                                  // 0.0
/*136 */                 /* need to catch errors */                                                // 0.0
/*138 */                 c->poll_entry = poll_entry;                                               // 0.0
/*140 */                 poll_entry->fd = fd;                                                      // 0.0
/*142 */                 poll_entry->events = POLLIN;/* Maybe this will work */                    // 0.0
/*144 */                 poll_entry++;                                                             // 0.0
/*146 */                 break;                                                                    // 0.0
/*148 */             case HTTPSTATE_WAIT:                                                          // 0.0
/*150 */                 c->poll_entry = NULL;                                                     // 0.0
/*152 */                 delay1 = compute_send_delay(c);                                           // 0.0
/*154 */                 if (delay1 < delay)                                                       // 0.0
/*156 */                     delay = delay1;                                                       // 0.0
/*158 */                 break;                                                                    // 0.0
/*160 */             case HTTPSTATE_WAIT_SHORT:                                                    // 0.0
/*162 */                 c->poll_entry = NULL;                                                     // 0.0
/*164 */                 delay1 = 10; /* one tick wait XXX: 10 ms assumed */                       // 0.0
/*166 */                 if (delay1 < delay)                                                       // 0.0
/*168 */                     delay = delay1;                                                       // 0.0
/*170 */                 break;                                                                    // 0.0
/*172 */             default:                                                                      // 0.0
/*174 */                 c->poll_entry = NULL;                                                     // 0.0
/*176 */                 break;                                                                    // 0.0
/*178 */             }                                                                             // 0.0
/*180 */             c = c->next;                                                                  // 0.0
/*182 */         }                                                                                 // 0.0
/*186 */         /* wait for an event on one connection. We poll at least every                    // 0.0
/*188 */            second to handle timeouts */                                                   // 0.0
/*190 */         do {                                                                              // 0.0
/*192 */             ret = poll(poll_table, poll_entry - poll_table, delay);                       // 0.0
/*194 */         } while (ret == -1);                                                              // 0.0
/*196 */                                                                                           // (31) 0.01562
/*198 */         cur_time = gettime_ms();                                                          // 0.0
/*202 */         if (need_to_start_children) {                                                     // 0.0
/*204 */             need_to_start_children = 0;                                                   // 0.0
/*206 */             start_children(first_feed);                                                   // 0.0
/*208 */         }                                                                                 // 0.0
/*212 */         /* now handle the events */                                                       // 0.0
/*214 */         for(c = first_http_ctx; c != NULL; c = c_next) {                                  // 0.0
/*216 */             c_next = c->next;                                                             // 0.0
/*218 */             if (handle_connection(c) < 0) {                                               // 0.0
/*220 */                 /* close and free the connection */                                       // 0.0
/*222 */                 log_connection(c);                                                        // 0.0
/*224 */                 close_connection(c);                                                      // 0.0
/*226 */             }                                                                             // 0.0
/*228 */         }                                                                                 // 0.0
/*232 */         poll_entry = poll_table;                                                          // 0.0
/*234 */         /* new HTTP connection request ? */                                               // 0.0
/*236 */         if (poll_entry->revents & POLLIN) {                                               // 0.0
/*238 */             new_connection(server_fd, 0);                                                 // 0.0
/*240 */         }                                                                                 // 0.0
/*242 */         poll_entry++;                                                                     // 0.0
/*244 */         /* new RTSP connection request ? */                                               // 0.0
/*246 */         if (poll_entry->revents & POLLIN) {                                               // 0.0
/*248 */             new_connection(rtsp_server_fd, 1);                                            // 0.0
/*250 */         }                                                                                 // 0.0
/*252 */     }                                                                                     // 0.0
/*254 */ }                                                                                         // 0.0
