/** **************************************************************************
 * @file
 * @brief Contains function main,functions and testcases.
 ****************************************************************************/

#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "thpe14.h"
#include "Card.h"
#include "Queue.h"

void usage(ostream& fout);

void fileopen(ifstream& fin, string argv);

void randomgen(card cards[], int seed, int used[]);

void Queueinsert(card cards1[], card cards2[], int i1, int i2);

void Queueoutput(Queue<card> &player1, Queue <card> &player2, int i);

/**
     * @brief To run and disable the process of running Test Cases.
*/

bool RUNCATCH = false;

 /** **************************************************************************
  * @mainpage Program 4 - Final Project (Game of War)
  *
  * @section course_section Course Information
  *
  * @author Aryan Raval
  *
  * @par Professor:
  *         Roger Schrader
  *
  * @par Course:
  *         CSC215 - M01 - Programming Techniques
  *
  * @par Location:
  *         McLaury - 306
  *
  * @date Due May 3, 2023
  *
  * @section program_section Program Information
  *
  * @details
  * 
  * This program takes 4 arugements.There are two default ways of starting the
  * program. One with -s which uses random generator to create 52 different 
  * cards for each player. While -f option uses files as input to get cards.
  * This cards are then enqued into a Queue one by one. Player 1 and Player 2
  * have thier own Queues.
  * 
  * Then untill one player rans out of cards the playRound function is called
  * which compares the top cards of the Queues from each players. If one is 
  * greater than the other then it first puts the loser's card into the 
  * winner's Queue followed by the winner's card. If there is a draw then 3
  * cards are drawn from each player's Queue and the third card decides who
  * will win the round. If there is a draw again the process continues.
  * If a player rans out of cards then the discard pile is loaded back into
  * his Queue.
  *
  * The Queue is template ADT while the stack used for storing the cards
  * thrown in the pile uses an STL ADT.The program in the end outputs the
  * number of rounds required to win the game followed by each 
  * player's hand after the game was ended.
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      none - a straight compile and link with no external libraries.
  *
  * @par Usage:
    @verbatim
    Usage: thpe14.exe [type] player1 player2
       Type
           -s cards retrieved using random number generator
           -f cards retrieved using files

       player1 - seed or file to use for player1
       player2 - seed or file to use for player2
    @endverbatim
  *
  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  *
  * @bug All the bugs have been fixed.
  *
  * @par Modifications and Development Timeline:
  * https://gitlab.cse.sdsmt.edu/101125506/csc215s23programs/-/commits/main/thpe14
  *
  *****************************************************************************/


  /** ***************************************************************************
   * @author Aryan Raval
   *
   * @par Description
   * Function main that is responsible for the taking input values from files 
   * and execution of the program while calling other functions in the process.
   *
   * @param[in]     argc - the total number of arguements supplied.
   * @param[in,out] argv - a array containing the arguements supplied.
   *
   * @returns 0 if successful.
   *
   * @par Example
   * @verbatim
     thpe14.exe -s 89 98   // calling the random generator
     thpe14.exr - f deck1.cards deck2.cards  // supplying files
     @endverbatim
   *****************************************************************************/


