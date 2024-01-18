// commit message qemu@db3b3c7281 (target=1, prob=0.99898165, correct=True): 9pfs: deprecate handle backend
/*0  */ static int handle_parse_opts(QemuOpts *opts, FsDriverEntry *fse, Error **errp)           // (0) 0.1498
/*1  */ {                                                                                        // (13) 0.004831
/*2  */     const char *sec_model = qemu_opt_get(opts, "security_model");                        // (1) 0.1256
/*3  */     const char *path = qemu_opt_get(opts, "path");                                       // (3) 0.1063
/*4  */     if (sec_model) {                                                                     // (8) 0.04831
/*5  */         error_report("Invalid argument security_model specified with handle fsdriver");  // (2) 0.1063
/*6  */         return -1;                                                                       // (6) 0.05314
/*7  */     }                                                                                    // (11) 0.01932
/*8  */     if (!path) {                                                                         // (9) 0.03865
/*9  */         error_report("fsdev: No path specified");                                        // (4) 0.08696
/*10 */         return -1;                                                                       // (7) 0.05314
/*11 */     }                                                                                    // (12) 0.01932
/*12 */     fse->path = g_strdup(path);                                                          // (5) 0.07729
/*13 */     return 0;                                                                            // (10) 0.02899
/*14 */ }                                                                                        // (14) 0.004831
