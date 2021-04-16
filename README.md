# Mastermind-C
The famous "Mastermind" game developed in C for universitary purposes


# INTRODUCTION
In the classic-irl version of the game "Mastermind", also known as "Bulls and Cows", a first player have to create a secret 4-color combination and a second player have to guess the secret combination in a maximum total of 12 possible attempts.
The player who have the objective of guessing the combination, will receive a black marble for each color guessed by type and position in the secret combination.
He will instead receive a white marble for each color guessed just by type but not the position in the secret combination.
As said before, the second player win if he guess the entire secret combination (he receive 4 marble black).
In this computerized version of the game, the Computer have the job of randomly generate the secret combination, and the player have the objective of guessing the combination.

At the start of the executable, it will display the player the main Menù with 3 possible choice: Play, Instructions and Exit;

Typing the desired choice and pressing [ENTER], the desired action will start his process.

Choosing "Play": a loading screen will be displayed, when the load is finished, the user will have in front of him the Game HUD, where he can control the entire play.

Choosing "Instruction": the instructions will be displayed.

Choosing "Exit": The program will terminate it's execution returning 0.

# MAIN
I choosed to mantain the "main" function more clear as possible, writing the real game instructions inside sub-functions so the code can re-start a play in the easiest way possible and without keeping a lot of memory occupied.
Inside the main we can find just the output of the main menù and a "do...while" loop who manage the input selection and filtering, displaying an error in case of invalid input.

# OTHER FUNCTIONS

# Void play();
The "void play" function is the main function for the execution of the game, it manage the "game session".
Thanks to the "time.h" library, the program will use the computer's clock to randomly generate an input, and with a simple "for" construct, the program will fill an int array called "estratti" who contain the 4 numbers of the secret combination.
Then inside a "do...while" loop we find:
-Display the intial HUD (Title and Secret code section);
-A "for" loop for displaying all the player's attempts;
-Control of the evenctually win o loose before attempting another guess;
-Display all the avaible colors and their identification int;
-Acquisition and control of input's validity in the current attempt.
  In case of invalidity of the input, an error will occur and the input acquisition will be repeated.
  In case of correct input validity, each char of the attempted sequence will be transformed in a integer and will be stored into the attempts's matrix;
-Function "void control(...)" call for the score control and store into the score matrix.

This cycle will end in case of victory or attempts's termination.

# Void control(int[], int[], char \*punttentati, bool \*win)
As said before, the "void control" function's job is the one of controlling and store the score of an attempt, and setting the boolean var "win" to "true" in case of victory.

# Const char* toColor(int x)
The "toColor" function is a simple function who take the int passed by parameters and convert it into a String rappresenting it's color using a simple "switch" construct.
(Example: 1 = Red)

# Display functions
All display functions: caricament(), istruzioni(), displayName() and displayHotbar() are simple functions who just have output instructions inside them, they're used for keeping the rest of the the code clean.
