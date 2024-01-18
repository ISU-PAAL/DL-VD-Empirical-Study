// commit message qemu@ba7806ad92 (target=1, prob=0.91907763, correct=True): cmd: Fix potential NULL pointer dereference
/*0  */ void add_command(const cmdinfo_t *ci)                             // (3) 0.1529
/*2  */ {                                                                 // (4) 0.01176
/*4  */     cmdtab = realloc((void *)cmdtab, ++ncmds * sizeof(*cmdtab));  // (0) 0.2824
/*6  */     cmdtab[ncmds - 1] = *ci;                                      // (2) 0.1882
/*8  */     qsort(cmdtab, ncmds, sizeof(*cmdtab), compare);               // (1) 0.2353
/*10 */ }                                                                 // (5) 0.01176
