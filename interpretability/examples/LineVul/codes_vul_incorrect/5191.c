// commit message qemu@3401c0d95f (target=1, prob=0.2594254, correct=False): Refactor and fix do_sendkey (Jan Kiszka).
/*0  */ static void do_send_key(const char *string)              // (15) 0.02539
/*2  */ {                                                        // (33) 0.001953
/*4  */     char keybuf[16], *q;                                 // (19) 0.02344
/*6  */     uint8_t keycodes[16];                                // (21) 0.02344
/*8  */     const char *p;                                       // (27) 0.01562
/*10 */     int nb_keycodes, keycode, i;                         // (10) 0.0293
/*14 */     nb_keycodes = 0;                                     // (24) 0.02148
/*16 */     p = string;                                          // (30) 0.01367
/*18 */     while (*p != '\0') {                                 // (20) 0.02344
/*20 */         q = keybuf;                                      // (22) 0.02344
/*22 */         while (*p != '\0' && *p != '-') {                // (4) 0.04492
/*24 */             if ((q - keybuf) < sizeof(keybuf) - 1) {     // (1) 0.05469
/*26 */                 *q++ = *p;                               // (5) 0.04297
/*28 */             }                                            // (23) 0.02344
/*30 */             p++;                                         // (17) 0.02539
/*32 */         }                                                // (28) 0.01562
/*34 */         *q = '\0';                                       // (14) 0.02734
/*36 */         keycode = get_keycode(keybuf);                   // (8) 0.03516
/*38 */         if (keycode < 0) {                               // (11) 0.0293
/*40 */             term_printf("unknown key: '%s'\n", keybuf);  // (0) 0.05469
/*42 */             return;                                      // (18) 0.02539
/*44 */         }                                                // (29) 0.01562
/*46 */         keycodes[nb_keycodes++] = keycode;               // (6) 0.03906
/*48 */         if (*p == '\0')                                  // (12) 0.0293
/*50 */             break;                                       // (16) 0.02539
/*52 */         p++;                                             // (25) 0.01758
/*54 */     }                                                    // (32) 0.007812
/*56 */     /* key down events */                                // (26) 0.01563
/*58 */     for(i = 0; i < nb_keycodes; i++) {                   // (7) 0.03906
/*60 */         keycode = keycodes[i];                           // (13) 0.0293
/*62 */         if (keycode & 0x80)                              // (9) 0.03125
/*64 */             kbd_put_keycode(0xe0);                       // (3) 0.04492
/*66 */         kbd_put_keycode(keycode & 0x7f);                 // (2) 0.04492
/*68 */     }                                                    // (31) 0.007813
/*70 */     /* key up events */                                  // 0.0
/*72 */     for(i = nb_keycodes - 1; i >= 0; i--) {              // 0.0
/*74 */         keycode = keycodes[i];                           // 0.0
/*76 */         if (keycode & 0x80)                              // 0.0
/*78 */             kbd_put_keycode(0xe0);                       // 0.0
/*80 */         kbd_put_keycode(keycode | 0x80);                 // 0.0
/*82 */     }                                                    // 0.0
/*84 */ }                                                        // 0.0
