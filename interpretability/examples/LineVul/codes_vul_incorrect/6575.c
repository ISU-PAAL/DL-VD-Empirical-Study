// commit message FFmpeg@65db4899fa (target=1, prob=0.18388455, correct=False): mmaldec: refactor to have more context per MMAL input buffer
/*0  */ static void input_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)  // (0) 0.2667
/*2  */ {                                                                            // (6) 0.009524
/*4  */     if (!buffer->cmd) {                                                      // (4) 0.09524
/*6  */         AVBufferRef *buf = buffer->user_data;                                // (1) 0.181
/*8  */         av_buffer_unref(&buf);                                               // (2) 0.1524
/*10 */     }                                                                        // (5) 0.0381
/*12 */     mmal_buffer_header_release(buffer);                                      // (3) 0.1333
/*14 */ }                                                                            // (7) 0.009524
