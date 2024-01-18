// commit message qemu@64a31d5c3d (target=0, prob=0.48455164, correct=True): dmg: use qemu block API
/*0   */ static int dmg_open(BlockDriverState *bs, const char *filename, int flags)  // (6) 0.03906
/*2   */ {                                                                           // (34) 0.001964
/*4   */     BDRVDMGState *s = bs->opaque;                                           // (8) 0.0332
/*6   */     off_t info_begin,info_end,last_in_offset,last_out_offset;               // (2) 0.05078
/*8   */     uint32_t count;                                                         // (26) 0.01758
/*10  */     uint32_t max_compressed_size=1,max_sectors_per_chunk=1,i;               // (0) 0.0586
/*12  */     int64_t offset;                                                         // (27) 0.01758
/*16  */     s->fd = open(filename, O_RDONLY | O_BINARY);                            // (5) 0.04492
/*18  */     if (s->fd < 0)                                                          // (19) 0.02148
/*20  */         return -errno;                                                      // (18) 0.02344
/*22  */     bs->read_only = 1;                                                      // (15) 0.02344
/*24  */     s->n_chunks = 0;                                                        // (14) 0.02344
/*26  */     s->offsets = s->lengths = s->sectors = s->sectorcounts = NULL;          // (1) 0.05078
/*30  */     /* read offset of info blocks */                                        // (20) 0.01953
/*32  */     offset = lseek(s->fd, -0x1d8, SEEK_END);                                // (4) 0.04687
/*34  */     if (offset < 0) {                                                       // (25) 0.01953
/*36  */         goto fail;                                                          // (24) 0.01953
/*38  */     }                                                                       // (33) 0.007812
/*42  */     info_begin = read_off(s->fd, offset);                                   // (10) 0.0332
/*44  */     if (info_begin == 0) {                                                  // (17) 0.02344
/*46  */ 	goto fail;                                                                 // (29) 0.009765
/*48  */     }                                                                       // (31) 0.007812
/*52  */     if (read_uint32(s->fd, info_begin) != 0x100) {                          // (3) 0.04687
/*54  */         goto fail;                                                          // (23) 0.01953
/*56  */     }                                                                       // (30) 0.007812
/*60  */     count = read_uint32(s->fd, info_begin + 4);                             // (7) 0.03906
/*62  */     if (count == 0) {                                                       // (21) 0.01953
/*64  */         goto fail;                                                          // (22) 0.01953
/*66  */     }                                                                       // (32) 0.007812
/*68  */     info_end = info_begin + count;                                          // (13) 0.02539
/*72  */     offset = info_begin + 0x100;                                            // (12) 0.02539
/*76  */     /* read offsets */                                                      // (28) 0.01367
/*78  */     last_in_offset = last_out_offset = 0;                                   // (9) 0.0332
/*80  */     while (offset < info_end) {                                             // (16) 0.02344
/*82  */         uint32_t type;                                                      // (11) 0.02539
/*86  */ 	count = read_uint32(s->fd, offset);                                        // 0.0
/*88  */ 	if(count==0)                                                               // 0.0
/*90  */ 	    goto fail;                                                             // 0.0
/*92  */         offset += 4;                                                        // 0.0
/*96  */ 	type = read_uint32(s->fd, offset);                                         // 0.0
/*98  */ 	if (type == 0x6d697368 && count >= 244) {                                  // 0.0
/*100 */ 	    int new_size, chunk_count;                                             // 0.0
/*104 */             offset += 4;                                                    // 0.0
/*106 */             offset += 200;                                                  // 0.0
/*110 */ 	    chunk_count = (count-204)/40;                                          // 0.0
/*112 */ 	    new_size = sizeof(uint64_t) * (s->n_chunks + chunk_count);             // 0.0
/*114 */ 	    s->types = qemu_realloc(s->types, new_size/2);                         // 0.0
/*116 */ 	    s->offsets = qemu_realloc(s->offsets, new_size);                       // 0.0
/*118 */ 	    s->lengths = qemu_realloc(s->lengths, new_size);                       // 0.0
/*120 */ 	    s->sectors = qemu_realloc(s->sectors, new_size);                       // 0.0
/*122 */ 	    s->sectorcounts = qemu_realloc(s->sectorcounts, new_size);             // 0.0
/*126 */ 	    for(i=s->n_chunks;i<s->n_chunks+chunk_count;i++) {                     // 0.0
/*128 */ 		s->types[i] = read_uint32(s->fd, offset);                                 // 0.0
/*130 */ 		offset += 4;                                                              // 0.0
/*132 */ 		if(s->types[i]!=0x80000005 && s->types[i]!=1 && s->types[i]!=2) {         // 0.0
/*134 */ 		    if(s->types[i]==0xffffffff) {                                         // 0.0
/*136 */ 			last_in_offset = s->offsets[i-1]+s->lengths[i-1];                        // 0.0
/*138 */ 			last_out_offset = s->sectors[i-1]+s->sectorcounts[i-1];                  // 0.0
/*140 */ 		    }                                                                     // 0.0
/*142 */ 		    chunk_count--;                                                        // 0.0
/*144 */ 		    i--;                                                                  // 0.0
/*146 */ 		    offset += 36;                                                         // 0.0
/*148 */ 		    continue;                                                             // 0.0
/*150 */ 		}                                                                         // 0.0
/*152 */ 		offset += 4;                                                              // 0.0
/*156 */ 		s->sectors[i] = last_out_offset+read_off(s->fd, offset);                  // 0.0
/*158 */ 		offset += 8;                                                              // 0.0
/*162 */ 		s->sectorcounts[i] = read_off(s->fd, offset);                             // 0.0
/*164 */ 		offset += 8;                                                              // 0.0
/*168 */ 		s->offsets[i] = last_in_offset+read_off(s->fd, offset);                   // 0.0
/*170 */ 		offset += 8;                                                              // 0.0
/*174 */ 		s->lengths[i] = read_off(s->fd, offset);                                  // 0.0
/*176 */ 		offset += 8;                                                              // 0.0
/*180 */ 		if(s->lengths[i]>max_compressed_size)                                     // 0.0
/*182 */ 		    max_compressed_size = s->lengths[i];                                  // 0.0
/*184 */ 		if(s->sectorcounts[i]>max_sectors_per_chunk)                              // 0.0
/*186 */ 		    max_sectors_per_chunk = s->sectorcounts[i];                           // 0.0
/*188 */ 	    }                                                                      // 0.0
/*190 */ 	    s->n_chunks+=chunk_count;                                              // 0.0
/*192 */ 	}                                                                          // 0.0
/*194 */     }                                                                       // 0.0
/*198 */     /* initialize zlib engine */                                            // 0.0
/*200 */     s->compressed_chunk = qemu_malloc(max_compressed_size+1);               // 0.0
/*202 */     s->uncompressed_chunk = qemu_malloc(512*max_sectors_per_chunk);         // 0.0
/*204 */     if(inflateInit(&s->zstream) != Z_OK)                                    // 0.0
/*206 */ 	goto fail;                                                                 // 0.0
/*210 */     s->current_chunk = s->n_chunks;                                         // 0.0
/*214 */     return 0;                                                               // 0.0
/*216 */ fail:                                                                       // 0.0
/*218 */     close(s->fd);                                                           // 0.0
/*220 */     return -1;                                                              // 0.0
/*222 */ }                                                                           // 0.0
