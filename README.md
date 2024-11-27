The Calculator Method [Version v1.0.0]

	
Project Description	
The Calculator Method is a simple, user-friendly application that features a graphical user interface (GUI) to
allow users to interact with the various operations it offers. It is designed for those who require a simple and
accessible tool to quickly perform basic calculations. Users are able to perform basic arithmetic operations
such as addition, subtraction, multiplication, and division, and are able to use a set of parentheses to offer 
control over which order the operations are performed. Designed with simplicity in mind, the app offers a simple
GUI which provides a straightforward and efficient way to perform calculations, without any complex features. 


Features 
  -  Basic arithmetic operations: addition, subtraction, multiplication, and division.
  -  Includes parentheses to allow the user to order their operations in a specific way.
  -  A user-friendly GUI that includes buttons 0-9, operations, parentheses, clear, and equals.
  -  Includes a help button to guide users on how to use the calculator.


Getting Started
This calculator is a command-line utility, such that it requires access to the various file that were used to 
develop the program. The following steps can guide you on how to set up the calculator for your own usage.
  1.  Clone the repository: 
	  git clone https://github.com/Sam-Scott-McMaster/the-team-assignment-team-17-method-men
  2.  NOTE: To use the GUI you will need to install the required libraries, which involves downloading and 
      setting up the GTK toolkit
	  sudo apt install libgtk-3-dev
  3.  Compile the program using the Makefile:
	  make
  4.  Run the application:
	  ./calculator

How to Use
  1.  Launch the app in the command-line to open the calculator interface.
  2.  Use the buttons on the GUI to perform operations of your choosing.
  3.  Click the equals button when you would like to perform the calculation.
  4.  Select the clear button, to clear all input numbers and operations.


Usage Examples
  1.  Basic Arithmetic: Press 14 / 2 --> Click = --> Result: 7
 		        Press 17 - 5 + 9 --> Click = --> Result: 21
  2.  Using Parentheses: Press 2 * (4 + 1) --> Click = --> Result: 10
                         Press 8 / (6 - 2) --> Click = --> Result: 2
  3.  Clear Input: Enter any calculation --> Click Clear --> Resets all input


FAQ
Q: Is this app cross-platform?
A: It is designed for systems with C compilers and compatible GUI libraries. Read the Getting Started page!
Q: Does the app offer more complex operations?
A: No! We wanted to focus on designing a user-friendly calculator that allows users to perform quick and basic calculations.


