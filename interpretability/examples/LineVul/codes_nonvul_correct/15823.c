// commit message qemu@2e6a64cb8d (target=0, prob=0.060690984, correct=True): input-linux: better capability checks, merge input_linux_event_{mouse, keyboard}
/*0  */ static void input_linux_event_mouse(void *opaque)                              // (7) 0.05119
/*2  */ {                                                                              // (16) 0.003413
/*4  */     InputLinux *il = opaque;                                                   // (10) 0.03413
/*6  */     struct input_event event;                                                  // (11) 0.03072
/*8  */     int rc;                                                                    // (14) 0.02048
/*12 */     for (;;) {                                                                 // (12) 0.0273
/*14 */         rc = read(il->fd, &event, sizeof(event));                              // (3) 0.07509
/*16 */         if (rc != sizeof(event)) {                                             // (6) 0.05461
/*18 */             if (rc < 0 && errno != EAGAIN) {                                   // (2) 0.08532
/*20 */                 fprintf(stderr, "%s: read: %s\n", __func__, strerror(errno));  // (0) 0.1468
/*22 */                 qemu_set_fd_handler(il->fd, NULL, NULL, NULL);                 // (1) 0.1195
/*24 */                 close(il->fd);                                                 // (4) 0.07167
/*26 */             }                                                                  // (9) 0.04096
/*28 */             break;                                                             // (8) 0.04437
/*30 */         }                                                                      // (13) 0.0273
/*34 */         input_linux_handle_mouse(il, &event);                                  // (5) 0.06826
/*36 */     }                                                                          // (15) 0.01365
/*38 */ }                                                                              // (17) 0.003413
