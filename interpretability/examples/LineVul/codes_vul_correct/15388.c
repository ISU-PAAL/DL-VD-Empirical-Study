// commit message qemu@3c94193e0b (target=1, prob=0.99916804, correct=True): tcg/optimize: optimize "op r, a, a => movi r, 0"
/*0   */ static TCGArg *tcg_constant_folding(TCGContext *s, uint16_t *tcg_opc_ptr,         // (2) 0.06445
/*1   */                                     TCGArg *args, TCGOpDef *tcg_op_defs)          // (0) 0.1055
/*2   */ {                                                                                 // (24) 0.001953
/*3   */     int i, nb_ops, op_index, nb_temps, nb_globals, nb_call_args;                  // (1) 0.06836
/*4   */     TCGOpcode op;                                                                 // (20) 0.01758
/*5   */     const TCGOpDef *def;                                                          // (18) 0.02148
/*6   */     TCGArg *gen_args;                                                             // (19) 0.02148
/*7   */     TCGArg tmp;                                                                   // (23) 0.01562
/*8   */     TCGCond cond;                                                                 // (22) 0.01563
/*9   */     /* Array VALS has an element for each temp.                                   // (16) 0.02734
/*10  */        If this temp holds a constant then its value is kept in VALS' element.     // (7) 0.04492
/*11  */        If this temp is a copy of other ones then the other copies are             // (9) 0.03906
/*12  */        available through the doubly linked circular list. */                      // (14) 0.03125
/*13  */     nb_temps = s->nb_temps;                                                       // (15) 0.03125
/*14  */     nb_globals = s->nb_globals;                                                   // (13) 0.03516
/*15  */     memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));                    // (3) 0.05273
/*16  */     nb_ops = tcg_opc_ptr - gen_opc_buf;                                           // (8) 0.04492
/*17  */     gen_args = args;                                                              // (21) 0.01758
/*18  */     for (op_index = 0; op_index < nb_ops; op_index++) {                           // (5) 0.04883
/*19  */         op = gen_opc_buf[op_index];                                               // (11) 0.03906
/*20  */         def = &tcg_op_defs[op];                                                   // (10) 0.03906
/*21  */         /* Do copy propagation */                                                 // (17) 0.02344
/*22  */         if (op == INDEX_op_call) {                                                // (12) 0.03711
/*23  */             int nb_oargs = args[0] >> 16;                                         // (6) 0.04883
/*24  */             int nb_iargs = args[0] & 0xffff;                                      // (4) 0.05273
/*25  */             for (i = nb_oargs + 1; i < nb_oargs + nb_iargs + 1; i++) {            // 0.0
/*26  */                 if (temps[args[i]].state == TCG_TEMP_COPY) {                      // 0.0
/*27  */                     args[i] = find_better_copy(s, args[i]);                       // 0.0
/*28  */         } else {                                                                  // 0.0
/*29  */             for (i = def->nb_oargs; i < def->nb_oargs + def->nb_iargs; i++) {     // 0.0
/*30  */                 if (temps[args[i]].state == TCG_TEMP_COPY) {                      // 0.0
/*31  */                     args[i] = find_better_copy(s, args[i]);                       // 0.0
/*32  */         /* For commutative operations make constant second argument */            // 0.0
/*33  */         CASE_OP_32_64(add):                                                       // 0.0
/*34  */         CASE_OP_32_64(mul):                                                       // 0.0
/*35  */         CASE_OP_32_64(and):                                                       // 0.0
/*36  */         CASE_OP_32_64(or):                                                        // 0.0
/*37  */         CASE_OP_32_64(eqv):                                                       // 0.0
/*38  */         CASE_OP_32_64(nand):                                                      // 0.0
/*39  */         CASE_OP_32_64(nor):                                                       // 0.0
/*40  */             if (temps[args[1]].state == TCG_TEMP_CONST) {                         // 0.0
/*41  */                 tmp = args[1];                                                    // 0.0
/*42  */                 args[1] = args[2];                                                // 0.0
/*43  */                 args[2] = tmp;                                                    // 0.0
/*44  */         CASE_OP_32_64(brcond):                                                    // 0.0
/*45  */             if (temps[args[0]].state == TCG_TEMP_CONST                            // 0.0
/*46  */                 && temps[args[1]].state != TCG_TEMP_CONST) {                      // 0.0
/*47  */                 tmp = args[0];                                                    // 0.0
/*48  */                 args[0] = args[1];                                                // 0.0
/*49  */                 args[1] = tmp;                                                    // 0.0
/*50  */                 args[2] = tcg_swap_cond(args[2]);                                 // 0.0
/*51  */         CASE_OP_32_64(setcond):                                                   // 0.0
/*52  */             if (temps[args[1]].state == TCG_TEMP_CONST                            // 0.0
/*53  */                 && temps[args[2]].state != TCG_TEMP_CONST) {                      // 0.0
/*54  */                 tmp = args[1];                                                    // 0.0
/*55  */                 args[1] = args[2];                                                // 0.0
/*56  */                 args[2] = tmp;                                                    // 0.0
/*57  */                 args[3] = tcg_swap_cond(args[3]);                                 // 0.0
/*58  */         CASE_OP_32_64(movcond):                                                   // 0.0
/*59  */             cond = args[5];                                                       // 0.0
/*60  */             if (temps[args[1]].state == TCG_TEMP_CONST                            // 0.0
/*61  */                 && temps[args[2]].state != TCG_TEMP_CONST) {                      // 0.0
/*62  */                 tmp = args[1];                                                    // 0.0
/*63  */                 args[1] = args[2];                                                // 0.0
/*64  */                 args[2] = tmp;                                                    // 0.0
/*65  */                 cond = tcg_swap_cond(cond);                                       // 0.0
/*66  */             /* For movcond, we canonicalize the "false" input reg to match        // 0.0
/*67  */                the destination reg so that the tcg backend can implement          // 0.0
/*68  */                a "move if true" operation.  */                                    // 0.0
/*69  */             if (args[0] == args[3]) {                                             // 0.0
/*70  */                 tmp = args[3];                                                    // 0.0
/*71  */                 args[3] = args[4];                                                // 0.0
/*72  */                 args[4] = tmp;                                                    // 0.0
/*73  */                 cond = tcg_invert_cond(cond);                                     // 0.0
/*74  */             args[5] = cond;                                                       // 0.0
/*75  */         /* Simplify expressions for "shift/rot r, 0, a => movi r, 0" */           // 0.0
/*76  */         CASE_OP_32_64(shl):                                                       // 0.0
/*77  */         CASE_OP_32_64(shr):                                                       // 0.0
/*78  */         CASE_OP_32_64(sar):                                                       // 0.0
/*79  */         CASE_OP_32_64(rotl):                                                      // 0.0
/*80  */         CASE_OP_32_64(rotr):                                                      // 0.0
/*81  */             if (temps[args[1]].state == TCG_TEMP_CONST                            // 0.0
/*82  */                 && temps[args[1]].val == 0) {                                     // 0.0
/*83  */         /* Simplify expression for "op r, a, 0 => mov r, a" cases */              // 0.0
/*84  */         CASE_OP_32_64(add):                                                       // 0.0
/*85  */         CASE_OP_32_64(shl):                                                       // 0.0
/*86  */         CASE_OP_32_64(shr):                                                       // 0.0
/*87  */         CASE_OP_32_64(sar):                                                       // 0.0
/*88  */         CASE_OP_32_64(rotl):                                                      // 0.0
/*89  */         CASE_OP_32_64(rotr):                                                      // 0.0
/*90  */         CASE_OP_32_64(or):                                                        // 0.0
/*91  */             if (temps[args[1]].state == TCG_TEMP_CONST) {                         // 0.0
/*92  */                 /* Proceed with possible constant folding. */                     // 0.0
/*93  */             if (temps[args[2]].state == TCG_TEMP_CONST                            // 0.0
/*94  */                 && temps[args[2]].val == 0) {                                     // 0.0
/*95  */                 if (temps_are_copies(args[0], args[1])) {                         // 0.0
/*96  */                     gen_opc_buf[op_index] = INDEX_op_nop;                         // 0.0
/*97  */                 } else {                                                          // 0.0
/*98  */                     gen_opc_buf[op_index] = op_to_mov(op);                        // 0.0
/*99  */                     tcg_opt_gen_mov(s, gen_args, args[0], args[1]);               // 0.0
/*100 */         /* Simplify expression for "op r, a, 0 => movi r, 0" cases */             // 0.0
/*101 */         CASE_OP_32_64(and):                                                       // 0.0
/*102 */         CASE_OP_32_64(mul):                                                       // 0.0
/*103 */             if ((temps[args[2]].state == TCG_TEMP_CONST                           // 0.0
/*104 */                 && temps[args[2]].val == 0)) {                                    // 0.0
/*105 */         /* Simplify expression for "op r, a, a => mov r, a" cases */              // 0.0
/*106 */         CASE_OP_32_64(or):                                                        // 0.0
/*107 */         CASE_OP_32_64(and):                                                       // 0.0
/*108 */                 if (temps_are_copies(args[0], args[1])) {                         // 0.0
/*109 */                     gen_opc_buf[op_index] = INDEX_op_nop;                         // 0.0
/*110 */                 } else {                                                          // 0.0
/*111 */                     gen_opc_buf[op_index] = op_to_mov(op);                        // 0.0
/*112 */                     tcg_opt_gen_mov(s, gen_args, args[0], args[1]);               // 0.0
/*113 */         /* Propagate constants through copy operations and do constant            // 0.0
/*114 */            folding.  Constants will be substituted to arguments by register       // 0.0
/*115 */            allocator where needed and possible.  Also detect copies. */           // 0.0
/*116 */         CASE_OP_32_64(mov):                                                       // 0.0
/*117 */             if (temps_are_copies(args[0], args[1])) {                             // 0.0
/*118 */                 args += 2;                                                        // 0.0
/*119 */                 gen_opc_buf[op_index] = INDEX_op_nop;                             // 0.0
/*120 */             if (temps[args[1]].state != TCG_TEMP_CONST) {                         // 0.0
/*121 */                 tcg_opt_gen_mov(s, gen_args, args[0], args[1]);                   // 0.0
/*122 */                 args += 2;                                                        // 0.0
/*123 */             /* Source argument is constant.  Rewrite the operation and            // 0.0
/*124 */                let movi case handle it. */                                        // 0.0
/*125 */             op = op_to_movi(op);                                                  // 0.0
/*126 */             gen_opc_buf[op_index] = op;                                           // 0.0
/*127 */             args[1] = temps[args[1]].val;                                         // 0.0
/*128 */             /* fallthrough */                                                     // 0.0
/*129 */         CASE_OP_32_64(movi):                                                      // 0.0
/*130 */             tcg_opt_gen_movi(gen_args, args[0], args[1]);                         // 0.0
/*131 */             args += 2;                                                            // 0.0
/*132 */         CASE_OP_32_64(not):                                                       // 0.0
/*133 */         CASE_OP_32_64(neg):                                                       // 0.0
/*134 */         CASE_OP_32_64(ext8s):                                                     // 0.0
/*135 */         CASE_OP_32_64(ext8u):                                                     // 0.0
/*136 */         CASE_OP_32_64(ext16s):                                                    // 0.0
/*137 */         CASE_OP_32_64(ext16u):                                                    // 0.0
/*138 */         case INDEX_op_ext32s_i64:                                                 // 0.0
/*139 */         case INDEX_op_ext32u_i64:                                                 // 0.0
/*140 */             if (temps[args[1]].state == TCG_TEMP_CONST) {                         // 0.0
/*141 */                 tmp = do_constant_folding(op, temps[args[1]].val, 0);             // 0.0
/*142 */                 tcg_opt_gen_movi(gen_args, args[0], tmp);                         // 0.0
/*143 */             } else {                                                              // 0.0
/*144 */                 reset_temp(args[0]);                                              // 0.0
/*145 */                 gen_args[0] = args[0];                                            // 0.0
/*146 */                 gen_args[1] = args[1];                                            // 0.0
/*147 */             args += 2;                                                            // 0.0
/*148 */         CASE_OP_32_64(add):                                                       // 0.0
/*149 */         CASE_OP_32_64(mul):                                                       // 0.0
/*150 */         CASE_OP_32_64(or):                                                        // 0.0
/*151 */         CASE_OP_32_64(and):                                                       // 0.0
/*152 */         CASE_OP_32_64(shl):                                                       // 0.0
/*153 */         CASE_OP_32_64(shr):                                                       // 0.0
/*154 */         CASE_OP_32_64(sar):                                                       // 0.0
/*155 */         CASE_OP_32_64(rotl):                                                      // 0.0
/*156 */         CASE_OP_32_64(rotr):                                                      // 0.0
/*157 */         CASE_OP_32_64(andc):                                                      // 0.0
/*158 */         CASE_OP_32_64(orc):                                                       // 0.0
/*159 */         CASE_OP_32_64(eqv):                                                       // 0.0
/*160 */         CASE_OP_32_64(nand):                                                      // 0.0
/*161 */         CASE_OP_32_64(nor):                                                       // 0.0
/*162 */             if (temps[args[1]].state == TCG_TEMP_CONST                            // 0.0
/*163 */                 && temps[args[2]].state == TCG_TEMP_CONST) {                      // 0.0
/*164 */                 tmp = do_constant_folding(op, temps[args[1]].val,                 // 0.0
/*165 */                                           temps[args[2]].val);                    // 0.0
/*166 */                 tcg_opt_gen_movi(gen_args, args[0], tmp);                         // 0.0
/*167 */             } else {                                                              // 0.0
/*168 */                 reset_temp(args[0]);                                              // 0.0
/*169 */                 gen_args[0] = args[0];                                            // 0.0
/*170 */                 gen_args[1] = args[1];                                            // 0.0
/*171 */                 gen_args[2] = args[2];                                            // 0.0
/*172 */                 gen_args += 3;                                                    // 0.0
/*173 */         CASE_OP_32_64(setcond):                                                   // 0.0
/*174 */             if (temps[args[1]].state == TCG_TEMP_CONST                            // 0.0
/*175 */                 && temps[args[2]].state == TCG_TEMP_CONST) {                      // 0.0
/*176 */                 tmp = do_constant_folding_cond(op, temps[args[1]].val,            // 0.0
/*177 */                                                temps[args[2]].val, args[3]);      // 0.0
/*178 */                 tcg_opt_gen_movi(gen_args, args[0], tmp);                         // 0.0
/*179 */             } else {                                                              // 0.0
/*180 */                 reset_temp(args[0]);                                              // 0.0
/*181 */                 gen_args[0] = args[0];                                            // 0.0
/*182 */                 gen_args[1] = args[1];                                            // 0.0
/*183 */                 gen_args[2] = args[2];                                            // 0.0
/*184 */                 gen_args[3] = args[3];                                            // 0.0
/*185 */                 gen_args += 4;                                                    // 0.0
/*186 */             args += 4;                                                            // 0.0
/*187 */         CASE_OP_32_64(brcond):                                                    // 0.0
/*188 */             if (temps[args[0]].state == TCG_TEMP_CONST                            // 0.0
/*189 */                 && temps[args[1]].state == TCG_TEMP_CONST) {                      // 0.0
/*190 */                 if (do_constant_folding_cond(op, temps[args[0]].val,              // 0.0
/*191 */                                              temps[args[1]].val, args[2])) {      // 0.0
/*192 */                     memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));    // 0.0
/*193 */                     gen_opc_buf[op_index] = INDEX_op_br;                          // 0.0
/*194 */                     gen_args[0] = args[3];                                        // 0.0
/*195 */                     gen_args += 1;                                                // 0.0
/*196 */                 } else {                                                          // 0.0
/*197 */                     gen_opc_buf[op_index] = INDEX_op_nop;                         // 0.0
/*198 */             } else {                                                              // 0.0
/*199 */                 memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));        // 0.0
/*200 */                 reset_temp(args[0]);                                              // 0.0
/*201 */                 gen_args[0] = args[0];                                            // 0.0
/*202 */                 gen_args[1] = args[1];                                            // 0.0
/*203 */                 gen_args[2] = args[2];                                            // 0.0
/*204 */                 gen_args[3] = args[3];                                            // 0.0
/*205 */                 gen_args += 4;                                                    // 0.0
/*206 */             args += 4;                                                            // 0.0
/*207 */         CASE_OP_32_64(movcond):                                                   // 0.0
/*208 */             if (temps[args[1]].state == TCG_TEMP_CONST                            // 0.0
/*209 */                 && temps[args[2]].state == TCG_TEMP_CONST) {                      // 0.0
/*210 */                 tmp = do_constant_folding_cond(op, temps[args[1]].val,            // 0.0
/*211 */                                                temps[args[2]].val, args[5]);      // 0.0
/*212 */                 if (temps_are_copies(args[0], args[4-tmp])) {                     // 0.0
/*213 */                     gen_opc_buf[op_index] = INDEX_op_nop;                         // 0.0
/*214 */                 } else if (temps[args[4-tmp]].state == TCG_TEMP_CONST) {          // 0.0
/*215 */                     tcg_opt_gen_movi(gen_args, args[0], temps[args[4-tmp]].val);  // 0.0
/*216 */                 } else {                                                          // 0.0
/*217 */                     gen_opc_buf[op_index] = op_to_mov(op);                        // 0.0
/*218 */                     tcg_opt_gen_mov(s, gen_args, args[0], args[4-tmp]);           // 0.0
/*219 */             } else {                                                              // 0.0
/*220 */                 reset_temp(args[0]);                                              // 0.0
/*221 */                 gen_args[0] = args[0];                                            // 0.0
/*222 */                 gen_args[1] = args[1];                                            // 0.0
/*223 */                 gen_args[2] = args[2];                                            // 0.0
/*224 */                 gen_args[3] = args[3];                                            // 0.0
/*225 */                 gen_args[4] = args[4];                                            // 0.0
/*226 */                 gen_args[5] = args[5];                                            // 0.0
/*227 */                 gen_args += 6;                                                    // 0.0
/*228 */             args += 6;                                                            // 0.0
/*229 */         case INDEX_op_call:                                                       // 0.0
/*230 */             nb_call_args = (args[0] >> 16) + (args[0] & 0xffff);                  // 0.0
/*231 */             if (!(args[nb_call_args + 1] & (TCG_CALL_CONST | TCG_CALL_PURE))) {   // 0.0
/*232 */                 for (i = 0; i < nb_globals; i++) {                                // 0.0
/*233 */                     reset_temp(i);                                                // 0.0
/*234 */             for (i = 0; i < (args[0] >> 16); i++) {                               // 0.0
/*235 */                 reset_temp(args[i + 1]);                                          // 0.0
/*236 */             i = nb_call_args + 3;                                                 // 0.0
/*237 */             while (i) {                                                           // 0.0
/*238 */                 *gen_args = *args;                                                // 0.0
/*239 */                 args++;                                                           // 0.0
/*240 */                 gen_args++;                                                       // 0.0
/*241 */                 i--;                                                              // 0.0
/*242 */             /* Default case: we do know nothing about operation so no             // 0.0
/*243 */                propagation is done.  We trash everything if the operation         // 0.0
/*244 */                is the end of a basic block, otherwise we only trash the           // 0.0
/*245 */                output args.  */                                                   // 0.0
/*246 */             if (def->flags & TCG_OPF_BB_END) {                                    // 0.0
/*247 */                 memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));        // 0.0
/*248 */             } else {                                                              // 0.0
/*249 */                 for (i = 0; i < def->nb_oargs; i++) {                             // 0.0
/*250 */                     reset_temp(args[i]);                                          // 0.0
/*251 */             for (i = 0; i < def->nb_args; i++) {                                  // 0.0
/*252 */                 gen_args[i] = args[i];                                            // 0.0
/*253 */             args += def->nb_args;                                                 // 0.0
/*254 */             gen_args += def->nb_args;                                             // 0.0
/*255 */     return gen_args;                                                              // 0.0
