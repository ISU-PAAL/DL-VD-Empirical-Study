// commit message qemu@e3737b820b (target=1, prob=0.99905497, correct=True): bochs: Check catalog_size header field (CVE-2014-0143)
/*0  */ static int bochs_open(BlockDriverState *bs, QDict *options, int flags,        // (9) 0.04493
/*1  */                       Error **errp)                                           // (3) 0.05078
/*2  */ {                                                                             // (23) 0.001953
/*3  */     BDRVBochsState *s = bs->opaque;                                           // (14) 0.03516
/*4  */     uint32_t i;                                                               // (20) 0.01758
/*5  */     struct bochs_header bochs;                                                // (16) 0.02539
/*6  */     int ret;                                                                  // (21) 0.01172
/*7  */     bs->read_only = 1; // no write support yet                                // (15) 0.0332
/*8  */     ret = bdrv_pread(bs->file, 0, &bochs, sizeof(bochs));                     // (2) 0.05469
/*9  */     if (ret < 0) {                                                            // (19) 0.01953
/*10 */         return ret;                                                           // (18) 0.01953
/*11 */     if (strcmp(bochs.magic, HEADER_MAGIC) ||                                  // (13) 0.04102
/*12 */         strcmp(bochs.type, REDOLOG_TYPE) ||                                   // (12) 0.04297
/*13 */         strcmp(bochs.subtype, GROWING_TYPE) ||                                // (8) 0.04687
/*14 */ 	((le32_to_cpu(bochs.version) != HEADER_VERSION) &&                           // (11) 0.04297
/*15 */ 	(le32_to_cpu(bochs.version) != HEADER_V1))) {                                // (10) 0.04492
/*16 */         error_setg(errp, "Image not in Bochs format");                        // (6) 0.04687
/*17 */         return -EINVAL;                                                       // (17) 0.02539
/*18 */     if (le32_to_cpu(bochs.version) == HEADER_V1) {                            // (4) 0.05078
/*19 */         bs->total_sectors = le64_to_cpu(bochs.extra.redolog_v1.disk) / 512;   // (0) 0.07617
/*20 */     } else {                                                                  // (22) 0.01172
/*21 */         bs->total_sectors = le64_to_cpu(bochs.extra.redolog.disk) / 512;      // (1) 0.07031
/*22 */     s->catalog_size = le32_to_cpu(bochs.catalog);                             // (7) 0.04687
/*23 */     s->catalog_bitmap = g_malloc(s->catalog_size * 4);                        // (5) 0.04883
/*24 */     ret = bdrv_pread(bs->file, le32_to_cpu(bochs.header), s->catalog_bitmap,  // 0.0
/*25 */                      s->catalog_size * 4);                                    // 0.0
/*26 */     if (ret < 0) {                                                            // 0.0
/*27 */         goto fail;                                                            // 0.0
/*28 */     for (i = 0; i < s->catalog_size; i++)                                     // 0.0
/*29 */ 	le32_to_cpus(&s->catalog_bitmap[i]);                                         // 0.0
/*30 */     s->data_offset = le32_to_cpu(bochs.header) + (s->catalog_size * 4);       // 0.0
/*31 */     s->bitmap_blocks = 1 + (le32_to_cpu(bochs.bitmap) - 1) / 512;             // 0.0
/*32 */     s->extent_blocks = 1 + (le32_to_cpu(bochs.extent) - 1) / 512;             // 0.0
/*33 */     s->extent_size = le32_to_cpu(bochs.extent);                               // 0.0
/*34 */     if (s->catalog_size < bs->total_sectors / s->extent_size) {               // 0.0
/*35 */         error_setg(errp, "Catalog size is too small for this disk size");     // 0.0
/*36 */         ret = -EINVAL;                                                        // 0.0
/*37 */         goto fail;                                                            // 0.0
/*38 */     qemu_co_mutex_init(&s->lock);                                             // 0.0
/*39 */     return 0;                                                                 // 0.0
/*40 */ fail:                                                                         // 0.0
/*41 */     g_free(s->catalog_bitmap);                                                // 0.0
/*42 */     return ret;                                                               // 0.0
