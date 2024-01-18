// commit message qemu@788cf9f8c8 (target=1, prob=0.008373538, correct=False): block: rip out all traces of password prompting
/*0  */ static void hmp_cont_cb(void *opaque, int err)  // (0) 0.3091
/*2  */ {                                               // (4) 0.01818
/*4  */     if (!err) {                                 // (2) 0.1455
/*6  */         qmp_cont(NULL);                         // (1) 0.2545
/*8  */     }                                           // (3) 0.07273
/*10 */ }                                               // (5) 0.01818
