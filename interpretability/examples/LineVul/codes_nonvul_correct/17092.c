// commit message qemu@4a19f1eced (target=0, prob=0.14540471, correct=True): Add --with-pkgversion. Allows distributors to identify their builds without needing to hack the sources.
/*0 */ static void do_info_version(Monitor *mon)       // (1) 0.2857
/*2 */ {                                               // (2) 0.02381
/*4 */     monitor_printf(mon, "%s\n", QEMU_VERSION);  // (0) 0.4762
/*6 */ }                                               // (3) 0.02381
