// commit message qemu@6817efea3a (target=1, prob=0.5463123, correct=True): vvfat: limit number of entries in root directory in FAT12/FAT16
/*0   */ static int init_directories(BDRVVVFATState* s,                                          // (12) 0.03516
/*2   */                             const char *dirname, int heads, int secs,                   // (0) 0.07813
/*4   */                             Error **errp)                                               // (1) 0.0625
/*6   */ {                                                                                       // (25) 0.001953
/*8   */     bootsector_t* bootsector;                                                           // (17) 0.02148
/*10  */     mapping_t* mapping;                                                                 // (18) 0.01758
/*12  */     unsigned int i;                                                                     // (21) 0.01367
/*14  */     unsigned int cluster;                                                               // (20) 0.01367
/*18  */     memset(&(s->first_sectors[0]),0,0x40*0x200);                                        // (6) 0.05078
/*22  */     s->cluster_size=s->sectors_per_cluster*0x200;                                       // (7) 0.04687
/*24  */     s->cluster_buffer=g_malloc(s->cluster_size);                                        // (10) 0.04297
/*28  */     /*                                                                                  // (23) 0.007812
/*30  */      * The formula: sc = spf+1+spf*spc*(512*8/fat_type),                                // (3) 0.05859
/*32  */      * where sc is sector_count,                                                        // (16) 0.02344
/*34  */      * spf is sectors_per_fat,                                                          // (15) 0.02734
/*36  */      * spc is sectors_per_clusters, and                                                 // (13) 0.03125
/*38  */      * fat_type = 12, 16 or 32.                                                         // (14) 0.0293
/*40  */      */                                                                                 // (22) 0.009766
/*42  */     i = 1+s->sectors_per_cluster*0x200*8/s->fat_type;                                   // (4) 0.05664
/*44  */     s->sectors_per_fat=(s->sector_count+i)/i; /* round up */                            // (5) 0.05078
/*48  */     s->offset_to_fat = s->offset_to_bootsector + 1;                                     // (9) 0.04297
/*50  */     s->offset_to_root_dir = s->offset_to_fat + s->sectors_per_fat * 2;                  // (2) 0.0625
/*54  */     array_init(&(s->mapping),sizeof(mapping_t));                                        // (11) 0.04102
/*56  */     array_init(&(s->directory),sizeof(direntry_t));                                     // (8) 0.04297
/*60  */     /* add volume label */                                                              // (19) 0.01563
/*62  */     {                                                                                   // (24) 0.007812
/*64  */         direntry_t* entry=array_get_next(&(s->directory));                              // 0.0
/*66  */         entry->attributes=0x28; /* archive | volume label */                            // 0.0
/*68  */         memcpy(entry->name, s->volume_label, sizeof(entry->name));                      // 0.0
/*70  */     }                                                                                   // 0.0
/*74  */     /* Now build FAT, and write back information into directory */                      // 0.0
/*76  */     init_fat(s);                                                                        // 0.0
/*80  */     s->cluster_count=sector2cluster(s, s->sector_count);                                // 0.0
/*84  */     mapping = array_get_next(&(s->mapping));                                            // 0.0
/*86  */     mapping->begin = 0;                                                                 // 0.0
/*88  */     mapping->dir_index = 0;                                                             // 0.0
/*90  */     mapping->info.dir.parent_mapping_index = -1;                                        // 0.0
/*92  */     mapping->first_mapping_index = -1;                                                  // 0.0
/*94  */     mapping->path = g_strdup(dirname);                                                  // 0.0
/*96  */     i = strlen(mapping->path);                                                          // 0.0
/*98  */     if (i > 0 && mapping->path[i - 1] == '/')                                           // 0.0
/*100 */         mapping->path[i - 1] = '\0';                                                    // 0.0
/*102 */     mapping->mode = MODE_DIRECTORY;                                                     // 0.0
/*104 */     mapping->read_only = 0;                                                             // 0.0
/*106 */     s->path = mapping->path;                                                            // 0.0
/*110 */     for (i = 0, cluster = 0; i < s->mapping.next; i++) {                                // 0.0
/*112 */         /* MS-DOS expects the FAT to be 0 for the root directory                        // 0.0
/*114 */          * (except for the media byte). */                                              // 0.0
/*116 */         /* LATER TODO: still true for FAT32? */                                         // 0.0
/*118 */         int fix_fat = (i != 0);                                                         // 0.0
/*120 */         mapping = array_get(&(s->mapping), i);                                          // 0.0
/*124 */         if (mapping->mode & MODE_DIRECTORY) {                                           // 0.0
/*126 */             mapping->begin = cluster;                                                   // 0.0
/*128 */             if(read_directory(s, i)) {                                                  // 0.0
/*130 */                 error_setg(errp, "Could not read directory %s",                         // 0.0
/*132 */                            mapping->path);                                              // 0.0
/*134 */                 return -1;                                                              // 0.0
/*136 */             }                                                                           // 0.0
/*138 */             mapping = array_get(&(s->mapping), i);                                      // 0.0
/*140 */         } else {                                                                        // 0.0
/*142 */             assert(mapping->mode == MODE_UNDEFINED);                                    // 0.0
/*144 */             mapping->mode=MODE_NORMAL;                                                  // 0.0
/*146 */             mapping->begin = cluster;                                                   // 0.0
/*148 */             if (mapping->end > 0) {                                                     // 0.0
/*150 */                 direntry_t* direntry = array_get(&(s->directory),                       // 0.0
/*152 */                         mapping->dir_index);                                            // 0.0
/*156 */                 mapping->end = cluster + 1 + (mapping->end-1)/s->cluster_size;          // 0.0
/*158 */                 set_begin_of_direntry(direntry, mapping->begin);                        // 0.0
/*160 */             } else {                                                                    // 0.0
/*162 */                 mapping->end = cluster + 1;                                             // 0.0
/*164 */                 fix_fat = 0;                                                            // 0.0
/*166 */             }                                                                           // 0.0
/*168 */         }                                                                               // 0.0
/*172 */         assert(mapping->begin < mapping->end);                                          // 0.0
/*176 */         /* next free cluster */                                                         // 0.0
/*178 */         cluster = mapping->end;                                                         // 0.0
/*182 */         if(cluster > s->cluster_count) {                                                // 0.0
/*184 */             error_setg(errp,                                                            // 0.0
/*186 */                        "Directory does not fit in FAT%d (capacity %.2f MB)",            // 0.0
/*188 */                        s->fat_type, s->sector_count / 2000.0);                          // 0.0
/*190 */             return -1;                                                                  // 0.0
/*192 */         }                                                                               // 0.0
/*196 */         /* fix fat for entry */                                                         // 0.0
/*198 */         if (fix_fat) {                                                                  // 0.0
/*200 */             int j;                                                                      // 0.0
/*202 */             for(j = mapping->begin; j < mapping->end - 1; j++)                          // 0.0
/*204 */                 fat_set(s, j, j+1);                                                     // 0.0
/*206 */             fat_set(s, mapping->end - 1, s->max_fat_value);                             // 0.0
/*208 */         }                                                                               // 0.0
/*210 */     }                                                                                   // 0.0
/*214 */     mapping = array_get(&(s->mapping), 0);                                              // 0.0
/*216 */     s->sectors_of_root_directory = mapping->end * s->sectors_per_cluster;               // 0.0
/*218 */     s->last_cluster_of_root_directory = mapping->end;                                   // 0.0
/*222 */     /* the FAT signature */                                                             // 0.0
/*224 */     fat_set(s,0,s->max_fat_value);                                                      // 0.0
/*226 */     fat_set(s,1,s->max_fat_value);                                                      // 0.0
/*230 */     s->current_mapping = NULL;                                                          // 0.0
/*234 */     bootsector = (bootsector_t *)(s->first_sectors                                      // 0.0
/*236 */                                   + s->offset_to_bootsector * 0x200);                   // 0.0
/*238 */     bootsector->jump[0]=0xeb;                                                           // 0.0
/*240 */     bootsector->jump[1]=0x3e;                                                           // 0.0
/*242 */     bootsector->jump[2]=0x90;                                                           // 0.0
/*244 */     memcpy(bootsector->name,"QEMU    ",8);                                              // 0.0
/*246 */     bootsector->sector_size=cpu_to_le16(0x200);                                         // 0.0
/*248 */     bootsector->sectors_per_cluster=s->sectors_per_cluster;                             // 0.0
/*250 */     bootsector->reserved_sectors=cpu_to_le16(1);                                        // 0.0
/*252 */     bootsector->number_of_fats=0x2; /* number of FATs */                                // 0.0
/*254 */     bootsector->root_entries=cpu_to_le16(s->sectors_of_root_directory*0x10);            // 0.0
/*256 */     bootsector->total_sectors16=s->sector_count>0xffff?0:cpu_to_le16(s->sector_count);  // 0.0
/*258 */     /* media descriptor: hard disk=0xf8, floppy=0xf0 */                                 // 0.0
/*260 */     bootsector->media_type = (s->offset_to_bootsector > 0 ? 0xf8 : 0xf0);               // 0.0
/*262 */     s->fat.pointer[0] = bootsector->media_type;                                         // 0.0
/*264 */     bootsector->sectors_per_fat=cpu_to_le16(s->sectors_per_fat);                        // 0.0
/*266 */     bootsector->sectors_per_track = cpu_to_le16(secs);                                  // 0.0
/*268 */     bootsector->number_of_heads = cpu_to_le16(heads);                                   // 0.0
/*270 */     bootsector->hidden_sectors = cpu_to_le32(s->offset_to_bootsector);                  // 0.0
/*272 */     bootsector->total_sectors=cpu_to_le32(s->sector_count>0xffff?s->sector_count:0);    // 0.0
/*276 */     /* LATER TODO: if FAT32, this is wrong */                                           // 0.0
/*278 */     /* drive_number: fda=0, hda=0x80 */                                                 // 0.0
/*280 */     bootsector->u.fat16.drive_number = s->offset_to_bootsector == 0 ? 0 : 0x80;         // 0.0
/*282 */     bootsector->u.fat16.signature=0x29;                                                 // 0.0
/*284 */     bootsector->u.fat16.id=cpu_to_le32(0xfabe1afd);                                     // 0.0
/*288 */     memcpy(bootsector->u.fat16.volume_label, s->volume_label,                           // 0.0
/*290 */            sizeof(bootsector->u.fat16.volume_label));                                   // 0.0
/*292 */     memcpy(bootsector->u.fat16.fat_type,                                                // 0.0
/*294 */            s->fat_type == 12 ? "FAT12   " : "FAT16   ", 8);                             // 0.0
/*296 */     bootsector->magic[0]=0x55; bootsector->magic[1]=0xaa;                               // 0.0
/*300 */     return 0;                                                                           // 0.0
/*302 */ }                                                                                       // 0.0