int main(int argc, char** argv)
{
    if(RUNCATCH)
    {
        Catch::Session session;
        int result;

        result = session.run();
        if (result != 0)
        {
            cout << "Didn't pass test cases " << endl;
            return 0;
        }
        return 0;
    }

    ifstream fin, fin2;
    int seed1, seed2;
    int i1 = 0, i2 = 0;
    int used[52] = { 0 }, used2[52] = { 0 };
    card cards1 [53];
    card cards2 [53];

    if (argc != 4) // invalid number of arguements
    {
        usage(cout);
    }

    if (strcmp(argv[1], "-s") != 0 && strcmp(argv[1], "-f") != 0)
    {
        cout << "Invalid game type" << endl;
        exit(0);
    }

    if (strcmp(argv[1], "-s") == 0) 
    {
        seed1 = stol(argv[2]);
        seed2 = stol(argv[3]);
        
        randomgen(cards1, seed1, used); // generate 52 random cards 
        randomgen(cards2, seed2, used2);

        Queueinsert(cards1, cards2, 52, 52);
    }

    else
    {
        fileopen(fin, argv[2]);
        fileopen(fin2, argv[3]);

        while (fin >> cards1[i1] ) // input from files until eof
        {
            i1++;
        }

        while (fin2 >> cards2[i2] )
        {
            i2++;
        }
        Queueinsert(cards1, cards2, i1, i2);
    }
    return 0;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This function contains the default usage statement to be printed out
 * on the screen.
 *
 * @param[in,out] fout - ofstream fout openend for output.
 *
 *
 * @par Example
 * @verbatim
   usage(cout);
   @endverbatim
 *****************************************************************************/


void usage(ostream &fout)
{
    fout << "Usage: thpe14.exe [type] player1 player2" << endl;
    fout << "       Type" << endl;
    fout << "           -s cards retrieved using random number generator"
        << endl;
    fout << "           -f cards retrieved using files" << endl;
    fout << endl;
    fout << "       player1 - seed or file to use for player1" << endl;
    fout << "       player2 - seed or file to use for player2" << endl;
    exit(0);
}



/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 *
 * @param[in,out] cards - a struct card to store card values.
 * @param[in]     seed  - seed value for random generator.
 * @param[in,out] used - a used array to keep track of cards in generator .
 *
 *
 * @par Example
 * @verbatim
   random(card, cards[],99,used); // will produce 52 cards using seed 99
   random(card, cards[],98,used); // will produce 52 cards using seed 98
   @endverbatim
 *****************************************************************************/


void randomgen(card cards[], int seed, int used[])
{
    int cardValue;
    int i = 0;

    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 51);

    while (i != 52)
    {
        cardValue = distribution(generator);

        if (used[cardValue] == 0)  // checks if card is already used
        {
            cards[i].faceValue = cardValue % 13;
            cards[i].suit = cardValue / 13;

            used[cardValue] ++;
            i++;
        }
    }
}



/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * Opens a file for input and checks whether it opened or not
 *
 * @param[in,out] fin - a ifstream file opened for input.
 * @param[in] argv - name of file to be opened.
 *
 *
 * @par Example
 * @verbatim
   fileopen(fin,argv); // will open file in fin with name from argv
   @endverbatim
 *****************************************************************************/


void fileopen(ifstream &fin , string argv)
{
    fin.open(argv);
    if (!fin.is_open())
    {
        cout << "Unable to open the file: " << argv;
        exit(0);
    }
}



/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This function takes the values of struct card and enques them into each
 * player's Queue and calls the playRound and output function in the end.
 *
 * @param[in,out]  cards1 - a array containing structs of card for player 1.
 * @param[in] cards2 - a array containing structs of card for player 2.
 * @param[in]  i1 - the size of the cards1.
 * @param[in] i2  - the size of the cards2.
 *
 *
 * @par Example
 * @verbatim
   Queueinsert(cards1,cards2,i1,i2); 
   // insertes the cards1 and cards2 the respective Queues
   @endverbatim
 *****************************************************************************/


void Queueinsert(card cards1[], card cards2[], int i1, int i2)
{
    int a = 0, b = 0, i = 0;

    Queue<card> player1, player2;

    for (a = 0; a < i1; a++)
    {
        player1.enque(cards1[a]);  // inserts the struct card inside Queue
    }

    for (b = 0; b < i2; b++)
    {
        player2.enque(cards2[b]);
    }

    while (!player1.isEmpty() && !player2.isEmpty()) // while both have cards
    {
        i++;
        playRound(player1, player2);
    }
    
    Queueoutput(player1, player2 ,i);// once one player runs out of cards;
}



/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This function outputs the number of rounds it took for a player to win the
 * game of war followed by each player's hand.
 *
 * @param[in,out]  player1 - a Queue containing player 1's cards.
 * @param[in,out]  player2 - a Queue containing player 2's cards.
 * @param[in] i - number of rounds needed to win the game of war.
 *
 * @par Example
 * @verbatim
   Queueoutput(player1,player2,i); 
   // will output the number of rounds to win the game of war
   // followed by each player's hand
   @endverbatim
 *****************************************************************************/


void Queueoutput(Queue<card> &player1, Queue <card> &player2 , int i)
{
    if (player2.isEmpty())
    {
        cout << "Player 1 wins after " << i << " rounds." << endl;
        cout << "Player 1 hand: ";

        player1.print(cout);
        cout << endl;
        cout << "Player 2 hand: ";
        player2.print(cout);
        cout << endl;
    }

    else
    {
        cout << "Player 2 wins after " << i << " rounds." << endl;
        cout << "Player 1 hand: ";

        player1.print(cout);
        cout << endl;
        cout << "Player 2 hand: ";
        player2.print(cout);
        cout << endl;
    }
}

