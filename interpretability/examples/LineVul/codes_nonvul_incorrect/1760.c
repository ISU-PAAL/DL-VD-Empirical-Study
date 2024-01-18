// commit message qemu@aaf89c8a49 (target=0, prob=0.74928415, correct=False): test: port postcopy test to ppc64
/*0   */ static void test_migrate(void)                                              // (15) 0.01758
/*2   */ {                                                                           // (20) 0.001953
/*4   */     char *uri = g_strdup_printf("unix:%s/migsocket", tmpfs);                // (6) 0.05469
/*6   */     QTestState *global = global_qtest, *from, *to;                          // (11) 0.03906
/*8   */     unsigned char dest_byte_a, dest_byte_b, dest_byte_c, dest_byte_d;       // (5) 0.05664
/*10  */     gchar *cmd;                                                             // (19) 0.01563
/*12  */     QDict *rsp;                                                             // (14) 0.01953
/*16  */     char *bootpath = g_strdup_printf("%s/bootsect", tmpfs);                 // (10) 0.04883
/*18  */     FILE *bootfile = fopen(bootpath, "wb");                                 // (12) 0.0332
/*22  */     got_stop = false;                                                       // (17) 0.01758
/*24  */     g_assert_cmpint(fwrite(bootsect, 512, 1, bootfile), ==, 1);             // (9) 0.05273
/*26  */     fclose(bootfile);                                                       // (18) 0.01758
/*30  */     cmd = g_strdup_printf("-machine accel=kvm:tcg -m 150M"                  // (7) 0.05469
/*32  */                           " -name pcsource,debug-threads=on"                // (1) 0.07617
/*34  */                           " -serial file:%s/src_serial"                     // (2) 0.07227
/*36  */                           " -drive file=%s,format=raw",                     // (3) 0.07227
/*38  */                           tmpfs, bootpath);                                 // (4) 0.06055
/*40  */     from = qtest_start(cmd);                                                // (13) 0.02344
/*42  */     g_free(cmd);                                                            // (16) 0.01758
/*46  */     cmd = g_strdup_printf("-machine accel=kvm:tcg -m 150M"                  // (8) 0.05469
/*48  */                           " -name pcdest,debug-threads=on"                  // (0) 0.07617
/*50  */                           " -serial file:%s/dest_serial"                    // 0.0
/*52  */                           " -drive file=%s,format=raw"                      // 0.0
/*54  */                           " -incoming %s",                                  // 0.0
/*56  */                           tmpfs, bootpath, uri);                            // 0.0
/*58  */     to = qtest_init(cmd);                                                   // 0.0
/*60  */     g_free(cmd);                                                            // 0.0
/*64  */     global_qtest = from;                                                    // 0.0
/*66  */     rsp = qmp("{ 'execute': 'migrate-set-capabilities',"                    // 0.0
/*68  */                   "'arguments': { "                                         // 0.0
/*70  */                       "'capabilities': [ {"                                 // 0.0
/*72  */                           "'capability': 'postcopy-ram',"                   // 0.0
/*74  */                           "'state': true } ] } }");                         // 0.0
/*76  */     g_assert(qdict_haskey(rsp, "return"));                                  // 0.0
/*78  */     QDECREF(rsp);                                                           // 0.0
/*82  */     global_qtest = to;                                                      // 0.0
/*84  */     rsp = qmp("{ 'execute': 'migrate-set-capabilities',"                    // 0.0
/*86  */                   "'arguments': { "                                         // 0.0
/*88  */                       "'capabilities': [ {"                                 // 0.0
/*90  */                           "'capability': 'postcopy-ram',"                   // 0.0
/*92  */                           "'state': true } ] } }");                         // 0.0
/*94  */     g_assert(qdict_haskey(rsp, "return"));                                  // 0.0
/*96  */     QDECREF(rsp);                                                           // 0.0
/*100 */     /* We want to pick a speed slow enough that the test completes          // 0.0
/*102 */      * quickly, but that it doesn't complete precopy even on a slow         // 0.0
/*104 */      * machine, so also set the downtime.                                   // 0.0
/*106 */      */                                                                     // 0.0
/*108 */     global_qtest = from;                                                    // 0.0
/*110 */     rsp = qmp("{ 'execute': 'migrate_set_speed',"                           // 0.0
/*112 */               "'arguments': { 'value': 100000000 } }");                     // 0.0
/*114 */     g_assert(qdict_haskey(rsp, "return"));                                  // 0.0
/*116 */     QDECREF(rsp);                                                           // 0.0
/*120 */     /* 1ms downtime - it should never finish precopy */                     // 0.0
/*122 */     rsp = qmp("{ 'execute': 'migrate_set_downtime',"                        // 0.0
/*124 */               "'arguments': { 'value': 0.001 } }");                         // 0.0
/*126 */     g_assert(qdict_haskey(rsp, "return"));                                  // 0.0
/*128 */     QDECREF(rsp);                                                           // 0.0
/*134 */     /* Wait for the first serial output from the source */                  // 0.0
/*136 */     wait_for_serial("src_serial");                                          // 0.0
/*140 */     cmd = g_strdup_printf("{ 'execute': 'migrate',"                         // 0.0
/*142 */                           "'arguments': { 'uri': '%s' } }",                 // 0.0
/*144 */                           uri);                                             // 0.0
/*146 */     rsp = qmp(cmd);                                                         // 0.0
/*148 */     g_free(cmd);                                                            // 0.0
/*150 */     g_assert(qdict_haskey(rsp, "return"));                                  // 0.0
/*152 */     QDECREF(rsp);                                                           // 0.0
/*156 */     wait_for_migration_pass();                                              // 0.0
/*160 */     rsp = return_or_event(qmp("{ 'execute': 'migrate-start-postcopy' }"));  // 0.0
/*162 */     g_assert(qdict_haskey(rsp, "return"));                                  // 0.0
/*164 */     QDECREF(rsp);                                                           // 0.0
/*168 */     if (!got_stop) {                                                        // 0.0
/*170 */         qmp_eventwait("STOP");                                              // 0.0
/*172 */     }                                                                       // 0.0
/*176 */     global_qtest = to;                                                      // 0.0
/*178 */     qmp_eventwait("RESUME");                                                // 0.0
/*182 */     wait_for_serial("dest_serial");                                         // 0.0
/*184 */     global_qtest = from;                                                    // 0.0
/*186 */     wait_for_migration_complete();                                          // 0.0
/*190 */     qtest_quit(from);                                                       // 0.0
/*194 */     global_qtest = to;                                                      // 0.0
/*198 */     qtest_memread(to, start_address, &dest_byte_a, 1);                      // 0.0
/*202 */     /* Destination still running, wait for a byte to change */              // 0.0
/*204 */     do {                                                                    // 0.0
/*206 */         qtest_memread(to, start_address, &dest_byte_b, 1);                  // 0.0
/*208 */         usleep(10 * 1000);                                                  // 0.0
/*210 */     } while (dest_byte_a == dest_byte_b);                                   // 0.0
/*214 */     qmp("{ 'execute' : 'stop'}");                                           // 0.0
/*216 */     /* With it stopped, check nothing changes */                            // 0.0
/*218 */     qtest_memread(to, start_address, &dest_byte_c, 1);                      // 0.0
/*220 */     sleep(1);                                                               // 0.0
/*222 */     qtest_memread(to, start_address, &dest_byte_d, 1);                      // 0.0
/*224 */     g_assert_cmpint(dest_byte_c, ==, dest_byte_d);                          // 0.0
/*228 */     check_guests_ram();                                                     // 0.0
/*232 */     qtest_quit(to);                                                         // 0.0
/*234 */     g_free(uri);                                                            // 0.0
/*238 */     global_qtest = global;                                                  // 0.0
/*242 */     cleanup("bootsect");                                                    // 0.0
/*244 */     cleanup("migsocket");                                                   // 0.0
/*246 */     cleanup("src_serial");                                                  // 0.0
/*248 */     cleanup("dest_serial");                                                 // 0.0
/*250 */ }                                                                           // 0.0
