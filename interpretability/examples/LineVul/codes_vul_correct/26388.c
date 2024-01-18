// commit message qemu@ba2ab2f2ca (target=1, prob=0.9992163, correct=True): qcow2: Flush image after creation
/*0   */ static int qcow2_create2(const char *filename, int64_t total_size,               // (7) 0.04297
/*1   */                          const char *backing_file, const char *backing_format,   // (1) 0.07812
/*2   */                          int flags, size_t cluster_size, int prealloc,           // (2) 0.07422
/*3   */                          QEMUOptionParameter *options, int version,              // (3) 0.06836
/*4   */                          Error **errp)                                           // (6) 0.05664
/*5   */ {                                                                                // (23) 0.001953
/*6   */     /* Calculate cluster_bits */                                                 // (16) 0.01953
/*7   */     int cluster_bits;                                                            // (18) 0.01562
/*8   */     cluster_bits = ffs(cluster_size) - 1;                                        // (14) 0.03516
/*9   */     if (cluster_bits < MIN_CLUSTER_BITS || cluster_bits > MAX_CLUSTER_BITS ||    // (4) 0.0625
/*10  */         (1 << cluster_bits) != cluster_size)                                     // (12) 0.03711
/*11  */     {                                                                            // (22) 0.007812
/*12  */         error_setg(errp, "Cluster size must be a power of two between %d and "   // (5) 0.05859
/*13  */                    "%dk", 1 << MIN_CLUSTER_BITS, 1 << (MAX_CLUSTER_BITS - 10));  // (0) 0.08984
/*14  */         return -EINVAL;                                                          // (15) 0.02539
/*15  */     /*                                                                           // (21) 0.007813
/*16  */      * Open the image file and write a minimal qcow2 header.                     // (13) 0.03516
/*17  */      *                                                                           // (20) 0.009766
/*18  */      * We keep things simple and start with a zero-sized image. We also          // (10) 0.03906
/*19  */      * do without refcount blocks or a L1 table for now. We'll fix the           // (8) 0.04297
/*20  */      * inconsistency later.                                                      // (17) 0.01562
/*21  */      *                                                                           // (19) 0.009766
/*22  */      * We do need a refcount table because growing the refcount table means      // (11) 0.03711
/*23  */      * allocating two new refcount blocks - the seconds of which would be at     // (9) 0.03906
/*24  */      * 2 GB for 64k clusters, and we don't want to have a 2 GB initial file      // 0.0
/*25  */      * size for any qcow2 image.                                                 // 0.0
/*26  */      */                                                                          // 0.0
/*27  */     BlockDriverState* bs;                                                        // 0.0
/*28  */     QCowHeader header;                                                           // 0.0
/*29  */     uint8_t* refcount_table;                                                     // 0.0
/*30  */     Error *local_err = NULL;                                                     // 0.0
/*31  */     int ret;                                                                     // 0.0
/*32  */     ret = bdrv_create_file(filename, options, &local_err);                       // 0.0
/*33  */     if (ret < 0) {                                                               // 0.0
/*34  */         return ret;                                                              // 0.0
/*35  */     ret = bdrv_file_open(&bs, filename, NULL, BDRV_O_RDWR, &local_err);          // 0.0
/*36  */     if (ret < 0) {                                                               // 0.0
/*37  */         return ret;                                                              // 0.0
/*38  */     /* Write the header */                                                       // 0.0
/*39  */     memset(&header, 0, sizeof(header));                                          // 0.0
/*40  */     header.magic = cpu_to_be32(QCOW_MAGIC);                                      // 0.0
/*41  */     header.version = cpu_to_be32(version);                                       // 0.0
/*42  */     header.cluster_bits = cpu_to_be32(cluster_bits);                             // 0.0
/*43  */     header.size = cpu_to_be64(0);                                                // 0.0
/*44  */     header.l1_table_offset = cpu_to_be64(0);                                     // 0.0
/*45  */     header.l1_size = cpu_to_be32(0);                                             // 0.0
/*46  */     header.refcount_table_offset = cpu_to_be64(cluster_size);                    // 0.0
/*47  */     header.refcount_table_clusters = cpu_to_be32(1);                             // 0.0
/*48  */     header.refcount_order = cpu_to_be32(3 + REFCOUNT_SHIFT);                     // 0.0
/*49  */     header.header_length = cpu_to_be32(sizeof(header));                          // 0.0
/*50  */     if (flags & BLOCK_FLAG_ENCRYPT) {                                            // 0.0
/*51  */         header.crypt_method = cpu_to_be32(QCOW_CRYPT_AES);                       // 0.0
/*52  */     } else {                                                                     // 0.0
/*53  */         header.crypt_method = cpu_to_be32(QCOW_CRYPT_NONE);                      // 0.0
/*54  */     if (flags & BLOCK_FLAG_LAZY_REFCOUNTS) {                                     // 0.0
/*55  */         header.compatible_features |=                                            // 0.0
/*56  */             cpu_to_be64(QCOW2_COMPAT_LAZY_REFCOUNTS);                            // 0.0
/*57  */     ret = bdrv_pwrite(bs, 0, &header, sizeof(header));                           // 0.0
/*58  */     if (ret < 0) {                                                               // 0.0
/*59  */         error_setg_errno(errp, -ret, "Could not write qcow2 header");            // 0.0
/*60  */     /* Write an empty refcount table */                                          // 0.0
/*61  */     refcount_table = g_malloc0(cluster_size);                                    // 0.0
/*62  */     ret = bdrv_pwrite(bs, cluster_size, refcount_table, cluster_size);           // 0.0
/*63  */     g_free(refcount_table);                                                      // 0.0
/*64  */     if (ret < 0) {                                                               // 0.0
/*65  */         error_setg_errno(errp, -ret, "Could not write refcount table");          // 0.0
/*66  */     /*                                                                           // 0.0
/*67  */      * And now open the image and make it consistent first (i.e. increase the    // 0.0
/*68  */      * refcount of the cluster that is occupied by the header and the refcount   // 0.0
/*69  */      * table)                                                                    // 0.0
/*70  */      */                                                                          // 0.0
/*71  */     BlockDriver* drv = bdrv_find_format("qcow2");                                // 0.0
/*72  */     assert(drv != NULL);                                                         // 0.0
/*73  */         BDRV_O_RDWR | BDRV_O_CACHE_WB | BDRV_O_NO_FLUSH, drv, &local_err);       // 0.0
/*74  */     if (ret < 0) {                                                               // 0.0
/*75  */     ret = qcow2_alloc_clusters(bs, 2 * cluster_size);                            // 0.0
/*76  */     if (ret < 0) {                                                               // 0.0
/*77  */         error_setg_errno(errp, -ret, "Could not allocate clusters for qcow2 "    // 0.0
/*78  */                          "header and refcount table");                           // 0.0
/*79  */     } else if (ret != 0) {                                                       // 0.0
/*80  */         error_report("Huh, first cluster in empty image is already in use?");    // 0.0
/*81  */         abort();                                                                 // 0.0
/*82  */     /* Okay, now that we have a valid image, let's give it the right size */     // 0.0
/*83  */     ret = bdrv_truncate(bs, total_size * BDRV_SECTOR_SIZE);                      // 0.0
/*84  */     if (ret < 0) {                                                               // 0.0
/*85  */         error_setg_errno(errp, -ret, "Could not resize image");                  // 0.0
/*86  */     /* Want a backing file? There you go.*/                                      // 0.0
/*87  */     if (backing_file) {                                                          // 0.0
/*88  */         ret = bdrv_change_backing_file(bs, backing_file, backing_format);        // 0.0
/*89  */         if (ret < 0) {                                                           // 0.0
/*90  */             error_setg_errno(errp, -ret, "Could not assign backing file '%s' "   // 0.0
/*91  */                              "with format '%s'", backing_file, backing_format);  // 0.0
/*92  */     /* And if we're supposed to preallocate metadata, do that now */             // 0.0
/*93  */     if (prealloc) {                                                              // 0.0
/*94  */         BDRVQcowState *s = bs->opaque;                                           // 0.0
/*95  */         qemu_co_mutex_lock(&s->lock);                                            // 0.0
/*96  */         ret = preallocate(bs);                                                   // 0.0
/*97  */         qemu_co_mutex_unlock(&s->lock);                                          // 0.0
/*98  */         if (ret < 0) {                                                           // 0.0
/*99  */             error_setg_errno(errp, -ret, "Could not preallocate metadata");      // 0.0
/*100 */     ret = 0;                                                                     // 0.0
/*101 */ out:                                                                             // 0.0
/*102 */     bdrv_unref(bs);                                                              // 0.0
/*103 */     return ret;                                                                  // 0.0
