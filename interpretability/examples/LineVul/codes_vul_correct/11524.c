// commit message qemu@459db780be (target=1, prob=0.5412472, correct=True): utils: drop strtok_r from envlist_parse
/*0  */ envlist_parse(envlist_t *envlist, const char *env,    // (3) 0.06522
/*2  */     int (*callback)(envlist_t *, const char *))       // (4) 0.06159
/*4  */ {                                                     // (23) 0.003623
/*6  */ 	char *tmpenv, *envvar;                               // (9) 0.03623
/*8  */ 	char *envsave = NULL;                                // (11) 0.03261
/*12 */ 	assert(callback != NULL);                            // (15) 0.02536
/*16 */ 	if ((envlist == NULL) || (env == NULL))              // (7) 0.05072
/*18 */ 		return (EINVAL);                                    // (12) 0.02899
/*22 */ 	/*                                                   // (20) 0.007246
/*24 */ 	 * We need to make temporary copy of the env string  // (8) 0.04348
/*26 */ 	 * as strtok_r(3) modifies it while it tokenizes.    // (2) 0.06884
/*28 */ 	 */                                                  // (21) 0.007246
/*30 */ 	if ((tmpenv = strdup(env)) == NULL)                  // (6) 0.05435
/*32 */ 		return (errno);                                     // (16) 0.02536
/*36 */ 	envvar = strtok_r(tmpenv, ",", &envsave);            // (0) 0.07609
/*38 */ 	while (envvar != NULL) {                             // (10) 0.03261
/*40 */ 		if ((*callback)(envlist, envvar) != 0) {            // (5) 0.06159
/*42 */ 			free(tmpenv);                                      // (13) 0.02899
/*44 */ 			return (errno);                                    // (14) 0.02899
/*46 */ 		}                                                   // (19) 0.01087
/*48 */ 		envvar = strtok_r(NULL, ",", &envsave);             // (1) 0.07609
/*50 */ 	}                                                    // (22) 0.007246
/*54 */ 	free(tmpenv);                                        // (17) 0.02174
/*56 */ 	return (0);                                          // (18) 0.01812
/*58 */ }                                                     // (24) 0.003623
