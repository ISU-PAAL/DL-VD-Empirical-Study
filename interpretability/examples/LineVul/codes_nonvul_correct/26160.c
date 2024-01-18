// commit message qemu@943cec86d0 (target=0, prob=0.09943148, correct=True): nbd: Avoid magic number for NBD max name size
/*0   */ static int nbd_receive_list(QIOChannel *ioc, char **name, Error **errp)         // (2) 0.05078
/*2   */ {                                                                               // (32) 0.001953
/*4   */     uint64_t magic;                                                             // (22) 0.01758
/*6   */     uint32_t opt;                                                               // (24) 0.01758
/*8   */     uint32_t type;                                                              // (23) 0.01758
/*10  */     uint32_t len;                                                               // (21) 0.01758
/*12  */     uint32_t namelen;                                                           // (15) 0.02148
/*14  */     int error;                                                                  // (26) 0.01172
/*18  */     *name = NULL;                                                               // (25) 0.01563
/*20  */     if (read_sync(ioc, &magic, sizeof(magic)) != sizeof(magic)) {               // (3) 0.04883
/*22  */         error_setg(errp, "failed to read list option magic");                   // (6) 0.04492
/*24  */         return -1;                                                              // (18) 0.02148
/*26  */     }                                                                           // (27) 0.007812
/*28  */     magic = be64_to_cpu(magic);                                                 // (12) 0.02734
/*30  */     if (magic != NBD_REP_MAGIC) {                                               // (10) 0.03125
/*32  */         error_setg(errp, "Unexpected option list magic");                       // (8) 0.04297
/*34  */         return -1;                                                              // (16) 0.02148
/*36  */     }                                                                           // (30) 0.007812
/*38  */     if (read_sync(ioc, &opt, sizeof(opt)) != sizeof(opt)) {                     // (5) 0.04883
/*40  */         error_setg(errp, "failed to read list option");                         // (9) 0.04297
/*42  */         return -1;                                                              // (19) 0.02148
/*44  */     }                                                                           // (28) 0.007812
/*46  */     opt = be32_to_cpu(opt);                                                     // (14) 0.02734
/*48  */     if (opt != NBD_OPT_LIST) {                                                  // (11) 0.03125
/*50  */         error_setg(errp, "Unexpected option type %" PRIx32 " expected %x",      // (0) 0.06055
/*52  */                    opt, NBD_OPT_LIST);                                          // (1) 0.05469
/*54  */         return -1;                                                              // (20) 0.02148
/*56  */     }                                                                           // (31) 0.007812
/*60  */     if (read_sync(ioc, &type, sizeof(type)) != sizeof(type)) {                  // (4) 0.04883
/*62  */         error_setg(errp, "failed to read list option type");                    // (7) 0.04492
/*64  */         return -1;                                                              // (17) 0.02148
/*66  */     }                                                                           // (29) 0.007812
/*68  */     type = be32_to_cpu(type);                                                   // (13) 0.02734
/*70  */     error = nbd_handle_reply_err(ioc, opt, type, errp);                         // 0.0
/*72  */     if (error <= 0) {                                                           // 0.0
/*74  */         return error;                                                           // 0.0
/*76  */     }                                                                           // 0.0
/*80  */     if (read_sync(ioc, &len, sizeof(len)) != sizeof(len)) {                     // 0.0
/*82  */         error_setg(errp, "failed to read option length");                       // 0.0
/*84  */         return -1;                                                              // 0.0
/*86  */     }                                                                           // 0.0
/*88  */     len = be32_to_cpu(len);                                                     // 0.0
/*92  */     if (type == NBD_REP_ACK) {                                                  // 0.0
/*94  */         if (len != 0) {                                                         // 0.0
/*96  */             error_setg(errp, "length too long for option end");                 // 0.0
/*98  */             return -1;                                                          // 0.0
/*100 */         }                                                                       // 0.0
/*102 */     } else if (type == NBD_REP_SERVER) {                                        // 0.0
/*104 */         if (len < sizeof(namelen) || len > NBD_MAX_BUFFER_SIZE) {               // 0.0
/*106 */             error_setg(errp, "incorrect option length");                        // 0.0
/*108 */             return -1;                                                          // 0.0
/*110 */         }                                                                       // 0.0
/*112 */         if (read_sync(ioc, &namelen, sizeof(namelen)) != sizeof(namelen)) {     // 0.0
/*114 */             error_setg(errp, "failed to read option name length");              // 0.0
/*116 */             return -1;                                                          // 0.0
/*118 */         }                                                                       // 0.0
/*120 */         namelen = be32_to_cpu(namelen);                                         // 0.0
/*122 */         len -= sizeof(namelen);                                                 // 0.0
/*124 */         if (len < namelen) {                                                    // 0.0
/*126 */             error_setg(errp, "incorrect option name length");                   // 0.0
/*128 */             return -1;                                                          // 0.0
/*130 */         }                                                                       // 0.0
/*132 */         if (namelen > 255) {                                                    // 0.0
/*134 */             error_setg(errp, "export name length too long %" PRIu32, namelen);  // 0.0
/*136 */             return -1;                                                          // 0.0
/*138 */         }                                                                       // 0.0
/*142 */         *name = g_new0(char, namelen + 1);                                      // 0.0
/*144 */         if (read_sync(ioc, *name, namelen) != namelen) {                        // 0.0
/*146 */             error_setg(errp, "failed to read export name");                     // 0.0
/*148 */             g_free(*name);                                                      // 0.0
/*150 */             *name = NULL;                                                       // 0.0
/*152 */             return -1;                                                          // 0.0
/*154 */         }                                                                       // 0.0
/*156 */         (*name)[namelen] = '\0';                                                // 0.0
/*158 */         len -= namelen;                                                         // 0.0
/*160 */         if (len) {                                                              // 0.0
/*162 */             char *buf = g_malloc(len + 1);                                      // 0.0
/*164 */             if (read_sync(ioc, buf, len) != len) {                              // 0.0
/*166 */                 error_setg(errp, "failed to read export description");          // 0.0
/*168 */                 g_free(*name);                                                  // 0.0
/*170 */                 g_free(buf);                                                    // 0.0
/*172 */                 *name = NULL;                                                   // 0.0
/*174 */                 return -1;                                                      // 0.0
/*176 */             }                                                                   // 0.0
/*178 */             buf[len] = '\0';                                                    // 0.0
/*180 */             TRACE("Ignoring export description: %s", buf);                      // 0.0
/*182 */             g_free(buf);                                                        // 0.0
/*184 */         }                                                                       // 0.0
/*186 */     } else {                                                                    // 0.0
/*188 */         error_setg(errp, "Unexpected reply type %" PRIx32 " expected %x",       // 0.0
/*190 */                    type, NBD_REP_SERVER);                                       // 0.0
/*192 */         return -1;                                                              // 0.0
/*194 */     }                                                                           // 0.0
/*196 */     return 1;                                                                   // 0.0
/*198 */ }                                                                               // 0.0
