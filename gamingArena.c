
//CS PROJECT 18
//->GAMING ARENA
//->1282 lines

//SOURCE CODE DEVELOPERS
/*NAME                                  ROLL NO
ADITYA ONAM                             2301ME03
PRIYAM MISHRA                           2302GT07
Arunvishal Palanisamy                   2301PH06
Aditya Mehrotra	                        2301MC02
Vineel Kumar Metta	                    2301CS62
Manshi Prajapati                        2302CS08
Lucky Mishra                            2301ME60         
Nishanth Kumar Nelanti                  2301MM11                   
Satyam Mansingh Chauhan	                2301EC38                   
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// 1.Functions and definitions in tic tac toe game:
#define SIZE 3                                           // board size
char board[SIZE*SIZE][SIZE*SIZE];
void initialize_board();                                 // Function to initialize the board
void print_board();                                      // Function to print the board
bool is_board_full();                                    // Function to check if the board is full
bool check_winner(char player, int box);                 // Function to check if there's a winner
void mark_board(int row, int col, char player, int box); // Function to mark the board at a given position
void print_instruction();                                // Function to print instruction 

// 2. Functions and definitions in wordle game:
char arrhint[5];
#define MAX_NUM_OF_WORDS 100
#define off "\033[m"                                            // Defining the colour
#define green "\033[32m "                                       // codes for colours used to
#define yellow "\033[33m "                                      // explain letter positions.
void inst(int x);                                               // game instructions
bool processGuess(const char *theAnswer, const char *theGuess); // Code behind guessing the letters.
int dice_roll(int n);                                           // die rolls to gain attempts

// 3. Functions and definitions in memory game:
void printCards(int cards[], int flipped[], int NUM_CARDS);       // Checks and prints the current state of cards(flipped/unflipped).
void initializeCards(int cards[], int NUM_CARDS);                 // Initialize cards with random numbers
void shuffle(int array[], int size);                              // Function to shuffle an array
int checkPairs(int cards[], int flipped[], int pair1, int pair2); // Check if the flipped cards match.
void clearScreen();                                               // Function to clear the screen
void Inst(char x);                                                // Game instrucions.

// 4. Functions and definitions in RPG Game:
// Define structure of player
typedef struct
{
    char name[30];
    int level;
    int health;
    int attack;
    int defense;
    int mana;
    int magic_attack;
    int magic_resistance;
    int experience;
    int quests_completed;
} Player;

// Define structure of enemy
typedef struct
{
    char name[50];
    int level;
    int health;
    int attack;
    int defense; // Corrected typo in member name
    int mana;
    int magic_attack;
    int magic_resistance;
} Enemy;

// Define structure of items
typedef struct
{
    char name[20];
    int increase_health;
    int increase_attack;
    int increase_defense; // Corrected typo in member name
    int increase_mana;
    int increase_magic_resistance;
} Item;

// Define structure of quest
typedef struct
{
    char Quest_description[200]; // Corrected member name
    int experience_increase; // Changed type to int to store the experience
} Quest;

void about_player(Player *player);              // Information about the game stats of the player.
void about_enemy(Enemy *enemy, int enemy_race); // Information about the enemy characters.
void about_items(Item *item, int item_type);    // Information about the items.
void show_quest(Quest *quest);                  // Displays the current quest.
void show_stats(Player *player);                // Statistics of the players progress.
void battle(Player *player, Enemy *enemy);      // Code for the battle between player and enemy.
void level_up(Player *player);                  // Text and logic when user levels' up.
void player_died();                             // Text when user is eliminated.
void use_items(Player *player, Item *items);    // Whether the player wants to use an item.
void complete_quest(Player *player, Quest *quest);


int main()
{   do{

        // lENGTH variable keeps a record of spaces where which are to be retained while printing a statement
        int length = 40;

        //%*s,this format specifier is used to insert specific string repeatedly in a statement
        //*->repetitions
        // s->string
        printf("\n%*sWELCOME TO GAMING ARENA", length, " ");
        printf("\n\n\n");

        printf("\n%*s1: MEMORY GAME", length, " ");
        printf("\n%*s2: WORDLE", length, " ");
        printf("\n%*s3: TIC-TAC-TOE", length, " ");
        printf("\n%*s4: R.P.G", length, " ");
        printf("\n%*s5: EXIT", length, " ");

        int game_choice;
        printf("\n\n\n");
        printf("\n%*sEnter the game of your choice: ", length, " ");
        scanf("%d", &game_choice);

        if (game_choice == 1)
        {

            char a, i;
            printf("Enter i to view instructions or any other character to continue game\n");
            scanf(" %c", &a);
            while (a == 'i')
            {   printf("\n\n");
                printf("INSTRUCTIONS : ");
                printf("\n\n");
                Inst(i);
                printf("\n\n");
                printf("Enter i to view instructions or any other character to continue game\n");
                scanf(" %c", &a);
            }
            printf("\n\n");
            int NUM_CARDS;
            printf("Enter the number of cards: ");
            scanf("%d", &NUM_CARDS);

            if (NUM_CARDS % 2 != 0 || NUM_CARDS <= 0 || NUM_CARDS > 16)
            {
                printf("Number of cards must be a positive even number and less than or equal to 16.\n");
                return 1;
            }

            int *cards = (int *)malloc(NUM_CARDS * sizeof(int));
            int *flipped = (int *)malloc(NUM_CARDS * sizeof(int));
            int pairsRemaining = NUM_CARDS / 2;
            int MAX_ATTEMPTS = (NUM_CARDS / 2) + 1;
            int pair1, pair2;
            int attempts = 0;
            int count = MAX_ATTEMPTS;

            // Seed random number generator
            srand(time(NULL));

            // Initialize cards
            initializeCards(cards, NUM_CARDS);

            // Print initial state of cards
            printCards(cards, flipped, NUM_CARDS);

            // Main game loop

            while (pairsRemaining && attempts < MAX_ATTEMPTS && count >= 0)
            {
                printf("Attempts remaining: %d\n", count--);
                printf("Enter two card indices to flip (0 - %d): ", NUM_CARDS - 1);
                scanf("%d %d", &pair1, &pair2);

                // Validate input
                if (pair1 < 0 || pair1 >= NUM_CARDS || pair2 < 0 || pair2 >= NUM_CARDS)
                {
                    printf("Invalid input. Please enter two valid indices.\n");
                    continue;
                }

                // Check if the selected cards are already matched or flipped
                if (flipped[pair1] || flipped[pair2])
                {
                    printf("Those cards are already matched or flipped. Please select other cards.\n");
                    continue;
                }

                // Clear the screen
                clearScreen();

                // Flip selected cards
                flipped[pair1] = 1;
                flipped[pair2] = 1;

                // Print current state of cards with flipped ones visible
                printCards(cards, flipped, NUM_CARDS);

                // Check if the flipped cards match
                if (checkPairs(cards, flipped, pair1, pair2))
                {
                    printf("Match found!\n");
                    pairsRemaining--; // Decrement pairs remaining
                }
                else
                {
                    printf("No match found. Flipping cards back...\n");
                    // Flip cards back after a delay
                    sleep(3);
                    flipped[pair1] = 0;
                    flipped[pair2] = 0;
                    // Clear the screen
                    clearScreen();
                    printCards(cards, flipped, NUM_CARDS);
                }

                attempts++; // Increment attempts
            }

            if (pairsRemaining == 0)
            {
                printf("Congratulations! You've matched all the pairs!\n");
            }
            else
            {
                printf("You've lost the game. All pairs were not matched within %d attempts.\n",
                    MAX_ATTEMPTS);
            }
            free(cards);
            free(flipped);
        }

        else if (game_choice == 2)
        {
            int x;
            int next = 1;

            // load the words
            char **wordsList = calloc(MAX_NUM_OF_WORDS, sizeof(char *));
            int wordCount = 0;
            char *fiveLetterWord = malloc(6 * sizeof(char));
            FILE *wordsFile = fopen("words.txt", "r");
            while (fscanf(wordsFile, "%s", fiveLetterWord) != EOF && wordCount < MAX_NUM_OF_WORDS)
            {
                wordsList[wordCount] = fiveLetterWord;
                wordCount++;
                fiveLetterWord = malloc(6 * sizeof(char));
            }
            fclose(wordsFile);

            // start the game
            // pick a word randomly
            while (next == 1)
            {
                srand(time(NULL));
                char *answer = wordsList[rand() % wordCount];
                // do the game loop
                int num_of_guesses = 1;
                bool guessed_correctly = false;
                char guess[6];
                while (num_of_guesses <= 6 && !guessed_correctly)
                {
                    // get guess from player
                    printf("guess no : %d :guess left : %d :Input a 5-letter word and press enter: ", num_of_guesses, 6 - num_of_guesses);
                    scanf("%s", guess);
                    if ((strlen(guess)) != 5)
                    {
                        printf("INVALID\n");
                        continue;
                    }
                    // process guess
                    guessed_correctly = processGuess(answer, guess);
                    // roll of dice
                    if (!guessed_correctly && num_of_guesses < 5)
                    {
                        printf("1:Roll a dice\n2:continue\n");
                        printf("3:See the instructions and then press 2 to continue or 1 to roll the dice\n");
                        int choice;
                        scanf("%d", &choice);
                        if (choice == 1)
                        {
                            int n, m;
                            printf("enter a number from 1 to 6: ");
                            scanf("%d", &n);
                            int v = dice_roll(n);
                            if (v == 1)
                            {
                                // giving a hint
                                char hint = arrhint[0];
                                int i;
                                for (int k = 0; k < 5; k++)
                                {
                                    while (hint == arrhint[k])
                                    {
                                        i = (rand() % 5);
                                        hint = *(answer + i);
                                    }
                                }
                                for (int m = 0; m < 5; m++)
                                {
                                    if (m == i)
                                    {
                                        printf("%c", hint);
                                    }
                                    else
                                    {
                                        printf("-");
                                    }
                                }
                                printf("\n");
                            }
                            num_of_guesses++;
                        }
                        if (choice == 3)
                        {
                            inst(3);
                            printf("1:Roll a dice\n2:continue\n");
                            printf("3:See the instructions and then press 2 to continue or 1 to roll dice\n");
                            int choice;
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                                int n, m;
                                printf("enter a number from 1 to 6: ");
                                scanf("%d", &n);
                                int v = dice_roll(n);
                                if (v == 1)
                                {
                                    // giving a hint
                                    char hint = arrhint[0];
                                    int i;
                                    for (int k = 0; k < 5; k++)
                                    {
                                        while (hint == arrhint[k])
                                        {
                                            i = (rand() % 5);
                                            hint = *(answer + i);
                                        }
                                    }
                                    for (int m = 0; m < 5; m++)
                                    {
                                        if (m == i)
                                        {
                                            printf("%c", hint);
                                        }
                                        else
                                        {
                                            printf("-");
                                        }
                                    }
                                    printf("\n");
                                }
                                num_of_guesses++;
                            }
                        }
                    }

                    num_of_guesses += 1;
                }

                // display end of game message
                if (guessed_correctly)
                {
                    printf("Congratulations! You guessed the correct word in %d times!\n", num_of_guesses);
                }
                else
                {
                    printf("You have used up yours guesses... the correct word is %s\n", answer);
                }
                for (int i = 0; i < 5; i++)
                {
                    arrhint[i] = '0';
                }
                printf("1:Start new game\n2:Exit\n");
                scanf("%d", &next);
            }

            for (int i = 0; i < wordCount; i++)
            {
                free(wordsList[i]);
            }
            free(wordsList);
            free(fiveLetterWord);
            return 0;
        }

        else if (game_choice == 3)
        {
            // Initializes the board
            initialize_board();

            // Set the first player to X
            char player = 'X';
            int row, col;

            printf("Welcome to %dX%d Tic Tac Toe!\n", SIZE * SIZE, SIZE * SIZE);
            printf("Player 1: X\n");
            printf("Player 2: O\n\n");
            bool first_play = true;
            int box = -1;
            print_instruction();

            while (!is_board_full())
            {
                print_board();

                // Get player's move
                if (!first_play)
                {
                    printf("\nPlayer %c, enter your move (row and column) for the %dth Box: ", player, box + 1);
                }
                else
                {
                    printf("\nPlayer %c, enter your move (row and column): ", player);
                }
                bool valid_input = false;
                while (!valid_input)
                {
                    scanf("%d %d", &row, &col);
                    row--;
                    col--;

                    //Prints instructions
                    if (row == -1 && col == -1)
                    {
                        print_instruction();
                        print_board();
                        printf("Player %c, please enter Valid move for %dth Box: ", player, box + 1);
                        continue;
                    }
                    // Check for out of range inputs
                    if (row > SIZE * SIZE - 1 || col > SIZE * SIZE - 1 || row < 0 || col < 0)
                    {
                        printf("Invalid Move!\n");
                    }
                    else
                    {
                        if (!first_play)
                        {
                            // Check if the input is in the required box
                            if (row / SIZE == box / SIZE && col / SIZE == box % SIZE)
                            {
                                // Checks if the position is filled
                                if (board[row][col] != '_')
                                {
                                    printf("Position already filled!\n");
                                }
                                else
                                {
                                    valid_input = true;
                                }
                            }
                        }
                        else
                        {
                            valid_input = true;
                        }
                    }
                    if (!valid_input)
                    {
                        printf("Player %c, please enter Valid move for %dth Box: ", player, box + 1);
                    }
                }

                // Mark the board
                mark_board(row, col, player, box);
                first_play = false;

                // Check for a winner
                if (check_winner(player, box))
                {
                    printf("\nCongratulations! Player %c wins!\n", player);
                    print_board();
                    break;
                }

                // Assign value of box according to input
                box = (row % 3) * SIZE + (col % 3);

                // Switch player
                player = (player == 'X') ? 'O' : 'X';
            }

            // Checks for draw
            if (!check_winner('X', box) && !check_winner('O', box))
            {
                printf("\nThe game is a draw!\n");
            }
        }
        else if (game_choice == 4)
        {

            // Initialize structures and other variables as needed
            Player player;
            Enemy enemy;
            Item items[6]; // Assuming you have 6 types of items
            Quest quest;

            // Initialize player, enemy, items, and quest
            about_player(&player);
            about_enemy(&enemy, 0); // Initialize enemy, let's say with Goblin for now
            about_items(items, 0);  // Initialize items, let's say with Healing potion for now
            show_quest(&quest);     // Initialize quest description

            // Game loop
            char choice;
            do
            {
                printf("\nWhat would you like to do?\n");
                printf("1. Show stats\n");
                printf("2. Battle\n");
                printf("3. Use items\n");
                printf("4. Complete quest\n");
                printf("5. Exit\n");
                printf("Enter your choice: ");
                scanf(" %c", &choice);

                switch (choice)
                {
                case '1':
                    show_stats(&player);
                    break;
                case '2':
                    battle(&player, &enemy);
                    break;
                case '3':
                    use_items(&player, items);
                    break;
                case '4':
                    complete_quest(&player, &quest);
                    break;
                case '5':
                    printf("Exiting the game.\n");
                    break;
                default:
                    printf("Invalid choice. Please enter a valid option.\n");
                    break;
                }

                // Check if the player leveled up after any action
                level_up(&player);

            } while (choice != '5');
        }
        else if(game_choice==5){

                //exit 
                exit(0);
            }
            
        else
        {
            printf("\n%*sEntered choice is invalid", length, " ");
            printf("\n%*sPlease enter again", length, " ");
            sleep(3);
            clearScreen();
            main();
        }
    }while(1);

    return 0;
}

//functions of memory game
void Inst (char x)
{
  printf ("1.   Objective:\n");
  printf ("a)Match all pairs of cards within a limited number of attempts.\n");
  printf ("2.   Setup:\n");
  printf ("a)Enter the number of cards you want to play with (must be a positive even number and less than or equal to 16).\n");
  printf ("b)The cards will be displayed face down initially.\n");
  printf ("3.   Gameplay:\n");
  printf ("a)You have a limited number of attempts to flip and match pairs of cards.\n");
  printf ("b)Each turn, you'll input two card indices to flip.\n");
  printf ("c)If the selected cards match, they remain face up.\n");
  printf ("d)If they don't match, they flip back after a brief delay.\n");
  printf ("4.   Rules:\n");
  printf ("a)You can only flip two cards per turn.\n");
  printf ("b)You cannot flip cards that are already matched or flipped.\n");
  printf ("c)If you flipped the cards that are already flipped than your attempts will reduce by 1.\n");
  printf ("d)The game ends when all pairs are matched or when the maximum attempts are reached.\n");
  printf ("5.   Controls:\n");
  printf ("a)Press the Enter key to select a card.\n");
  printf ("6.   Winning:\n");
  printf ("a)Match all pairs of cards within the given attempts to win the game.\n");
  printf ("7.    Losing:\n");
  printf ("a)If you fail to match all pairs within the given attempts, you lose the game.\n");
  printf ("8.   Restart:\n");
  printf ("a)To play again, restart the program.\n");
  printf ("9.    Note:\n");
  printf ("a)Enjoy the challenge of testing your memory skills and have fun matching the pairs of cards!\n");

  return;
 
}

void printCards (int cards[], int flipped[], int NUM_CARDS)
{
  printf ("\nCurrent state of cards:\n");
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  // Print the card pattern instead of "?"
		  printf (" __________");
		}
	  else
		{
		  printf (" __________");
		}
	}
  printf ("\n");

  // Print the second row of cards
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  printf ("|         |");
		}
	  else
		{
		  printf ("|         |");
		}
	}
  printf ("\n");
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  printf ("|         |");
		}
	  else
		{
		  printf ("|         |");
		}
	}
  printf ("\n");
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  printf ("|         |");
		}
	  else
		{
		  printf ("|         |");
		}
	}
  printf ("\n");
  // Print the third row of cards with card values
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  printf ("|   %2d    |", cards[i]);	// Assuming card values are two digits
		}
	  else
		{
		  printf ("|    ?    |");
		}
	}
  printf ("\n");

  // Print the fourth row of cards
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  printf ("|         |");
		}
	  else
		{
		  printf ("|         |");
		}
	}
  printf ("\n");
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  printf ("|         |");
		}
	  else
		{
		  printf ("|         |");
		}
	}
  printf ("\n");

  // Print the bottom row of cards
  for (int i = 0; i < NUM_CARDS; i++)
	{

	  if (flipped[i])
		{
		  printf ("|_________|");
		}
	  else
		{
		  printf ("|_________|");
		}
	}
  printf ("\n");
}

// Function to initialize cards with random numbers
void
initializeCards (int cards[], int NUM_CARDS)
{
  for (int i = 0; i < NUM_CARDS; i++)
	{
	  cards[i] = (i % (NUM_CARDS / 2)) + 1;
	}
  // Shuffle the cards
  shuffle (cards, NUM_CARDS);
}

// Function to shuffle an array
void
shuffle (int array[], int size)
{
  for (int i = 0; i < size - 1; i++)
	{
	  int j = i + rand () % (size - i);
	  int temp = array[i];
	  array[i] = array[j];
	  array[j] = temp;
	}
}

// Function to check if the flipped cards match
int checkPairs (int cards[], int flipped[], int pair1, int pair2)
{
  return cards[pair1] == cards[pair2];
}

// Clear the screen using ANSI escape codes
void clearScreen ()
{
  printf ("\033[2J\033[H");
}

//functions for wordle
void inst(int x)
{
    int wordle_Choice;
    printf("Here are the instructions for the game :-\n");
    printf("\n");
    printf("1. The game gives you 6 attempt to guess a 5 letter word\n");
    printf("\n");
    printf("2.Each time you guess a word you will recieve feedback on your guess as\n");

    printf("a." green " Green" off " letters indicate correct letters in the correct position\n");
    printf("b." yellow "Yellow" off " letters indicate the correct letter but at wrong position\n");
    printf("c. Normal color letters indicate letters that are not  in the hidden word\n ");
    printf("\n");
    printf("3.After each feedback users are given three options  as 1,2and3\n");
    printf("a. 1 give you way to dice a roll but with the cost of losing one attempt in which you have to select a number from 1 to 6.If your guess\n");
    printf("is correct you will be provided an hint about one of the letter present in the hidden word\n ");
    printf("If your guess is wrong then you will not be  given any hint\n");
    printf("b.If you press 2.You can continue your game and your attempts will be saved\n");
    printf("c.If you press 3 instructions will be display\n");
    printf("\n");
    printf("4.If your attempts are over and you are not able to guess the hidden word you will loose but you will be shown the correct word\n");
    printf("\n");
    printf("5.If your guess is correct,You will win the game.You will aslo  be shown the number of attempt at which you got the correct word\n");
    printf("\n");
    printf("6.After that you can press 1 to restart the game or press 2 to exit\n");
    scanf("%d",&wordle_Choice);
    printf("\n");

    if(wordle_Choice==1){

        return;
    }

    else if(wordle_Choice==2){

        exit(0);
    }

  
}

bool processGuess(const char *theAnswer, const char *theGuess)
{
  // the clue
  char clue[6] = {'-', '-', '-', '-', '-', '\0'};
  // a set of flags indicating if that letter in the answer is used as clue
  bool answerFlags[5] = {false, false, false, false, false};

  // first pass, look for exact matches
  for (int i = 0; i < 5; i++)
  {
    if (theGuess[i] == theAnswer[i])
    {
      clue[i] = 'G';
      answerFlags[i] = true;
    }
  }

  // second pass, look for there but elsewhere
  for (int i = 0; i < 5; i++)
  {
    if (clue[i] == '-')
    { // means no exact match from first pass
      for (int j = 0; j < 5; j++)
      {
        if (theGuess[i] == theAnswer[j] && !answerFlags[j])
        {
          // a match at another position and has not been used as clue
          clue[i] = 'Y';
          answerFlags[j] = true;
          break; // end this j-loop because we don't want multiple clues from the same letter
        }
      }
    }
  }
  // giving color
  for (int i = 0; i < 5; i++)
  {
    if (clue[i] == 'Y')
    {
      arrhint[i] = theGuess[i];
      printf(yellow "%c" off, theGuess[i]);
    }
    else if (clue[i] == 'G')
    {
      arrhint[i] = theGuess[i];
      printf(green "%c" off, theGuess[i]);
    }
    else
    {
      printf(" %c", theGuess[i]);
    }
    if (i == 4)
    {
      printf("\n");
    }
  }

  return strcmp(clue, "GGGGG") == 0; // if match strcmp returns 0
}
int dice_roll(int n)
{
  srand(time(NULL));
  int dice = ((rand() % 6) + 1);
  printf("dice roll = %d\n", dice);
  if (dice == n)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

//functions for tic tac toe

//Function to print instrictions
void print_instruction()
{
    printf("INSTRUCTIONS:\n");
    printf("1. The rules for tic tac toe also apply here.\n");
    printf("2. There are 9 3X3 blocks in this tic tac toe board.\n");
    printf("3. The player had to place his/her move in the block corresponding to the box\n   the previous player placed his/her move.\n");
    printf("4. The player must play his move in his alloted 3X3 box\n");
    printf("5. The boxes are denoted by the co-ordinates (x,y).where x is row number and y is column number\n   Enter input in\"x y\" format");
    printf("6. If he/she match all the three elments in a row,column or diagonal in their respective box,he/she will win the match\n");
    printf("7. If a player wanna check the instuctions,he may use the resume button\n");
    printf("8. To view the instructions again type \"0 0\"\n\n");
}

// Function to initialize the board
void initialize_board() {
    for (int i = 0; i < SIZE*SIZE; i++) {
        for (int j = 0; j < SIZE*SIZE; j++) {
            board[i][j] = '_';
        }
    }
}

// Function to print the board
void print_board() {
    printf("\n");
    char breaker[]="     -----------------------------------";
    printf("         1  2  3    4  5  6    7  8  9\n");
    for(int i=0; i<SIZE*SIZE; i++){
        //Prints the breaker after each row of boxes
        if(i%SIZE==0){
                printf("%s\n", breaker);
        }
        //Print row Numbers
        printf("%2d   ", i+1);
        for(int j=0; j<SIZE*SIZE; j++){
            //Print Vertical Breakers
            if(j%SIZE==0){
                printf("||");
            }
            //Prints elements of board
            printf(" %c ",board[i][j]);
        }
        printf("||\n");
    }
    printf("%s\n", breaker);
}

// Function to check if the board is full
bool is_board_full() {
    for (int i = 0; i < SIZE*SIZE; i++) {
        for (int j = 0; j < SIZE*SIZE; j++) {
            if (board[i][j] == '_') {
                return false;
            }
        }
    }
    return true;
}

// Function to check if there's a winner
bool check_winner(char player, int box) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        bool row_win = true;
        bool col_win = true;
        for (int j = 0; j < SIZE; j++) {
            if (board[i + (box/SIZE)*SIZE][j + (box%SIZE)*SIZE] != player) {
                row_win = false;
            }
            if (board[j + (box/SIZE)*SIZE][i + (box%SIZE)*SIZE] != player) {
                col_win = false;
            }
        }
        if (row_win || col_win) {
            return true;
        }
    }

    // Check diagonals
    bool diag1_win = true;
    bool diag2_win = true;
    for (int i = 0; i < SIZE; i++) {
        if (board[i + (box/SIZE)*SIZE][i + (box%SIZE)*SIZE] != player) {
            diag1_win = false;
        }
        if (board[i + (box/SIZE)*SIZE][(box%SIZE)*SIZE + SIZE - 1 - i] != player) {
            diag2_win = false;
        }
    }
    if (diag1_win || diag2_win) {
        return true;
    }
    //If the player haven't won
    return false;
}

// Function to mark the board at a given position
void mark_board(int row, int col, char player, int box) {
    if (row >= 0 && row < SIZE*SIZE && col >= 0 && col < SIZE*SIZE && board[row][col] == '_') {
        board[row][col] = player;
    }
}

//function for rpg
void about_player(Player *player)
{
    strcpy(player->name, "");
    player->level = 1;
    player->health = 100;
    player->attack = 20;
    player->defense = 5;
    player->mana = 40;
    player->magic_attack = 30;
    player->magic_resistance = 10;
    player->experience = 0;
    player->quests_completed = 0;
}

void about_enemy(Enemy *enemy, int enemy_race)
{
    switch (enemy_race)
    {
    case 0:
        strcpy(enemy->name, "Goblin");
        enemy->level = 1;
        enemy->health = 60;
        enemy->attack = 8;
        enemy->defense = 4;
        enemy->mana = 0;
        enemy->magic_attack = 0;
        enemy->magic_resistance = 0;
        break;
    case 1:
        strcpy(enemy->name, "Skeleton");
        enemy->level = 2;
        enemy->health = 40;
        enemy->attack = 15;
        enemy->defense = 4;
        enemy->mana = 5;
        enemy->magic_attack = 5;
        enemy->magic_resistance = 5;
        break;
    case 2:
        strcpy(enemy->name, "Orc");
        enemy->level = 3;
        enemy->health = 85;
        enemy->attack = 15;
        enemy->defense = 6;
        enemy->mana = 5;
        enemy->magic_attack = 5;
        enemy->magic_resistance = 10;
        break;
    case 3:
        strcpy(enemy->name, "Ram Rider"); // Removed extra space
        enemy->level = 4;
        enemy->health = 70;
        enemy->attack = 25;
        enemy->defense = 6;
        enemy->mana = 15;
        enemy->magic_attack = 10;
        enemy->magic_resistance = 15;
        break;
    case 4:
        strcpy(enemy->name, "Golem");
        enemy->level = 5;
        enemy->health = 100;
        enemy->attack = 15;
        enemy->defense = 12;
        enemy->mana = 20;
        enemy->magic_attack = 5;
        enemy->magic_resistance = 25;
        break;
    case 5:
        strcpy(enemy->name, "Pekka");
        enemy->level = 6;
        enemy->health = 80;
        enemy->attack = 50;
        enemy->defense = 4;
        enemy->mana = 30;
        enemy->magic_attack = 25;
        enemy->magic_resistance = 10;
        break;
    case 6:
        strcpy(enemy->name, "Wizard");
        enemy->level = 7;
        enemy->health = 70;
        enemy->attack = 50;
        enemy->defense = 20;
        enemy->mana = 100;
        enemy->magic_attack = 50;
        enemy->magic_resistance = 25;
        break;
    case 7:
        strcpy(enemy->name, "Skeleton King");
        enemy->level = 8;
        enemy->health = 150;
        enemy->attack = 100;
        enemy->defense = 40;
        enemy->mana = 120;
        enemy->magic_attack = 75;
        enemy->magic_resistance = 40;
        break;
    case 8:
        strcpy(enemy->name, "Inferno Dragon");
        enemy->level = 9;
        enemy->health = 200;
        enemy->attack = 130;
        enemy->defense = 60;
        enemy->mana = 140;
        enemy->magic_attack = 95;
        enemy->magic_resistance = 55;
        break;
    case 9:
        strcpy(enemy->name, "Demon King");
        enemy->level = 10;
        enemy->health = 400;
        enemy->attack = 200;
        enemy->defense = 100;
        enemy->mana = 250;
        enemy->magic_attack = 125;
        enemy->magic_resistance = 75;
        break;
    default:
        break;
    }
}

void about_items(Item *item, int item_type)
{
    switch (item_type)
    {
    case 0:
        strcpy(item->name, "Healing potion");
        item->increase_health = 50;
        item->increase_attack = 0;
        item->increase_defense = 0;
        item->increase_mana = 0;
        item->increase_magic_resistance = 0;
        break;
    case 1:
        strcpy(item->name, "Rage potion");
        item->increase_health = 0;
        item->increase_attack = 20;
        item->increase_defense = 0;
        item->increase_mana = 0;
        item->increase_magic_resistance = 0;
        break;
    case 2:
        strcpy(item->name, "Hardening potion");
        item->increase_health = 0;
        item->increase_attack = 0;
        item->increase_defense = 10;
        item->increase_mana = 0;
        item->increase_magic_resistance = 0;
        break;
    case 3:
        strcpy(item->name, "Mana potion");
        item->increase_health = 0;
        item->increase_attack = 0;
        item->increase_defense = 0;
        item->increase_mana = 20;
        item->increase_magic_resistance = 0;
        break;
    case 4:
        strcpy(item->name, "Magic resistance potion");
        item->increase_health = 0;
        item->increase_attack = 0;
        item->increase_defense = 0;
        item->increase_mana = 0;
        item->increase_magic_resistance = 15;
        break;
    case 5:
        strcpy(item->name, "Rainbow potion");
        item->increase_health = 30;
        item->increase_attack = 10;
        item->increase_defense = 5;
        item->increase_mana = 10;
        item->increase_magic_resistance = 5;
        break;
    }
}

void show_quest(Quest *quest)
{
    strcpy(quest->Quest_description, "Eliminate all the minions of the demon king and demon king and bring peace to the earth"); // Corrected typo in member name
    quest->experience_increase = 100; // Assigning an integer value instead of a string
}

void show_stats(Player *player)
{
    printf("Name: %s\n", player->name);
    printf("Level: %d\n", player->level);
    printf("Health: %d\n", player->health);
    printf("Attack: %d\n", player->attack);
    printf("Defense: %d\n", player->defense);
    printf("Mana: %d\n", player->mana);
    printf("Magic Attack: %d\n", player->magic_attack);
    printf("Magic Resistance: %d\n", player->magic_resistance);
    printf("Experience of player: %d\n", player->experience);
    printf("Number of quests completed: %d\n", player->quests_completed);
}

void battle(Player *player, Enemy *enemy)
{
    // Implement battle logic here
}

void level_up(Player *player)
{
    if (player->experience >= player->level * 100)
    {
        printf("Congratulations! You leveled up!\n");
        player->level++;
        player->health += (player->level) * 10;
        player->attack += (player->level) * 8;
        player->defense += (player->level) * 4;
        player->mana += (player->level) * 5;
        player->magic_attack += (player->level) * 4;
        player->magic_resistance += (player->level) * 3;
    }
}

void player_died()
{
    printf(" You have put a great effort Hero! It is very unfortunate that you are killed by a demon.");
    printf(" so I have decided to reincarnate you again into this world. Use the experience and knowledge you have gained in your previous life to claim victory over the Demon Lord");
}

void use_items(Player *player, Item *items)
{
    char choice;
    int option;
    printf("Do you want to use the item ? (y/n): ");
    scanf(" %c", &choice);
    if (choice == 'y')
    {
        printf("Select the item you want to use: ");
        printf("1. Healing potion (Increases health points)\n");
        printf("2. Rage potion (Increases attack)\n");
        printf("3. Hardening potion (Increases defense)\n");
        printf("4. Mana potion (Increases mana)\n");
        printf("5. Magic resistance potion (Increases magic resistance)\n");
        printf("6. Rainbow potion (Increases all stats)\n");

        scanf(" %d", &option);
        switch (option)
        {
        case 1:
            printf("You have selected the Healing potion.\n");
            printf("Now your health will be increased by 50 points.\n");
            player->health += 50;
            printf("Your stats have been updated.\n");
            break;
        case 2:
            printf("You have selected the Rage potion.\n");
            printf("Now your attack will be increased by 20 points.\n");
            player->attack += 20;
            printf("Your stats have been updated.\n");
            break;
        case 3:
            printf("You have selected the Hardening potion.\n");
            printf("Now your defense will be increased by 10 points.\n");
            player->defense += 10;
            printf("Your stats have been updated.\n");
            break;
        case 4:
            printf("You have selected the Mana potion.\n");
            printf("Now your mana will be increased by 20 points.\n");
            player->mana += 20;
            printf("Your stats have been updated.\n");
            break;
        case 5:
            printf("You have selected the Magic resistance potion.\n");
            printf("Now your magic resistance will be increased by 15 points.\n");
            player->magic_resistance += 15;
            printf("Your stats have been updated.\n");
            break;
        case 6:
            printf("You have selected the Rainbow potion.\n");
            printf("Now your health will be increased by 30 points.\n");
            printf("Now your attack will be increased by 10 points.\n");
            printf("Now your defense will be increased by 5 points.\n");
            printf("Now your mana will be increased by 10 points.\n");
            printf("Now your magic resistance will be increased by 5 points.\n");
            player->health += 30;
            player->attack += 10;
            player->defense += 5;
            player->mana += 10;
            player->magic_resistance += 5;
            printf("Your stats have been updated.\n");
            break;
        default:
            printf("Please enter a valid choice.\n");
            break;
        }
    }
}

void complete_quest(Player *player, Quest *quest)
{
    // Implement logic to complete the quest
}
