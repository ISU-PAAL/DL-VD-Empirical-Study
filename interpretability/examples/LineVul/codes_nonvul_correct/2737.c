// commit message qemu@4cdd01d32e (target=0, prob=0.38165706, correct=True): block: Pass driver-specific options to .bdrv_refresh_filename()
/*0   */ void bdrv_refresh_filename(BlockDriverState *bs)                                  // (14) 0.03125
/*2   */ {                                                                                 // (29) 0.001953
/*4   */     BlockDriver *drv = bs->drv;                                                   // (16) 0.0293
/*6   */     QDict *opts;                                                                  // (20) 0.01953
/*10  */     if (!drv) {                                                                   // (24) 0.01758
/*12  */         return;                                                                   // (23) 0.01758
/*14  */     }                                                                             // (27) 0.007812
/*18  */     /* This BDS's file name will most probably depend on its file's name, so      // (9) 0.03906
/*20  */      * refresh that first */                                                      // (22) 0.01758
/*22  */     if (bs->file) {                                                               // (21) 0.01953
/*24  */         bdrv_refresh_filename(bs->file->bs);                                      // (5) 0.04297
/*26  */     }                                                                             // (28) 0.007812
/*30  */     if (drv->bdrv_refresh_filename) {                                             // (11) 0.03516
/*32  */         /* Obsolete information is of no use here, so drop the old file name      // (0) 0.04492
/*34  */          * information before refreshing it */                                    // (18) 0.02734
/*36  */         bs->exact_filename[0] = '\0';                                             // (3) 0.04297
/*38  */         if (bs->full_open_options) {                                              // (13) 0.03516
/*40  */             QDECREF(bs->full_open_options);                                       // (1) 0.04492
/*42  */             bs->full_open_options = NULL;                                         // (7) 0.04297
/*44  */         }                                                                         // (25) 0.01562
/*48  */         drv->bdrv_refresh_filename(bs);                                           // (8) 0.04102
/*50  */     } else if (bs->file) {                                                        // (19) 0.02344
/*52  */         /* Try to reconstruct valid information from the underlying file */       // (10) 0.03516
/*54  */         bool has_open_options;                                                    // (17) 0.02734
/*58  */         bs->exact_filename[0] = '\0';                                             // (4) 0.04297
/*60  */         if (bs->full_open_options) {                                              // (12) 0.03516
/*62  */             QDECREF(bs->full_open_options);                                       // (2) 0.04492
/*64  */             bs->full_open_options = NULL;                                         // (6) 0.04297
/*66  */         }                                                                         // (26) 0.01562
/*70  */         opts = qdict_new();                                                       // (15) 0.0293
/*72  */         has_open_options = append_open_options(opts, bs);                         // 0.0
/*76  */         /* If no specific options have been given for this BDS, the filename of   // 0.0
/*78  */          * the underlying file should suffice for this one as well */             // 0.0
/*80  */         if (bs->file->bs->exact_filename[0] && !has_open_options) {               // 0.0
/*82  */             strcpy(bs->exact_filename, bs->file->bs->exact_filename);             // 0.0
/*84  */         }                                                                         // 0.0
/*86  */         /* Reconstructing the full options QDict is simple for most format block  // 0.0
/*88  */          * drivers, as long as the full options are known for the underlying      // 0.0
/*90  */          * file BDS. The full options QDict of that file BDS should somehow       // 0.0
/*92  */          * contain a representation of the filename, therefore the following      // 0.0
/*94  */          * suffices without querying the (exact_)filename of this BDS. */         // 0.0
/*96  */         if (bs->file->bs->full_open_options) {                                    // 0.0
/*98  */             qdict_put_obj(opts, "driver",                                         // 0.0
/*100 */                           QOBJECT(qstring_from_str(drv->format_name)));           // 0.0
/*102 */             QINCREF(bs->file->bs->full_open_options);                             // 0.0
/*104 */             qdict_put_obj(opts, "file",                                           // 0.0
/*106 */                           QOBJECT(bs->file->bs->full_open_options));              // 0.0
/*110 */             bs->full_open_options = opts;                                         // 0.0
/*112 */         } else {                                                                  // 0.0
/*114 */             QDECREF(opts);                                                        // 0.0
/*116 */         }                                                                         // 0.0
/*118 */     } else if (!bs->full_open_options && qdict_size(bs->options)) {               // 0.0
/*120 */         /* There is no underlying file BDS (at least referenced by BDS.file),     // 0.0
/*122 */          * so the full options QDict should be equal to the options given         // 0.0
/*124 */          * specifically for this block device when it was opened (plus the        // 0.0
/*126 */          * driver specification).                                                 // 0.0
/*128 */          * Because those options don't change, there is no need to update         // 0.0
/*130 */          * full_open_options when it's already set. */                            // 0.0
/*134 */         opts = qdict_new();                                                       // 0.0
/*136 */         append_open_options(opts, bs);                                            // 0.0
/*138 */         qdict_put_obj(opts, "driver",                                             // 0.0
/*140 */                       QOBJECT(qstring_from_str(drv->format_name)));               // 0.0
/*144 */         if (bs->exact_filename[0]) {                                              // 0.0
/*146 */             /* This may not work for all block protocol drivers (some may         // 0.0
/*148 */              * require this filename to be parsed), but we have to find some      // 0.0
/*150 */              * default solution here, so just include it. If some block driver    // 0.0
/*152 */              * does not support pure options without any filename at all or       // 0.0
/*154 */              * needs some special format of the options QDict, it needs to        // 0.0
/*156 */              * implement the driver-specific bdrv_refresh_filename() function.    // 0.0
/*158 */              */                                                                   // 0.0
/*160 */             qdict_put_obj(opts, "filename",                                       // 0.0
/*162 */                           QOBJECT(qstring_from_str(bs->exact_filename)));         // 0.0
/*164 */         }                                                                         // 0.0
/*168 */         bs->full_open_options = opts;                                             // 0.0
/*170 */     }                                                                             // 0.0
/*174 */     if (bs->exact_filename[0]) {                                                  // 0.0
/*176 */         pstrcpy(bs->filename, sizeof(bs->filename), bs->exact_filename);          // 0.0
/*178 */     } else if (bs->full_open_options) {                                           // 0.0
/*180 */         QString *json = qobject_to_json(QOBJECT(bs->full_open_options));          // 0.0
/*182 */         snprintf(bs->filename, sizeof(bs->filename), "json:%s",                   // 0.0
/*184 */                  qstring_get_str(json));                                          // 0.0
/*186 */         QDECREF(json);                                                            // 0.0
/*188 */     }                                                                             // 0.0
/*190 */ }                                                                                 // 0.0
