// commit message qemu@72cf2d4f0e (target=0, prob=0.010610791, correct=True): Fix sys-queue.h conflict for good
/*0  */ int qemu_opts_print(QemuOpts *opts, void *dummy)             // (2) 0.1364
/*2  */ {                                                            // (9) 0.005682
/*4  */     QemuOpt *opt;                                            // (6) 0.05682
/*8  */     fprintf(stderr, "%s: %s:", opts->list->name,             // (3) 0.1364
/*10 */             opts->id ? opts->id : "<noid>");                 // (1) 0.1477
/*12 */     TAILQ_FOREACH(opt, &opts->head, next) {                  // (4) 0.1193
/*14 */         fprintf(stderr, " %s=\"%s\"", opt->name, opt->str);  // (0) 0.1705
/*16 */     }                                                        // (8) 0.02273
/*18 */     fprintf(stderr, "\n");                                   // (5) 0.07386
/*20 */     return 0;                                                // (7) 0.03409
/*22 */ }                                                            // (10) 0.005682
