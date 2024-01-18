// commit message qemu@660edd4eda (target=1, prob=0.9991321, correct=True): virtio-9p-proxy: Fix sockfd leak
/*0  */ static int connect_namedsocket(const char *path)                  // (7) 0.04332
/*2  */ {                                                                 // (18) 0.00361
/*4  */     int sockfd, size;                                             // (13) 0.03249
/*6  */     struct sockaddr_un helper;                                    // (12) 0.0361
/*10 */     sockfd = socket(AF_UNIX, SOCK_STREAM, 0);                     // (3) 0.07581
/*12 */     if (sockfd < 0) {                                             // (8) 0.04332
/*14 */         fprintf(stderr, "socket %s\n", strerror(errno));          // (0) 0.1011
/*16 */         return -1;                                                // (10) 0.03971
/*18 */     }                                                             // (16) 0.01444
/*20 */     strcpy(helper.sun_path, path);                                // (5) 0.05776
/*22 */     helper.sun_family = AF_UNIX;                                  // (6) 0.05054
/*24 */     size = strlen(helper.sun_path) + sizeof(helper.sun_family);   // (2) 0.09025
/*26 */     if (connect(sockfd, (struct sockaddr *)&helper, size) < 0) {  // (1) 0.09386
/*28 */         fprintf(stderr, "socket error\n");                        // (4) 0.0722
/*31 */         return -1;                                                // (11) 0.03971
/*33 */     }                                                             // (17) 0.01444
/*37 */     /* remove the socket for security reasons */                  // (9) 0.03971
/*39 */     unlink(path);                                                 // (14) 0.02888
/*41 */     return sockfd;                                                // (15) 0.02527
/*43 */ }                                                                 // (19) 0.00361
