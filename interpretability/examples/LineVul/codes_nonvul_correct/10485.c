// commit message qemu@ad11ad7774 (target=0, prob=0.36870492, correct=True): linux-user: Remove redundant null check and replace free by g_free
/*0   */ static abi_long do_ioctl_dm(const IOCTLEntry *ie, uint8_t *buf_temp, int fd,         // (1) 0.06638
/*2   */                             abi_long cmd, abi_long arg)                              // (0) 0.07612
/*4   */ {                                                                                    // (30) 0.002101
/*6   */     void *argptr;                                                                    // (26) 0.01561
/*8   */     struct dm_ioctl *host_dm;                                                        // (13) 0.02733
/*10  */     abi_long guest_data;                                                             // (16) 0.02147
/*12  */     uint32_t guest_data_size;                                                        // (15) 0.02537
/*14  */     int target_size;                                                                 // (25) 0.01562
/*16  */     const argtype *arg_type = ie->arg_type;                                          // (9) 0.03318
/*18  */     abi_long ret;                                                                    // (22) 0.01757
/*20  */     void *big_buf = NULL;                                                            // (18) 0.02147
/*22  */     char *host_data;                                                                 // (23) 0.01757
/*26  */     arg_type++;                                                                      // (27) 0.01366
/*28  */     target_size = thunk_type_size(arg_type, 0);                                      // (5) 0.03904
/*30  */     argptr = lock_user(VERIFY_READ, arg, target_size, 1);                            // (4) 0.04684
/*32  */     if (!argptr) {                                                                   // (24) 0.01757
/*34  */         ret = -TARGET_EFAULT;                                                        // (10) 0.03123
/*36  */         goto out;                                                                    // (20) 0.01952
/*38  */     }                                                                                // (28) 0.007807
/*40  */     thunk_convert(buf_temp, argptr, arg_type, THUNK_HOST);                           // (3) 0.0527
/*42  */     unlock_user(argptr, arg, 0);                                                     // (12) 0.0274
/*46  */     /* buf_temp is too small, so fetch things into a bigger buffer */                // (6) 0.03708
/*48  */     big_buf = g_malloc0(((struct dm_ioctl*)buf_temp)->data_size * 2);                // (2) 0.06246
/*50  */     memcpy(big_buf, buf_temp, target_size);                                          // (7) 0.03708
/*52  */     buf_temp = big_buf;                                                              // (19) 0.02147
/*54  */     host_dm = big_buf;                                                               // (17) 0.02147
/*58  */     guest_data = arg + host_dm->data_start;                                          // (8) 0.03318
/*60  */     if ((guest_data - arg) < 0) {                                                    // (11) 0.03123
/*62  */         ret = -EINVAL;                                                               // (14) 0.02732
/*64  */         goto out;                                                                    // (21) 0.01952
/*66  */     }                                                                                // (29) 0.007807
/*68  */     guest_data_size = host_dm->data_size - host_dm->data_start;                      // 0.0
/*70  */     host_data = (char*)host_dm + host_dm->data_start;                                // 0.0
/*74  */     argptr = lock_user(VERIFY_READ, guest_data, guest_data_size, 1);                 // 0.0
/*76  */     switch (ie->host_cmd) {                                                          // 0.0
/*78  */     case DM_REMOVE_ALL:                                                              // 0.0
/*80  */     case DM_LIST_DEVICES:                                                            // 0.0
/*82  */     case DM_DEV_CREATE:                                                              // 0.0
/*84  */     case DM_DEV_REMOVE:                                                              // 0.0
/*86  */     case DM_DEV_SUSPEND:                                                             // 0.0
/*88  */     case DM_DEV_STATUS:                                                              // 0.0
/*90  */     case DM_DEV_WAIT:                                                                // 0.0
/*92  */     case DM_TABLE_STATUS:                                                            // 0.0
/*94  */     case DM_TABLE_CLEAR:                                                             // 0.0
/*96  */     case DM_TABLE_DEPS:                                                              // 0.0
/*98  */     case DM_LIST_VERSIONS:                                                           // 0.0
/*100 */         /* no input data */                                                          // 0.0
/*102 */         break;                                                                       // 0.0
/*104 */     case DM_DEV_RENAME:                                                              // 0.0
/*106 */     case DM_DEV_SET_GEOMETRY:                                                        // 0.0
/*108 */         /* data contains only strings */                                             // 0.0
/*110 */         memcpy(host_data, argptr, guest_data_size);                                  // 0.0
/*112 */         break;                                                                       // 0.0
/*114 */     case DM_TARGET_MSG:                                                              // 0.0
/*116 */         memcpy(host_data, argptr, guest_data_size);                                  // 0.0
/*118 */         *(uint64_t*)host_data = tswap64(*(uint64_t*)argptr);                         // 0.0
/*120 */         break;                                                                       // 0.0
/*122 */     case DM_TABLE_LOAD:                                                              // 0.0
/*124 */     {                                                                                // 0.0
/*126 */         void *gspec = argptr;                                                        // 0.0
/*128 */         void *cur_data = host_data;                                                  // 0.0
/*130 */         const argtype arg_type[] = { MK_STRUCT(STRUCT_dm_target_spec) };             // 0.0
/*132 */         int spec_size = thunk_type_size(arg_type, 0);                                // 0.0
/*134 */         int i;                                                                       // 0.0
/*138 */         for (i = 0; i < host_dm->target_count; i++) {                                // 0.0
/*140 */             struct dm_target_spec *spec = cur_data;                                  // 0.0
/*142 */             uint32_t next;                                                           // 0.0
/*144 */             int slen;                                                                // 0.0
/*148 */             thunk_convert(spec, gspec, arg_type, THUNK_HOST);                        // 0.0
/*150 */             slen = strlen((char*)gspec + spec_size) + 1;                             // 0.0
/*152 */             next = spec->next;                                                       // 0.0
/*154 */             spec->next = sizeof(*spec) + slen;                                       // 0.0
/*156 */             strcpy((char*)&spec[1], gspec + spec_size);                              // 0.0
/*158 */             gspec += next;                                                           // 0.0
/*160 */             cur_data += spec->next;                                                  // 0.0
/*162 */         }                                                                            // 0.0
/*164 */         break;                                                                       // 0.0
/*166 */     }                                                                                // 0.0
/*168 */     default:                                                                         // 0.0
/*170 */         ret = -TARGET_EINVAL;                                                        // 0.0
/*172 */         goto out;                                                                    // 0.0
/*174 */     }                                                                                // 0.0
/*176 */     unlock_user(argptr, guest_data, 0);                                              // 0.0
/*180 */     ret = get_errno(ioctl(fd, ie->host_cmd, buf_temp));                              // 0.0
/*182 */     if (!is_error(ret)) {                                                            // 0.0
/*184 */         guest_data = arg + host_dm->data_start;                                      // 0.0
/*186 */         guest_data_size = host_dm->data_size - host_dm->data_start;                  // 0.0
/*188 */         argptr = lock_user(VERIFY_WRITE, guest_data, guest_data_size, 0);            // 0.0
/*190 */         switch (ie->host_cmd) {                                                      // 0.0
/*192 */         case DM_REMOVE_ALL:                                                          // 0.0
/*194 */         case DM_DEV_CREATE:                                                          // 0.0
/*196 */         case DM_DEV_REMOVE:                                                          // 0.0
/*198 */         case DM_DEV_RENAME:                                                          // 0.0
/*200 */         case DM_DEV_SUSPEND:                                                         // 0.0
/*202 */         case DM_DEV_STATUS:                                                          // 0.0
/*204 */         case DM_TABLE_LOAD:                                                          // 0.0
/*206 */         case DM_TABLE_CLEAR:                                                         // 0.0
/*208 */         case DM_TARGET_MSG:                                                          // 0.0
/*210 */         case DM_DEV_SET_GEOMETRY:                                                    // 0.0
/*212 */             /* no return data */                                                     // 0.0
/*214 */             break;                                                                   // 0.0
/*216 */         case DM_LIST_DEVICES:                                                        // 0.0
/*218 */         {                                                                            // 0.0
/*220 */             struct dm_name_list *nl = (void*)host_dm + host_dm->data_start;          // 0.0
/*222 */             uint32_t remaining_data = guest_data_size;                               // 0.0
/*224 */             void *cur_data = argptr;                                                 // 0.0
/*226 */             const argtype arg_type[] = { MK_STRUCT(STRUCT_dm_name_list) };           // 0.0
/*228 */             int nl_size = 12; /* can't use thunk_size due to alignment */            // 0.0
/*232 */             while (1) {                                                              // 0.0
/*234 */                 uint32_t next = nl->next;                                            // 0.0
/*236 */                 if (next) {                                                          // 0.0
/*238 */                     nl->next = nl_size + (strlen(nl->name) + 1);                     // 0.0
/*240 */                 }                                                                    // 0.0
/*242 */                 if (remaining_data < nl->next) {                                     // 0.0
/*244 */                     host_dm->flags |= DM_BUFFER_FULL_FLAG;                           // 0.0
/*246 */                     break;                                                           // 0.0
/*248 */                 }                                                                    // 0.0
/*250 */                 thunk_convert(cur_data, nl, arg_type, THUNK_TARGET);                 // 0.0
/*252 */                 strcpy(cur_data + nl_size, nl->name);                                // 0.0
/*254 */                 cur_data += nl->next;                                                // 0.0
/*256 */                 remaining_data -= nl->next;                                          // 0.0
/*258 */                 if (!next) {                                                         // 0.0
/*260 */                     break;                                                           // 0.0
/*262 */                 }                                                                    // 0.0
/*264 */                 nl = (void*)nl + next;                                               // 0.0
/*266 */             }                                                                        // 0.0
/*268 */             break;                                                                   // 0.0
/*270 */         }                                                                            // 0.0
/*272 */         case DM_DEV_WAIT:                                                            // 0.0
/*274 */         case DM_TABLE_STATUS:                                                        // 0.0
/*276 */         {                                                                            // 0.0
/*278 */             struct dm_target_spec *spec = (void*)host_dm + host_dm->data_start;      // 0.0
/*280 */             void *cur_data = argptr;                                                 // 0.0
/*282 */             const argtype arg_type[] = { MK_STRUCT(STRUCT_dm_target_spec) };         // 0.0
/*284 */             int spec_size = thunk_type_size(arg_type, 0);                            // 0.0
/*286 */             int i;                                                                   // 0.0
/*290 */             for (i = 0; i < host_dm->target_count; i++) {                            // 0.0
/*292 */                 uint32_t next = spec->next;                                          // 0.0
/*294 */                 int slen = strlen((char*)&spec[1]) + 1;                              // 0.0
/*296 */                 spec->next = (cur_data - argptr) + spec_size + slen;                 // 0.0
/*298 */                 if (guest_data_size < spec->next) {                                  // 0.0
/*300 */                     host_dm->flags |= DM_BUFFER_FULL_FLAG;                           // 0.0
/*302 */                     break;                                                           // 0.0
/*304 */                 }                                                                    // 0.0
/*306 */                 thunk_convert(cur_data, spec, arg_type, THUNK_TARGET);               // 0.0
/*308 */                 strcpy(cur_data + spec_size, (char*)&spec[1]);                       // 0.0
/*310 */                 cur_data = argptr + spec->next;                                      // 0.0
/*312 */                 spec = (void*)host_dm + host_dm->data_start + next;                  // 0.0
/*314 */             }                                                                        // 0.0
/*316 */             break;                                                                   // 0.0
/*318 */         }                                                                            // 0.0
/*320 */         case DM_TABLE_DEPS:                                                          // 0.0
/*322 */         {                                                                            // 0.0
/*324 */             void *hdata = (void*)host_dm + host_dm->data_start;                      // 0.0
/*326 */             int count = *(uint32_t*)hdata;                                           // 0.0
/*328 */             uint64_t *hdev = hdata + 8;                                              // 0.0
/*330 */             uint64_t *gdev = argptr + 8;                                             // 0.0
/*332 */             int i;                                                                   // 0.0
/*336 */             *(uint32_t*)argptr = tswap32(count);                                     // 0.0
/*338 */             for (i = 0; i < count; i++) {                                            // 0.0
/*340 */                 *gdev = tswap64(*hdev);                                              // 0.0
/*342 */                 gdev++;                                                              // 0.0
/*344 */                 hdev++;                                                              // 0.0
/*346 */             }                                                                        // 0.0
/*348 */             break;                                                                   // 0.0
/*350 */         }                                                                            // 0.0
/*352 */         case DM_LIST_VERSIONS:                                                       // 0.0
/*354 */         {                                                                            // 0.0
/*356 */             struct dm_target_versions *vers = (void*)host_dm + host_dm->data_start;  // 0.0
/*358 */             uint32_t remaining_data = guest_data_size;                               // 0.0
/*360 */             void *cur_data = argptr;                                                 // 0.0
/*362 */             const argtype arg_type[] = { MK_STRUCT(STRUCT_dm_target_versions) };     // 0.0
/*364 */             int vers_size = thunk_type_size(arg_type, 0);                            // 0.0
/*368 */             while (1) {                                                              // 0.0
/*370 */                 uint32_t next = vers->next;                                          // 0.0
/*372 */                 if (next) {                                                          // 0.0
/*374 */                     vers->next = vers_size + (strlen(vers->name) + 1);               // 0.0
/*376 */                 }                                                                    // 0.0
/*378 */                 if (remaining_data < vers->next) {                                   // 0.0
/*380 */                     host_dm->flags |= DM_BUFFER_FULL_FLAG;                           // 0.0
/*382 */                     break;                                                           // 0.0
/*384 */                 }                                                                    // 0.0
/*386 */                 thunk_convert(cur_data, vers, arg_type, THUNK_TARGET);               // 0.0
/*388 */                 strcpy(cur_data + vers_size, vers->name);                            // 0.0
/*390 */                 cur_data += vers->next;                                              // 0.0
/*392 */                 remaining_data -= vers->next;                                        // 0.0
/*394 */                 if (!next) {                                                         // 0.0
/*396 */                     break;                                                           // 0.0
/*398 */                 }                                                                    // 0.0
/*400 */                 vers = (void*)vers + next;                                           // 0.0
/*402 */             }                                                                        // 0.0
/*404 */             break;                                                                   // 0.0
/*406 */         }                                                                            // 0.0
/*408 */         default:                                                                     // 0.0
/*410 */             ret = -TARGET_EINVAL;                                                    // 0.0
/*412 */             goto out;                                                                // 0.0
/*414 */         }                                                                            // 0.0
/*416 */         unlock_user(argptr, guest_data, guest_data_size);                            // 0.0
/*420 */         argptr = lock_user(VERIFY_WRITE, arg, target_size, 0);                       // 0.0
/*422 */         if (!argptr) {                                                               // 0.0
/*424 */             ret = -TARGET_EFAULT;                                                    // 0.0
/*426 */             goto out;                                                                // 0.0
/*428 */         }                                                                            // 0.0
/*430 */         thunk_convert(argptr, buf_temp, arg_type, THUNK_TARGET);                     // 0.0
/*432 */         unlock_user(argptr, arg, target_size);                                       // 0.0
/*434 */     }                                                                                // 0.0
/*436 */ out:                                                                                 // 0.0
/*438 */     if (big_buf) {                                                                   // 0.0
/*440 */         free(big_buf);                                                               // 0.0
/*442 */     }                                                                                // 0.0
/*444 */     return ret;                                                                      // 0.0
/*446 */ }                                                                                    // 0.0
