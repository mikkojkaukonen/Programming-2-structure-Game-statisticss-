# Programming-2-structure-Game-statisticss-
Tampere University, Projects made in the course Programming 2: structures

Data processed by the program

The input file given to the program contains lines, each of which has three data fields: a game, a player, and the player’s score. These fields are separated by semicolons from each other. The structure of an input file accepted by the program can, for example, be as follows:

Sudoku;Matti;1

Sudoku;Manu;25

Sudoku;Maarit;50

Sudoku;Master Player;100

Hitori;Manu;10

Hitori;Mikko;10

Hitori;Maarit;30

Hitori;Master Player;100

Minesweeper;Minna;40

Minesweeper;Manu;50

Minesweeper;Mikko;60

Afrikan tähti;Maarit;1

Afrikan tähti;Juho;5

Kimble;Minna;5

Kimble;Juho;10

Here, all the players of a game have been listed one after the other, but the above lines could have been listed in any order. However, you can assume that a player occurs at each game only once (or not at all).

The names of both games and players can consist of several words. If this is the case, queries require quote marks, as will be shown in later examples. On the other hand, in implementing the program you need not care about this, since the given split function can handle quotes in an appropriate way.

Error messages related to file management

When the program starts up, it reads the name of the input file from the user as follows:

Give a name for input file: data.txt

If the program cannot open the input file, it will print the text:

Error: File could not be read.

After that, the program terminates with no other prints with the return value EXIT_FAILURE.

If the input file can be opened but the file does not correspond to the specification above, the program prints the error message:

Error: Invalid format in file.

and terminates with the return value EXIT_FAILURE. This can be the case, if, for example, a line of the input file contains something else than three text pieces separated by a semicolon. Empty game or player names are not accepted either.

There are more error messages related to the commands. They will be explained in the context of the command in question.

Commands and error messages in general

The program parses the lines of the input file and stores the information about games and players in an adequate internal data structure.

After reading the input file, the program starts the actual execution. Each time the user is expected to give input, the program prints the prompt:

games>

to which, the user can give commands listed in next sections. The commands to be implemented will be introduced in two parts: first mandatory ones and after that voluntary ones.

Each command has 0-3 parameters. If too few parameters are given for a command, the program gives the error message:

Error: Invalid input.

If there are too many parameters, the extra ones are ignored. No error message is given, the extra ones are just useless.

Parameters are typically games and/or players. If a command is used to print something about them, the program ensures that the game/player in question can be found in the data structure. If this is not the case, the program gives an error message explained with the commands in question a bit later.

On the other hand, if a command concerns adding a game, the program ensures that the game in question does not already exist, and gives an error message if needed. Adding an existing player is not considered as an error, but in this way it is possible to update the player’s score.

If the user gives another command, not listed below, the program prints the error message:

games> SOMETHING

Error: Invalid input.

games>

After completing the execution of a command given by the user, the program prints the prompt again, until the user gives the command QUIT.

Both lower-case and upper-case letters are allowed in the commands. (Here you can use toupper function provided for char type. Before comparing user input e.g. to the word QUIT, change all the letters in the user-given command into upper-case ones.)

Mandatory commands of the program with their error messages

All the commands listed in this section must be implemented and they must work to get any points from the project. If you implement only the commands in this section, the scale 0-30 will be used in evaluating your project.

QUIT - The program terminates with the return value EXIT_SUCCESS without printing anything.

ALL_GAMES - The command prints the games one after the other in alphabetical order. For example:

games> ALL_GAMES

All games in alphabetical order:

Afrikan tähti

Hitori

Kimble

Minesweeper

Sudoku

games>

Here alphabetical order means the order according to ASCII codes. It is almost like alphabetical order but all upper-case letters precede all lower-case letters. For example, if we had above written Hitori as hitori, it would have been written as the last one in the list.

GAME <game> - The command prints the scores and players of the given game. The print follows the ascending order of scores. If two or more players have the same score, the players are listed in the same line in alphabetical order separated by a comma. For example:

games> GAME Hitori

Game Hitori has these scores and players, listed in ascending order:

10 : Manu, Mikko

30 : Maarit

100 : Master Player

games>

If a game has no players (yet), only the first line of the above output would be printed. Such a situation can be seen more precisely at the command ADD_GAME a bit later.

The command must have at least one parameter. If this is not the case, the program gives the error message:

games> GAME

Error: Invalid input.

games>

If the given game is unknown, the program prints the error message:

games> GAME Unknown

Error: Game could not be found.

games>

The name of a game can consist of several words. In such cases, the name must be enclosed with quotes, since otherwise the name cannot be considered as a single parameter. For example:

games> GAME "Afrikan tähti"

Game Afrikan tähti has these scores and players, listed in ascending order:

