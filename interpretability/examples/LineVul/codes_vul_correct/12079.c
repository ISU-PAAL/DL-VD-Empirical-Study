// commit message qemu@c951d9a675 (target=1, prob=0.5077772, correct=True): monitor: Fix file_completion() to check for stat() failure
/*0   */ static void file_completion(const char *input)                                 // (16) 0.02344
/*2   */ {                                                                              // (32) 0.001953
/*4   */     DIR *ffs;                                                                  // (20) 0.01758
/*6   */     struct dirent *d;                                                          // (21) 0.01758
/*8   */     char path[1024];                                                           // (25) 0.01562
/*10  */     char file[1024], file_prefix[1024];                                        // (13) 0.02734
/*12  */     int input_path_len;                                                        // (19) 0.01953
/*14  */     const char *p;                                                             // (26) 0.01562
/*18  */     p = strrchr(input, '/');                                                   // (12) 0.02734
/*20  */     if (!p) {                                                                  // (27) 0.01562
/*22  */         input_path_len = 0;                                                    // (11) 0.0293
/*24  */         pstrcpy(file_prefix, sizeof(file_prefix), input);                      // (3) 0.04687
/*26  */         pstrcpy(path, sizeof(path), ".");                                      // (7) 0.04102
/*28  */     } else {                                                                   // (29) 0.01172
/*30  */         input_path_len = p - input + 1;                                        // (9) 0.03711
/*32  */         memcpy(path, input, input_path_len);                                   // (6) 0.04102
/*34  */         if (input_path_len > sizeof(path) - 1)                                 // (5) 0.04297
/*36  */             input_path_len = sizeof(path) - 1;                                 // (4) 0.04687
/*38  */         path[input_path_len] = '\0';                                           // (8) 0.03906
/*40  */         pstrcpy(file_prefix, sizeof(file_prefix), p + 1);                      // (1) 0.05078
/*42  */     }                                                                          // (30) 0.007812
/*44  */ #ifdef DEBUG_COMPLETION                                                        // (28) 0.01367
/*46  */     monitor_printf(cur_mon, "input='%s' path='%s' prefix='%s'\n",              // (0) 0.05859
/*48  */                    input, path, file_prefix);                                  // (2) 0.05078
/*50  */ #endif                                                                         // (31) 0.003906
/*52  */     ffs = opendir(path);                                                       // (17) 0.02344
/*54  */     if (!ffs)                                                                  // (24) 0.01562
/*56  */         return;                                                                // (22) 0.01758
/*58  */     for(;;) {                                                                  // (23) 0.01562
/*60  */         struct stat sb;                                                        // (15) 0.02344
/*62  */         d = readdir(ffs);                                                      // (10) 0.0293
/*64  */         if (!d)                                                                // (18) 0.02148
/*66  */             break;                                                             // (14) 0.02539
/*70  */         if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {     // 0.0
/*72  */             continue;                                                          // 0.0
/*74  */         }                                                                      // 0.0
/*78  */         if (strstart(d->d_name, file_prefix, NULL)) {                          // 0.0
/*80  */             memcpy(file, input, input_path_len);                               // 0.0
/*82  */             if (input_path_len < sizeof(file))                                 // 0.0
/*84  */                 pstrcpy(file + input_path_len, sizeof(file) - input_path_len,  // 0.0
/*86  */                         d->d_name);                                            // 0.0
/*88  */             /* stat the file to find out if it's a directory.                  // 0.0
/*90  */              * In that case add a slash to speed up typing long paths          // 0.0
/*92  */              */                                                                // 0.0
/*94  */             stat(file, &sb);                                                   // 0.0
/*96  */             if(S_ISDIR(sb.st_mode))                                            // 0.0
/*98  */                 pstrcat(file, sizeof(file), "/");                              // 0.0
/*100 */             readline_add_completion(cur_mon->rs, file);                        // 0.0
/*102 */         }                                                                      // 0.0
/*104 */     }                                                                          // 0.0
/*106 */     closedir(ffs);                                                             // 0.0
/*108 */ }                                                                              // 0.0
