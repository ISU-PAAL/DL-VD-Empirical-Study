// commit message qemu@8be7e7e4c7 (target=1, prob=0.658776, correct=True): qemu-option: qemu_opts_create(): use error_set()
/*0  */ QemuOpts *qemu_opts_from_qdict(QemuOptsList *list, const QDict *qdict)  // (0) 0.2288
/*2  */ {                                                                       // (7) 0.006536
/*4  */     QemuOpts *opts;                                                     // (3) 0.07843
/*8  */     opts = qemu_opts_create(list, qdict_get_try_str(qdict, "id"), 1);   // (1) 0.2222
/*10 */     if (opts == NULL)                                                   // (4) 0.06536
/*12 */         return NULL;                                                    // (5) 0.06536
/*16 */     qdict_iter(qdict, qemu_opts_from_qdict_1, opts);                    // (2) 0.183
/*18 */     return opts;                                                        // (6) 0.04575
/*20 */ }                                                                       // (8) 0.006536
