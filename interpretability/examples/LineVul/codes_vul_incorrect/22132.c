// commit message qemu@60fe637bf0 (target=1, prob=0.20444518, correct=False): Start migrating migration code into a migration directory
/*0  */ static int unix_close(void *opaque)  // (1) 0.1935
/*2  */ {                                    // (5) 0.01613
/*4  */     QEMUFileSocket *s = opaque;      // (0) 0.2097
/*6  */     close(s->fd);                    // (2) 0.1452
/*8  */     g_free(s);                       // (3) 0.1452
/*10 */     return 0;                        // (4) 0.09677
/*12 */ }                                    // (6) 0.01613
