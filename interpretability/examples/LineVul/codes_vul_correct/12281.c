// commit message qemu@04f8c053cc (target=1, prob=0.99914527, correct=True): QMP: Check "arguments" member's type
/*0   */ static void handle_qmp_command(JSONMessageParser *parser, QList *tokens)       // (4) 0.02476
/*2   */ {                                                                              // (26) 0.002969
/*4   */     int err;                                                                   // (24) 0.003431
/*6   */     QObject *obj;                                                              // (23) 0.003916
/*8   */     QDict *input, *args;                                                       // (22) 0.005096
/*10  */     const mon_cmd_t *cmd;                                                      // (12) 0.008366
/*12  */     Monitor *mon = cur_mon;                                                    // (15) 0.007063
/*14  */     const char *cmd_name, *info_item;                                          // (19) 0.006425
/*18  */     args = NULL;                                                               // (17) 0.006679
/*22  */     obj = json_parser_parse(tokens, NULL);                                     // (10) 0.009627
/*24  */     if (!obj) {                                                                // (3) 0.02918
/*26  */         // FIXME: should be triggered in json_parser_parse()                   // (0) 0.5619
/*28  */         qerror_report(QERR_JSON_PARSING);                                      // (5) 0.02229
/*30  */         goto err_out;                                                          // (1) 0.04575
/*33  */         qerror_report(QERR_QMP_BAD_INPUT_OBJECT, "object");                    // (8) 0.01155
/*35  */         qobject_decref(obj);                                                   // (16) 0.006993
/*37  */         goto err_out;                                                          // (2) 0.04431
/*39  */     }                                                                          // (27) 0.001906
/*43  */     input = qobject_to_qdict(obj);                                             // (18) 0.00646
/*47  */     mon->mc->id = qdict_get(input, "id");                                      // (13) 0.008334
/*49  */     qobject_incref(mon->mc->id);                                               // (20) 0.006185
/*53  */     obj = qdict_get(input, "execute");                                         // (21) 0.005454
/*55  */     if (!obj) {                                                                // (25) 0.00313
/*57  */         qerror_report(QERR_QMP_BAD_INPUT_OBJECT, "execute");                   // (7) 0.01278
/*60  */     } else if (qobject_type(obj) != QTYPE_QSTRING) {                           // (14) 0.008006
/*62  */         qerror_report(QERR_QMP_BAD_INPUT_OBJECT_MEMBER, "execute", "string");  // (6) 0.01516
/*65  */     }                                                                          // (28) 0.001618
/*69  */     cmd_name = qstring_get_str(qobject_to_qstring(obj));                       // (11) 0.008678
/*73  */     if (invalid_qmp_mode(mon, cmd_name)) {                                     // (9) 0.009945
/*75  */         qerror_report(QERR_COMMAND_NOT_FOUND, cmd_name);                       // 0.0
/*78  */     }                                                                          // 0.0
/*82  */     /*                                                                         // 0.0
/*84  */      * XXX: We need this special case until we get info handlers               // 0.0
/*86  */      * converted into 'query-' commands                                        // 0.0
/*88  */      */                                                                        // 0.0
/*90  */     if (compare_cmd(cmd_name, "info")) {                                       // 0.0
/*92  */         qerror_report(QERR_COMMAND_NOT_FOUND, cmd_name);                       // 0.0
/*95  */     } else if (strstart(cmd_name, "query-", &info_item)) {                     // 0.0
/*97  */         cmd = monitor_find_command("info");                                    // 0.0
/*99  */         qdict_put_obj(input, "arguments",                                      // 0.0
/*101 */                       qobject_from_jsonf("{ 'item': %s }", info_item));        // 0.0
/*103 */     } else {                                                                   // 0.0
/*105 */         cmd = monitor_find_command(cmd_name);                                  // 0.0
/*107 */         if (!cmd || !monitor_handler_ported(cmd)) {                            // 0.0
/*109 */             qerror_report(QERR_COMMAND_NOT_FOUND, cmd_name);                   // 0.0
/*112 */         }                                                                      // 0.0
/*114 */     }                                                                          // 0.0
/*118 */     obj = qdict_get(input, "arguments");                                       // 0.0
/*120 */     if (!obj) {                                                                // 0.0
/*122 */         args = qdict_new();                                                    // 0.0
/*127 */     } else {                                                                   // 0.0
/*129 */         args = qobject_to_qdict(obj);                                          // 0.0
/*131 */         QINCREF(args);                                                         // 0.0
/*133 */     }                                                                          // 0.0
/*137 */     QDECREF(input);                                                            // 0.0
/*141 */     err = monitor_check_qmp_args(cmd, args);                                   // 0.0
/*143 */     if (err < 0) {                                                             // 0.0
/*145 */         goto err_out;                                                          // 0.0
/*147 */     }                                                                          // 0.0
/*151 */     if (monitor_handler_is_async(cmd)) {                                       // 0.0
/*153 */         qmp_async_cmd_handler(mon, cmd, args);                                 // 0.0
/*155 */     } else {                                                                   // 0.0
/*157 */         monitor_call_handler(mon, cmd, args);                                  // 0.0
/*159 */     }                                                                          // 0.0
/*161 */     goto out;                                                                  // 0.0
/*165 */ err_input:                                                                     // 0.0
/*167 */     QDECREF(input);                                                            // 0.0
/*169 */ err_out:                                                                       // 0.0
/*171 */     monitor_protocol_emitter(mon, NULL);                                       // 0.0
/*173 */ out:                                                                           // 0.0
/*175 */     QDECREF(args);                                                             // 0.0
/*177 */ }                                                                              // 0.0
