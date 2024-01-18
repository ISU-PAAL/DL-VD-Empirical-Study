// commit message FFmpeg@9241cd2095 (target=0, prob=0.33874956, correct=True): Make avfilter_parse_graph() output a more meaningful message when an invalid filterchain is detected.
/*0   */ int avfilter_graph_parse(AVFilterGraph *graph, const char *filters,                       // (9) 0.03906
/*2   */                          AVFilterInOut *open_inputs,                                      // (4) 0.06641
/*4   */                          AVFilterInOut *open_outputs, AVClass *log_ctx)                   // (1) 0.08008
/*6   */ {                                                                                         // (21) 0.001953
/*8   */     int index = 0, ret;                                                                   // (17) 0.01953
/*10  */     char chr = 0;                                                                         // (18) 0.01758
/*14  */     AVFilterInOut *curr_inputs = NULL;                                                    // (12) 0.03125
/*18  */     do {                                                                                  // (20) 0.009766
/*20  */         AVFilterContext *filter;                                                          // (16) 0.02539
/*22  */         filters += strspn(filters, WHITESPACES);                                          // (8) 0.04297
/*26  */         if ((ret = parse_inputs(&filters, &curr_inputs, &open_outputs, log_ctx)) < 0)     // (3) 0.07617
/*28  */             goto fail;                                                                    // (13) 0.02734
/*32  */         if ((ret = parse_filter(&filter, &filters, graph, index, log_ctx)) < 0)           // (5) 0.0625
/*34  */             goto fail;                                                                    // (14) 0.02734
/*38  */         if (filter->input_count == 1 && !curr_inputs && !index) {                         // (6) 0.05469
/*40  */             /* First input can be omitted if it is "[in]" */                              // (7) 0.04688
/*42  */             const char *tmp = "[in]";                                                     // (10) 0.03906
/*44  */             if ((ret = parse_inputs(&tmp, &curr_inputs, &open_outputs, log_ctx)) < 0)     // (0) 0.08203
/*46  */                 goto fail;                                                                // (11) 0.03516
/*48  */         }                                                                                 // (19) 0.01562
/*52  */         if ((ret = link_filter_inouts(filter, &curr_inputs, &open_inputs, log_ctx)) < 0)  // (2) 0.07813
/*54  */             goto fail;                                                                    // (15) 0.02734
/*58  */         if ((ret = parse_outputs(&filters, &curr_inputs, &open_inputs, &open_outputs,     // 0.0
/*60  */                                  log_ctx)) < 0)                                           // 0.0
/*62  */             goto fail;                                                                    // 0.0
/*66  */         filters += strspn(filters, WHITESPACES);                                          // 0.0
/*68  */         chr = *filters++;                                                                 // 0.0
/*72  */         if (chr == ';' && curr_inputs) {                                                  // 0.0
/*74  */             av_log(log_ctx, AV_LOG_ERROR,                                                 // 0.0
/*76  */                    "Could not find a output to link when parsing \"%s\"\n",               // 0.0
/*78  */                    filters - 1);                                                          // 0.0
/*80  */             ret = AVERROR(EINVAL);                                                        // 0.0
/*82  */             goto fail;                                                                    // 0.0
/*84  */         }                                                                                 // 0.0
/*86  */         index++;                                                                          // 0.0
/*88  */     } while (chr == ',' || chr == ';');                                                   // 0.0
/*92  */     if (chr) {                                                                            // 0.0
/*94  */         av_log(log_ctx, AV_LOG_ERROR,                                                     // 0.0
/*96  */                "Unable to parse graph description substring: \"%s\"\n",                   // 0.0
/*98  */                filters - 1);                                                              // 0.0
/*100 */         ret = AVERROR(EINVAL);                                                            // 0.0
/*102 */         goto fail;                                                                        // 0.0
/*104 */     }                                                                                     // 0.0
/*108 */     if (open_inputs && !strcmp(open_inputs->name, "out") && curr_inputs) {                // 0.0
/*110 */         /* Last output can be omitted if it is "[out]" */                                 // 0.0
/*112 */         const char *tmp = "[out]";                                                        // 0.0
/*114 */         if ((ret = parse_outputs(&tmp, &curr_inputs, &open_inputs, &open_outputs,         // 0.0
/*116 */                                  log_ctx)) < 0)                                           // 0.0
/*118 */             goto fail;                                                                    // 0.0
/*120 */     }                                                                                     // 0.0
/*124 */     return 0;                                                                             // 0.0
/*128 */  fail:                                                                                    // 0.0
/*130 */     avfilter_graph_free(graph);                                                           // 0.0
/*132 */     free_inout(open_inputs);                                                              // 0.0
/*134 */     free_inout(open_outputs);                                                             // 0.0
/*136 */     free_inout(curr_inputs);                                                              // 0.0
/*138 */     return ret;                                                                           // 0.0
/*140 */ }                                                                                         // 0.0
