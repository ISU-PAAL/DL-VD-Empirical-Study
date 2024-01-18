// commit message qemu@f17fd4fdf0 (target=0, prob=0.13357826, correct=True): util/cutils: Return qemu_strtosz*() error and value separately
/*0   */ static void x86_cpu_parse_featurestr(const char *typename, char *features,  // (4) 0.04492
/*2   */                                      Error **errp)                          // (1) 0.08008
/*4   */ {                                                                           // (27) 0.001953
/*6   */     char *featurestr; /* Single 'key=value" string being parsed */          // (7) 0.03711
/*8   */     static bool cpu_globals_initialized;                                    // (12) 0.02539
/*10  */     bool ambiguous = false;                                                 // (23) 0.01562
/*14  */     if (cpu_globals_initialized) {                                          // (10) 0.02734
/*16  */         return;                                                             // (22) 0.01758
/*18  */     }                                                                       // (26) 0.007812
/*20  */     cpu_globals_initialized = true;                                         // (13) 0.02539
/*24  */     if (!features) {                                                        // (24) 0.01562
/*26  */         return;                                                             // (21) 0.01758
/*28  */     }                                                                       // (25) 0.007812
/*32  */     for (featurestr = strtok(features, ",");                                // (9) 0.0332
/*34  */          featurestr;                                                        // (20) 0.02148
/*36  */          featurestr = strtok(NULL, ",")) {                                  // (5) 0.04102
/*38  */         const char *name;                                                   // (19) 0.02344
/*40  */         const char *val = NULL;                                             // (11) 0.02734
/*42  */         char *eq = NULL;                                                    // (14) 0.02539
/*44  */         char num[32];                                                       // (18) 0.02344
/*46  */         GlobalProperty *prop;                                               // (17) 0.02344
/*50  */         /* Compatibility syntax: */                                         // (16) 0.02344
/*52  */         if (featurestr[0] == '+') {                                         // (8) 0.03711
/*54  */             plus_features = g_list_append(plus_features,                    // (3) 0.04883
/*56  */                                           g_strdup(featurestr + 1));        // (0) 0.1016
/*58  */             continue;                                                       // (15) 0.02539
/*60  */         } else if (featurestr[0] == '-') {                                  // (6) 0.04102
/*62  */             minus_features = g_list_append(minus_features,                  // (2) 0.04883
/*64  */                                            g_strdup(featurestr + 1));       // 0.0
/*66  */             continue;                                                       // 0.0
/*68  */         }                                                                   // 0.0
/*72  */         eq = strchr(featurestr, '=');                                       // 0.0
/*74  */         if (eq) {                                                           // 0.0
/*76  */             *eq++ = 0;                                                      // 0.0
/*78  */             val = eq;                                                       // 0.0
/*80  */         } else {                                                            // 0.0
/*82  */             val = "on";                                                     // 0.0
/*84  */         }                                                                   // 0.0
/*88  */         feat2prop(featurestr);                                              // 0.0
/*90  */         name = featurestr;                                                  // 0.0
/*94  */         if (g_list_find_custom(plus_features, name, compare_string)) {      // 0.0
/*96  */             error_report("warning: Ambiguous CPU model string. "            // 0.0
/*98  */                          "Don't mix both \"+%s\" and \"%s=%s\"",            // 0.0
/*100 */                          name, name, val);                                  // 0.0
/*102 */             ambiguous = true;                                               // 0.0
/*104 */         }                                                                   // 0.0
/*106 */         if (g_list_find_custom(minus_features, name, compare_string)) {     // 0.0
/*108 */             error_report("warning: Ambiguous CPU model string. "            // 0.0
/*110 */                          "Don't mix both \"-%s\" and \"%s=%s\"",            // 0.0
/*112 */                          name, name, val);                                  // 0.0
/*114 */             ambiguous = true;                                               // 0.0
/*116 */         }                                                                   // 0.0
/*120 */         /* Special case: */                                                 // 0.0
/*122 */         if (!strcmp(name, "tsc-freq")) {                                    // 0.0
/*124 */             int64_t tsc_freq;                                               // 0.0
/*128 */             tsc_freq = qemu_strtosz_metric(val, NULL);                      // 0.0
/*130 */             if (tsc_freq < 0) {                                             // 0.0
/*132 */                 error_setg(errp, "bad numerical value %s", val);            // 0.0
/*134 */                 return;                                                     // 0.0
/*136 */             }                                                               // 0.0
/*138 */             snprintf(num, sizeof(num), "%" PRId64, tsc_freq);               // 0.0
/*140 */             val = num;                                                      // 0.0
/*142 */             name = "tsc-frequency";                                         // 0.0
/*144 */         }                                                                   // 0.0
/*148 */         prop = g_new0(typeof(*prop), 1);                                    // 0.0
/*150 */         prop->driver = typename;                                            // 0.0
/*152 */         prop->property = g_strdup(name);                                    // 0.0
/*154 */         prop->value = g_strdup(val);                                        // 0.0
/*156 */         prop->errp = &error_fatal;                                          // 0.0
/*158 */         qdev_prop_register_global(prop);                                    // 0.0
/*160 */     }                                                                       // 0.0
/*164 */     if (ambiguous) {                                                        // 0.0
/*166 */         error_report("warning: Compatibility of ambiguous CPU model "       // 0.0
/*168 */                      "strings won't be kept on future QEMU versions");      // 0.0
/*170 */     }                                                                       // 0.0
/*172 */ }                                                                           // 0.0
