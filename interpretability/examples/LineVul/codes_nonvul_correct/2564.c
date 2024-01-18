// commit message qemu@32bafa8fdd (target=0, prob=0.14651842, correct=True): qapi: Don't special-case simple union wrappers
/*0 */ static CharDriverState *vc_init(const char *id, ChardevBackend *backend,  // (1) 0.2396
/*2 */                                 ChardevReturn *ret, Error **errp)         // (0) 0.4479
/*4 */ {                                                                         // (3) 0.01042
/*6 */     return vc_handler(backend->u.vc, errp);                               // (2) 0.1979
/*8 */ }                                                                         // (4) 0.01042
