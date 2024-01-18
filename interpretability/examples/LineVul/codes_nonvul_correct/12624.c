// commit message qemu@2e061a7c86 (target=0, prob=0.09726457, correct=True): QMP: Simplify do_info_commands()
/*0  */ static void do_info_commands(Monitor *mon, QObject **ret_data)             // (8) 0.0551
/*2  */ {                                                                          // (18) 0.002755
/*4  */     QList *cmd_list;                                                       // (13) 0.02755
/*6  */     const mon_cmd_t *cmd;                                                  // (11) 0.03306
/*10 */     cmd_list = qlist_new();                                                // (12) 0.03306
/*14 */     for (cmd = qmp_cmds; cmd->name != NULL; cmd++) {                       // (7) 0.06061
/*16 */         if (monitor_handler_ported(cmd) && !monitor_cmd_user_only(cmd) &&  // (2) 0.08264
/*18 */             !compare_cmd(cmd->name, "info")) {                             // (5) 0.06887
/*20 */             qlist_append_obj(cmd_list, get_cmd_dict(cmd->name));           // (0) 0.08815
/*22 */         }                                                                  // (14) 0.02204
/*24 */     }                                                                      // (16) 0.01102
/*28 */     for (cmd = qmp_query_cmds; cmd->name != NULL; cmd++) {                 // (6) 0.06612
/*30 */         if (monitor_handler_ported(cmd) && !monitor_cmd_user_only(cmd)) {  // (1) 0.08264
/*32 */             char buf[128];                                                 // (9) 0.04408
/*34 */             snprintf(buf, sizeof(buf), "query-%s", cmd->name);             // (3) 0.08264
/*36 */             qlist_append_obj(cmd_list, get_cmd_dict(buf));                 // (4) 0.08264
/*38 */         }                                                                  // (15) 0.02204
/*40 */     }                                                                      // (17) 0.01102
/*44 */     *ret_data = QOBJECT(cmd_list);                                         // (10) 0.04408
/*46 */ }                                                                          // (19) 0.002755
