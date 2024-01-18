// commit message qemu@8ba2aae32c (target=0, prob=0.014549855, correct=True): vdi: don't override libuuid symbols
/*0  */ void uuid_unparse(const uuid_t uu, char *out)                               // (2) 0.1332
/*2  */ {                                                                           // (5) 0.006716
/*4  */     snprintf(out, 37, UUID_FMT,                                             // (3) 0.1087
/*6  */             uu[0], uu[1], uu[2], uu[3], uu[4], uu[5], uu[6], uu[7],         // (1) 0.3348
/*8  */             uu[8], uu[9], uu[10], uu[11], uu[12], uu[13], uu[14], uu[15]);  // (0) 0.335
/*10 */ }                                                                           // (4) 0.00677
