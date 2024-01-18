// commit message qemu@60fe637bf0 (target=1, prob=0.8333314, correct=True): Start migrating migration code into a migration directory
/*0  */ static void control_to_network(RDMAControlHeader *control)  // (0) 0.2297
/*2  */ {                                                           // (4) 0.01351
/*4  */     control->type = htonl(control->type);                   // (2) 0.2027
/*6  */     control->len = htonl(control->len);                     // (3) 0.2027
/*8  */     control->repeat = htonl(control->repeat);               // (1) 0.2027
/*10 */ }                                                           // (5) 0.01351
