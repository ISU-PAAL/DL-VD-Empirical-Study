// commit message qemu@dc8764f061 (target=1, prob=0.36874598, correct=False): qemu-ga: guest-suspend: make the API synchronous
/*0 */ static void child_handler(int sig)                            // (1) 0.1698
/*2 */ {                                                             // (3) 0.01887
/*4 */     int status;                                               // (2) 0.1132
/*6 */     while (waitpid(-1, &status, WNOHANG) > 0) /* NOTHING */;  // (0) 0.5094
/*8 */ }                                                             // (4) 0.01887