1 : Maarit

5 : Juho

games>

Even if the name of a game consists only of a single word, the user is allowed to use quotes. For example the commands GAME Hitori and GAME "Hitori" have the same effect.

ALL_PLAYERS - The command prints the players one after the other in alphabetical order. (Again the order is based on ASCII codes as with the command ALL_GAMES.) For example:

games> ALL_PLAYERS

All players in alphabetical order:

Juho

Maarit

Manu

Master Player

Matti

Mikko

Minna

games>

PLAYER <player> - The command prints in alphabetical order (based on ASCII codes) those games the given player plays. Each game will be printed in the line of its own. For example:

games> PLAYER Maarit

Player Maarit playes the following games:

Afrikan tähti

Hitori

Sudoku

games>

The command requires at least one parameter. If this is not the case, the given error message is the same as with the command GAME in the corresponding situation.

If the given stop is unknown, the program prints the error message:

games> PLAYER Unknown

Error: Player could not be found.

games>

The name of a player can consist of several words. In such case, quote marks are used in the same way as in command GAME. Quote marks can be used also in names with a single word.

Voluntary commands of the program with their error messages

If you, besides the mandatory commands, implement also the commands introduced in the section, the scale 0-50 will be used in evaluating your project.

ADD_GAME <game> - The command adds the given game in the data structure (without players) and prints the text Game was added.. For example:

games> ALL_GAMES

All games in alphabetical order:

Afrikan tähti

Hitori

Kimble

Minesweeper

Sudoku

games> ADD_GAME "New game"

Game was added.

games> ALL_GAMES

All games in alphabetical order:

Afrikan tähti

Hitori

Kimble

Minesweeper

New game

Sudoku

games> GAME "New game"

Game New game has these scores and players, listed in ascending order:

games>

After adding a game, the command ALL_GAMES prints the added game in the correct place (in alphabetical order). From the execution above, you can also see how to print a game that has no players (yet).

The command requires at least one parameter. If this is not the case, the given error message is the same as with the command GAME in the corresponding situation.

If the game to be added already exists, the program prints the following error message:

games> ADD_GAME Hitori

Error: Already exists.

games>

ADD_PLAYER <game> <player> <score> - The command adds in the data structure the given player for the given game and prints the text Player was added. For example:

games> GAME Sudoku

Game Sudoku has these scores and players, listed in ascending order:

1 : Matti

25 : Manu

50 : Maarit

100 : Master Player

games> ADD_PLAYER Sudoku "New player" 30

Player was added.

games> GAME Sudoku

Game Sudoku has these scores and players, listed in ascending order:

1 : Matti

25 : Manu

30 : New player

50 : Maarit

100 : Master Player

games>

Note that the added player will be printed in the correct place based on their score in command GAME. Correspondingly, the command ALL_PLAYERS would print the new player in the correct place (in alphabetical order).

If the given player already exists (possibly with a different score), the command updates the score. For example:

games> ADD_PLAYER Sudoku Matti 30

Player was added.

games> GAME Sudoku

Game Sudoku has these scores and players, listed in ascending order:

25 : Manu

30 : Matti, New player

50 : Maarit

100 : Master Player

games>

Note that the printing order can change accordingly, when the player’s score changes.

Usually scores becomes better, i.e. usually updating means replacing a smaller number with a bigger one. Even if the given score is worse than or the same as player’s earlier score, no checks are required. A worse score can be assumed to mean an error fix. If the same score is given, no changes occur in the printing order.

The command requires at least three parameters. If this is not the case, the given error message is the same as with the command GAME in the corresponding situation.

If the line given as the first parameter is unknown, the given error message is the same as with the command GAME in the corresponding situation.

Note that the command has very much the same action as has been done in reading the input file and storing its content into a data structure. Could it be possible to use here code you have written earlier?

REMOVE <player> - The command removes the given player from all the games, i.e. the player quits playing totally. In addition, the command prints the text Player was removed from all games. For example:

games> PLAYER "Master Player"

Player Master Player playes the following games:

Hitori

Sudoku

games> REMOVE "Master Player"

Player was removed from all games.

games> GAME Hitori

Game Hitori has these scores and players, listed in ascending order:

10 : Manu, Mikko

30 : Maarit

games> GAME Sudoku

Game Sudoku has these scores and players, listed in ascending order:

25 : Manu

30 : Matti, New player

50 : Maarit

games> PLAYER "Master Player"

Error: Player could not be found.

games>

The command requires at least one parameter. If this is not the case, the given error message is the same as with the command GAME in the corresponding situation.

If the stop to be removed is unknown, the program prints the following error message:

games> REMOVE Unknown

Error: Player could not be found.

games>

The addition and remove commands described above do not require modifying the file. It is enough to just change the data structure.
