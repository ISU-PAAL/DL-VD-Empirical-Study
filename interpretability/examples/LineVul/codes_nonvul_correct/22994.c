// commit message qemu@43c5d8f800 (target=0, prob=0.29810393, correct=True): block: Don't add trailing space in "Formating..." message
/*0  */ void qemu_opts_print(QemuOpts *opts)                                 // (10) 0.04017
/*2  */ {                                                                    // (25) 0.002114
/*4  */     QemuOpt *opt;                                                    // (17) 0.02114
/*6  */     QemuOptDesc *desc = opts->list->desc;                            // (11) 0.03805
/*10 */     if (desc[0].name == NULL) {                                      // (13) 0.0296
/*12 */         QTAILQ_FOREACH(opt, &opts->head, next) {                     // (4) 0.05497
/*14 */             printf("%s=\"%s\" ", opt->name, opt->str);               // (3) 0.0592
/*16 */         }                                                            // (20) 0.01691
/*18 */         return;                                                      // (19) 0.01903
/*20 */     }                                                                // (23) 0.008457
/*22 */     for (; desc && desc->name; desc++) {                             // (12) 0.03171
/*24 */         const char *value;                                           // (15) 0.02537
/*26 */         QemuOpt *opt = qemu_opt_find(opts, desc->name);              // (2) 0.06131
/*30 */         value = opt ? opt->str : desc->def_value_str;                // (9) 0.04863
/*32 */         if (!value) {                                                // (16) 0.02537
/*34 */             continue;                                                // (14) 0.02748
/*36 */         }                                                            // (21) 0.01691
/*38 */         if (desc->type == QEMU_OPT_STRING) {                         // (7) 0.05074
/*40 */             printf("%s='%s' ", desc->name, value);                   // (5) 0.05497
/*42 */         } else if ((desc->type == QEMU_OPT_SIZE ||                   // (8) 0.05074
/*44 */                     desc->type == QEMU_OPT_NUMBER) && opt) {         // (0) 0.07822
/*46 */             printf("%s=%" PRId64 " ", desc->name, opt->value.uint);  // (1) 0.06765
/*48 */         } else {                                                     // (18) 0.02114
/*50 */             printf("%s=%s ", desc->name, value);                     // (6) 0.05285
/*52 */         }                                                            // (22) 0.01691
/*54 */     }                                                                // (24) 0.008457
/*56 */ }                                                                    // (26) 0.002114
