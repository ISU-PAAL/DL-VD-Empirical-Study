// commit message qemu@c9fc508398 (target=0, prob=0.53706753, correct=False): qemu-img: fix missing space in qemu-img check output
/*0  */ static void dump_human_image_check(ImageCheck *check)                                  // (16) 0.0293
/*2  */ {                                                                                      // (23) 0.001953
/*4  */     if (!(check->corruptions || check->leaks || check->check_errors)) {                // (7) 0.04687
/*6  */         printf("No errors were found on the image.\n");                                // (12) 0.03906
/*8  */     } else {                                                                           // (21) 0.01172
/*10 */         if (check->corruptions) {                                                      // (14) 0.03125
/*12 */             printf("\n%" PRId64 " errors were found on the image.\n"                   // (4) 0.05859
/*14 */                 "Data may be corrupted, or further writes to the image "               // (5) 0.05469
/*16 */                 "may corrupt it.\n",                                                   // (8) 0.04492
/*18 */                 check->corruptions);                                                   // (10) 0.04102
/*20 */         }                                                                              // (18) 0.01562
/*24 */         if (check->leaks) {                                                            // (17) 0.0293
/*26 */             printf("\n%" PRId64 " leaked clusters were found on the image.\n"          // (2) 0.06055
/*28 */                 "This means waste of disk space, but no harm to data.\n",              // (1) 0.0625
/*30 */                 check->leaks);                                                         // (13) 0.03906
/*32 */         }                                                                              // (19) 0.01562
/*36 */         if (check->check_errors) {                                                     // (15) 0.03125
/*38 */             printf("\n%" PRId64 " internal errors have occurred during the check.\n",  // (3) 0.06055
/*40 */                 check->check_errors);                                                  // (11) 0.04102
/*42 */         }                                                                              // (20) 0.01562
/*44 */     }                                                                                  // (22) 0.007812
/*48 */     if (check->total_clusters != 0 && check->allocated_clusters != 0) {                // (6) 0.04883
/*50 */         printf("%" PRId64 "/%" PRId64 "= %0.2f%% allocated, %0.2f%% fragmented\n",     // (0) 0.07422
/*52 */         check->allocated_clusters, check->total_clusters,                              // (9) 0.04297
/*54 */         check->allocated_clusters * 100.0 / check->total_clusters,                     // 0.0
/*56 */         check->fragmented_clusters * 100.0 / check->allocated_clusters);               // 0.0
/*58 */     }                                                                                  // 0.0
/*62 */     if (check->image_end_offset) {                                                     // 0.0
/*64 */         printf("Image end offset: %" PRId64 "\n", check->image_end_offset);            // 0.0
/*66 */     }                                                                                  // 0.0
/*68 */ }                                                                                      // 0.0
