// commit message qemu@9c5ce8db2e (target=0, prob=0.09319389, correct=True): vl: Switch qemu_uuid to QemuUUID
/*0  */ UuidInfo *qmp_query_uuid(Error **errp)                                          // (6) 0.05231
/*2  */ {                                                                               // (10) 0.003077
/*4  */     UuidInfo *info = g_malloc0(sizeof(*info));                                  // (5) 0.06154
/*6  */     char uuid[64];                                                              // (8) 0.02769
/*10 */     snprintf(uuid, sizeof(uuid), UUID_FMT, qemu_uuid[0], qemu_uuid[1],          // (3) 0.1169
/*12 */                    qemu_uuid[2], qemu_uuid[3], qemu_uuid[4], qemu_uuid[5],      // (0) 0.1662
/*14 */                    qemu_uuid[6], qemu_uuid[7], qemu_uuid[8], qemu_uuid[9],      // (1) 0.1662
/*16 */                    qemu_uuid[10], qemu_uuid[11], qemu_uuid[12], qemu_uuid[13],  // (2) 0.1662
/*18 */                    qemu_uuid[14], qemu_uuid[15]);                               // (4) 0.1108
/*22 */     info->UUID = g_strdup(uuid);                                                // (7) 0.05231
/*24 */     return info;                                                                // (9) 0.01846
/*26 */ }                                                                               // (11) 0.003077
