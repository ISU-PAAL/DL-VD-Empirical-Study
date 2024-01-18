// commit message FFmpeg@ea97859c8c (target=1, prob=0.428983, correct=False): gdigrab: fix gdi object leak if using mouse
/*0   */ static void paint_mouse_pointer(AVFormatContext *s1, struct gdigrab *gdigrab)  // (5) 0.04883
/*2   */ {                                                                              // (25) 0.001953
/*4   */     CURSORINFO ci = {0};                                                       // (16) 0.02734
/*8   */ #define CURSOR_ERROR(str)                 \                                    // (2) 0.05469
/*10  */     if (!gdigrab->cursor_error_printed) {       \                              // (6) 0.04687
/*12  */         WIN32_API_ERROR(str);             \                                    // (0) 0.05664
/*14  */         gdigrab->cursor_error_printed = 1;      \                              // (3) 0.05273
/*16  */     }                                                                          // (24) 0.007812
/*20  */     ci.cbSize = sizeof(ci);                                                    // (17) 0.02539
/*24  */     if (GetCursorInfo(&ci)) {                                                  // (18) 0.02539
/*26  */         HCURSOR icon = CopyCursor(ci.hCursor);                                 // (7) 0.04492
/*28  */         ICONINFO info;                                                         // (21) 0.02344
/*30  */         POINT pos;                                                             // (22) 0.02148
/*32  */         RECT clip_rect = gdigrab->clip_rect;                                   // (9) 0.04297
/*34  */         HWND hwnd = gdigrab->hwnd;                                             // (11) 0.04102
/*36  */         info.hbmMask = NULL;                                                   // (15) 0.0293
/*38  */         info.hbmColor = NULL;                                                  // (14) 0.0293
/*42  */         if (ci.flags != CURSOR_SHOWING)                                        // (8) 0.04297
/*44  */             return;                                                            // (19) 0.02539
/*48  */         if (!icon) {                                                           // (20) 0.02344
/*50  */             /* Use the standard arrow cursor as a fallback.                    // (10) 0.04297
/*52  */              * You'll probably only hit this in Wine, which can't fetch        // (4) 0.05078
/*54  */              * the current system cursor. */                                   // (13) 0.03711
/*56  */             icon = CopyCursor(LoadCursor(NULL, IDC_ARROW));                    // (1) 0.05664
/*58  */         }                                                                      // (23) 0.01562
/*62  */         if (!GetIconInfo(icon, &info)) {                                       // (12) 0.03711
/*64  */             CURSOR_ERROR("Could not get icon info");                           // 0.0
/*66  */             goto icon_error;                                                   // 0.0
/*68  */         }                                                                      // 0.0
/*72  */         pos.x = ci.ptScreenPos.x - clip_rect.left - info.xHotspot;             // 0.0
/*74  */         pos.y = ci.ptScreenPos.y - clip_rect.top - info.yHotspot;              // 0.0
/*78  */         if (hwnd) {                                                            // 0.0
/*80  */             RECT rect;                                                         // 0.0
/*84  */             if (GetWindowRect(hwnd, &rect)) {                                  // 0.0
/*86  */                 pos.x -= rect.left;                                            // 0.0
/*88  */                 pos.y -= rect.top;                                             // 0.0
/*90  */             } else {                                                           // 0.0
/*92  */                 CURSOR_ERROR("Couldn't get window rectangle");                 // 0.0
/*94  */                 goto icon_error;                                               // 0.0
/*96  */             }                                                                  // 0.0
/*98  */         }                                                                      // 0.0
/*102 */         av_log(s1, AV_LOG_DEBUG, "Cursor pos (%li,%li) -> (%li,%li)\n",        // 0.0
/*104 */                 ci.ptScreenPos.x, ci.ptScreenPos.y, pos.x, pos.y);             // 0.0
/*108 */         if (pos.x >= 0 && pos.x <= clip_rect.right - clip_rect.left &&         // 0.0
/*110 */                 pos.y >= 0 && pos.y <= clip_rect.bottom - clip_rect.top) {     // 0.0
/*112 */             if (!DrawIcon(gdigrab->dest_hdc, pos.x, pos.y, icon))              // 0.0
/*114 */                 CURSOR_ERROR("Couldn't draw icon");                            // 0.0
/*116 */         }                                                                      // 0.0
/*120 */ icon_error:                                                                    // 0.0
/*126 */         if (icon)                                                              // 0.0
/*128 */             DestroyCursor(icon);                                               // 0.0
/*130 */     } else {                                                                   // 0.0
/*132 */         CURSOR_ERROR("Couldn't get cursor info");                              // 0.0
/*134 */     }                                                                          // 0.0
/*136 */ }                                                                              // 0.0
