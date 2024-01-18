// commit message qemu@eabb7b91b3 (target=0, prob=0.77054405, correct=False): tcg: use tcg_debug_assert instead of assert (fix performance regression)
/*0   */ void tcg_add_target_add_op_defs(const TCGTargetOpDef *tdefs)                                           // (4) 0.05078
/*2   */ {                                                                                                      // (26) 0.001953
/*4   */     TCGOpcode op;                                                                                      // (23) 0.01758
/*6   */     TCGOpDef *def;                                                                                     // (21) 0.01953
/*8   */     const char *ct_str;                                                                                // (22) 0.01953
/*10  */     int i, nb_args;                                                                                    // (20) 0.02148
/*14  */     for(;;) {                                                                                          // (24) 0.01563
/*16  */         if (tdefs->op == (TCGOpcode)-1)                                                                // (6) 0.04492
/*18  */             break;                                                                                     // (17) 0.02539
/*20  */         op = tdefs->op;                                                                                // (15) 0.0293
/*22  */         assert((unsigned)op < NB_OPS);                                                                 // (13) 0.0332
/*24  */         def = &tcg_op_defs[op];                                                                        // (10) 0.03906
/*26  */ #if defined(CONFIG_DEBUG_TCG)                                                                          // (19) 0.02344
/*28  */         /* Duplicate entry in op definitions? */                                                       // (14) 0.03125
/*30  */         assert(!def->used);                                                                            // (16) 0.02734
/*32  */         def->used = 1;                                                                                 // (18) 0.02539
/*34  */ #endif                                                                                                 // (25) 0.003906
/*36  */         nb_args = def->nb_iargs + def->nb_oargs;                                                       // (5) 0.05078
/*38  */         for(i = 0; i < nb_args; i++) {                                                                 // (7) 0.04492
/*40  */             ct_str = tdefs->args_ct_str[i];                                                            // (3) 0.05469
/*42  */             /* Incomplete TCGTargetOpDef entry? */                                                     // (9) 0.04297
/*44  */             assert(ct_str != NULL);                                                                    // (12) 0.03711
/*46  */             tcg_regset_clear(def->args_ct[i].u.regs);                                                  // (1) 0.0625
/*48  */             def->args_ct[i].ct = 0;                                                                    // (8) 0.04492
/*50  */             if (ct_str[0] >= '0' && ct_str[0] <= '9') {                                                // (0) 0.07031
/*52  */                 int oarg;                                                                              // (11) 0.03711
/*54  */                 oarg = ct_str[0] - '0';                                                                // (2) 0.05664
/*56  */                 assert(oarg < def->nb_oargs);                                                          // 0.0
/*58  */                 assert(def->args_ct[oarg].ct & TCG_CT_REG);                                            // 0.0
/*60  */                 /* TCG_CT_ALIAS is for the output arguments. The input                                 // 0.0
/*62  */                    argument is tagged with TCG_CT_IALIAS. */                                           // 0.0
/*64  */                 def->args_ct[i] = def->args_ct[oarg];                                                  // 0.0
/*66  */                 def->args_ct[oarg].ct = TCG_CT_ALIAS;                                                  // 0.0
/*68  */                 def->args_ct[oarg].alias_index = i;                                                    // 0.0
/*70  */                 def->args_ct[i].ct |= TCG_CT_IALIAS;                                                   // 0.0
/*72  */                 def->args_ct[i].alias_index = oarg;                                                    // 0.0
/*74  */             } else {                                                                                   // 0.0
/*76  */                 for(;;) {                                                                              // 0.0
/*78  */                     if (*ct_str == '\0')                                                               // 0.0
/*80  */                         break;                                                                         // 0.0
/*82  */                     switch(*ct_str) {                                                                  // 0.0
/*84  */                     case 'i':                                                                          // 0.0
/*86  */                         def->args_ct[i].ct |= TCG_CT_CONST;                                            // 0.0
/*88  */                         ct_str++;                                                                      // 0.0
/*90  */                         break;                                                                         // 0.0
/*92  */                     default:                                                                           // 0.0
/*94  */                         if (target_parse_constraint(&def->args_ct[i], &ct_str) < 0) {                  // 0.0
/*96  */                             fprintf(stderr, "Invalid constraint '%s' for arg %d of operation '%s'\n",  // 0.0
/*98  */                                     ct_str, i, def->name);                                             // 0.0
/*100 */                             exit(1);                                                                   // 0.0
/*102 */                         }                                                                              // 0.0
/*104 */                     }                                                                                  // 0.0
/*106 */                 }                                                                                      // 0.0
/*108 */             }                                                                                          // 0.0
/*110 */         }                                                                                              // 0.0
/*114 */         /* TCGTargetOpDef entry with too much information? */                                          // 0.0
/*116 */         assert(i == TCG_MAX_OP_ARGS || tdefs->args_ct_str[i] == NULL);                                 // 0.0
/*120 */         /* sort the constraints (XXX: this is just an heuristic) */                                    // 0.0
/*122 */         sort_constraints(def, 0, def->nb_oargs);                                                       // 0.0
/*124 */         sort_constraints(def, def->nb_oargs, def->nb_iargs);                                           // 0.0
/*128 */ #if 0                                                                                                  // 0.0
/*130 */         {                                                                                              // 0.0
/*132 */             int i;                                                                                     // 0.0
/*136 */             printf("%s: sorted=", def->name);                                                          // 0.0
/*138 */             for(i = 0; i < def->nb_oargs + def->nb_iargs; i++)                                         // 0.0
/*140 */                 printf(" %d", def->sorted_args[i]);                                                    // 0.0
/*142 */             printf("\n");                                                                              // 0.0
/*144 */         }                                                                                              // 0.0
/*146 */ #endif                                                                                                 // 0.0
/*148 */         tdefs++;                                                                                       // 0.0
/*150 */     }                                                                                                  // 0.0
/*154 */ #if defined(CONFIG_DEBUG_TCG)                                                                          // 0.0
/*156 */     i = 0;                                                                                             // 0.0
/*158 */     for (op = 0; op < tcg_op_defs_max; op++) {                                                         // 0.0
/*160 */         const TCGOpDef *def = &tcg_op_defs[op];                                                        // 0.0
/*162 */         if (def->flags & TCG_OPF_NOT_PRESENT) {                                                        // 0.0
/*164 */             /* Wrong entry in op definitions? */                                                       // 0.0
/*166 */             if (def->used) {                                                                           // 0.0
/*168 */                 fprintf(stderr, "Invalid op definition for %s\n", def->name);                          // 0.0
/*170 */                 i = 1;                                                                                 // 0.0
/*172 */             }                                                                                          // 0.0
/*174 */         } else {                                                                                       // 0.0
/*176 */             /* Missing entry in op definitions? */                                                     // 0.0
/*178 */             if (!def->used) {                                                                          // 0.0
/*180 */                 fprintf(stderr, "Missing op definition for %s\n", def->name);                          // 0.0
/*182 */                 i = 1;                                                                                 // 0.0
/*184 */             }                                                                                          // 0.0
/*186 */         }                                                                                              // 0.0
/*188 */     }                                                                                                  // 0.0
/*190 */     if (i == 1) {                                                                                      // 0.0
/*192 */         tcg_abort();                                                                                   // 0.0
/*194 */     }                                                                                                  // 0.0
/*196 */ #endif                                                                                                 // 0.0
/*198 */ }                                                                                                      // 0.0
