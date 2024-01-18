// commit message qemu@72cf2d4f0e (target=0, prob=0.010445718, correct=True): Fix sys-queue.h conflict for good
/*0  */ int qemu_opt_set(QemuOpts *opts, const char *name, const char *value)        // (2) 0.05469
/*2  */ {                                                                            // (25) 0.001953
/*4  */     QemuOpt *opt;                                                            // (20) 0.01953
/*8  */     opt = qemu_opt_find(opts, name);                                         // (11) 0.03516
/*10 */     if (!opt) {                                                              // (22) 0.01562
/*12 */         QemuOptDesc *desc = opts->list->desc;                                // (7) 0.04297
/*14 */         int i;                                                               // (21) 0.01953
/*18 */         for (i = 0; desc[i].name != NULL; i++) {                             // (5) 0.04687
/*20 */             if (strcmp(desc[i].name, name) == 0) {                           // (3) 0.05469
/*22 */                 break;                                                       // (15) 0.0332
/*24 */             }                                                                // (18) 0.02344
/*26 */         }                                                                    // (23) 0.01562
/*28 */         if (desc[i].name == NULL) {                                          // (12) 0.03516
/*30 */             if (i == 0) {                                                    // (13) 0.03516
/*32 */                 /* empty list -> allow any */;                               // (6) 0.04492
/*34 */             } else {                                                         // (17) 0.02734
/*36 */                 fprintf(stderr, "option \"%s\" is not valid for %s\n",       // (0) 0.07227
/*38 */                         name, opts->list->name);                             // (1) 0.0625
/*40 */                 return -1;                                                   // (10) 0.03711
/*42 */             }                                                                // (19) 0.02344
/*44 */         }                                                                    // (24) 0.01562
/*46 */         opt = qemu_mallocz(sizeof(*opt));                                    // (8) 0.04297
/*48 */         opt->name = qemu_strdup(name);                                       // (9) 0.04102
/*50 */         opt->opts = opts;                                                    // (16) 0.0293
/*52 */         TAILQ_INSERT_TAIL(&opts->head, opt, next);                           // (4) 0.05078
/*54 */         if (desc[i].name != NULL) {                                          // (14) 0.03516
/*56 */             opt->desc = desc+i;                                              // 0.0
/*58 */         }                                                                    // 0.0
/*60 */     }                                                                        // 0.0
/*62 */     qemu_free((/* !const */ char*)opt->str);                                 // 0.0
/*64 */     opt->str = NULL;                                                         // 0.0
/*66 */     if (value) {                                                             // 0.0
/*68 */         opt->str = qemu_strdup(value);                                       // 0.0
/*70 */     }                                                                        // 0.0
/*72 */     if (qemu_opt_parse(opt) < 0) {                                           // 0.0
/*74 */         fprintf(stderr, "Failed to parse \"%s\" for \"%s.%s\"\n", opt->str,  // 0.0
/*76 */                 opts->list->name, opt->name);                                // 0.0
/*78 */         qemu_opt_del(opt);                                                   // 0.0
/*80 */         return -1;                                                           // 0.0
/*82 */     }                                                                        // 0.0
/*84 */     return 0;                                                                // 0.0
/*86 */ }                                                                            // 0.0
