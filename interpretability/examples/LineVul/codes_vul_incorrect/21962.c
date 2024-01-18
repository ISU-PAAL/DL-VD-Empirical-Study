// commit message qemu@671f66f87f (target=1, prob=0.020645566, correct=False): net/filter: fix nf->netdev_id leak
/*0  */ static void netfilter_finalize(Object *obj)                   // (5) 0.07317
/*2  */ {                                                             // (9) 0.006098
/*4  */     NetFilterState *nf = NETFILTER(obj);                      // (3) 0.1037
/*6  */     NetFilterClass *nfc = NETFILTER_GET_CLASS(obj);           // (2) 0.128
/*10 */     if (nfc->cleanup) {                                       // (6) 0.07317
/*12 */         nfc->cleanup(nf);                                     // (4) 0.09756
/*14 */     }                                                         // (7) 0.02439
/*18 */     if (nf->netdev && !QTAILQ_EMPTY(&nf->netdev->filters)) {  // (0) 0.1829
/*20 */         QTAILQ_REMOVE(&nf->netdev->filters, nf, next);        // (1) 0.1829
/*22 */     }                                                         // (8) 0.02439
/*25 */ }                                                             // (10) 0.006098
