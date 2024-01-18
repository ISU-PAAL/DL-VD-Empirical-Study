// commit message qemu@f0536bb848 (target=0, prob=0.38715032, correct=True): Don't require encryption password for 'qemu-img info' command
/*0   */ static int img_info(int argc, char **argv)                                      // (10) 0.0293
/*2   */ {                                                                               // (33) 0.001953
/*4   */     int c;                                                                      // (32) 0.01172
/*6   */     OutputFormat output_format = OFORMAT_HUMAN;                                 // (6) 0.0332
/*8   */     const char *filename, *fmt, *output;                                        // (11) 0.0293
/*10  */     BlockDriverState *bs;                                                       // (24) 0.01758
/*12  */     ImageInfo *info;                                                            // (25) 0.01563
/*16  */     fmt = NULL;                                                                 // (31) 0.01367
/*18  */     output = NULL;                                                              // (30) 0.01367
/*20  */     for(;;) {                                                                   // (26) 0.01563
/*22  */         int option_index = 0;                                                   // (14) 0.02734
/*24  */         static const struct option long_options[] = {                           // (7) 0.0332
/*26  */             {"help", no_argument, 0, 'h'},                                      // (3) 0.04687
/*28  */             {"format", required_argument, 0, 'f'},                              // (4) 0.04687
/*30  */             {"output", required_argument, 0, OPTION_OUTPUT},                    // (1) 0.05273
/*32  */             {0, 0, 0, 0}                                                        // (5) 0.03906
/*34  */         };                                                                      // (27) 0.01562
/*36  */         c = getopt_long(argc, argv, "f:h",                                      // (2) 0.04883
/*38  */                         long_options, &option_index);                           // (0) 0.0625
/*40  */         if (c == -1) {                                                          // (13) 0.0293
/*42  */             break;                                                              // (17) 0.02539
/*44  */         }                                                                       // (29) 0.01562
/*46  */         switch(c) {                                                             // (20) 0.02344
/*48  */         case '?':                                                               // (21) 0.02148
/*50  */         case 'h':                                                               // (22) 0.02148
/*52  */             help();                                                             // (15) 0.02539
/*54  */             break;                                                              // (18) 0.02539
/*56  */         case 'f':                                                               // (23) 0.02148
/*58  */             fmt = optarg;                                                       // (8) 0.03125
/*60  */             break;                                                              // (16) 0.02539
/*62  */         case OPTION_OUTPUT:                                                     // (12) 0.0293
/*64  */             output = optarg;                                                    // (9) 0.03125
/*66  */             break;                                                              // (19) 0.02539
/*68  */         }                                                                       // (28) 0.01562
/*70  */     }                                                                           // 0.0
/*72  */     if (optind >= argc) {                                                       // 0.0
/*74  */         help();                                                                 // 0.0
/*76  */     }                                                                           // 0.0
/*78  */     filename = argv[optind++];                                                  // 0.0
/*82  */     if (output && !strcmp(output, "json")) {                                    // 0.0
/*84  */         output_format = OFORMAT_JSON;                                           // 0.0
/*86  */     } else if (output && !strcmp(output, "human")) {                            // 0.0
/*88  */         output_format = OFORMAT_HUMAN;                                          // 0.0
/*90  */     } else if (output) {                                                        // 0.0
/*92  */         error_report("--output must be used with human or json as argument.");  // 0.0
/*94  */         return 1;                                                               // 0.0
/*96  */     }                                                                           // 0.0
/*100 */     bs = bdrv_new_open(filename, fmt, BDRV_O_FLAGS | BDRV_O_NO_BACKING);        // 0.0
/*102 */     if (!bs) {                                                                  // 0.0
/*104 */         return 1;                                                               // 0.0
/*106 */     }                                                                           // 0.0
/*110 */     info = g_new0(ImageInfo, 1);                                                // 0.0
/*112 */     collect_image_info(bs, info, filename, fmt);                                // 0.0
/*116 */     switch (output_format) {                                                    // 0.0
/*118 */     case OFORMAT_HUMAN:                                                         // 0.0
/*120 */         dump_human_image_info(info);                                            // 0.0
/*122 */         dump_snapshots(bs);                                                     // 0.0
/*124 */         break;                                                                  // 0.0
/*126 */     case OFORMAT_JSON:                                                          // 0.0
/*128 */         collect_snapshots(bs, info);                                            // 0.0
/*130 */         dump_json_image_info(info);                                             // 0.0
/*132 */         break;                                                                  // 0.0
/*134 */     }                                                                           // 0.0
/*138 */     qapi_free_ImageInfo(info);                                                  // 0.0
/*140 */     bdrv_delete(bs);                                                            // 0.0
/*142 */     return 0;                                                                   // 0.0
/*144 */ }                                                                               // 0.0
