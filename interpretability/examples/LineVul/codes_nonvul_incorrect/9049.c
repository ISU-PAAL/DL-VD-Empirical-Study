// commit message qemu@31783203c3 (target=0, prob=0.55149245, correct=False): qemu_find_file: check name as a straight path even if it has no '/'
/*0  */ char *qemu_find_file(int type, const char *name)                             // (5) 0.04787
/*2  */ {                                                                            // (27) 0.00266
/*4  */     int len;                                                                 // (21) 0.01596
/*6  */     const char *subdir;                                                      // (15) 0.02394
/*8  */     char *buf;                                                               // (20) 0.01862
/*12 */     /* If name contains path separators then try it as a straight path.  */  // (3) 0.05319
/*14 */     if ((strchr(name, '/') || strchr(name, '\\'))                            // (2) 0.06383
/*16 */         && access(name, R_OK) == 0) {                                        // (4) 0.05319
/*18 */         return g_strdup(name);                                               // (6) 0.04255
/*20 */     }                                                                        // (24) 0.01064
/*22 */     switch (type) {                                                          // (19) 0.02128
/*24 */     case QEMU_FILE_TYPE_BIOS:                                                // (7) 0.03989
/*26 */         subdir = "";                                                         // (13) 0.03191
/*28 */         break;                                                               // (16) 0.02394
/*30 */     case QEMU_FILE_TYPE_KEYMAP:                                              // (8) 0.03989
/*32 */         subdir = "keymaps/";                                                 // (9) 0.03989
/*34 */         break;                                                               // (17) 0.02394
/*36 */     default:                                                                 // (23) 0.0133
/*38 */         abort();                                                             // (18) 0.02394
/*40 */     }                                                                        // (25) 0.01064
/*42 */     len = strlen(data_dir) + strlen(name) + strlen(subdir) + 2;              // (0) 0.07447
/*44 */     buf = g_malloc0(len);                                                    // (11) 0.03457
/*46 */     snprintf(buf, len, "%s/%s%s", data_dir, subdir, name);                   // (1) 0.07181
/*48 */     if (access(buf, R_OK)) {                                                 // (10) 0.03723
/*50 */         g_free(buf);                                                         // (12) 0.03457
/*52 */         return NULL;                                                         // (14) 0.0266
/*54 */     }                                                                        // (26) 0.01064
/*56 */     return buf;                                                              // (22) 0.01596
/*58 */ }                                                                            // (28) 0.00266
