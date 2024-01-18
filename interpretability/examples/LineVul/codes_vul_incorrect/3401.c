// commit message qemu@bea60dd767 (target=1, prob=0.32401893, correct=False): ui/vnc: fix potential memory corruption issues
/*0   */ static int protocol_client_init(VncState *vs, uint8_t *data, size_t len)  // (2) 0.05078
/*2   */ {                                                                         // (29) 0.001953
/*4   */     char buf[1024];                                                       // (25) 0.01563
/*6   */     VncShareMode mode;                                                    // (18) 0.01758
/*8   */     int size;                                                             // (28) 0.01172
/*12  */     mode = data[0] ? VNC_SHARE_MODE_SHARED : VNC_SHARE_MODE_EXCLUSIVE;    // (1) 0.0625
/*14  */     switch (vs->vd->share_policy) {                                       // (16) 0.02734
/*16  */     case VNC_SHARE_POLICY_IGNORE:                                         // (14) 0.03125
/*18  */         /*                                                                // (26) 0.01562
/*20  */          * Ignore the shared flag.  Nothing to do here.                   // (7) 0.03906
/*22  */          *                                                                // (19) 0.01758
/*24  */          * Doesn't conform to the rfb spec but is traditional qemu        // (4) 0.04492
/*26  */          * behavior, thus left here as option for compatibility           // (11) 0.03516
/*28  */          * reasons.                                                       // (17) 0.02148
/*30  */          */                                                               // (20) 0.01758
/*32  */         break;                                                            // (21) 0.01758
/*34  */     case VNC_SHARE_POLICY_ALLOW_EXCLUSIVE:                                // (8) 0.03906
/*36  */         /*                                                                // (27) 0.01562
/*38  */          * Policy: Allow clients ask for exclusive access.                // (12) 0.03516
/*40  */          *                                                                // (22) 0.01758
/*42  */          * Implementation: When a client asks for exclusive access,       // (10) 0.03711
/*44  */          * disconnect all others. Shared connects are allowed as long     // (9) 0.03711
/*46  */          * as no exclusive connection exists.                             // (15) 0.0293
/*48  */          *                                                                // (23) 0.01758
/*50  */          * This is how the rfb spec suggests to handle the shared flag.   // (3) 0.04492
/*52  */          */                                                               // (24) 0.01758
/*54  */         if (mode == VNC_SHARE_MODE_EXCLUSIVE) {                           // (5) 0.04492
/*56  */             VncState *client;                                             // (13) 0.0332
/*58  */             QTAILQ_FOREACH(client, &vs->vd->clients, next) {              // (0) 0.0625
/*60  */                 if (vs == client) {                                       // (6) 0.04297
/*62  */                     continue;                                             // 0.0
/*64  */                 }                                                         // 0.0
/*66  */                 if (client->share_mode != VNC_SHARE_MODE_EXCLUSIVE &&     // 0.0
/*68  */                     client->share_mode != VNC_SHARE_MODE_SHARED) {        // 0.0
/*70  */                     continue;                                             // 0.0
/*72  */                 }                                                         // 0.0
/*74  */                 vnc_disconnect_start(client);                             // 0.0
/*76  */             }                                                             // 0.0
/*78  */         }                                                                 // 0.0
/*80  */         if (mode == VNC_SHARE_MODE_SHARED) {                              // 0.0
/*82  */             if (vs->vd->num_exclusive > 0) {                              // 0.0
/*84  */                 vnc_disconnect_start(vs);                                 // 0.0
/*86  */                 return 0;                                                 // 0.0
/*88  */             }                                                             // 0.0
/*90  */         }                                                                 // 0.0
/*92  */         break;                                                            // 0.0
/*94  */     case VNC_SHARE_POLICY_FORCE_SHARED:                                   // 0.0
/*96  */         /*                                                                // 0.0
/*98  */          * Policy: Shared connects only.                                  // 0.0
/*100 */          * Implementation: Disallow clients asking for exclusive access.  // 0.0
/*102 */          *                                                                // 0.0
/*104 */          * Useful for shared desktop sessions where you don't want        // 0.0
/*106 */          * someone forgetting to say -shared when running the vnc         // 0.0
/*108 */          * client disconnect everybody else.                              // 0.0
/*110 */          */                                                               // 0.0
/*112 */         if (mode == VNC_SHARE_MODE_EXCLUSIVE) {                           // 0.0
/*114 */             vnc_disconnect_start(vs);                                     // 0.0
/*116 */             return 0;                                                     // 0.0
/*118 */         }                                                                 // 0.0
/*120 */         break;                                                            // 0.0
/*122 */     }                                                                     // 0.0
/*124 */     vnc_set_share_mode(vs, mode);                                         // 0.0
/*128 */     vs->client_width = surface_width(vs->vd->ds);                         // 0.0
/*130 */     vs->client_height = surface_height(vs->vd->ds);                       // 0.0
/*132 */     vnc_write_u16(vs, vs->client_width);                                  // 0.0
/*134 */     vnc_write_u16(vs, vs->client_height);                                 // 0.0
/*138 */     pixel_format_message(vs);                                             // 0.0
/*142 */     if (qemu_name)                                                        // 0.0
/*144 */         size = snprintf(buf, sizeof(buf), "QEMU (%s)", qemu_name);        // 0.0
/*146 */     else                                                                  // 0.0
/*148 */         size = snprintf(buf, sizeof(buf), "QEMU");                        // 0.0
/*152 */     vnc_write_u32(vs, size);                                              // 0.0
/*154 */     vnc_write(vs, buf, size);                                             // 0.0
/*156 */     vnc_flush(vs);                                                        // 0.0
/*160 */     vnc_client_cache_auth(vs);                                            // 0.0
/*162 */     vnc_qmp_event(vs, QAPI_EVENT_VNC_INITIALIZED);                        // 0.0
/*166 */     vnc_read_when(vs, protocol_client_msg, 1);                            // 0.0
/*170 */     return 0;                                                             // 0.0
/*172 */ }                                                                         // 0.0
