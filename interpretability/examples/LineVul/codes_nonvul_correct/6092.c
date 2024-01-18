// commit message qemu@130257dc44 (target=0, prob=0.021075306, correct=True): char: Convert to new qapi union layout
/*0  */ static CharDriverState *qemu_chr_open_spice_port(const char *id,           // (4) 0.06575
/*2  */                                                  ChardevBackend *backend,  // (0) 0.1562
/*4  */                                                  ChardevReturn *ret,       // (1) 0.1507
/*6  */                                                  Error **errp)             // (2) 0.1452
/*8  */ {                                                                          // (15) 0.00274
/*10 */     const char *name = backend->spiceport->fqdn;                           // (6) 0.04932
/*12 */     CharDriverState *chr;                                                  // (9) 0.0274
/*14 */     SpiceCharDriver *s;                                                    // (12) 0.02466
/*18 */     if (name == NULL) {                                                    // (10) 0.0274
/*20 */         fprintf(stderr, "spice-qemu-char: missing name parameter\n");      // (3) 0.08219
/*22 */         return NULL;                                                       // (11) 0.0274
/*24 */     }                                                                      // (14) 0.01096
/*28 */     chr = chr_open("port", spice_port_set_fe_open);                        // (5) 0.06301
/*30 */     s = chr->opaque;                                                       // (8) 0.03014
/*32 */     s->sin.portname = g_strdup(name);                                      // (7) 0.04932
/*36 */     return chr;                                                            // (13) 0.01918
/*38 */ }                                                                          // (16) 0.00274