//! @cond Doxygen_Suppress   // To avoid documenting the test cases

TEST_CASE(" Testing enque front and size")
{
    card temp;
    temp.faceValue = 15;
    temp.suit = 0;

    card temp2;
    temp2.faceValue = 20;
    temp2.suit = 0;

    Queue<card> tempQ;
    tempQ.enque(temp);

    REQUIRE(tempQ.size() == 1);
    tempQ.front(temp2); // temp2 now has the front of Queue 
    REQUIRE((temp == temp2));  // front of Queue is temp
}


TEST_CASE(" Testing enque middle and size")
{
    card temp;
    temp.faceValue = 15;
    temp.suit = 0;

    card temp2;
    temp2.faceValue = 20;
    temp2.suit = 0;

    card temp3;

    Queue<card> tempQ;
    tempQ.enque(temp);
    tempQ.enque(temp);
    tempQ.enque(temp2); // puts them ar the end

    REQUIRE(tempQ.size() == 3);
    tempQ.front(temp3); // temp3 now has front of Queue 
    REQUIRE((temp3 == temp));  // front of the Queue is temp
}


TEST_CASE("testing deque empty")
{
    card t;
    Queue<card> temp;
    REQUIRE(temp.deque(t) == false); // removing from empty Queue
}


TEST_CASE("testing deque end")
{
    card a, b, c;
    a.faceValue = 15;
    a.suit = 2;
    Queue<card> temp;
    card ans;

    ans.faceValue = 10;
    ans.suit = 2;

    temp.enque(a);  // a at first spot
    temp.enque(b); // b at first spot
    temp.enque(c);  // c at first spot 

    temp.deque(ans);  // will remove a from end
    REQUIRE((ans == a));
}


TEST_CASE(" isempty() true ")
{
    Queue<card> temp;
    REQUIRE(temp.isEmpty() == true);
}

TEST_CASE(" isempty() false ")
{
    card t;
    Queue<card> temp;
    temp.enque(t);
    REQUIRE(temp.isEmpty() == false);
}


TEST_CASE("front()")
{
    card t;
    card z;
    z.faceValue = 12;
    z.suit = 3;

    Queue<card> temp;
    temp.enque(z);  // now front contains z

    temp.front(t);  // now t is equal to z
    REQUIRE((t == z));
}


TEST_CASE(" front false ")
{
    card t;
    Queue<card> temp;  // empty queue
    REQUIRE(temp.front(t) == false);
}


TEST_CASE(" overloading operator and print ")
{
    ostringstream sout, sout2;
    Queue <card> test;
    card temp;
    temp.faceValue = 10;
    temp.suit = 0;

    card temp2;
    temp2.faceValue = 9;
    temp2.suit = 1;

    card temp3;
    temp3.faceValue = 5;
    temp3.suit = 3;

    test.enque(temp);
    test.enque(temp2);
    test.enque(temp3);

    sout << test;
    REQUIRE(sout.str() == "JH TD 6S");

    test.print(sout2);
    REQUIRE(sout2.str() == "JH TD 6S");
}


TEST_CASE("overloading operators ")
{
    card temp1;
    temp1.faceValue = 3;
    card temp2;
    temp2.faceValue = 8;

    REQUIRE((temp1 < temp2) == true);
    REQUIRE((temp1 > temp2) == false);
    REQUIRE((temp1 != temp2) == true);

    temp1.faceValue = 0;
    REQUIRE((temp1 > temp2) == true);
    REQUIRE((temp1 < temp2) == false);
}


TEST_CASE("playRound - single card wins")
{
    card aCard;
    int i;
    ostringstream sout1, sout2;
    Queue<card> p1, p2;
    int p1cards[2] = { 5, 8 };
    int p2cards[2] = { 2, 7 };
    for (i = 0; i < 2; i++)
    {
        aCard.faceValue = p1cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p1.enque(aCard);  // p1 contains 5 , 8
    }
    for (i = 0; i < 2; i++)
    {
        aCard.faceValue = p2cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p2.enque(aCard);   // p2 contains 2 , 7 
    }
    SECTION("Single Card win")
    {
        playRound(p1, p2);
        sout1 << p1; // I overloaded the << operator to make this work
        sout2 << p2;
        REQUIRE(sout1.str() == "9H 3H 6H");
        REQUIRE(sout2.str() == "8H");
    }

    SECTION("Second round single card win")
    {
        playRound(p1, p2);
        playRound(p1, p2);  // p1 will win again 
        sout1 << p1;
        sout2 << p2;
        REQUIRE(sout1.str() == "3H 6H 8H 9H");
        REQUIRE(sout2.str() == "");
    }

    SECTION("player 2 wins ")
    {
        card s1;
        card s2;

        s1.faceValue = 5;
        s1.suit = 3;
        s2.faceValue = 0;
        s2.suit = 1;

        p1.clear();
        p2.clear();

        p1.enque(s1);
        p2.enque(s2);

        playRound(p1, p2);  // since ace is bigger p2 will win
        sout1 << p1;
        sout2 << p2;
        CHECK(sout1.str() == "");
        CHECK(sout2.str() == "6S AD");
    }
}


