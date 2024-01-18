// commit message FFmpeg@16c6795465 (target=0, prob=0.46648237, correct=True): lavd/x11grab: check 32-bits color masks.
/*0   */ x11grab_read_header(AVFormatContext *s1)                                                                                                     // (10) 0.0293
/*2   */ {                                                                                                                                            // (30) 0.001954
/*4   */     struct x11grab *x11grab = s1->priv_data;                                                                                                 // (6) 0.03711
/*6   */     Display *dpy;                                                                                                                            // (22) 0.01563
/*8   */     AVStream *st = NULL;                                                                                                                     // (14) 0.01953
/*10  */     enum AVPixelFormat input_pixfmt;                                                                                                         // (11) 0.0293
/*12  */     XImage *image;                                                                                                                           // (23) 0.01562
/*14  */     int x_off = 0;                                                                                                                           // (18) 0.01953
/*16  */     int y_off = 0;                                                                                                                           // (15) 0.01953
/*18  */     int screen;                                                                                                                              // (28) 0.01172
/*20  */     int use_shm;                                                                                                                             // (19) 0.01758
/*22  */     char *dpyname, *offset;                                                                                                                  // (12) 0.02344
/*24  */     int ret = 0;                                                                                                                             // (24) 0.01562
/*26  */     Colormap color_map;                                                                                                                      // (17) 0.01953
/*28  */     XColor color[256];                                                                                                                       // (20) 0.01758
/*30  */     int i;                                                                                                                                   // (27) 0.01172
/*34  */     dpyname = av_strdup(s1->filename);                                                                                                       // (7) 0.03711
/*36  */     if (!dpyname)                                                                                                                            // (21) 0.01758
/*38  */         goto out;                                                                                                                            // (16) 0.01953
/*42  */     offset = strchr(dpyname, '+');                                                                                                           // (9) 0.03125
/*44  */     if (offset) {                                                                                                                            // (25) 0.01562
/*46  */         sscanf(offset, "%d,%d", &x_off, &y_off);                                                                                             // (3) 0.05664
/*48  */         if (strstr(offset, "nomouse")) {                                                                                                     // (8) 0.03711
/*50  */             av_log(s1, AV_LOG_WARNING,                                                                                                       // (4) 0.04687
/*52  */                    "'nomouse' specification in argument is deprecated: "                                                                     // (2) 0.05664
/*54  */                    "use 'draw_mouse' option with value 0 instead\n");                                                                        // (1) 0.06445
/*56  */             x11grab->draw_mouse = 0;                                                                                                         // (5) 0.04102
/*58  */         }                                                                                                                                    // (26) 0.01562
/*60  */         *offset= 0;                                                                                                                          // (13) 0.02344
/*62  */     }                                                                                                                                        // (29) 0.007812
/*66  */     av_log(s1, AV_LOG_INFO, "device: %s -> display: %s x: %d y: %d width: %d height: %d\n",                                                  // (0) 0.08789
/*68  */            s1->filename, dpyname, x_off, y_off, x11grab->width, x11grab->height);                                                            // 0.0
/*72  */     dpy = XOpenDisplay(dpyname);                                                                                                             // 0.0
/*74  */     av_freep(&dpyname);                                                                                                                      // 0.0
/*76  */     if(!dpy) {                                                                                                                               // 0.0
/*78  */         av_log(s1, AV_LOG_ERROR, "Could not open X display.\n");                                                                             // 0.0
/*80  */         ret = AVERROR(EIO);                                                                                                                  // 0.0
/*82  */         goto out;                                                                                                                            // 0.0
/*84  */     }                                                                                                                                        // 0.0
/*88  */     st = avformat_new_stream(s1, NULL);                                                                                                      // 0.0
/*90  */     if (!st) {                                                                                                                               // 0.0
/*92  */         ret = AVERROR(ENOMEM);                                                                                                               // 0.0
/*94  */         goto out;                                                                                                                            // 0.0
/*96  */     }                                                                                                                                        // 0.0
/*98  */     avpriv_set_pts_info(st, 64, 1, 1000000); /* 64 bits pts in us */                                                                         // 0.0
/*102 */     screen = DefaultScreen(dpy);                                                                                                             // 0.0
/*106 */     if (x11grab->follow_mouse) {                                                                                                             // 0.0
/*108 */         int screen_w, screen_h;                                                                                                              // 0.0
/*110 */         Window w;                                                                                                                            // 0.0
/*114 */         screen_w = DisplayWidth(dpy, screen);                                                                                                // 0.0
/*116 */         screen_h = DisplayHeight(dpy, screen);                                                                                               // 0.0
/*118 */         XQueryPointer(dpy, RootWindow(dpy, screen), &w, &w, &x_off, &y_off, &ret, &ret, &ret);                                               // 0.0
/*120 */         x_off -= x11grab->width / 2;                                                                                                         // 0.0
/*122 */         y_off -= x11grab->height / 2;                                                                                                        // 0.0
/*124 */         x_off = FFMIN(FFMAX(x_off, 0), screen_w - x11grab->width);                                                                           // 0.0
/*126 */         y_off = FFMIN(FFMAX(y_off, 0), screen_h - x11grab->height);                                                                          // 0.0
/*128 */         av_log(s1, AV_LOG_INFO, "followmouse is enabled, resetting grabbing region to x: %d y: %d\n", x_off, y_off);                         // 0.0
/*130 */     }                                                                                                                                        // 0.0
/*134 */     use_shm = XShmQueryExtension(dpy);                                                                                                       // 0.0
/*136 */     av_log(s1, AV_LOG_INFO, "shared memory extension%s found\n", use_shm ? "" : " not");                                                     // 0.0
/*140 */     if(use_shm) {                                                                                                                            // 0.0
/*142 */         int scr = XDefaultScreen(dpy);                                                                                                       // 0.0
/*144 */         image = XShmCreateImage(dpy,                                                                                                         // 0.0
/*146 */                                 DefaultVisual(dpy, scr),                                                                                     // 0.0
/*148 */                                 DefaultDepth(dpy, scr),                                                                                      // 0.0
/*150 */                                 ZPixmap,                                                                                                     // 0.0
/*152 */                                 NULL,                                                                                                        // 0.0
/*154 */                                 &x11grab->shminfo,                                                                                           // 0.0
/*156 */                                 x11grab->width, x11grab->height);                                                                            // 0.0
/*158 */         x11grab->shminfo.shmid = shmget(IPC_PRIVATE,                                                                                         // 0.0
/*160 */                                         image->bytes_per_line * image->height,                                                               // 0.0
/*162 */                                         IPC_CREAT|0777);                                                                                     // 0.0
/*164 */         if (x11grab->shminfo.shmid == -1) {                                                                                                  // 0.0
/*166 */             av_log(s1, AV_LOG_ERROR, "Fatal: Can't get shared memory!\n");                                                                   // 0.0
/*168 */             ret = AVERROR(ENOMEM);                                                                                                           // 0.0
/*170 */             goto out;                                                                                                                        // 0.0
/*172 */         }                                                                                                                                    // 0.0
/*174 */         x11grab->shminfo.shmaddr = image->data = shmat(x11grab->shminfo.shmid, 0, 0);                                                        // 0.0
/*176 */         x11grab->shminfo.readOnly = False;                                                                                                   // 0.0
/*180 */         if (!XShmAttach(dpy, &x11grab->shminfo)) {                                                                                           // 0.0
/*182 */             av_log(s1, AV_LOG_ERROR, "Fatal: Failed to attach shared memory!\n");                                                            // 0.0
/*184 */             /* needs some better error subroutine :) */                                                                                      // 0.0
/*186 */             ret = AVERROR(EIO);                                                                                                              // 0.0
/*188 */             goto out;                                                                                                                        // 0.0
/*190 */         }                                                                                                                                    // 0.0
/*192 */     } else {                                                                                                                                 // 0.0
/*194 */         image = XGetImage(dpy, RootWindow(dpy, screen),                                                                                      // 0.0
/*196 */                           x_off,y_off,                                                                                                       // 0.0
/*198 */                           x11grab->width, x11grab->height,                                                                                   // 0.0
/*200 */                           AllPlanes, ZPixmap);                                                                                               // 0.0
/*202 */     }                                                                                                                                        // 0.0
/*206 */     switch (image->bits_per_pixel) {                                                                                                         // 0.0
/*208 */     case 8:                                                                                                                                  // 0.0
/*210 */         av_log (s1, AV_LOG_DEBUG, "8 bit palette\n");                                                                                        // 0.0
/*212 */         input_pixfmt = AV_PIX_FMT_PAL8;                                                                                                      // 0.0
/*214 */         color_map = DefaultColormap(dpy, screen);                                                                                            // 0.0
/*216 */         for (i = 0; i < 256; ++i)                                                                                                            // 0.0
/*218 */             color[i].pixel = i;                                                                                                              // 0.0
/*220 */         XQueryColors(dpy, color_map, color, 256);                                                                                            // 0.0
/*222 */         for (i = 0; i < 256; ++i)                                                                                                            // 0.0
/*224 */             x11grab->palette[i] = (color[i].red   & 0xFF00) << 8 |                                                                           // 0.0
/*226 */                                   (color[i].green & 0xFF00)      |                                                                           // 0.0
/*228 */                                   (color[i].blue  & 0xFF00) >> 8;                                                                            // 0.0
/*230 */         x11grab->palette_changed = 1;                                                                                                        // 0.0
/*232 */         break;                                                                                                                               // 0.0
/*234 */     case 16:                                                                                                                                 // 0.0
/*236 */         if (       image->red_mask   == 0xf800 &&                                                                                            // 0.0
/*238 */                    image->green_mask == 0x07e0 &&                                                                                            // 0.0
/*240 */                    image->blue_mask  == 0x001f ) {                                                                                           // 0.0
/*242 */             av_log (s1, AV_LOG_DEBUG, "16 bit RGB565\n");                                                                                    // 0.0
/*244 */             input_pixfmt = AV_PIX_FMT_RGB565;                                                                                                // 0.0
/*246 */         } else if (image->red_mask   == 0x7c00 &&                                                                                            // 0.0
/*248 */                    image->green_mask == 0x03e0 &&                                                                                            // 0.0
/*250 */                    image->blue_mask  == 0x001f ) {                                                                                           // 0.0
/*252 */             av_log(s1, AV_LOG_DEBUG, "16 bit RGB555\n");                                                                                     // 0.0
/*254 */             input_pixfmt = AV_PIX_FMT_RGB555;                                                                                                // 0.0
/*256 */         } else {                                                                                                                             // 0.0
/*258 */             av_log(s1, AV_LOG_ERROR, "RGB ordering at image depth %i not supported ... aborting\n", image->bits_per_pixel);                  // 0.0
/*260 */             av_log(s1, AV_LOG_ERROR, "color masks: r 0x%.6lx g 0x%.6lx b 0x%.6lx\n", image->red_mask, image->green_mask, image->blue_mask);  // 0.0
/*262 */             ret = AVERROR_PATCHWELCOME;                                                                                                      // 0.0
/*264 */             goto out;                                                                                                                        // 0.0
/*266 */         }                                                                                                                                    // 0.0
/*268 */         break;                                                                                                                               // 0.0
/*270 */     case 24:                                                                                                                                 // 0.0
/*272 */         if (        image->red_mask   == 0xff0000 &&                                                                                         // 0.0
/*274 */                     image->green_mask == 0x00ff00 &&                                                                                         // 0.0
/*276 */                     image->blue_mask  == 0x0000ff ) {                                                                                        // 0.0
/*278 */             input_pixfmt = AV_PIX_FMT_BGR24;                                                                                                 // 0.0
/*280 */         } else if ( image->red_mask   == 0x0000ff &&                                                                                         // 0.0
/*282 */                     image->green_mask == 0x00ff00 &&                                                                                         // 0.0
/*284 */                     image->blue_mask  == 0xff0000 ) {                                                                                        // 0.0
/*286 */             input_pixfmt = AV_PIX_FMT_RGB24;                                                                                                 // 0.0
/*288 */         } else {                                                                                                                             // 0.0
/*290 */             av_log(s1, AV_LOG_ERROR,"rgb ordering at image depth %i not supported ... aborting\n", image->bits_per_pixel);                   // 0.0
/*292 */             av_log(s1, AV_LOG_ERROR, "color masks: r 0x%.6lx g 0x%.6lx b 0x%.6lx\n", image->red_mask, image->green_mask, image->blue_mask);  // 0.0
/*294 */             ret = AVERROR_PATCHWELCOME;                                                                                                      // 0.0
/*296 */             goto out;                                                                                                                        // 0.0
/*298 */         }                                                                                                                                    // 0.0
/*300 */         break;                                                                                                                               // 0.0
/*302 */     case 32:                                                                                                                                 // 0.0
/*304 */         input_pixfmt = AV_PIX_FMT_0RGB32;                                                                                                    // 0.0
/*306 */         break;                                                                                                                               // 0.0
/*308 */     default:                                                                                                                                 // 0.0
/*310 */         av_log(s1, AV_LOG_ERROR, "image depth %i not supported ... aborting\n", image->bits_per_pixel);                                      // 0.0
/*312 */         ret = AVERROR_PATCHWELCOME;                                                                                                          // 0.0
/*314 */         goto out;                                                                                                                            // 0.0
/*316 */     }                                                                                                                                        // 0.0
/*320 */     x11grab->frame_size = x11grab->width * x11grab->height * image->bits_per_pixel/8;                                                        // 0.0
/*322 */     x11grab->dpy = dpy;                                                                                                                      // 0.0
/*324 */     x11grab->time_base  = av_inv_q(x11grab->framerate);                                                                                      // 0.0
/*326 */     x11grab->time_frame = av_gettime() / av_q2d(x11grab->time_base);                                                                         // 0.0
/*328 */     x11grab->x_off = x_off;                                                                                                                  // 0.0
/*330 */     x11grab->y_off = y_off;                                                                                                                  // 0.0
/*332 */     x11grab->image = image;                                                                                                                  // 0.0
/*334 */     x11grab->use_shm = use_shm;                                                                                                              // 0.0
/*338 */     st->codec->codec_type = AVMEDIA_TYPE_VIDEO;                                                                                              // 0.0
/*340 */     st->codec->codec_id = AV_CODEC_ID_RAWVIDEO;                                                                                              // 0.0
/*342 */     st->codec->width  = x11grab->width;                                                                                                      // 0.0
/*344 */     st->codec->height = x11grab->height;                                                                                                     // 0.0
/*346 */     st->codec->pix_fmt = input_pixfmt;                                                                                                       // 0.0
/*348 */     st->codec->time_base = x11grab->time_base;                                                                                               // 0.0
/*350 */     st->codec->bit_rate = x11grab->frame_size * 1/av_q2d(x11grab->time_base) * 8;                                                            // 0.0
/*354 */ out:                                                                                                                                         // 0.0
/*356 */     av_free(dpyname);                                                                                                                        // 0.0
/*358 */     return ret;                                                                                                                              // 0.0
/*360 */ }                                                                                                                                            // 0.0
