// commit message qemu@449041d4db (target=1, prob=0.7758655, correct=True): qdev-properties: Fix (u)intXX parsers
/*0  */ static int parse_uint8(DeviceState *dev, Property *prop, const char *str)  // (2) 0.1382
/*2  */ {                                                                          // (9) 0.006579
/*4  */     uint8_t *ptr = qdev_get_prop_ptr(dev, prop);                           // (1) 0.1513
/*6  */     const char *fmt;                                                       // (6) 0.05921
/*10 */     /* accept both hex and decimal */                                      // (5) 0.06579
/*12 */     fmt = strncasecmp(str, "0x",2) == 0 ? "%" PRIx8 : "%" PRIu8;           // (0) 0.2303
/*14 */     if (sscanf(str, fmt, ptr) != 1)                                        // (3) 0.1184
/*16 */         return -EINVAL;                                                    // (4) 0.08553
/*18 */     return 0;                                                              // (7) 0.03947
/*20 */ }                                                                          // (8) 0.006579
