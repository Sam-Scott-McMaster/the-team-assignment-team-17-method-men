#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "bedmas.h"
#include "evaluateWithParentheses.h"

/*
 * Global variables that will be used to store the input sequence from the calculator
 * userInput is initialized within the main() function
 */
char *userInput;
GtkLabel *input_label;
int currentIndex = 0;

// Returns a string pointer to an allocated block of memory 100 bytes long
char *string_memory_allocate()
{
  char *inputString = calloc(100, sizeof(char));
  if (inputString == NULL)
  {
    fprintf(stderr, "Not enough memory to store string input\n");
    exit(EXIT_FAILURE);
  }

  return inputString;
}

// Stores characters in string at currentIndex position
static void store_input_value(char value_to_store)
{
  userInput[currentIndex] = value_to_store;
  currentIndex++;
}

// Allocates a new string pointer using string_memory_allocate(), frees old pointer
char *reset_userInput(char *inputString)
{
  char *resetString = string_memory_allocate();
  free(inputString);

  currentIndex = 0; // Resets index back to 0
  return resetString;
}

static void load_css()
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();

    // Load the CSS file
    gtk_css_provider_load_from_path(provider, "styles.css");

    // Apply the CSS provider globally to the display
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref(provider);
}

static void on_digit_click(GtkButton *button, gpointer user_data)
{
  int digit = GPOINTER_TO_INT(user_data); // Retrieve digit input from pointer
  store_input_value(digit + '0');         // Store digit in input string

  /// Label Code
  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text); // Update the label
  g_free(new_label_text);                          // Free memory for the temporary string

  g_print("The current input index location is: %d\n", currentIndex);
  g_print("Button %d was pressed!\n", digit);
  // Will pass this digit off into backend calculator processing functions
}

// Resizes the string to minimal necessary byte size
char *string_reallocate(char *stringInput)
{
  char *resizedString = realloc(stringInput, strlen(userInput) + 1);

  return resizedString;
}

// Acts as an input sequence break, processes' input and then resets it for next input sequence
static void on_equal_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The equal button was pushed!\n");

  userInput = string_reallocate(userInput);
  g_printf("%s\n", userInput);
  g_printf("Size of string: %ld\n", strlen(userInput));

  // =============== Pass input string to backend functions ===================
  int size = strlen(userInput);
  // adjusts the values of the inputted array
  char *adjustedArray = adjustValues(userInput, &size);

  // evaluates data to extract parentheses
  char *evaluatedArray = evaluateWithParentheses(adjustedArray, &size);
  // printf("Expression after evaluating parentheses: %s\n", evaluatedArray);

  double result = bedmasCalculation(evaluatedArray); // calulcates final result

  // Displays the calculated result to the screen of the calculator
  char *new_label_text = g_strdup_printf("%.3f", result);
  gtk_label_set_text(input_label, new_label_text); // Update the label
  g_free(new_label_text);                          // Free memory for the temporary string

  free(adjustedArray);
  if (evaluatedArray != adjustedArray)
  {
    free(evaluatedArray);
  }
  // ======================================

  userInput = reset_userInput(userInput); // Clear userInput string
  sprintf(userInput, "%f", result);       // Set userInput string to the result of the previous operations
  currentIndex = strlen(userInput);       // Set the new string index to the end of the result
  g_print("\n");
}

static void on_open_parenthesis_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The '(' button was pushed!\n");

  store_input_value('(');

  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}

static void on_close_parenthesis_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The ')' button was pushed!\n");

  store_input_value(')');

  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}

static void on_add_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The add button was pushed!\n");

  store_input_value('+');

  /// Label Code
  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}

static void on_subtract_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The subtract button was pushed!\n");

  store_input_value('-');

  /// Label Code
  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}

static void on_divide_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The divide button was pushed!\n");

  store_input_value('/');

  /// Label Code
  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}

static void on_multiply_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The multiply button was pushed!\n");

  store_input_value('*');

  /// Label Code
  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}

static void on_clear_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The clear button was pushed!\n");

  userInput = reset_userInput(userInput);

  /// Label Code
  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}

static void on_negative_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("The negative button was pushed!\n");

  store_input_value('~');

  /// Label Code
  char *new_label_text = g_strdup_printf("%s", userInput);
  gtk_label_set_text(input_label, new_label_text);
  g_free(new_label_text);
}
/* Callback for the "Help" button.
 * Displays information about how to use the calculator in the terminal.
 */
