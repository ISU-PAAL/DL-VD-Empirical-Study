// commit message qemu@161c4f20bf (target=1, prob=0.99918276, correct=True): vnc: remove a memory leak in zlib
/*0  */ static void vnc_disconnect_finish(VncState *vs)                        // (5) 0.04971
/*1  */ {                                                                      // (21) 0.002924
/*2  */     vnc_qmp_event(vs, QEVENT_VNC_DISCONNECTED);                        // (1) 0.0731
/*3  */     buffer_free(&vs->input);                                           // (13) 0.03216
/*4  */     buffer_free(&vs->output);                                          // (14) 0.03216
/*5  */     qobject_decref(vs->info);                                          // (11) 0.03801
/*6  */ #ifdef CONFIG_VNC_TLS                                                  // (18) 0.02924
/*7  */     vnc_tls_client_cleanup(vs);                                        // (7) 0.04678
/*8  */ #endif /* CONFIG_VNC_TLS */                                            // (15) 0.03216
/*9  */ #ifdef CONFIG_VNC_SASL                                                 // (16) 0.03216
/*10 */     vnc_sasl_client_cleanup(vs);                                       // (6) 0.04971
/*11 */ #endif /* CONFIG_VNC_SASL */                                           // (12) 0.03509
/*12 */     audio_del(vs);                                                     // (19) 0.02632
/*13 */     QTAILQ_REMOVE(&vs->vd->clients, vs, next);                         // (2) 0.06725
/*14 */     if (QTAILQ_EMPTY(&vs->vd->clients)) {                              // (4) 0.0614
/*15 */         dcl->idle = 1;                                                 // (8) 0.04386
/*16 */     }                                                                  // (20) 0.0117
/*17 */     qemu_remove_mouse_mode_change_notifier(&vs->mouse_mode_notifier);  // (0) 0.07895
/*18 */     vnc_remove_timer(vs->vd);                                          // (10) 0.04094
/*19 */     if (vs->vd->lock_key_sync)                                         // (9) 0.04386
/*20 */         qemu_remove_led_event_handler(vs->led);                        // (3) 0.06725
/*21 */     qemu_free(vs);                                                     // (17) 0.03216
/*22 */ }                                                                      // (22) 0.002924