TEST_CASE(" playerRound - draw occurs ")
{
    card aCard;
    int i;
    ostringstream sout1, sout2;
    Queue<card> p1, p2;
    int p1cards[6] = { 5, 8, 9, 4, 3, 12 };
    int p2cards[6] = { 5, 7, 11, 12, 0, 9 };
    for (i = 0; i < 6; i++)
    {
        aCard.faceValue = p1cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p1.enque(aCard);  // p1 contains 5,8,9,4,3,12
    }
    for (i = 0; i < 6; i++)
    {
        aCard.faceValue = p2cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p2.enque(aCard);   // p2 contains 5,7,11,12,0,9
    }

    playRound(p1, p2);
    sout1 << p1;
    sout2 << p2;

    REQUIRE(sout1.str() == "4H KH");
    REQUIRE(sout2.str() == "AH TH 5H TH 9H 6H KH QH 8H 6H");
}


TEST_CASE("playRound - draw occurs twice")
{
    card aCard;
    int i;
    ostringstream sout1, sout2;
    Queue<card> p1, p2;
    int p1cards[10] = { 6, 10, 0, 2, 9 , 4, 10 };
    int p2cards[10] = { 6, 11, 4, 2, 12, 4, 9 };

    for (i = 0; i < 7; i++)
    {
        aCard.faceValue = p1cards[i];
        aCard.suit = 0;
        p1.enque(aCard);

    }

    for (i = 0; i < 7; i++)
    {
        aCard.faceValue = p2cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }

    SECTION("check output")
    {
        playRound(p1, p2);

        sout1 << p1;
        sout2 << p2;

        REQUIRE(sout1.str() == "TH 5H KH 3H 5H QH 7H JH 5H TH 3H AH JH 7H");
        REQUIRE(sout2.str() == "");
    }
}


TEST_CASE("playRound - draw occurs twice and discard pile used")
{
    card aCard;
    int i;
    ostringstream sout1, sout2;
    Queue<card> p1, p2;
    int p1cards[10] = { 6, 10, 0, 2, 9 };
    int p2cards[10] = { 6, 11, 4, 2, 12 };

    for (i = 0; i < 5; i++)
    {
        aCard.faceValue = p1cards[i];
        aCard.suit = 0;
        p1.enque(aCard);

    }

    for (i = 0; i < 5; i++)
    {
        aCard.faceValue = p2cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }

    SECTION("check output")
    {
        playRound(p1, p2);

        sout1 << p1;
        sout2 << p2;

        CHECK(sout1.str() == "");
        CHECK(sout2.str() == "TH 3H AH JH 7H KH 3H 5H QH 7H");
    }
}


TEST_CASE(" tie and player rans out of cards")
{
    card aCard;
    int i;
    ostringstream sout1, sout2, s1,s2;
    Queue<card> p1, p2;
    int p1cards[10] = { 6, 10, 0, 2 };
    int p2cards[10] = { 6, 11, 4, 2 };

    for (i = 0; i < 4; i++)
    {
        aCard.faceValue = p1cards[i];
        aCard.suit = 0;
        p1.enque(aCard);

    }

    for (i = 0; i < 4; i++)
    {
        aCard.faceValue = p2cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }

    SECTION("check output")
    {
        playRound(p1, p2);

        sout1 << p1;
        sout2 << p2;

        CHECK(sout1.str() == "3H AH JH 7H");
        CHECK(sout2.str() == "3H 5H QH 7H");

        playRound(p1, p2);
        s1 << p1;
        s2 << p2;

        CHECK(s1.str() == "7H JH AH 3H");
        CHECK(s2.str() == "7H QH 5H 3H");
    }   
}

//! @endcond