static void on_help_button_clicked(GtkButton *button, gpointer user_data)
{
  g_print("Calculator Application Help\n\n");
  g_print("This calculator application allows you to perform basic arithmetic operations.\n");
  g_print("Use the Help button in the application for quick guidance.\n\n");
  g_print("Features:\n");
  g_print("  - Supported Operations:\n");
  g_print("      +   Addition (e.g., 5 + 3)\n");
  g_print("      -   Subtraction (e.g., 8 - 2)\n");
  g_print("      *   Multiplication (e.g., 4 * 7)\n");
  g_print("      /   Division (e.g., 9 / 3)\n");
  g_print("      ~   Negativity Toggle (e.g., press ~ to toggle 5 to -5)\n");
  g_print("      ( ) Parentheses for grouping expressions (note: parentheses cannot be nested).\n\n");
  g_print("How to Use:\n");
  g_print("  1. Enter numbers using the digit buttons (0-9).\n");
  g_print("  2. Select an operation (+, -, *, /) to apply to the numbers.\n");
  g_print("  3. Use parentheses to prioritize parts of the calculation (e.g., 5 * (3 + 2)).\n");
  g_print("      - Nested parentheses are not supported.\n");
  g_print("  4. Press \"=\" to calculate and display the result.\n");
  g_print("  5. Press \"Clear\" to reset the input field for a new calculation.\n");
  g_print("  6. Press the \"Help\" button anytime to view this guide in the terminal.\n\n");
  g_print("Examples:\n");
  g_print("  - Simple Calculation: 12 + 4 = 16\n");
  g_print("  - Parentheses: 7 * (5 + 3) = 56\n");
  g_print("  - Multi-step Calculation: 8 / 2 + 3 * 4 = 14\n\n");
  g_print("Notes:\n");
  g_print("  - Decimal numbers are supported (e.g., 3.14, 0.5).\n");
  g_print("  - Invalid inputs or unsupported formats will display an error.\n");
  g_print("  - The application does not support nested parentheses or advanced operations like exponentiation.\n\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
  /* Construct a GtkBuilder instance and load our UI description */
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "builder.ui", NULL);

  /* Connect signal handlers to the constructed widgets. */
  GObject *window = gtk_builder_get_object(builder, "window");
  gtk_window_set_application(GTK_WINDOW(window), app);

  load_css();

  input_label = GTK_LABEL(gtk_builder_get_object(builder, "input_label"));

  // Creates buttons 0 through 9, connects them to the on_digit_click() function
  // builder.ui xml is where each button is "styled"
  for (int currentDigit = 0; currentDigit <= 9; currentDigit++)
  {
    char currentButton[10];
    sprintf(currentButton, "button%d", currentDigit);

    GObject *button = gtk_builder_get_object(builder, currentButton);
    g_signal_connect(button, "clicked", G_CALLBACK(on_digit_click), GINT_TO_POINTER(currentDigit));
  }

  GObject *help_button = gtk_builder_get_object(builder, "button_help");
  g_signal_connect(help_button, "clicked", G_CALLBACK(on_help_button_clicked), NULL);

  GObject *equal_button = gtk_builder_get_object(builder, "button_equal");
  g_signal_connect(equal_button, "clicked", G_CALLBACK(on_equal_button_clicked), NULL);

  GObject *addition_button = gtk_builder_get_object(builder, "button_add");
  g_signal_connect(addition_button, "clicked", G_CALLBACK(on_add_button_clicked), NULL);

  GObject *subtraction_button = gtk_builder_get_object(builder, "button_subtract");
  g_signal_connect(subtraction_button, "clicked", G_CALLBACK(on_subtract_button_clicked), NULL);

  GObject *division_button = gtk_builder_get_object(builder, "button_divide");
  g_signal_connect(division_button, "clicked", G_CALLBACK(on_divide_button_clicked), NULL);

  GObject *multiplication_button = gtk_builder_get_object(builder, "button_multiply");
  g_signal_connect(multiplication_button, "clicked", G_CALLBACK(on_multiply_button_clicked), NULL);

  GObject *negative_button = gtk_builder_get_object(builder, "button_negative");
  g_signal_connect(negative_button, "clicked", G_CALLBACK(on_negative_button_clicked), NULL);

  GObject *clear_button = gtk_builder_get_object(builder, "button_clear");
  g_signal_connect(clear_button, "clicked", G_CALLBACK(on_clear_button_clicked), NULL);

  GObject *open_parenthesis_button = gtk_builder_get_object(builder, "button_parentheses_open");
  g_signal_connect(open_parenthesis_button, "clicked", G_CALLBACK(on_open_parenthesis_button_clicked), NULL);

  GObject *close_parenthesis_button = gtk_builder_get_object(builder, "button_parentheses_close");
  g_signal_connect(close_parenthesis_button, "clicked", G_CALLBACK(on_close_parenthesis_button_clicked), NULL);

  gtk_widget_set_visible(GTK_WIDGET(window), TRUE);

  /* We do not need the builder any more */
  g_object_unref(builder);
}

int main(int argc, char *argv[])
{
  userInput = string_memory_allocate(); // Initialize the input string

#ifdef GTK_SRCDIR
  g_chdir(GTK_SRCDIR);
#endif

  GtkApplication *calculatorApp = gtk_application_new("com.github.methodmen", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(calculatorApp, "activate", G_CALLBACK(activate), NULL);

  int status = g_application_run(G_APPLICATION(calculatorApp), argc, argv);
  g_object_unref(calculatorApp);

  free(userInput);
  return status;
}
