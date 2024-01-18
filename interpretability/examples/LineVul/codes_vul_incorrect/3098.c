// commit message qemu@0b5538c300 (target=1, prob=0.26037547, correct=False): simpletrace: Thread-safe tracing
/*0 */ void st_print_trace_file_status(FILE *stream, int (*stream_printf)(FILE *stream, const char *fmt, ...))  // (1) 0.3204
/*2 */ {                                                                                                        // (3) 0.009709
/*4 */     stream_printf(stream, "Trace file \"%s\" %s.\n",                                                     // (2) 0.2233
/*6 */                   trace_file_name, trace_file_enabled ? "on" : "off");                                   // (0) 0.3495
/*8 */ }                                                                                                        // (4) 0.009709
