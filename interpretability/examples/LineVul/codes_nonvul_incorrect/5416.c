// commit message FFmpeg@fc5a905a6d (target=0, prob=0.5612665, correct=False): ffserver: check chdir() return
/*0   */ static void start_children(FFStream *feed)                                       // (21) 0.02148
/*2   */ {                                                                                // (24) 0.001953
/*4   */     if (no_launch)                                                               // (22) 0.01758
/*6   */         return;                                                                  // (23) 0.01758
/*10  */     for (; feed; feed = feed->next) {                                            // (19) 0.0293
/*12  */         if (feed->child_argv && !feed->pid) {                                    // (6) 0.04297
/*14  */             feed->pid_start = time(0);                                           // (7) 0.04102
/*18  */             feed->pid = fork();                                                  // (17) 0.0332
/*22  */             if (feed->pid < 0) {                                                 // (10) 0.03906
/*24  */                 http_log("Unable to create children\n");                         // (1) 0.05273
/*26  */                 exit(1);                                                         // (14) 0.03711
/*28  */             }                                                                    // (20) 0.02344
/*30  */             if (!feed->pid) {                                                    // (15) 0.03516
/*32  */                 /* In child */                                                   // (13) 0.03711
/*34  */                 char pathname[1024];                                             // (8) 0.04102
/*36  */                 char *slash;                                                     // (11) 0.03906
/*38  */                 int i;                                                           // (16) 0.03516
/*42  */                 av_strlcpy(pathname, my_program_name, sizeof(pathname));         // (0) 0.06836
/*46  */                 slash = strrchr(pathname, '/');                                  // (2) 0.05273
/*48  */                 if (!slash)                                                      // (12) 0.03906
/*50  */                     slash = pathname;                                            // (5) 0.04688
/*52  */                 else                                                             // (18) 0.03125
/*54  */                     slash++;                                                     // (9) 0.04102
/*56  */                 strcpy(slash, "ffmpeg");                                         // (3) 0.05078
/*60  */                 http_log("Launch command line: ");                               // (4) 0.04883
/*62  */                 http_log("%s ", pathname);                                       // 0.0
/*64  */                 for (i = 1; feed->child_argv[i] && feed->child_argv[i][0]; i++)  // 0.0
/*66  */                     http_log("%s ", feed->child_argv[i]);                        // 0.0
/*68  */                 http_log("\n");                                                  // 0.0
/*72  */                 for (i = 3; i < 256; i++)                                        // 0.0
/*74  */                     close(i);                                                    // 0.0
/*78  */                 if (!ffserver_debug) {                                           // 0.0
/*80  */                     i = open("/dev/null", O_RDWR);                               // 0.0
/*82  */                     if (i != -1) {                                               // 0.0
/*84  */                         dup2(i, 0);                                              // 0.0
/*86  */                         dup2(i, 1);                                              // 0.0
/*88  */                         dup2(i, 2);                                              // 0.0
/*90  */                         close(i);                                                // 0.0
/*92  */                     }                                                            // 0.0
/*94  */                 }                                                                // 0.0
/*98  */                 /* This is needed to make relative pathnames work */             // 0.0
/*100 */                 chdir(my_program_dir);                                           // 0.0
/*104 */                 signal(SIGPIPE, SIG_DFL);                                        // 0.0
/*108 */                 execvp(pathname, feed->child_argv);                              // 0.0
/*112 */                 _exit(1);                                                        // 0.0
/*114 */             }                                                                    // 0.0
/*116 */         }                                                                        // 0.0
/*118 */     }                                                                            // 0.0
/*120 */ }                                                                                // 0.0
