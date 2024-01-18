// commit message qemu@03a63484a6 (target=1, prob=0.4881729, correct=False): monitor: Fix leakage during completion processing
/*0   */ static void monitor_find_completion(const char *cmdline)                  // (12) 0.0293
/*2   */ {                                                                         // (32) 0.001953
/*4   */     const char *cmdname;                                                  // (23) 0.01758
/*6   */     char *args[MAX_ARGS];                                                 // (18) 0.02344
/*8   */     int nb_args, i, len;                                                  // (14) 0.02539
/*10  */     const char *ptype, *str;                                              // (17) 0.02344
/*12  */     const mon_cmd_t *cmd;                                                 // (16) 0.02344
/*14  */     const KeyDef *key;                                                    // (22) 0.01758
/*18  */     parse_cmdline(cmdline, &nb_args, args);                               // (8) 0.03516
/*20  */ #ifdef DEBUG_COMPLETION                                                   // (27) 0.01367
/*22  */     for(i = 0; i < nb_args; i++) {                                        // (7) 0.03711
/*24  */         monitor_printf(cur_mon, "arg%d = '%s'\n", i, (char *)args[i]);    // (0) 0.07031
/*26  */     }                                                                     // (29) 0.007812
/*28  */ #endif                                                                    // (31) 0.003906
/*32  */     /* if the line ends with a space, it means we want to complete the    // (6) 0.03711
/*34  */        next arg */                                                        // (24) 0.01758
/*36  */     len = strlen(cmdline);                                                // (21) 0.02148
/*38  */     if (len > 0 && qemu_isspace(cmdline[len - 1])) {                      // (3) 0.04883
/*40  */         if (nb_args >= MAX_ARGS)                                          // (9) 0.03516
/*42  */             return;                                                       // (15) 0.02539
/*44  */         args[nb_args++] = qemu_strdup("");                                // (4) 0.04687
/*46  */     }                                                                     // (30) 0.007812
/*48  */     if (nb_args <= 1) {                                                   // (19) 0.02344
/*50  */         /* command completion */                                          // (20) 0.02148
/*52  */         if (nb_args == 0)                                                 // (13) 0.0293
/*54  */             cmdname = "";                                                 // (11) 0.03125
/*56  */         else                                                              // (25) 0.01562
/*58  */             cmdname = args[0];                                            // (10) 0.03516
/*60  */         readline_set_completion_index(cur_mon->rs, strlen(cmdname));      // (1) 0.05664
/*62  */         for(cmd = mon_cmds; cmd->name != NULL; cmd++) {                   // (2) 0.04883
/*64  */             cmd_completion(cmdname, cmd->name);                           // (5) 0.04492
/*66  */         }                                                                 // (26) 0.01562
/*68  */     } else {                                                              // (28) 0.01172
/*70  */         /* find the command */                                            // 0.0
/*72  */         for(cmd = mon_cmds; cmd->name != NULL; cmd++) {                   // 0.0
/*74  */             if (compare_cmd(args[0], cmd->name))                          // 0.0
/*76  */                 goto found;                                               // 0.0
/*78  */         }                                                                 // 0.0
/*80  */         return;                                                           // 0.0
/*82  */     found:                                                                // 0.0
/*84  */         ptype = next_arg_type(cmd->args_type);                            // 0.0
/*86  */         for(i = 0; i < nb_args - 2; i++) {                                // 0.0
/*88  */             if (*ptype != '\0') {                                         // 0.0
/*90  */                 ptype = next_arg_type(ptype);                             // 0.0
/*92  */                 while (*ptype == '?')                                     // 0.0
/*94  */                     ptype = next_arg_type(ptype);                         // 0.0
/*96  */             }                                                             // 0.0
/*98  */         }                                                                 // 0.0
/*100 */         str = args[nb_args - 1];                                          // 0.0
/*102 */         if (*ptype == '-' && ptype[1] != '\0') {                          // 0.0
/*104 */             ptype += 2;                                                   // 0.0
/*106 */         }                                                                 // 0.0
/*108 */         switch(*ptype) {                                                  // 0.0
/*110 */         case 'F':                                                         // 0.0
/*112 */             /* file completion */                                         // 0.0
/*114 */             readline_set_completion_index(cur_mon->rs, strlen(str));      // 0.0
/*116 */             file_completion(str);                                         // 0.0
/*118 */             break;                                                        // 0.0
/*120 */         case 'B':                                                         // 0.0
/*122 */             /* block device name completion */                            // 0.0
/*124 */             readline_set_completion_index(cur_mon->rs, strlen(str));      // 0.0
/*126 */             bdrv_iterate(block_completion_it, (void *)str);               // 0.0
/*128 */             break;                                                        // 0.0
/*130 */         case 's':                                                         // 0.0
/*132 */             /* XXX: more generic ? */                                     // 0.0
/*134 */             if (!strcmp(cmd->name, "info")) {                             // 0.0
/*136 */                 readline_set_completion_index(cur_mon->rs, strlen(str));  // 0.0
/*138 */                 for(cmd = info_cmds; cmd->name != NULL; cmd++) {          // 0.0
/*140 */                     cmd_completion(str, cmd->name);                       // 0.0
/*142 */                 }                                                         // 0.0
/*144 */             } else if (!strcmp(cmd->name, "sendkey")) {                   // 0.0
/*146 */                 char *sep = strrchr(str, '-');                            // 0.0
/*148 */                 if (sep)                                                  // 0.0
/*150 */                     str = sep + 1;                                        // 0.0
/*152 */                 readline_set_completion_index(cur_mon->rs, strlen(str));  // 0.0
/*154 */                 for(key = key_defs; key->name != NULL; key++) {           // 0.0
/*156 */                     cmd_completion(str, key->name);                       // 0.0
/*158 */                 }                                                         // 0.0
/*160 */             } else if (!strcmp(cmd->name, "help|?")) {                    // 0.0
/*162 */                 readline_set_completion_index(cur_mon->rs, strlen(str));  // 0.0
/*164 */                 for (cmd = mon_cmds; cmd->name != NULL; cmd++) {          // 0.0
/*166 */                     cmd_completion(str, cmd->name);                       // 0.0
/*168 */                 }                                                         // 0.0
/*170 */             }                                                             // 0.0
/*172 */             break;                                                        // 0.0
/*174 */         default:                                                          // 0.0
/*176 */             break;                                                        // 0.0
/*178 */         }                                                                 // 0.0
/*180 */     }                                                                     // 0.0
/*182 */     for(i = 0; i < nb_args; i++)                                          // 0.0
/*184 */         qemu_free(args[i]);                                               // 0.0
/*186 */ }                                                                         // 0.0
