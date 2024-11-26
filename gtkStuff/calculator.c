#include <gtk/gtk.h>
#include <glib/gstdio.h>

static void quit_cb (GtkWindow *window) {
  gtk_window_close (window);
}

static void on_digit_click(GtkButton *button, gpointer user_data) {
  int digit = GPOINTER_TO_INT(user_data);
  g_print("Button %d was pressed!\n", digit);
  // Will pass this digit off into backend calculator processing functions
}

static void activate (GtkApplication *app, gpointer user_data) {
  /* Construct a GtkBuilder instance and load our UI description */
  GtkBuilder *builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "builder.ui", NULL);

  /* Connect signal handlers to the constructed widgets. */
  GObject *window = gtk_builder_get_object (builder, "window");
  gtk_window_set_application (GTK_WINDOW (window), app);

  // Creates buttons 0 through 9, connects them to the on_digit_click() function
  // builder.ui xml is where each button is "styled"
  for (int currentDigit = 0; currentDigit <= 9; currentDigit++) {
    char currentButton[10];
    sprintf(currentButton, "button%d", currentDigit);

    GObject *button = gtk_builder_get_object (builder, currentButton);
    g_signal_connect(button, "clicked", G_CALLBACK(on_digit_click), GINT_TO_POINTER(currentDigit));
  }

  gtk_widget_set_visible (GTK_WIDGET (window), TRUE);

  /* We do not need the builder any more */
  g_object_unref (builder);
}



int main (int argc, char *argv[]) {
  #ifdef GTK_SRCDIR
    g_chdir (GTK_SRCDIR);
  #endif

  GtkApplication *calculatorApp = gtk_application_new ("com.github.methodmen", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (calculatorApp, "activate", G_CALLBACK (activate), NULL);

  int status = g_application_run (G_APPLICATION (calculatorApp), argc, argv);
  g_object_unref (calculatorApp);

  return status;
}
