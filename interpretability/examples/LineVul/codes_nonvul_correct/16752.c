// commit message qemu@f892291eee (target=0, prob=0.22990435, correct=True): numa: Fix format string for "Invalid node" message
/*0  */ static void parse_numa_distance(NumaDistOptions *dist, Error **errp)        // (12) 0.04102
/*2  */ {                                                                           // (24) 0.001953
/*4  */     uint16_t src = dist->src;                                               // (16) 0.02539
/*6  */     uint16_t dst = dist->dst;                                               // (15) 0.02734
/*8  */     uint8_t val = dist->val;                                                // (17) 0.02539
/*12 */     if (src >= MAX_NODES || dst >= MAX_NODES) {                             // (10) 0.04297
/*14 */         error_setg(errp,                                                    // (14) 0.0293
/*16 */                    "Invalid node %" PRIu16                                  // (7) 0.05273
/*18 */                    ", max possible could be %" PRIu16,                      // (2) 0.05859
/*20 */                    MAX(src, dst), MAX_NODES);                               // (3) 0.05859
/*22 */         return;                                                             // (18) 0.01758
/*24 */     }                                                                       // (21) 0.007813
/*28 */     if (!numa_info[src].present || !numa_info[dst].present) {               // (9) 0.05078
/*30 */         error_setg(errp, "Source/Destination NUMA node is missing. "        // (5) 0.05469
/*32 */                    "Please use '-numa node' option to declare it first.");  // (0) 0.06641
/*34 */         return;                                                             // (19) 0.01758
/*36 */     }                                                                       // (22) 0.007812
/*40 */     if (val < NUMA_DISTANCE_MIN) {                                          // (13) 0.03516
/*42 */         error_setg(errp, "NUMA distance (%" PRIu8 ") is invalid, "          // (1) 0.0625
/*44 */                    "it shouldn't be less than %d.",                         // (6) 0.05469
/*46 */                    val, NUMA_DISTANCE_MIN);                                 // (4) 0.05859
/*48 */         return;                                                             // (20) 0.01758
/*50 */     }                                                                       // (23) 0.007812
/*54 */     if (src == dst && val != NUMA_DISTANCE_MIN) {                           // (11) 0.04297
/*56 */         error_setg(errp, "Local distance of node %d should be %d.",         // (8) 0.05273
/*58 */                    src, NUMA_DISTANCE_MIN);                                 // 0.0
/*60 */         return;                                                             // 0.0
/*62 */     }                                                                       // 0.0
/*66 */     numa_info[src].distance[dst] = val;                                     // 0.0
/*68 */     have_numa_distance = true;                                              // 0.0
/*70 */ }                                                                           // 0.0
