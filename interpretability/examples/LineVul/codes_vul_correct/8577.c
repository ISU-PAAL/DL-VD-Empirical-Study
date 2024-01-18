// commit message qemu@456d606923 (target=1, prob=0.99912435, correct=True): qemu-char: Call fe_claim / fe_release when not using qdev chr properties
/*0  */ static int ipoctal_init(IPackDevice *ip)                                    // (17) 0.02734
/*2  */ {                                                                           // (20) 0.001953
/*4  */     IPOctalState *s = IPOCTAL(ip);                                          // (13) 0.03125
/*6  */     unsigned i;                                                             // (19) 0.01172
/*10 */     for (i = 0; i < N_CHANNELS; i++) {                                      // (10) 0.03906
/*12 */         SCC2698Channel *ch = &s->ch[i];                                     // (8) 0.04297
/*14 */         ch->ipoctal = s;                                                    // (14) 0.0293
/*18 */         /* Redirect IP-Octal channels to host character devices */          // (9) 0.03906
/*20 */         if (ch->devpath) {                                                  // (15) 0.0293
/*22 */             const char chr_name[] = "ipoctal";                              // (7) 0.04688
/*24 */             char label[ARRAY_SIZE(chr_name) + 2];                           // (6) 0.05273
/*26 */             static int index;                                               // (16) 0.0293
/*30 */             snprintf(label, sizeof(label), "%s%d", chr_name, index);        // (4) 0.0625
/*34 */             ch->dev = qemu_chr_new(label, ch->devpath, NULL);               // (3) 0.06445
/*38 */             if (ch->dev) {                                                  // (11) 0.03516
/*40 */                 index++;                                                    // (12) 0.0332
/*43 */                 qemu_chr_add_handlers(ch->dev, hostdev_can_receive,         // (1) 0.07617
/*45 */                                       hostdev_receive, hostdev_event, ch);  // (0) 0.09766
/*47 */                 DPRINTF("Redirecting channel %u to %s (%s)\n",              // (2) 0.06445
/*49 */                         i, ch->devpath, label);                             // (5) 0.0625
/*51 */             } else {                                                        // (18) 0.02734
/*53 */                 DPRINTF("Could not redirect channel %u to %s\n",            // 0.0
/*55 */                         i, ch->devpath);                                    // 0.0
/*57 */             }                                                               // 0.0
/*59 */         }                                                                   // 0.0
/*61 */     }                                                                       // 0.0
/*65 */     return 0;                                                               // 0.0
/*67 */ }                                                                           // 0.0
