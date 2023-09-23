/** **************************************************************************
 * @file
 * @brief contains functions for playing the game.
 ****************************************************************************/


#include "thpe14.h"
#include "Card.h"
#include "Queue.h"


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * The backbone function of the program which starts with comparing two
  * cards, if one of them is has larger facevalue then other then the player 
  * with larger facevalue gets both the cards with opponents one being put in
  * the deck first. If there is a draw then both players draw 3 cards and the 
  * 3rd card decides who would win the round. If the 3rd card is also a draw 
  * then a another pair of 3 cards are drawn. If a player runs out of cards 
  * then both of them load the discard pile into thier deck.The suit of cards
  * don't come into considered for this function.
  *
  * @param[in,out] player1 - Queue containing cards from deck of player 1.
  * @param[in,out] player2 - Queue containing cards from deck of player 2.
  *
  *
  * @par Example
  * @verbatim
    card temp1,temp2;
    
    temp1.faceValue = 10;
    temp1.suit = 0;
    temp2.faceValue = 0;
    temp2.suit = 0;

    player1.enque(temp1);
    player2.enque(temp2);

    Queue<card> player1,player2;
    playRound(player1,player2);  // will lead to player2 winning the round
    @endverbatim
 *****************************************************************************/


void playRound(Queue<card>& player1, Queue<card>& player2)
{
    int i;
    card temp1, temp2;
    stack<card> pile1, pile2;
    size_t size = 0;
    dequepush(player1, player2, pile1, pile2, temp1, temp2);

    while (temp1 == temp2 && player1.size() >= 3 && player2.size() >= 3) 
        // both have enough cards 
    {
        for (i = 0; i < 3; i++)
        {
            dequepush(player1, player2, pile1, pile2,temp1,temp2);
        }
    }
    //player 1 cant put 3 cards in pile
    if (temp1 == temp2 && player1.size() < 3)
    {   
        size = player1.size();
        for (i = 0; i < size; i++)
        {
            dequepush(player1, player2, pile1, pile2, temp1, temp2);
        }
        if (pile1.top() == pile2.top())  // the card is still equal after draw
        {
            pileretake(player1, player2, pile1, pile2);
        }
    }
    //player 2 cant put 3 cards in pile
    if (temp1 == temp2 && player2.size() < 3)
    {
        size = player2.size();
        for (i = 0; i < size; i++)
        {
            dequepush(player1, player2, pile1, pile2, temp1, temp2);
        }
        if (pile1.top() == pile2.top())  // the card is still equal after draw
        {
            pileretake(player1, player2, pile1, pile2);
        }
    }

    if (temp1 > temp2)  // if player 1 wins after draw or single card win
    {
        player1win(player1, pile1, pile2);
        return;
    }
    if (temp2 > temp1) // player 2 wins after draw or single card win
    {
        player2win( player2, pile1, pile2);
        return;
    }
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This function deques one element from each of the player's Queue and
  * pushing it into their stack pile.
  *
  * @param[in,out] player1 - Queue containing player1's deck.
  * @param[in,out] player2 - Queue containing player2's deck.
  * @param[in,out] pile1 - stack containing discard pile of player 1.
  * @param[in,out] pile2 - stack containing discard pile of player 2.
  * @param[in,out] temp1 - a struct card which is pushed into the pile1.
  * @param[in,out] temp2 - a struct card which is pushed into the pile2.
  * 
  *
  * @par Example
  * @verbatim
    card temp1,temp2;
    Queue<card> player1, player2;
    stack<card> pile1,pile2;

    dequepush(player1,player2,pile1,pile2,temp1,temp2);
    @endverbatim
 *****************************************************************************/


void dequepush(Queue<card>& player1, Queue<card>& player2,
    stack<card>& pile1, stack<card>& pile2,card &temp1 ,card &temp2)
{
    // removes one card from each Queues and pushed it to the stacks
    player1.deque(temp1);  
    player2.deque(temp2);
    pile1.push(temp1);
    pile2.push(temp2);
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This function would be called when player1 wins the round. This function
  * would take player2's pile and enque it to player1's pile then proceed to 
  * enque player'1 pile into his deck as well.
  * 
  * @param[in,out] player1 - Queue containig player1's deck.
  * @param[in,out] pile1 - stack containing player1's discard pile.
  * @param[in,out] pile2 - stack containing player2's discard pile.
  *
  *
  * @par Example
    @verbatim
    card temp1,temp2;

    player1.deque(temp1);
    player2.deque(temp2);

    if (temp1 > temp2)
    player1win(player1,pile1,pile2);

    @endverbatim
 *****************************************************************************/


void player1win(Queue<card>& player1,
    stack<card>& pile1, stack<card>& pile2)
{
    // adds first loser's card then winner's card to the winner's deck

    while (!pile2.empty()) 
    {
        player1.enque(pile2.top());
        pile2.pop();
    }
    while (!pile1.empty()) 
    {
        player1.enque(pile1.top());
        pile1.pop();
    }
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This function would be called when player2 wins the round. This function
  * would take player1's pile and enque it to player2's pile then proceed to
  * enque player'2 pile into his deck as well.
  *
  * @param[in,out] player2 - Queue containig player2's deck.
  * @param[in,out] pile1 - stack containing player1's discard pile.
  * @param[in,out] pile2 - stack containing player2's discard pile.
  *
  *
  * @par Example
    @verbatim
    card temp1,temp2;

    player1.deque(temp1);
    player2.deque(temp2);

    if (temp1 < temp2)
    player2win(player1,pile1,pile2);

    @endverbatim
 *****************************************************************************/


void player2win( Queue<card>& player2,
    stack<card>& pile1, stack<card>& pile2)
{
    // adds first loser's card then winner's card to the winner's deck

    while (!pile1.empty()) 
    {
        player2.enque(pile1.top());
        pile1.pop();
    }
    while (!pile2.empty()) 
    {
        player2.enque(pile2.top());
        pile2.pop();
    }
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This function is called when a player runs out of cards on his deck during
  * a draw, therfore he loads the cards from his discard pile to his deck which
  * is also done by the opponent in the same number of cards.
  *
  * @param[in,out] player1 - Queue containing player1's deck.
  * @param[in,out] player2 - Queue containing player2's deck.
  * @param[in,out] pile1 - stack containing discard pile of player 1.
  * @param[in,out] pile2 - stack containing discard pile of player 2.
  *
  *
  * @par Example
  * @verbatim
    Queue<card> player1,player2;
    card temp1, temp2;
    stack<card> pile1,pile2;

    player1.deque(temp1);
    player2.deque(temp2);

    pile1.push(temp1);
    pile2.push(temp2);

    if (temp1 == temp2 && player1.size() < 3)
    {
       pileretake(player1,player2,pile1,pile2);
    }
    @endverbatim
 *****************************************************************************/


void pileretake(Queue<card>& player1, Queue<card>& player2,
    stack<card>& pile1, stack<card>& pile2)
{
    // when player runs of cards he takes the cards back from the pile

    while (!pile1.empty())
    {
        player1.enque(pile1.top());
        pile1.pop();
    }
    while (!pile2.empty())
    {
        player2.enque(pile2.top());
        pile2.pop();
    }
}







