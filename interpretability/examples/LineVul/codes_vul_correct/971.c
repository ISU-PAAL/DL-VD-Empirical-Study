// commit message qemu@d3c8c67469 (target=1, prob=0.9992254, correct=True): block: Skip implicit nodes in query-block/blockstats
/*0   */ void commit_start(const char *job_id, BlockDriverState *bs,                        // (9) 0.03516
/*2   */                   BlockDriverState *base, BlockDriverState *top, int64_t speed,    // (3) 0.06836
/*4   */                   BlockdevOnError on_error, const char *backing_file_str,          // (1) 0.06836
/*6   */                   const char *filter_node_name, Error **errp)                      // (4) 0.06055
/*8   */ {                                                                                  // (26) 0.001954
/*10  */     CommitBlockJob *s;                                                             // (20) 0.01758
/*12  */     BlockReopenQueue *reopen_queue = NULL;                                         // (10) 0.0293
/*14  */     int orig_overlay_flags;                                                        // (15) 0.02148
/*16  */     int orig_base_flags;                                                           // (18) 0.01953
/*18  */     BlockDriverState *iter;                                                        // (19) 0.01758
/*20  */     BlockDriverState *overlay_bs;                                                  // (13) 0.02344
/*22  */     BlockDriverState *commit_top_bs = NULL;                                        // (11) 0.0293
/*24  */     Error *local_err = NULL;                                                       // (14) 0.02148
/*26  */     int ret;                                                                       // (25) 0.01172
/*30  */     assert(top != bs);                                                             // (16) 0.01953
/*32  */     if (top == base) {                                                             // (17) 0.01953
/*34  */         error_setg(errp, "Invalid files for merge: top and base are the same");    // (6) 0.05469
/*36  */         return;                                                                    // (21) 0.01758
/*41  */     overlay_bs = bdrv_find_overlay(bs, top);                                       // (8) 0.03906
/*45  */     if (overlay_bs == NULL) {                                                      // (12) 0.02539
/*47  */         error_setg(errp, "Could not find overlay image for %s:", top->filename);   // (5) 0.05859
/*49  */         return;                                                                    // (23) 0.01758
/*54  */     s = block_job_create(job_id, &commit_job_driver, bs, 0, BLK_PERM_ALL,          // (2) 0.06836
/*56  */                          speed, BLOCK_JOB_DEFAULT, NULL, NULL, errp);              // (0) 0.08203
/*58  */     if (!s) {                                                                      // (24) 0.01562
/*60  */         return;                                                                    // (22) 0.01758
/*65  */     orig_base_flags    = bdrv_get_flags(base);                                     // (7) 0.04297
/*67  */     orig_overlay_flags = bdrv_get_flags(overlay_bs);                               // 0.0
/*71  */     /* convert base & overlay_bs to r/w, if necessary */                           // 0.0
/*73  */     if (!(orig_base_flags & BDRV_O_RDWR)) {                                        // 0.0
/*75  */         reopen_queue = bdrv_reopen_queue(reopen_queue, base, NULL,                 // 0.0
/*77  */                                          orig_base_flags | BDRV_O_RDWR);           // 0.0
/*80  */     if (!(orig_overlay_flags & BDRV_O_RDWR)) {                                     // 0.0
/*82  */         reopen_queue = bdrv_reopen_queue(reopen_queue, overlay_bs, NULL,           // 0.0
/*84  */                                          orig_overlay_flags | BDRV_O_RDWR);        // 0.0
/*87  */     if (reopen_queue) {                                                            // 0.0
/*89  */         bdrv_reopen_multiple(bdrv_get_aio_context(bs), reopen_queue, &local_err);  // 0.0
/*91  */         if (local_err != NULL) {                                                   // 0.0
/*93  */             error_propagate(errp, local_err);                                      // 0.0
/*95  */             goto fail;                                                             // 0.0
/*101 */     /* Insert commit_top block node above top, so we can block consistent read     // 0.0
/*103 */      * on the backing chain below it */                                            // 0.0
/*105 */     commit_top_bs = bdrv_new_open_driver(&bdrv_commit_top, filter_node_name, 0,    // 0.0
/*107 */                                          errp);                                    // 0.0
/*109 */     if (commit_top_bs == NULL) {                                                   // 0.0
/*111 */         goto fail;                                                                 // 0.0
/*117 */     commit_top_bs->total_sectors = top->total_sectors;                             // 0.0
/*119 */     bdrv_set_aio_context(commit_top_bs, bdrv_get_aio_context(top));                // 0.0
/*123 */     bdrv_set_backing_hd(commit_top_bs, top, &local_err);                           // 0.0
/*125 */     if (local_err) {                                                               // 0.0
/*127 */         bdrv_unref(commit_top_bs);                                                 // 0.0
/*129 */         commit_top_bs = NULL;                                                      // 0.0
/*131 */         error_propagate(errp, local_err);                                          // 0.0
/*133 */         goto fail;                                                                 // 0.0
/*136 */     bdrv_set_backing_hd(overlay_bs, commit_top_bs, &local_err);                    // 0.0
/*138 */     if (local_err) {                                                               // 0.0
/*140 */         bdrv_unref(commit_top_bs);                                                 // 0.0
/*142 */         commit_top_bs = NULL;                                                      // 0.0
/*144 */         error_propagate(errp, local_err);                                          // 0.0
/*146 */         goto fail;                                                                 // 0.0
/*151 */     s->commit_top_bs = commit_top_bs;                                              // 0.0
/*153 */     bdrv_unref(commit_top_bs);                                                     // 0.0
/*157 */     /* Block all nodes between top and base, because they will                     // 0.0
/*159 */      * disappear from the chain after this operation. */                           // 0.0
/*161 */     assert(bdrv_chain_contains(top, base));                                        // 0.0
/*163 */     for (iter = top; iter != base; iter = backing_bs(iter)) {                      // 0.0
/*165 */         /* XXX BLK_PERM_WRITE needs to be allowed so we don't block ourselves      // 0.0
/*167 */          * at s->base (if writes are blocked for a node, they are also blocked     // 0.0
/*169 */          * for its backing file). The other options would be a second filter       // 0.0
/*171 */          * driver above s->base. */                                                // 0.0
/*173 */         ret = block_job_add_bdrv(&s->common, "intermediate node", iter, 0,         // 0.0
/*175 */                                  BLK_PERM_WRITE_UNCHANGED | BLK_PERM_WRITE,        // 0.0
/*177 */                                  errp);                                            // 0.0
/*179 */         if (ret < 0) {                                                             // 0.0
/*181 */             goto fail;                                                             // 0.0
/*187 */     ret = block_job_add_bdrv(&s->common, "base", base, 0, BLK_PERM_ALL, errp);     // 0.0
/*189 */     if (ret < 0) {                                                                 // 0.0
/*191 */         goto fail;                                                                 // 0.0
/*196 */     /* overlay_bs must be blocked because it needs to be modified to               // 0.0
/*198 */      * update the backing image string. */                                         // 0.0
/*200 */     ret = block_job_add_bdrv(&s->common, "overlay of top", overlay_bs,             // 0.0
/*202 */                              BLK_PERM_GRAPH_MOD, BLK_PERM_ALL, errp);              // 0.0
/*204 */     if (ret < 0) {                                                                 // 0.0
/*206 */         goto fail;                                                                 // 0.0
/*211 */     s->base = blk_new(BLK_PERM_CONSISTENT_READ                                     // 0.0
/*213 */                       | BLK_PERM_WRITE                                             // 0.0
/*215 */                       | BLK_PERM_RESIZE,                                           // 0.0
/*217 */                       BLK_PERM_CONSISTENT_READ                                     // 0.0
/*219 */                       | BLK_PERM_GRAPH_MOD                                         // 0.0
/*221 */                       | BLK_PERM_WRITE_UNCHANGED);                                 // 0.0
/*223 */     ret = blk_insert_bs(s->base, base, errp);                                      // 0.0
/*225 */     if (ret < 0) {                                                                 // 0.0
/*227 */         goto fail;                                                                 // 0.0
/*232 */     /* Required permissions are already taken with block_job_add_bdrv() */         // 0.0
/*234 */     s->top = blk_new(0, BLK_PERM_ALL);                                             // 0.0
/*236 */     ret = blk_insert_bs(s->top, top, errp);                                        // 0.0
/*238 */     if (ret < 0) {                                                                 // 0.0
/*240 */         goto fail;                                                                 // 0.0
/*245 */     s->active = bs;                                                                // 0.0
/*249 */     s->base_flags          = orig_base_flags;                                      // 0.0
/*251 */     s->orig_overlay_flags  = orig_overlay_flags;                                   // 0.0
/*255 */     s->backing_file_str = g_strdup(backing_file_str);                              // 0.0
/*259 */     s->on_error = on_error;                                                        // 0.0
/*263 */     trace_commit_start(bs, base, top, s);                                          // 0.0
/*265 */     block_job_start(&s->common);                                                   // 0.0
/*267 */     return;                                                                        // 0.0
/*271 */ fail:                                                                              // 0.0
/*273 */     if (s->base) {                                                                 // 0.0
/*275 */         blk_unref(s->base);                                                        // 0.0
/*278 */     if (s->top) {                                                                  // 0.0
/*280 */         blk_unref(s->top);                                                         // 0.0
/*283 */     if (commit_top_bs) {                                                           // 0.0
/*285 */         bdrv_set_backing_hd(overlay_bs, top, &error_abort);                        // 0.0
/*288 */     block_job_early_fail(&s->common);                                              // 0.0
