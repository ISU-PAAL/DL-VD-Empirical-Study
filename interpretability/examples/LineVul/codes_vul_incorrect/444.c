// commit message qemu@25d9747b64 (target=1, prob=0.08083442, correct=False): block/raw-posix: Don't think /dev/fd/<NN> is a floppy drive.
/*0  */ static int floppy_probe_device(const char *filename)     // (6) 0.04294
/*2  */ {                                                        // (25) 0.003067
/*4  */     int fd, ret;                                         // (15) 0.02761
/*6  */     int prio = 0;                                        // (16) 0.02761
/*8  */     struct floppy_struct fdparam;                        // (10) 0.03374
/*10 */     struct stat st;                                      // (18) 0.02147
/*14 */     if (strstart(filename, "/dev/fd", NULL) &&           // (4) 0.05521
/*16 */         !strstart(filename, "/dev/fdset/", NULL)) {      // (2) 0.07055
/*18 */         prio = 50;                                       // (8) 0.03681
/*20 */     }                                                    // (20) 0.01227
/*24 */     fd = qemu_open(filename, O_RDONLY | O_NONBLOCK);     // (0) 0.08282
/*26 */     if (fd < 0) {                                        // (13) 0.03067
/*28 */         goto out;                                        // (14) 0.03067
/*30 */     }                                                    // (21) 0.01227
/*32 */     ret = fstat(fd, &st);                                // (7) 0.03988
/*34 */     if (ret == -1 || !S_ISBLK(st.st_mode)) {             // (1) 0.07362
/*36 */         goto outc;                                       // (12) 0.03374
/*38 */     }                                                    // (22) 0.01227
/*42 */     /* Attempt to detect via a floppy specific ioctl */  // (5) 0.04294
/*44 */     ret = ioctl(fd, FDGETPRM, &fdparam);                 // (3) 0.05828
/*46 */     if (ret >= 0)                                        // (17) 0.02761
/*48 */         prio = 100;                                      // (9) 0.03681
/*52 */ outc:                                                    // (23) 0.009202
/*54 */     qemu_close(fd);                                      // (11) 0.03374
/*56 */ out:                                                     // (24) 0.006135
/*58 */     return prio;                                         // (19) 0.02147
/*60 */ }                                                        // (26) 0.003067
