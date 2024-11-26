#include <gtk/gtk.h>
#include <glib/gstdio.h>

/*
 * Global variables that will be used to store the input sequence from the calculator 
 * userInput is initialized within the main() function
*/ 
char *userInput;
int currentIndex = 0;


// Returns a string pointer to an allocated block of memory 100 bytes long
char *string_memory_allocate() {
  char *inputString = calloc(100, sizeof(char));
  if (inputString == NULL) {
    fprintf(stderr, "Not enough memory to store string input\n");
    exit(EXIT_FAILURE);
  }
  
  return inputString;
}

// Stores characters in string at currentIndex position
static void store_input_value(char value_to_store) { 
  userInput[currentIndex] = value_to_store;
  currentIndex++;
}

// Allocates a new string pointer using string_memory_allocate(), frees old pointer
char *reset_userInput(char *inputString) {
  char *resetString = string_memory_allocate();
  free(inputString);

  currentIndex = 0; // Resets index back to 0
  return resetString;
}

static void on_digit_click(GtkButton *button, gpointer user_data) {
  int digit = GPOINTER_TO_INT(user_data); // Retrieve digit input from pointer
  store_input_value(digit+'0'); // Store digit in input string

  g_print("The current input index location is: %d\n", currentIndex);
  g_print("Button %d was pressed!\n", digit);
  // Will pass this digit off into backend calculator processing functions
}

// Resizes the string to minimal necessary byte size
char *string_reallocate(char *stringInput) {
  char *resizedString = realloc(stringInput, strlen(userInput)+1);
  
  return resizedString;
}

// Acts as an input sequence break, processes' input and then resets it for next input sequence
static void on_equal_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("The equal button was pushed!\n");
    
    userInput = string_reallocate(userInput);
    g_printf("%s\n", userInput);
    g_printf("Size of string: %ld\n", strlen(userInput));
    userInput = reset_userInput(userInput);
    g_print("\n");
}

static void on_add_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("The add button was pushed!\n");

    store_input_value('+');
}


// Help callback function, outputs application instructions to whatever terminal was used to launch the application
static void on_help_button_clicked(GtkButton *button, gpointer user_data) {
    g_print("This app is in very early development, and only contains the basic calculator functions\n");
    g_print("These functions include: addition and subtraction.\nIn order to properly operate this calculator, follow these steps:\n");
    g_print("1: Enter the first number you would like to add, or subtract from\n2: Select the add or subtract operator\n3: Enter the second number you are adding with the first, or subtracting from the first\n");
    g_print("4: Press the equals button to show the sum/difference\n");
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

  GObject *help_button = gtk_builder_get_object(builder, "button_help");
  g_signal_connect(help_button, "clicked", G_CALLBACK(on_help_button_clicked), NULL);

  GObject *equal_button = gtk_builder_get_object(builder, "button_equal");
  g_signal_connect(equal_button, "clicked", G_CALLBACK(on_equal_button_clicked), NULL);

  GObject *addition_button = gtk_builder_get_object(builder, "button_add");
  g_signal_connect(addition_button, "clicked", G_CALLBACK(on_add_button_clicked), NULL);


  gtk_widget_set_visible (GTK_WIDGET (window), TRUE);

  /* We do not need the builder any more */
  g_object_unref (builder);
}


int main (int argc, char *argv[]) {
  userInput = string_memory_allocate(); // Initialize the input string

  #ifdef GTK_SRCDIR
    g_chdir (GTK_SRCDIR);
  #endif

  GtkApplication *calculatorApp = gtk_application_new ("com.github.methodmen", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (calculatorApp, "activate", G_CALLBACK (activate), NULL);

  int status = g_application_run (G_APPLICATION (calculatorApp), argc, argv);
  g_object_unref (calculatorApp);

  free(userInput);
  return status;
}
