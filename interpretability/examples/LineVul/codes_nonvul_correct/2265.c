// commit message qemu@dfd100f242 (target=0, prob=0.33035678, correct=True): sockets: Rename SocketAddress to SocketAddressLegacy
/*0   */ static gboolean ga_channel_open(GAChannel *c, const gchar *path,                  // (9) 0.04102
/*2   */                                 GAChannelMethod method, int fd)                   // (0) 0.07813
/*4   */ {                                                                                 // (27) 0.001953
/*6   */     int ret;                                                                      // (24) 0.01172
/*8   */     c->method = method;                                                           // (21) 0.01758
/*12  */     switch (c->method) {                                                          // (18) 0.01953
/*14  */     case GA_CHANNEL_VIRTIO_SERIAL: {                                              // (10) 0.03516
/*16  */         assert(fd < 0);                                                           // (16) 0.02539
/*18  */         fd = qemu_open(path, O_RDWR | O_NONBLOCK                                  // (3) 0.05664
/*20  */ #ifndef CONFIG_SOLARIS                                                            // (19) 0.01953
/*22  */                            | O_ASYNC                                              // (2) 0.06055
/*24  */ #endif                                                                            // (26) 0.003906
/*26  */                            );                                                     // (6) 0.05273
/*28  */         if (fd == -1) {                                                           // (11) 0.0293
/*30  */             g_critical("error opening channel: %s", strerror(errno));             // (4) 0.05664
/*32  */             return false;                                                         // (14) 0.02734
/*34  */         }                                                                         // (22) 0.01562
/*36  */ #ifdef CONFIG_SOLARIS                                                             // (20) 0.01758
/*38  */         ret = ioctl(fd, I_SETSIG, S_OUTPUT | S_INPUT | S_HIPRI);                  // (1) 0.07227
/*40  */         if (ret == -1) {                                                          // (12) 0.0293
/*42  */             g_critical("error setting event mask for channel: %s",                // (7) 0.04883
/*44  */                        strerror(errno));                                          // (5) 0.05664
/*46  */             close(fd);                                                            // (13) 0.0293
/*48  */             return false;                                                         // (15) 0.02734
/*50  */         }                                                                         // (23) 0.01562
/*52  */ #endif                                                                            // (25) 0.003906
/*54  */         ret = ga_channel_client_add(c, fd);                                       // (8) 0.04297
/*56  */         if (ret) {                                                                // (17) 0.02344
/*58  */             g_critical("error adding channel to main loop");                      // 0.0
/*60  */             close(fd);                                                            // 0.0
/*62  */             return false;                                                         // 0.0
/*64  */         }                                                                         // 0.0
/*66  */         break;                                                                    // 0.0
/*68  */     }                                                                             // 0.0
/*70  */     case GA_CHANNEL_ISA_SERIAL: {                                                 // 0.0
/*72  */         struct termios tio;                                                       // 0.0
/*76  */         assert(fd < 0);                                                           // 0.0
/*78  */         fd = qemu_open(path, O_RDWR | O_NOCTTY | O_NONBLOCK);                     // 0.0
/*80  */         if (fd == -1) {                                                           // 0.0
/*82  */             g_critical("error opening channel: %s", strerror(errno));             // 0.0
/*84  */             return false;                                                         // 0.0
/*86  */         }                                                                         // 0.0
/*88  */         tcgetattr(fd, &tio);                                                      // 0.0
/*90  */         /* set up serial port for non-canonical, dumb byte streaming */           // 0.0
/*92  */         tio.c_iflag &= ~(IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP |     // 0.0
/*94  */                          INLCR | IGNCR | ICRNL | IXON | IXOFF | IXANY |           // 0.0
/*96  */                          IMAXBEL);                                                // 0.0
/*98  */         tio.c_oflag = 0;                                                          // 0.0
/*100 */         tio.c_lflag = 0;                                                          // 0.0
/*102 */         tio.c_cflag |= GA_CHANNEL_BAUDRATE_DEFAULT;                               // 0.0
/*104 */         /* 1 available byte min or reads will block (we'll set non-blocking       // 0.0
/*106 */          * elsewhere, else we have to deal with read()=0 instead)                 // 0.0
/*108 */          */                                                                       // 0.0
/*110 */         tio.c_cc[VMIN] = 1;                                                       // 0.0
/*112 */         tio.c_cc[VTIME] = 0;                                                      // 0.0
/*114 */         /* flush everything waiting for read/xmit, it's garbage at this point */  // 0.0
/*116 */         tcflush(fd, TCIFLUSH);                                                    // 0.0
/*118 */         tcsetattr(fd, TCSANOW, &tio);                                             // 0.0
/*120 */         ret = ga_channel_client_add(c, fd);                                       // 0.0
/*122 */         if (ret) {                                                                // 0.0
/*124 */             g_critical("error adding channel to main loop");                      // 0.0
/*126 */             close(fd);                                                            // 0.0
/*128 */             return false;                                                         // 0.0
/*130 */         }                                                                         // 0.0
/*132 */         break;                                                                    // 0.0
/*134 */     }                                                                             // 0.0
/*136 */     case GA_CHANNEL_UNIX_LISTEN: {                                                // 0.0
/*138 */         if (fd < 0) {                                                             // 0.0
/*140 */             Error *local_err = NULL;                                              // 0.0
/*144 */             fd = unix_listen(path, NULL, strlen(path), &local_err);               // 0.0
/*146 */             if (local_err != NULL) {                                              // 0.0
/*148 */                 g_critical("%s", error_get_pretty(local_err));                    // 0.0
/*150 */                 error_free(local_err);                                            // 0.0
/*152 */                 return false;                                                     // 0.0
/*154 */             }                                                                     // 0.0
/*156 */         }                                                                         // 0.0
/*158 */         ga_channel_listen_add(c, fd, true);                                       // 0.0
/*160 */         break;                                                                    // 0.0
/*162 */     }                                                                             // 0.0
/*164 */     case GA_CHANNEL_VSOCK_LISTEN: {                                               // 0.0
/*166 */         if (fd < 0) {                                                             // 0.0
/*168 */             Error *local_err = NULL;                                              // 0.0
/*170 */             SocketAddress *addr;                                                  // 0.0
/*172 */             char *addr_str;                                                       // 0.0
/*176 */             addr_str = g_strdup_printf("vsock:%s", path);                         // 0.0
/*178 */             addr = socket_parse(addr_str, &local_err);                            // 0.0
/*180 */             g_free(addr_str);                                                     // 0.0
/*182 */             if (local_err != NULL) {                                              // 0.0
/*184 */                 g_critical("%s", error_get_pretty(local_err));                    // 0.0
/*186 */                 error_free(local_err);                                            // 0.0
/*188 */                 return false;                                                     // 0.0
/*190 */             }                                                                     // 0.0
/*194 */             fd = socket_listen(addr, &local_err);                                 // 0.0
/*196 */             qapi_free_SocketAddress(addr);                                        // 0.0
/*198 */             if (local_err != NULL) {                                              // 0.0
/*200 */                 g_critical("%s", error_get_pretty(local_err));                    // 0.0
/*202 */                 error_free(local_err);                                            // 0.0
/*204 */                 return false;                                                     // 0.0
/*206 */             }                                                                     // 0.0
/*208 */         }                                                                         // 0.0
/*210 */         ga_channel_listen_add(c, fd, true);                                       // 0.0
/*212 */         break;                                                                    // 0.0
/*214 */     }                                                                             // 0.0
/*216 */     default:                                                                      // 0.0
/*218 */         g_critical("error binding/listening to specified socket");                // 0.0
/*220 */         return false;                                                             // 0.0
/*222 */     }                                                                             // 0.0
/*226 */     return true;                                                                  // 0.0
/*228 */ }                                                                                 // 0.0
