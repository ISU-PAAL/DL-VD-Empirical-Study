// commit message qemu@72cf2d4f0e (target=0, prob=0.013046276, correct=True): Fix sys-queue.h conflict for good
/*0  */ static void qbus_list_bus(DeviceState *dev, char *dest, int len)           // (3) 0.1071
/*2  */ {                                                                          // (10) 0.005102
/*4  */     BusState *child;                                                       // (7) 0.04082
/*6  */     const char *sep = " ";                                                 // (5) 0.06122
/*8  */     int pos = 0;                                                           // (8) 0.04082
/*12 */     pos += snprintf(dest+pos, len-pos,"child busses at \"%s\":",           // (2) 0.1327
/*14 */                     dev->id ? dev->id : dev->info->name);                  // (0) 0.1684
/*16 */     LIST_FOREACH(child, &dev->child_bus, sibling) {                        // (4) 0.102
/*18 */         pos += snprintf(dest+pos, len-pos, "%s\"%s\"", sep, child->name);  // (1) 0.1684
/*20 */         sep = ", ";                                                        // (6) 0.06122
/*22 */     }                                                                      // (9) 0.02041
/*24 */ }                                                                          // (11) 0.005102
