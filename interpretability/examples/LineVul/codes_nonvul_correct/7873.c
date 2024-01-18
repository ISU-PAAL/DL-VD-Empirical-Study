// commit message qemu@db1da1f2b5 (target=0, prob=0.049604736, correct=True): gtk: Use ctrl+alt+q for quit accelerator
/*0  */ static GtkWidget *gd_create_menu_machine(GtkDisplayState *s, GtkAccelGroup *accel_group)  // (3) 0.06055
/*2  */ {                                                                                         // (18) 0.001953
/*4  */     GtkWidget *machine_menu;                                                              // (16) 0.02148
/*6  */     GtkWidget *separator;                                                                 // (17) 0.01953
/*10 */     machine_menu = gtk_menu_new();                                                        // (15) 0.02734
/*12 */     gtk_menu_set_accel_group(GTK_MENU(machine_menu), accel_group);                        // (6) 0.05859
/*16 */     s->pause_item = gtk_check_menu_item_new_with_mnemonic(_("_Pause"));                   // (8) 0.05859
/*18 */     gtk_menu_shell_append(GTK_MENU_SHELL(machine_menu), s->pause_item);                   // (4) 0.06055
/*22 */     separator = gtk_separator_menu_item_new();                                            // (14) 0.03516
/*24 */     gtk_menu_shell_append(GTK_MENU_SHELL(machine_menu), separator);                       // (11) 0.05469
/*28 */     s->reset_item = gtk_menu_item_new_with_mnemonic(_("_Reset"));                         // (10) 0.05664
/*30 */     gtk_menu_shell_append(GTK_MENU_SHELL(machine_menu), s->reset_item);                   // (5) 0.06055
/*34 */     s->powerdown_item = gtk_menu_item_new_with_mnemonic(_("Power _Down"));                // (7) 0.05859
/*36 */     gtk_menu_shell_append(GTK_MENU_SHELL(machine_menu), s->powerdown_item);               // (2) 0.0625
/*40 */     separator = gtk_separator_menu_item_new();                                            // (13) 0.03516
/*42 */     gtk_menu_shell_append(GTK_MENU_SHELL(machine_menu), separator);                       // (12) 0.05469
/*46 */     s->quit_item = gtk_menu_item_new_with_mnemonic(_("_Quit"));                           // (9) 0.05664
/*48 */     gtk_menu_item_set_accel_path(GTK_MENU_ITEM(s->quit_item),                             // (1) 0.0625
/*50 */                                  "<QEMU>/Machine/Quit");                                  // (0) 0.08398
/*52 */     gtk_accel_map_add_entry("<QEMU>/Machine/Quit",                                        // 0.0
/*54 */                             GDK_KEY_q, GDK_CONTROL_MASK);                                 // 0.0
/*56 */     gtk_menu_shell_append(GTK_MENU_SHELL(machine_menu), s->quit_item);                    // 0.0
/*60 */     return machine_menu;                                                                  // 0.0
/*62 */ }                                                                                         // 0.0
