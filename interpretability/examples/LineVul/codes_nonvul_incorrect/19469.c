// commit message qemu@0a982b1bf3 (target=0, prob=0.7425229, correct=False): qga: Better mapping of SEEK_* in guest-file-seek
/*0   */ static void test_qga_file_write_read(gconstpointer fix)                // (8) 0.03516
/*2   */ {                                                                      // (27) 0.001953
/*4   */     const TestFixture *fixture = fix;                                  // (16) 0.02539
/*6   */     const unsigned char helloworld[] = "Hello World!\n";               // (9) 0.03516
/*8   */     const char *b64;                                                   // (22) 0.01758
/*10  */     gchar *cmd, *enc;                                                  // (21) 0.02148
/*12  */     QDict *ret, *val;                                                  // (17) 0.02344
/*14  */     int64_t id, eof;                                                   // (18) 0.02344
/*16  */     gsize count;                                                       // (24) 0.01367
/*20  */     /* open */                                                         // (25) 0.01172
/*22  */     ret = qmp_fd(fixture->fd, "{'execute': 'guest-file-open',"         // (3) 0.05273
/*24  */                  " 'arguments': { 'path': 'foo', 'mode': 'w+' } }");   // (2) 0.07422
/*26  */     g_assert_nonnull(ret);                                             // (19) 0.02344
/*28  */     qmp_assert_no_error(ret);                                          // (14) 0.02734
/*30  */     id = qdict_get_int(ret, "return");                                 // (12) 0.0332
/*32  */     QDECREF(ret);                                                      // (23) 0.01758
/*36  */     enc = g_base64_encode(helloworld, sizeof(helloworld));             // (5) 0.04492
/*38  */     /* write */                                                        // (26) 0.01172
/*40  */     cmd = g_strdup_printf("{'execute': 'guest-file-write',"            // (4) 0.04883
/*42  */                           " 'arguments': { 'handle': %" PRId64 ","     // (1) 0.08008
/*44  */                           " 'buf-b64': '%s' } }", id, enc);            // (0) 0.08398
/*46  */     ret = qmp_fd(fixture->fd, cmd);                                    // (11) 0.0332
/*48  */     g_assert_nonnull(ret);                                             // (20) 0.02344
/*50  */     qmp_assert_no_error(ret);                                          // (15) 0.02734
/*54  */     val = qdict_get_qdict(ret, "return");                              // (10) 0.03516
/*56  */     count = qdict_get_int(val, "count");                               // (13) 0.0332
/*58  */     eof = qdict_get_bool(val, "eof");                                  // (7) 0.03711
/*60  */     g_assert_cmpint(count, ==, sizeof(helloworld));                    // (6) 0.03906
/*62  */     g_assert_cmpint(eof, ==, 0);                                       // 0.0
/*64  */     QDECREF(ret);                                                      // 0.0
/*66  */     g_free(cmd);                                                       // 0.0
/*70  */     /* read (check implicit flush) */                                  // 0.0
/*72  */     cmd = g_strdup_printf("{'execute': 'guest-file-read',"             // 0.0
/*74  */                           " 'arguments': { 'handle': %" PRId64 "} }",  // 0.0
/*76  */                           id);                                         // 0.0
/*78  */     ret = qmp_fd(fixture->fd, cmd);                                    // 0.0
/*80  */     val = qdict_get_qdict(ret, "return");                              // 0.0
/*82  */     count = qdict_get_int(val, "count");                               // 0.0
/*84  */     eof = qdict_get_bool(val, "eof");                                  // 0.0
/*86  */     b64 = qdict_get_str(val, "buf-b64");                               // 0.0
/*88  */     g_assert_cmpint(count, ==, 0);                                     // 0.0
/*90  */     g_assert(eof);                                                     // 0.0
/*92  */     g_assert_cmpstr(b64, ==, "");                                      // 0.0
/*94  */     QDECREF(ret);                                                      // 0.0
/*96  */     g_free(cmd);                                                       // 0.0
/*100 */     /* seek to 0 */                                                    // 0.0
/*102 */     cmd = g_strdup_printf("{'execute': 'guest-file-seek',"             // 0.0
/*104 */                           " 'arguments': { 'handle': %" PRId64 ", "    // 0.0
/*106 */                           " 'offset': %d, 'whence': %d } }",           // 0.0
/*108 */                           id, 0, SEEK_SET);                            // 0.0
/*110 */     ret = qmp_fd(fixture->fd, cmd);                                    // 0.0
/*112 */     qmp_assert_no_error(ret);                                          // 0.0
/*114 */     val = qdict_get_qdict(ret, "return");                              // 0.0
/*116 */     count = qdict_get_int(val, "position");                            // 0.0
/*118 */     eof = qdict_get_bool(val, "eof");                                  // 0.0
/*120 */     g_assert_cmpint(count, ==, 0);                                     // 0.0
/*122 */     g_assert(!eof);                                                    // 0.0
/*124 */     QDECREF(ret);                                                      // 0.0
/*126 */     g_free(cmd);                                                       // 0.0
/*130 */     /* read */                                                         // 0.0
/*132 */     cmd = g_strdup_printf("{'execute': 'guest-file-read',"             // 0.0
/*134 */                           " 'arguments': { 'handle': %" PRId64 "} }",  // 0.0
/*136 */                           id);                                         // 0.0
/*138 */     ret = qmp_fd(fixture->fd, cmd);                                    // 0.0
/*140 */     val = qdict_get_qdict(ret, "return");                              // 0.0
/*142 */     count = qdict_get_int(val, "count");                               // 0.0
/*144 */     eof = qdict_get_bool(val, "eof");                                  // 0.0
/*146 */     b64 = qdict_get_str(val, "buf-b64");                               // 0.0
/*148 */     g_assert_cmpint(count, ==, sizeof(helloworld));                    // 0.0
/*150 */     g_assert(eof);                                                     // 0.0
/*152 */     g_assert_cmpstr(b64, ==, enc);                                     // 0.0
/*154 */     QDECREF(ret);                                                      // 0.0
/*156 */     g_free(cmd);                                                       // 0.0
/*158 */     g_free(enc);                                                       // 0.0
/*162 */     /* close */                                                        // 0.0
/*164 */     cmd = g_strdup_printf("{'execute': 'guest-file-close',"            // 0.0
/*166 */                           " 'arguments': {'handle': %" PRId64 "} }",   // 0.0
/*168 */                           id);                                         // 0.0
/*170 */     ret = qmp_fd(fixture->fd, cmd);                                    // 0.0
/*172 */     QDECREF(ret);                                                      // 0.0
/*174 */     g_free(cmd);                                                       // 0.0
/*176 */ }                                                                      // 0.0
