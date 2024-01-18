// commit message qemu@2f859f80c2 (target=0, prob=0.5097409, correct=False): dump: eliminate DumpState.page_size ("guest's page size")
/*0   */ static int write_dump_pages(DumpState *s)                                        // (13) 0.02734
/*2   */ {                                                                                // (33) 0.001953
/*4   */     int ret = 0;                                                                 // (27) 0.01562
/*6   */     DataCache page_desc, page_data;                                              // (18) 0.02539
/*8   */     size_t len_buf_out, size_out;                                                // (10) 0.03125
/*10  */ #ifdef CONFIG_LZO                                                                // (26) 0.01562
/*12  */     lzo_bytep wrkmem = NULL;                                                     // (12) 0.0293
/*14  */ #endif                                                                           // (32) 0.003906
/*16  */     uint8_t *buf_out = NULL;                                                     // (15) 0.02734
/*18  */     off_t offset_desc, offset_data;                                              // (14) 0.02734
/*20  */     PageDescriptor pd, pd_zero;                                                  // (11) 0.0293
/*22  */     uint8_t *buf;                                                                // (23) 0.01953
/*24  */     int endian = s->dump_info.d_endian;                                          // (7) 0.03516
/*26  */     GuestPhysBlock *block_iter = NULL;                                           // (17) 0.02539
/*28  */     uint64_t pfn_iter;                                                           // (20) 0.02344
/*32  */     /* get offset of page_desc and page_data in dump file */                     // (8) 0.03516
/*34  */     offset_desc = s->offset_page;                                                // (19) 0.02539
/*36  */     offset_data = offset_desc + sizeof(PageDescriptor) * s->num_dumpable;        // (2) 0.05078
/*40  */     prepare_data_cache(&page_desc, s, offset_desc);                              // (5) 0.03711
/*42  */     prepare_data_cache(&page_data, s, offset_data);                              // (6) 0.03711
/*46  */     /* prepare buffer to store compressed data */                                // (22) 0.02148
/*48  */     len_buf_out = get_len_buf_out(s->page_size, s->flag_compress);               // (0) 0.05859
/*50  */     if (len_buf_out == 0) {                                                      // (16) 0.02734
/*52  */         dump_error(s, "dump: failed to get length of output buffer.\n");         // (1) 0.05273
/*54  */         goto out;                                                                // (24) 0.01953
/*56  */     }                                                                            // (29) 0.007813
/*60  */ #ifdef CONFIG_LZO                                                                // (25) 0.01563
/*62  */     wrkmem = g_malloc(LZO1X_1_MEM_COMPRESS);                                     // (3) 0.05078
/*64  */ #endif                                                                           // (31) 0.003906
/*68  */     buf_out = g_malloc(len_buf_out);                                             // (9) 0.03516
/*72  */     /*                                                                           // (30) 0.007812
/*74  */      * init zero page's page_desc and page_data, because every zero page         // (4) 0.04102
/*76  */      * uses the same page_data                                                   // (21) 0.02148
/*78  */      */                                                                          // (28) 0.009766
/*80  */     pd_zero.size = cpu_convert_to_target32(s->page_size, endian);                // 0.0
/*82  */     pd_zero.flags = cpu_convert_to_target32(0, endian);                          // 0.0
/*84  */     pd_zero.offset = cpu_convert_to_target64(offset_data, endian);               // 0.0
/*86  */     pd_zero.page_flags = cpu_convert_to_target64(0, endian);                     // 0.0
/*88  */     buf = g_malloc0(s->page_size);                                               // 0.0
/*90  */     ret = write_cache(&page_data, buf, s->page_size, false);                     // 0.0
/*92  */     g_free(buf);                                                                 // 0.0
/*94  */     if (ret < 0) {                                                               // 0.0
/*96  */         dump_error(s, "dump: failed to write page data(zero page).\n");          // 0.0
/*98  */         goto out;                                                                // 0.0
/*100 */     }                                                                            // 0.0
/*104 */     offset_data += s->page_size;                                                 // 0.0
/*108 */     /*                                                                           // 0.0
/*110 */      * dump memory to vmcore page by page. zero page will all be resided in the  // 0.0
/*112 */      * first page of page section                                                // 0.0
/*114 */      */                                                                          // 0.0
/*116 */     while (get_next_page(&block_iter, &pfn_iter, &buf, s)) {                     // 0.0
/*118 */         /* check zero page */                                                    // 0.0
/*120 */         if (is_zero_page(buf, s->page_size)) {                                   // 0.0
/*122 */             ret = write_cache(&page_desc, &pd_zero, sizeof(PageDescriptor),      // 0.0
/*124 */                               false);                                            // 0.0
/*126 */             if (ret < 0) {                                                       // 0.0
/*128 */                 dump_error(s, "dump: failed to write page desc.\n");             // 0.0
/*130 */                 goto out;                                                        // 0.0
/*132 */             }                                                                    // 0.0
/*134 */         } else {                                                                 // 0.0
/*136 */             /*                                                                   // 0.0
/*138 */              * not zero page, then:                                              // 0.0
/*140 */              * 1. compress the page                                              // 0.0
/*142 */              * 2. write the compressed page into the cache of page_data          // 0.0
/*144 */              * 3. get page desc of the compressed page and write it into the     // 0.0
/*146 */              *    cache of page_desc                                             // 0.0
/*148 */              *                                                                   // 0.0
/*150 */              * only one compression format will be used here, for                // 0.0
/*152 */              * s->flag_compress is set. But when compression fails to work,      // 0.0
/*154 */              * we fall back to save in plaintext.                                // 0.0
/*156 */              */                                                                  // 0.0
/*158 */              size_out = len_buf_out;                                             // 0.0
/*160 */              if ((s->flag_compress & DUMP_DH_COMPRESSED_ZLIB) &&                 // 0.0
/*162 */                     (compress2(buf_out, (uLongf *)&size_out, buf, s->page_size,  // 0.0
/*164 */                     Z_BEST_SPEED) == Z_OK) && (size_out < s->page_size)) {       // 0.0
/*166 */                 pd.flags = cpu_convert_to_target32(DUMP_DH_COMPRESSED_ZLIB,      // 0.0
/*168 */                                                    endian);                      // 0.0
/*170 */                 pd.size  = cpu_convert_to_target32(size_out, endian);            // 0.0
/*174 */                 ret = write_cache(&page_data, buf_out, size_out, false);         // 0.0
/*176 */                 if (ret < 0) {                                                   // 0.0
/*178 */                     dump_error(s, "dump: failed to write page data.\n");         // 0.0
/*180 */                     goto out;                                                    // 0.0
/*182 */                 }                                                                // 0.0
/*184 */ #ifdef CONFIG_LZO                                                                // 0.0
/*186 */             } else if ((s->flag_compress & DUMP_DH_COMPRESSED_LZO) &&            // 0.0
/*188 */                     (lzo1x_1_compress(buf, s->page_size, buf_out,                // 0.0
/*190 */                     (lzo_uint *)&size_out, wrkmem) == LZO_E_OK) &&               // 0.0
/*192 */                     (size_out < s->page_size)) {                                 // 0.0
/*194 */                 pd.flags = cpu_convert_to_target32(DUMP_DH_COMPRESSED_LZO,       // 0.0
/*196 */                                                    endian);                      // 0.0
/*198 */                 pd.size  = cpu_convert_to_target32(size_out, endian);            // 0.0
/*202 */                 ret = write_cache(&page_data, buf_out, size_out, false);         // 0.0
/*204 */                 if (ret < 0) {                                                   // 0.0
/*206 */                     dump_error(s, "dump: failed to write page data.\n");         // 0.0
/*208 */                     goto out;                                                    // 0.0
/*210 */                 }                                                                // 0.0
/*212 */ #endif                                                                           // 0.0
/*214 */ #ifdef CONFIG_SNAPPY                                                             // 0.0
/*216 */             } else if ((s->flag_compress & DUMP_DH_COMPRESSED_SNAPPY) &&         // 0.0
/*218 */                     (snappy_compress((char *)buf, s->page_size,                  // 0.0
/*220 */                     (char *)buf_out, &size_out) == SNAPPY_OK) &&                 // 0.0
/*222 */                     (size_out < s->page_size)) {                                 // 0.0
/*224 */                 pd.flags = cpu_convert_to_target32(                              // 0.0
/*226 */                                         DUMP_DH_COMPRESSED_SNAPPY, endian);      // 0.0
/*228 */                 pd.size  = cpu_convert_to_target32(size_out, endian);            // 0.0
/*232 */                 ret = write_cache(&page_data, buf_out, size_out, false);         // 0.0
/*234 */                 if (ret < 0) {                                                   // 0.0
/*236 */                     dump_error(s, "dump: failed to write page data.\n");         // 0.0
/*238 */                     goto out;                                                    // 0.0
/*240 */                 }                                                                // 0.0
/*242 */ #endif                                                                           // 0.0
/*244 */             } else {                                                             // 0.0
/*246 */                 /*                                                               // 0.0
/*248 */                  * fall back to save in plaintext, size_out should be            // 0.0
/*250 */                  * assigned to s->page_size                                      // 0.0
/*252 */                  */                                                              // 0.0
/*254 */                 pd.flags = cpu_convert_to_target32(0, endian);                   // 0.0
/*256 */                 size_out = s->page_size;                                         // 0.0
/*258 */                 pd.size = cpu_convert_to_target32(size_out, endian);             // 0.0
/*262 */                 ret = write_cache(&page_data, buf, s->page_size, false);         // 0.0
/*264 */                 if (ret < 0) {                                                   // 0.0
/*266 */                     dump_error(s, "dump: failed to write page data.\n");         // 0.0
/*268 */                     goto out;                                                    // 0.0
/*270 */                 }                                                                // 0.0
/*272 */             }                                                                    // 0.0
/*276 */             /* get and write page desc here */                                   // 0.0
/*278 */             pd.page_flags = cpu_convert_to_target64(0, endian);                  // 0.0
/*280 */             pd.offset = cpu_convert_to_target64(offset_data, endian);            // 0.0
/*282 */             offset_data += size_out;                                             // 0.0
/*286 */             ret = write_cache(&page_desc, &pd, sizeof(PageDescriptor), false);   // 0.0
/*288 */             if (ret < 0) {                                                       // 0.0
/*290 */                 dump_error(s, "dump: failed to write page desc.\n");             // 0.0
/*292 */                 goto out;                                                        // 0.0
/*294 */             }                                                                    // 0.0
/*296 */         }                                                                        // 0.0
/*298 */     }                                                                            // 0.0
/*302 */     ret = write_cache(&page_desc, NULL, 0, true);                                // 0.0
/*304 */     if (ret < 0) {                                                               // 0.0
/*306 */         dump_error(s, "dump: failed to sync cache for page_desc.\n");            // 0.0
/*308 */         goto out;                                                                // 0.0
/*310 */     }                                                                            // 0.0
/*312 */     ret = write_cache(&page_data, NULL, 0, true);                                // 0.0
/*314 */     if (ret < 0) {                                                               // 0.0
/*316 */         dump_error(s, "dump: failed to sync cache for page_data.\n");            // 0.0
/*318 */         goto out;                                                                // 0.0
/*320 */     }                                                                            // 0.0
/*324 */ out:                                                                             // 0.0
/*326 */     free_data_cache(&page_desc);                                                 // 0.0
/*328 */     free_data_cache(&page_data);                                                 // 0.0
/*332 */ #ifdef CONFIG_LZO                                                                // 0.0
/*334 */     g_free(wrkmem);                                                              // 0.0
/*336 */ #endif                                                                           // 0.0
/*340 */     g_free(buf_out);                                                             // 0.0
/*344 */     return ret;                                                                  // 0.0
/*346 */ }                                                                                // 0.0
