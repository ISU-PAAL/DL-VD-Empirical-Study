// commit message qemu@49aa4058ac (target=1, prob=0.45641243, correct=False): qemu-char: Fix potential out of bounds access to local arrays
/*0   */ QemuOpts *qemu_chr_parse_compat(const char *label, const char *filename)        // (4) 0.05469
/*2   */ {                                                                               // (25) 0.001953
/*4   */     char host[65], port[33], width[8], height[8];                               // (10) 0.03906
/*6   */     int pos;                                                                    // (22) 0.01172
/*8   */     const char *p;                                                              // (20) 0.01562
/*10  */     QemuOpts *opts;                                                             // (16) 0.02344
/*12  */     Error *local_err = NULL;                                                    // (17) 0.02148
/*16  */     opts = qemu_opts_create(qemu_find_opts("chardev"), label, 1, &local_err);   // (0) 0.07031
/*18  */     if (error_is_set(&local_err)) {                                             // (14) 0.03125
/*20  */         qerror_report_err(local_err);                                           // (13) 0.03516
/*22  */         error_free(local_err);                                                  // (15) 0.0293
/*24  */         return NULL;                                                            // (19) 0.01953
/*26  */     }                                                                           // (23) 0.007813
/*30  */     if (strstart(filename, "mon:", &p)) {                                       // (12) 0.03516
/*32  */         filename = p;                                                           // (18) 0.02148
/*34  */         qemu_opt_set(opts, "mux", "on");                                        // (7) 0.04883
/*36  */         if (strcmp(filename, "stdio") == 0) {                                   // (9) 0.04297
/*38  */             /* Monitor is muxed to stdio: do not exit on Ctrl+C by default      // (2) 0.05859
/*40  */              * but pass it to the guest.  Handle this only for compat syntax,   // (5) 0.05469
/*42  */              * for -chardev syntax we have special option for this.             // (8) 0.04883
/*44  */              * This is what -nographic did, redirecting+muxing serial+monitor   // (1) 0.05859
/*46  */              * to stdio causing Ctrl+C to be passed to guest. */                // (6) 0.05273
/*48  */             qemu_opt_set(opts, "signal", "off");                                // (3) 0.05664
/*50  */         }                                                                       // (21) 0.01562
/*52  */     }                                                                           // (24) 0.007812
/*56  */     if (strcmp(filename, "null")    == 0 ||                                     // (11) 0.03711
/*58  */         strcmp(filename, "pty")     == 0 ||                                     // 0.0
/*60  */         strcmp(filename, "msmouse") == 0 ||                                     // 0.0
/*62  */         strcmp(filename, "braille") == 0 ||                                     // 0.0
/*64  */         strcmp(filename, "stdio")   == 0) {                                     // 0.0
/*66  */         qemu_opt_set(opts, "backend", filename);                                // 0.0
/*68  */         return opts;                                                            // 0.0
/*70  */     }                                                                           // 0.0
/*72  */     if (strstart(filename, "vc", &p)) {                                         // 0.0
/*74  */         qemu_opt_set(opts, "backend", "vc");                                    // 0.0
/*76  */         if (*p == ':') {                                                        // 0.0
/*78  */             if (sscanf(p+1, "%8[0-9]x%8[0-9]", width, height) == 2) {           // 0.0
/*80  */                 /* pixels */                                                    // 0.0
/*82  */                 qemu_opt_set(opts, "width", width);                             // 0.0
/*84  */                 qemu_opt_set(opts, "height", height);                           // 0.0
/*86  */             } else if (sscanf(p+1, "%8[0-9]Cx%8[0-9]C", width, height) == 2) {  // 0.0
/*88  */                 /* chars */                                                     // 0.0
/*90  */                 qemu_opt_set(opts, "cols", width);                              // 0.0
/*92  */                 qemu_opt_set(opts, "rows", height);                             // 0.0
/*94  */             } else {                                                            // 0.0
/*96  */                 goto fail;                                                      // 0.0
/*98  */             }                                                                   // 0.0
/*100 */         }                                                                       // 0.0
/*102 */         return opts;                                                            // 0.0
/*104 */     }                                                                           // 0.0
/*106 */     if (strcmp(filename, "con:") == 0) {                                        // 0.0
/*108 */         qemu_opt_set(opts, "backend", "console");                               // 0.0
/*110 */         return opts;                                                            // 0.0
/*112 */     }                                                                           // 0.0
/*114 */     if (strstart(filename, "COM", NULL)) {                                      // 0.0
/*116 */         qemu_opt_set(opts, "backend", "serial");                                // 0.0
/*118 */         qemu_opt_set(opts, "path", filename);                                   // 0.0
/*120 */         return opts;                                                            // 0.0
/*122 */     }                                                                           // 0.0
/*124 */     if (strstart(filename, "file:", &p)) {                                      // 0.0
/*126 */         qemu_opt_set(opts, "backend", "file");                                  // 0.0
/*128 */         qemu_opt_set(opts, "path", p);                                          // 0.0
/*130 */         return opts;                                                            // 0.0
/*132 */     }                                                                           // 0.0
/*134 */     if (strstart(filename, "pipe:", &p)) {                                      // 0.0
/*136 */         qemu_opt_set(opts, "backend", "pipe");                                  // 0.0
/*138 */         qemu_opt_set(opts, "path", p);                                          // 0.0
/*140 */         return opts;                                                            // 0.0
/*142 */     }                                                                           // 0.0
/*144 */     if (strstart(filename, "tcp:", &p) ||                                       // 0.0
/*146 */         strstart(filename, "telnet:", &p)) {                                    // 0.0
/*148 */         if (sscanf(p, "%64[^:]:%32[^,]%n", host, port, &pos) < 2) {             // 0.0
/*150 */             host[0] = 0;                                                        // 0.0
/*152 */             if (sscanf(p, ":%32[^,]%n", port, &pos) < 1)                        // 0.0
/*154 */                 goto fail;                                                      // 0.0
/*156 */         }                                                                       // 0.0
/*158 */         qemu_opt_set(opts, "backend", "socket");                                // 0.0
/*160 */         qemu_opt_set(opts, "host", host);                                       // 0.0
/*162 */         qemu_opt_set(opts, "port", port);                                       // 0.0
/*164 */         if (p[pos] == ',') {                                                    // 0.0
/*166 */             if (qemu_opts_do_parse(opts, p+pos+1, NULL) != 0)                   // 0.0
/*168 */                 goto fail;                                                      // 0.0
/*170 */         }                                                                       // 0.0
/*172 */         if (strstart(filename, "telnet:", &p))                                  // 0.0
/*174 */             qemu_opt_set(opts, "telnet", "on");                                 // 0.0
/*176 */         return opts;                                                            // 0.0
/*178 */     }                                                                           // 0.0
/*180 */     if (strstart(filename, "udp:", &p)) {                                       // 0.0
/*182 */         qemu_opt_set(opts, "backend", "udp");                                   // 0.0
/*184 */         if (sscanf(p, "%64[^:]:%32[^@,]%n", host, port, &pos) < 2) {            // 0.0
/*186 */             host[0] = 0;                                                        // 0.0
/*188 */             if (sscanf(p, ":%32[^@,]%n", port, &pos) < 1) {                     // 0.0
/*190 */                 goto fail;                                                      // 0.0
/*192 */             }                                                                   // 0.0
/*194 */         }                                                                       // 0.0
/*196 */         qemu_opt_set(opts, "host", host);                                       // 0.0
/*198 */         qemu_opt_set(opts, "port", port);                                       // 0.0
/*200 */         if (p[pos] == '@') {                                                    // 0.0
/*202 */             p += pos + 1;                                                       // 0.0
/*204 */             if (sscanf(p, "%64[^:]:%32[^,]%n", host, port, &pos) < 2) {         // 0.0
/*206 */                 host[0] = 0;                                                    // 0.0
/*208 */                 if (sscanf(p, ":%32[^,]%n", port, &pos) < 1) {                  // 0.0
/*210 */                     goto fail;                                                  // 0.0
/*212 */                 }                                                               // 0.0
/*214 */             }                                                                   // 0.0
/*216 */             qemu_opt_set(opts, "localaddr", host);                              // 0.0
/*218 */             qemu_opt_set(opts, "localport", port);                              // 0.0
/*220 */         }                                                                       // 0.0
/*222 */         return opts;                                                            // 0.0
/*224 */     }                                                                           // 0.0
/*226 */     if (strstart(filename, "unix:", &p)) {                                      // 0.0
/*228 */         qemu_opt_set(opts, "backend", "socket");                                // 0.0
/*230 */         if (qemu_opts_do_parse(opts, p, "path") != 0)                           // 0.0
/*232 */             goto fail;                                                          // 0.0
/*234 */         return opts;                                                            // 0.0
/*236 */     }                                                                           // 0.0
/*238 */     if (strstart(filename, "/dev/parport", NULL) ||                             // 0.0
/*240 */         strstart(filename, "/dev/ppi", NULL)) {                                 // 0.0
/*242 */         qemu_opt_set(opts, "backend", "parport");                               // 0.0
/*244 */         qemu_opt_set(opts, "path", filename);                                   // 0.0
/*246 */         return opts;                                                            // 0.0
/*248 */     }                                                                           // 0.0
/*250 */     if (strstart(filename, "/dev/", NULL)) {                                    // 0.0
/*252 */         qemu_opt_set(opts, "backend", "tty");                                   // 0.0
/*254 */         qemu_opt_set(opts, "path", filename);                                   // 0.0
/*256 */         return opts;                                                            // 0.0
/*258 */     }                                                                           // 0.0
/*262 */ fail:                                                                           // 0.0
/*264 */     qemu_opts_del(opts);                                                        // 0.0
/*266 */     return NULL;                                                                // 0.0
/*268 */ }                                                                               // 0.0
