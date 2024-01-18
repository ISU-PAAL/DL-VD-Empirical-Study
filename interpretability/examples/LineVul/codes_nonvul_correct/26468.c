// commit message qemu@5f1d1fc592 (target=0, prob=0.27890477, correct=True): spapr_vio: Pair g_malloc() with g_free(), not free()
/*0  */ int spapr_populate_vdevice(VIOsPAPRBus *bus, void *fdt)                    // (1) 0.05702
/*2  */ {                                                                          // (30) 0.002193
/*4  */     DeviceState *qdev, **qdevs;                                            // (11) 0.0307
/*6  */     BusChild *kid;                                                         // (19) 0.01754
/*8  */     int i, num, ret = 0;                                                   // (15) 0.02632
/*12 */     /* Count qdevs on the bus list */                                      // (14) 0.02851
/*14 */     num = 0;                                                               // (22) 0.01535
/*16 */     QTAILQ_FOREACH(kid, &bus->bus.children, sibling) {                     // (2) 0.05044
/*18 */         num++;                                                             // (17) 0.01974
/*20 */     }                                                                      // (26) 0.008772
/*24 */     /* Copy out into an array of pointers */                               // (16) 0.02632
/*26 */     qdevs = g_malloc(sizeof(qdev) * num);                                  // (5) 0.04605
/*28 */     num = 0;                                                               // (23) 0.01535
/*30 */     QTAILQ_FOREACH(kid, &bus->bus.children, sibling) {                     // (3) 0.05044
/*32 */         qdevs[num++] = kid->child;                                         // (9) 0.04167
/*34 */     }                                                                      // (27) 0.008772
/*38 */     /* Sort the array */                                                   // (20) 0.01754
/*40 */     qsort(qdevs, num, sizeof(qdev), compare_reg);                          // (6) 0.04605
/*44 */     /* Hack alert. Give the devices to libfdt in reverse order, we happen  // (7) 0.04386
/*46 */      * to know that will mean they are in forward order in the tree. */    // (8) 0.04386
/*48 */     for (i = num - 1; i >= 0; i--) {                                       // (10) 0.04167
/*50 */         VIOsPAPRDevice *dev = (VIOsPAPRDevice *)(qdevs[i]);                // (0) 0.07237
/*54 */         ret = vio_make_devnode(dev, fdt);                                  // (4) 0.04825
/*58 */         if (ret < 0) {                                                     // (12) 0.0307
/*60 */             goto out;                                                      // (13) 0.0307
/*62 */         }                                                                  // (21) 0.01754
/*64 */     }                                                                      // (28) 0.008772
/*68 */     ret = 0;                                                               // (24) 0.01535
/*70 */ out:                                                                       // (29) 0.004386
/*72 */     free(qdevs);                                                           // (18) 0.01974
/*76 */     return ret;                                                            // (25) 0.01316
/*78 */ }                                                                          // (31) 0.002193
