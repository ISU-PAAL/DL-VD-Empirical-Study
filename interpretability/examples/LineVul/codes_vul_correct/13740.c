// commit message FFmpeg@8d0a218058 (target=1, prob=0.63532233, correct=True): lavc/ffjni: fix uninitialized variable
/*0   */ int ff_jni_exception_get_summary(JNIEnv *env, jthrowable exception, char **error, void *log_ctx)       // (1) 0.06841
/*2   */ {                                                                                                      // (28) 0.00196
/*4   */     int ret = 0;                                                                                       // (24) 0.01562
/*8   */     AVBPrint bp;                                                                                       // (22) 0.01758
/*12  */     char *name = NULL;                                                                                 // (23) 0.01758
/*14  */     char *message = NULL;                                                                              // (21) 0.01758
/*18  */     jclass class_class = NULL;                                                                         // (18) 0.02148
/*20  */     jmethodID get_name_id = NULL;                                                                      // (15) 0.02736
/*24  */     jclass exception_class = NULL;                                                                     // (17) 0.02148
/*26  */     jmethodID get_message_id = NULL;                                                                   // (16) 0.02736
/*30  */     jstring string;                                                                                    // (25) 0.01367
/*34  */     av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);                                                  // (4) 0.05272
/*38  */     exception_class = (*env)->GetObjectClass(env, exception);                                          // (6) 0.0371
/*40  */     if ((*env)->ExceptionCheck(env)) {                                                                 // (14) 0.02929
/*42  */         (*env)->ExceptionClear(env);                                                                   // (11) 0.03124
/*44  */         av_log(log_ctx, AV_LOG_ERROR, "Could not find Throwable class\n");                             // (3) 0.06053
/*46  */         ret = AVERROR_EXTERNAL;                                                                        // (8) 0.0332
/*48  */         goto done;                                                                                     // (20) 0.01953
/*50  */     }                                                                                                  // (27) 0.007811
/*54  */     class_class = (*env)->GetObjectClass(env, exception_class);                                        // (5) 0.04101
/*56  */     if ((*env)->ExceptionCheck(env)) {                                                                 // (13) 0.02929
/*58  */         (*env)->ExceptionClear(env);                                                                   // (10) 0.03124
/*60  */         av_log(log_ctx, AV_LOG_ERROR, "Could not find Throwable class's class\n");                     // (2) 0.06444
/*62  */         ret = AVERROR_EXTERNAL;                                                                        // (7) 0.0332
/*64  */         goto done;                                                                                     // (19) 0.01953
/*66  */     }                                                                                                  // (26) 0.007811
/*70  */     get_name_id = (*env)->GetMethodID(env, class_class, "getName", "()Ljava/lang/String;");            // (0) 0.0723
/*72  */     if ((*env)->ExceptionCheck(env)) {                                                                 // (12) 0.02929
/*74  */         (*env)->ExceptionClear(env);                                                                   // (9) 0.03124
/*76  */         av_log(log_ctx, AV_LOG_ERROR, "Could not find method Class.getName()\n");                      // 0.0
/*78  */         ret = AVERROR_EXTERNAL;                                                                        // 0.0
/*80  */         goto done;                                                                                     // 0.0
/*82  */     }                                                                                                  // 0.0
/*86  */     string = (*env)->CallObjectMethod(env, exception_class, get_name_id);                              // 0.0
/*88  */     if ((*env)->ExceptionCheck(env)) {                                                                 // 0.0
/*90  */         (*env)->ExceptionClear(env);                                                                   // 0.0
/*92  */         av_log(log_ctx, AV_LOG_ERROR, "Class.getName() threw an exception\n");                         // 0.0
/*94  */         ret = AVERROR_EXTERNAL;                                                                        // 0.0
/*96  */         goto done;                                                                                     // 0.0
/*98  */     }                                                                                                  // 0.0
/*102 */     if (string) {                                                                                      // 0.0
/*104 */         name = ff_jni_jstring_to_utf_chars(env, string, log_ctx);                                      // 0.0
/*106 */         (*env)->DeleteLocalRef(env, string);                                                           // 0.0
/*108 */         string = NULL;                                                                                 // 0.0
/*110 */     }                                                                                                  // 0.0
/*114 */     get_message_id = (*env)->GetMethodID(env, exception_class, "getMessage", "()Ljava/lang/String;");  // 0.0
/*116 */     if ((*env)->ExceptionCheck(env)) {                                                                 // 0.0
/*118 */         (*env)->ExceptionClear(env);                                                                   // 0.0
/*120 */         av_log(log_ctx, AV_LOG_ERROR, "Could not find method java/lang/Throwable.getMessage()\n");     // 0.0
/*122 */         ret = AVERROR_EXTERNAL;                                                                        // 0.0
/*124 */         goto done;                                                                                     // 0.0
/*126 */     }                                                                                                  // 0.0
/*130 */     string = (*env)->CallObjectMethod(env, exception, get_message_id);                                 // 0.0
/*132 */     if ((*env)->ExceptionCheck(env)) {                                                                 // 0.0
/*134 */         (*env)->ExceptionClear(env);                                                                   // 0.0
/*136 */         av_log(log_ctx, AV_LOG_ERROR, "Throwable.getMessage() threw an exception\n");                  // 0.0
/*138 */         ret = AVERROR_EXTERNAL;                                                                        // 0.0
/*140 */         goto done;                                                                                     // 0.0
/*142 */     }                                                                                                  // 0.0
/*146 */     if (string) {                                                                                      // 0.0
/*148 */         message = ff_jni_jstring_to_utf_chars(env, string, log_ctx);                                   // 0.0
/*150 */         (*env)->DeleteLocalRef(env, string);                                                           // 0.0
/*152 */         string = NULL;                                                                                 // 0.0
/*154 */     }                                                                                                  // 0.0
/*158 */     if (name && message) {                                                                             // 0.0
/*160 */         av_bprintf(&bp, "%s: %s", name, message);                                                      // 0.0
/*162 */     } else if (name && !message) {                                                                     // 0.0
/*164 */         av_bprintf(&bp, "%s occurred", name);                                                          // 0.0
/*166 */     } else if (!name && message) {                                                                     // 0.0
/*168 */         av_bprintf(&bp, "Exception: %s", message);                                                     // 0.0
/*170 */     } else {                                                                                           // 0.0
/*172 */         av_log(log_ctx, AV_LOG_WARNING, "Could not retreive exception name and message\n");            // 0.0
/*174 */         av_bprintf(&bp, "Exception occurred");                                                         // 0.0
/*176 */     }                                                                                                  // 0.0
/*180 */     ret = av_bprint_finalize(&bp, error);                                                              // 0.0
/*182 */ done:                                                                                                  // 0.0
/*186 */     av_free(name);                                                                                     // 0.0
/*188 */     av_free(message);                                                                                  // 0.0
/*192 */     if (class_class) {                                                                                 // 0.0
/*194 */         (*env)->DeleteLocalRef(env, class_class);                                                      // 0.0
/*196 */     }                                                                                                  // 0.0
/*200 */     if (exception_class) {                                                                             // 0.0
/*202 */         (*env)->DeleteLocalRef(env, exception_class);                                                  // 0.0
/*204 */     }                                                                                                  // 0.0
/*208 */     if (string) {                                                                                      // 0.0
/*210 */         (*env)->DeleteLocalRef(env, string);                                                           // 0.0
/*212 */     }                                                                                                  // 0.0
/*216 */     return ret;                                                                                        // 0.0
/*218 */ }                                                                                                      // 0.0
