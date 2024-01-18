// commit message qemu@72cf2d4f0e (target=0, prob=0.0062830574, correct=True): Fix sys-queue.h conflict for good
/*0  */ int qemu_acl_remove(qemu_acl *acl,                     // (4) 0.08673
/*2  */                     const char *match)                 // (1) 0.1224
/*4  */ {                                                      // (12) 0.005102
/*6  */     qemu_acl_entry *entry;                             // (6) 0.06633
/*8  */     int i = 0;                                         // (8) 0.04082
/*12 */     TAILQ_FOREACH(entry, &acl->entries, next) {        // (3) 0.1071
/*14 */         i++;                                           // (7) 0.04592
/*16 */         if (strcmp(entry->match, match) == 0) {        // (2) 0.1122
/*18 */             TAILQ_REMOVE(&acl->entries, entry, next);  // (0) 0.1429
/*20 */             return i;                                  // (5) 0.07143
/*22 */         }                                              // (9) 0.04082
/*24 */     }                                                  // (11) 0.02041
/*26 */     return -1;                                         // (10) 0.03571
/*28 */ }                                                      // (13) 0.005102
