// commit message qemu@9d8256ebc0 (target=1, prob=0.9991604, correct=True): virgl: pass whole GL scanout dimensions
/*0  */ void sdl2_gl_scanout(DisplayChangeListener *dcl,                              // (12) 0.0332
/*2  */                      uint32_t backing_id, bool backing_y_0_top,               // (0) 0.07227
/*5  */                      uint32_t x, uint32_t y,                                  // (2) 0.0625
/*7  */                      uint32_t w, uint32_t h)                                  // (1) 0.0625
/*9  */ {                                                                             // (23) 0.001953
/*11 */     struct sdl2_console *scon = container_of(dcl, struct sdl2_console, dcl);  // (4) 0.05859
/*15 */     assert(scon->opengl);                                                     // (15) 0.02344
/*17 */     scon->x = x;                                                              // (17) 0.01953
/*19 */     scon->y = y;                                                              // (16) 0.01953
/*21 */     scon->w = w;                                                              // (18) 0.01953
/*23 */     scon->h = h;                                                              // (19) 0.01953
/*25 */     scon->tex_id = backing_id;                                                // (13) 0.02734
/*27 */     scon->y0_top = backing_y_0_top;                                           // (10) 0.03711
/*31 */     SDL_GL_MakeCurrent(scon->real_window, scon->winctx);                      // (7) 0.04688
/*35 */     if (scon->tex_id == 0 || scon->w == 0 || scon->h == 0) {                  // (5) 0.05664
/*37 */         sdl2_set_scanout_mode(scon, false);                                   // (9) 0.04492
/*39 */         return;                                                               // (20) 0.01758
/*41 */     }                                                                         // (21) 0.007812
/*45 */     sdl2_set_scanout_mode(scon, true);                                        // (11) 0.03711
/*47 */     if (!scon->fbo_id) {                                                      // (14) 0.02734
/*49 */         glGenFramebuffers(1, &scon->fbo_id);                                  // (8) 0.04687
/*51 */     }                                                                         // (22) 0.007812
/*55 */     glBindFramebuffer(GL_FRAMEBUFFER_EXT, scon->fbo_id);                      // (6) 0.04883
/*57 */     glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,   // (3) 0.06055
/*59 */                               GL_TEXTURE_2D, scon->tex_id, 0);                // 0.0
/*61 */ }                                                                             // 0.0
