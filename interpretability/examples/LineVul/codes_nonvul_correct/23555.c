// commit message qemu@3b00f702c2 (target=0, prob=0.031719163, correct=True): s390x/cpumodel: add zpci, aen and ais facilities
/*0  */ static void s390_flic_common_realize(DeviceState *dev, Error **errp)       // (3) 0.1173
/*2  */ {                                                                          // (8) 0.005102
/*4  */     S390FLICState *fs = S390_FLIC_COMMON(dev);                             // (4) 0.1122
/*6  */     uint32_t max_batch = fs->adapter_routes_max_batch;                     // (2) 0.1224
/*10 */     if (max_batch > ADAPTER_ROUTES_MAX_GSI) {                              // (5) 0.1122
/*12 */         error_setg(errp, "flic property adapter_routes_max_batch too big"  // (1) 0.1582
/*14 */                    " (%d > %d)", max_batch, ADAPTER_ROUTES_MAX_GSI);       // (0) 0.2092
/*16 */     }                                                                      // (7) 0.02041
/*20 */     fs->ais_supported = true;                                              // (6) 0.05612
/*22 */ }                                                                          // (9) 0.005102
