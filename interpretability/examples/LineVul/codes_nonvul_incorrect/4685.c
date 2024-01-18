// commit message FFmpeg@33d69a9008 (target=0, prob=0.5068853, correct=False): lavc/ffjni: remove use of private JniInvocation API to retreive the Java VM
/*0  */ JNIEnv *ff_jni_attach_env(int *attached, void *log_ctx)                                                                 // (9) 0.04883
/*2  */ {                                                                                                                       // (23) 0.001953
/*4  */     int ret = 0;                                                                                                        // (18) 0.01562
/*6  */     JNIEnv *env = NULL;                                                                                                 // (12) 0.02344
/*10 */     *attached = 0;                                                                                                      // (17) 0.01758
/*14 */     pthread_mutex_lock(&lock);                                                                                          // (11) 0.02539
/*16 */     if (java_vm == NULL && (java_vm = av_jni_get_java_vm(log_ctx)) == NULL) {                                           // (5) 0.06836
/*20 */         av_log(log_ctx, AV_LOG_INFO, "Retrieving current Java virtual machine using Android JniInvocation wrapper\n");  // (3) 0.07422
/*22 */         if (check_jni_invocation(log_ctx) == 0) {                                                                       // (8) 0.04883
/*24 */             if ((java_vm = get_java_vm(NULL, log_ctx)) != NULL ||                                                       // (6) 0.0625
/*26 */                 (java_vm = get_java_vm("libdvm.so", log_ctx)) != NULL ||                                                // (1) 0.07617
/*28 */                 (java_vm = get_java_vm("libart.so", log_ctx)) != NULL) {                                                // (2) 0.07617
/*30 */                 av_log(log_ctx, AV_LOG_INFO, "Found Java virtual machine using Android JniInvocation wrapper\n");       // (0) 0.08594
/*32 */             }                                                                                                           // (14) 0.02344
/*34 */         }                                                                                                               // (19) 0.01562
/*36 */     }                                                                                                                   // (21) 0.007812
/*38 */     pthread_mutex_unlock(&lock);                                                                                        // (10) 0.02734
/*42 */     if (!java_vm) {                                                                                                     // (15) 0.01953
/*44 */         av_log(log_ctx, AV_LOG_ERROR, "Could not retrieve a Java virtual machine\n");                                   // (7) 0.0625
/*46 */         return NULL;                                                                                                    // (16) 0.01953
/*48 */     }                                                                                                                   // (22) 0.007812
/*52 */     ret = (*java_vm)->GetEnv(java_vm, (void **)&env, JNI_VERSION_1_6);                                                  // (4) 0.06836
/*54 */     switch(ret) {                                                                                                       // (20) 0.01562
/*56 */     case JNI_EDETACHED:                                                                                                 // (13) 0.02344
/*58 */         if ((*java_vm)->AttachCurrentThread(java_vm, &env, NULL) != 0) {                                                // 0.0
/*60 */             av_log(log_ctx, AV_LOG_ERROR, "Failed to attach the JNI environment to the current thread\n");              // 0.0
/*62 */             env = NULL;                                                                                                 // 0.0
/*64 */         } else {                                                                                                        // 0.0
/*66 */             *attached = 1;                                                                                              // 0.0
/*68 */         }                                                                                                               // 0.0
/*70 */         break;                                                                                                          // 0.0
/*72 */     case JNI_OK:                                                                                                        // 0.0
/*74 */         break;                                                                                                          // 0.0
/*76 */     case JNI_EVERSION:                                                                                                  // 0.0
/*78 */         av_log(log_ctx, AV_LOG_ERROR, "The specified JNI version is not supported\n");                                  // 0.0
/*80 */         break;                                                                                                          // 0.0
/*82 */     default:                                                                                                            // 0.0
/*84 */         av_log(log_ctx, AV_LOG_ERROR, "Failed to get the JNI environment attached to this thread");                     // 0.0
/*86 */         break;                                                                                                          // 0.0
/*88 */     }                                                                                                                   // 0.0
/*92 */     return env;                                                                                                         // 0.0
/*94 */ }                                                                                                                       // 0.0
