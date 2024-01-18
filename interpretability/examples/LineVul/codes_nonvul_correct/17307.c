// commit message qemu@22f2e34474 (target=0, prob=0.049847562, correct=True): fix qdev_print_devinfo()
/*0  */ static int qdev_print_devinfo(DeviceInfo *info, char *dest, int len)        // (5) 0.1
/*2  */ {                                                                           // (11) 0.004348
/*4  */     int pos = 0;                                                            // (9) 0.03478
/*8  */     pos += snprintf(dest+pos, len-pos, "name \"%s\", bus %s",               // (3) 0.113
/*10 */                     info->name, info->bus_info->name);                      // (0) 0.1348
/*12 */     if (info->alias)                                                        // (7) 0.03913
/*14 */         pos += snprintf(dest+pos, len-pos, ", alias \"%s\"", info->alias);  // (1) 0.1348
/*16 */     if (info->desc)                                                         // (8) 0.03913
/*18 */         pos += snprintf(dest+pos, len-pos, ", desc \"%s\"", info->desc);    // (2) 0.1348
/*20 */     if (info->no_user)                                                      // (6) 0.04783
/*22 */         pos += snprintf(dest+pos, len-pos, ", no-user");                    // (4) 0.1087
/*24 */     return pos;                                                             // (10) 0.02609
/*26 */ }                                                                           // (12) 0.004348
