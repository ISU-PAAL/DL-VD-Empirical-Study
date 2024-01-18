// commit message qemu@6817efea3a (target=1, prob=0.7442493, correct=True): vvfat: limit number of entries in root directory in FAT12/FAT16
/*0   */ static int read_directory(BDRVVVFATState* s, int mapping_index)                 // (7) 0.04298
/*2   */ {                                                                               // (28) 0.001957
/*4   */     mapping_t* mapping = array_get(&(s->mapping), mapping_index);               // (6) 0.04492
/*6   */     direntry_t* direntry;                                                       // (16) 0.02539
/*8   */     const char* dirname = mapping->path;                                        // (19) 0.02539
/*10  */     int first_cluster = mapping->begin;                                         // (20) 0.02539
/*12  */     int parent_index = mapping->info.dir.parent_mapping_index;                  // (8) 0.04101
/*14  */     mapping_t* parent_mapping = (mapping_t*)                                    // (9) 0.03515
/*16  */         (parent_index >= 0 ? array_get(&(s->mapping), parent_index) : NULL);    // (0) 0.06054
/*18  */     int first_cluster_of_parent = parent_mapping ? parent_mapping->begin : -1;  // (3) 0.05468
/*22  */     DIR* dir=opendir(dirname);                                                  // (13) 0.0293
/*24  */     struct dirent* entry;                                                       // (23) 0.01758
/*26  */     int i;                                                                      // (25) 0.01172
/*30  */     assert(mapping->mode & MODE_DIRECTORY);                                     // (10) 0.0332
/*34  */     if(!dir) {                                                                  // (24) 0.01758
/*36  */         mapping->end = mapping->begin;                                          // (15) 0.02929
/*38  */         return -1;                                                              // (22) 0.02148
/*40  */     }                                                                           // (27) 0.007812
/*44  */     i = mapping->info.dir.first_dir_index =                                     // (12) 0.0332
/*46  */             first_cluster == 0 ? 0 : s->directory.next;                         // (5) 0.05078
/*50  */     if (first_cluster != 0) {                                                   // (17) 0.02539
/*52  */         /* create the top entries of a subdirectory */                          // (11) 0.0332
/*54  */         (void)create_short_and_long_name(s, i, ".", 1);                         // (4) 0.05468
/*56  */         (void)create_short_and_long_name(s, i, "..", 1);                        // (1) 0.05664
/*58  */     }                                                                           // (26) 0.007812
/*62  */     /* actually read the directory, and allocate the mappings */                // (14) 0.0293
/*64  */     while((entry=readdir(dir))) {                                               // (18) 0.02539
/*66  */         unsigned int length=strlen(dirname)+2+strlen(entry->d_name);            // (2) 0.05468
/*68  */         char* buffer;                                                           // (21) 0.02148
/*70  */         direntry_t* direntry;                                                   // 0.0
/*72  */         struct stat st;                                                         // 0.0
/*74  */         int is_dot=!strcmp(entry->d_name,".");                                  // 0.0
/*76  */         int is_dotdot=!strcmp(entry->d_name,"..");                              // 0.0
/*80  */         if(first_cluster == 0 && (is_dotdot || is_dot))                         // 0.0
/*82  */             continue;                                                           // 0.0
/*86  */         buffer = g_malloc(length);                                              // 0.0
/*88  */         snprintf(buffer,length,"%s/%s",dirname,entry->d_name);                  // 0.0
/*92  */         if(stat(buffer,&st)<0) {                                                // 0.0
/*94  */             g_free(buffer);                                                     // 0.0
/*96  */             continue;                                                           // 0.0
/*98  */         }                                                                       // 0.0
/*102 */         /* create directory entry for this file */                              // 0.0
/*104 */         if (!is_dot && !is_dotdot) {                                            // 0.0
/*106 */             direntry = create_short_and_long_name(s, i, entry->d_name, 0);      // 0.0
/*108 */         } else {                                                                // 0.0
/*110 */             direntry = array_get(&(s->directory), is_dot ? i : i + 1);          // 0.0
/*112 */         }                                                                       // 0.0
/*114 */         direntry->attributes=(S_ISDIR(st.st_mode)?0x10:0x20);                   // 0.0
/*116 */         direntry->reserved[0]=direntry->reserved[1]=0;                          // 0.0
/*118 */         direntry->ctime=fat_datetime(st.st_ctime,1);                            // 0.0
/*120 */         direntry->cdate=fat_datetime(st.st_ctime,0);                            // 0.0
/*122 */         direntry->adate=fat_datetime(st.st_atime,0);                            // 0.0
/*124 */         direntry->begin_hi=0;                                                   // 0.0
/*126 */         direntry->mtime=fat_datetime(st.st_mtime,1);                            // 0.0
/*128 */         direntry->mdate=fat_datetime(st.st_mtime,0);                            // 0.0
/*130 */         if(is_dotdot)                                                           // 0.0
/*132 */             set_begin_of_direntry(direntry, first_cluster_of_parent);           // 0.0
/*134 */         else if(is_dot)                                                         // 0.0
/*136 */             set_begin_of_direntry(direntry, first_cluster);                     // 0.0
/*138 */         else                                                                    // 0.0
/*140 */             direntry->begin=0; /* do that later */                              // 0.0
/*142 */         if (st.st_size > 0x7fffffff) {                                          // 0.0
/*144 */             fprintf(stderr, "File %s is larger than 2GB\n", buffer);            // 0.0
/*146 */             g_free(buffer);                                                     // 0.0
/*148 */             closedir(dir);                                                      // 0.0
/*150 */             return -2;                                                          // 0.0
/*152 */         }                                                                       // 0.0
/*154 */         direntry->size=cpu_to_le32(S_ISDIR(st.st_mode)?0:st.st_size);           // 0.0
/*158 */         /* create mapping for this file */                                      // 0.0
/*160 */         if(!is_dot && !is_dotdot && (S_ISDIR(st.st_mode) || st.st_size)) {      // 0.0
/*162 */             s->current_mapping = array_get_next(&(s->mapping));                 // 0.0
/*164 */             s->current_mapping->begin=0;                                        // 0.0
/*166 */             s->current_mapping->end=st.st_size;                                 // 0.0
/*168 */             /*                                                                  // 0.0
/*170 */              * we get the direntry of the most recent direntry, which           // 0.0
/*172 */              * contains the short name and all the relevant information.        // 0.0
/*174 */              */                                                                 // 0.0
/*176 */             s->current_mapping->dir_index=s->directory.next-1;                  // 0.0
/*178 */             s->current_mapping->first_mapping_index = -1;                       // 0.0
/*180 */             if (S_ISDIR(st.st_mode)) {                                          // 0.0
/*182 */                 s->current_mapping->mode = MODE_DIRECTORY;                      // 0.0
/*184 */                 s->current_mapping->info.dir.parent_mapping_index =             // 0.0
/*186 */                     mapping_index;                                              // 0.0
/*188 */             } else {                                                            // 0.0
/*190 */                 s->current_mapping->mode = MODE_UNDEFINED;                      // 0.0
/*192 */                 s->current_mapping->info.file.offset = 0;                       // 0.0
/*194 */             }                                                                   // 0.0
/*196 */             s->current_mapping->path=buffer;                                    // 0.0
/*198 */             s->current_mapping->read_only =                                     // 0.0
/*200 */                 (st.st_mode & (S_IWUSR | S_IWGRP | S_IWOTH)) == 0;              // 0.0
/*202 */         } else {                                                                // 0.0
/*204 */             g_free(buffer);                                                     // 0.0
/*206 */         }                                                                       // 0.0
/*208 */     }                                                                           // 0.0
/*210 */     closedir(dir);                                                              // 0.0
/*214 */     /* fill with zeroes up to the end of the cluster */                         // 0.0
/*216 */     while(s->directory.next%(0x10*s->sectors_per_cluster)) {                    // 0.0
/*218 */         direntry_t* direntry=array_get_next(&(s->directory));                   // 0.0
/*220 */         memset(direntry,0,sizeof(direntry_t));                                  // 0.0
/*222 */     }                                                                           // 0.0
/*226 */ /* TODO: if there are more entries, bootsector has to be adjusted! */           // 0.0
/*228 */ #define ROOT_ENTRIES (0x02 * 0x10 * s->sectors_per_cluster)                     // 0.0
/*230 */     if (mapping_index == 0 && s->directory.next < ROOT_ENTRIES) {               // 0.0
/*232 */         /* root directory */                                                    // 0.0
/*234 */         int cur = s->directory.next;                                            // 0.0
/*236 */         array_ensure_allocated(&(s->directory), ROOT_ENTRIES - 1);              // 0.0
/*238 */         s->directory.next = ROOT_ENTRIES;                                       // 0.0
/*240 */         memset(array_get(&(s->directory), cur), 0,                              // 0.0
/*242 */                 (ROOT_ENTRIES - cur) * sizeof(direntry_t));                     // 0.0
/*244 */     }                                                                           // 0.0
/*248 */     /* re-get the mapping, since s->mapping was possibly realloc()ed */         // 0.0
/*250 */     mapping = array_get(&(s->mapping), mapping_index);                          // 0.0
/*252 */     first_cluster += (s->directory.next - mapping->info.dir.first_dir_index)    // 0.0
/*254 */         * 0x20 / s->cluster_size;                                               // 0.0
/*256 */     mapping->end = first_cluster;                                               // 0.0
/*260 */     direntry = array_get(&(s->directory), mapping->dir_index);                  // 0.0
/*262 */     set_begin_of_direntry(direntry, mapping->begin);                            // 0.0
/*266 */     return 0;                                                                   // 0.0
/*268 */ }                                                                               // 0.0
