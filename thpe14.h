/** **************************************************************************
 * @file
 * @brief contains functions prototypes from game.cpp.
 ****************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <stack>

using namespace std;

#ifndef __thpe14__H__
#define __thpe14__H__

#include "Queue.h"
#include "Card.h"

void playRound(Queue<card>& player1, Queue<card>& player2);

void dequepush(Queue<card>& player1, Queue<card>& player2,
    stack<card>& pile1, stack<card>& pile2,card &temp1 ,card &temp2);

void player1win(Queue<card>& player1,
    stack<card>& pile1, stack<card>& pile2);

void player2win( Queue<card>& player2,
    stack<card>& pile1, stack<card>& pile2);

void pileretake(Queue<card>& player1, Queue<card>& player2,
    stack<card>& pile1, stack<card>& pile2);

#endif