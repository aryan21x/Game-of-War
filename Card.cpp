/** **************************************************************************
 * @file
 * @brief Contains overloading operators.
 ****************************************************************************/

#include "thpe14.h"
#include "Card.h"
#include "Queue.h"


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This is a overloaded operator that can take input from a ifstream file
  * as a integer and store in strut card.
  *
  * @param[in,out] fin - a istream file opened for input.
  * @param[in,out] temp - a struct card that contains faceValue and suit.
  *
  * @return a istream as reference
  *
  * @par Example
  * @verbatim
    ifstream fin;
    card temp;
    fin >> temp;
    @endverbatim
 *****************************************************************************/


istream &operator >> (istream &fin, card& temp)
{
    int cardValue;
    fin >> cardValue;
    temp.faceValue = cardValue % 13;
    temp.suit = cardValue / 13;

    return fin;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * The is overloaded operator that can ouput a struct card on the screen
  * according to a particular format.
  *
  * @param[in,out] fout - a ofstream file opened for output.
  * @param[in,out] temp - a struct card containing faceValue and suit.
  *
  * @returns an ostream as reference
  * 
  * @par Example
  * @verbatim
    ofstream fout;
    card temp;
    fout << temp;
    @endverbatim
 *****************************************************************************/


ostream &operator << (ostream& fout, card& temp)
{
    if (temp.faceValue == 1)
    {
        fout << "A"; 
    }

    if (temp.faceValue == 9)
    {
        fout << "T";
    }

    if (temp.faceValue == 10)
    {
        fout << "J"; 
    }

    if (temp.faceValue == 11)
    {
        fout << "Q"; 
    }

    if (temp.faceValue == 12)
    {
        fout << "K";
    }

    if ( temp.faceValue != 1 && temp.faceValue != 9 && temp.faceValue != 10
        && temp.faceValue != 11 && temp.faceValue != 12)
    {
        fout << temp.faceValue + 1;
    }

    if (temp.suit == 0)
    {
        fout << "H";
    }

    if (temp.suit == 1)
    {
        fout << "D";
    }

    if (temp.suit == 2)
    {
        fout << "C";
    }

    if (temp.suit == 3)
    {
        fout << "S";
    }
    fout << " ";
    return fout;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This is a overloaded operator that compares the lhs and rhs 
  * and returns true if lhs is smaller than rhs
  *
  * @param[in,out] temp1 - a struct of type card.
  * @param[in,out] temp2 - another struct of type card.
  *
  *
  * @returns true if true or false otherwise.
  * 
  * @par Example
  * @verbatim
    card temp1,temp2;
    if ( temp1 < temp2 )
    {
       \\ do something
    }
    @endverbatim
 *****************************************************************************/


bool operator < (card& temp1 , card& temp2)
{
    if (temp2.faceValue == 0 && temp1 != temp2)
    {
        return true;
    }

    if (temp1.faceValue == 0 && temp1 != temp2)
    {
        return false;
    }

    if (temp1.faceValue < temp2.faceValue)
    {
        return true;
    }
    return false;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This is a overloaded operator that compares the lhs and rhs 
  * and returns true if lhs is greater than rhs
  * 
  * @param[in,out] temp1 - a struct of type card.
  * @param[in,out] temp2 - another struct of type card.
  *
  * @returns true if true or false otherwise.
  *
  * @par Example
  * @verbatim
    card temp1,temp2;
    if (temp1 > temp2)
    { 
      // do something
    }
    @endverbatim
 *****************************************************************************/


bool operator > (card& temp1, card& temp2)
{
    if (temp1.faceValue == 0 && temp1 != temp2)
    {
        return true;
    }

    if (temp2.faceValue == 0 && temp1 != temp2)
    {
        return false;
    }

    if (temp1.faceValue > temp2.faceValue)
    {
        return true;
    }
    return false;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This is a overloaded operator that compares the lhs and rhs 
  * and returns true if lhs is equal to rhs.
  * 
  * @param[in,out] temp1 - a struct of type card.
  * @param[in,out] temp2 - another struct of type card.
  *
  * @returns true if true or false otherwise.
  *
  * @par Example
  * @verbatim
     card temp1,temp2;
    if (temp1 == temp2)
    { 
      // do something
    }
    @endverbatim
 *****************************************************************************/


bool operator == (card& temp1, card& temp2)
{
    if (temp1.faceValue == temp2.faceValue)
    {
        return true;
    }
    return false;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This is a overloaded operator that compares the lhs and rhs 
  * and returns true if lhs is not equal to rhs.
  * 
  * @param[in,out] temp1 - a struct of type card.
  * @param[in,out] temp2 - another struct of type card.
  *
  * @returns true if true or false otherwise.
  * 
  * @par Example
  * @verbatim
    card temp1,temp2;
    if (temp1 != temp2)
    { 
      // do something
    }
    @endverbatim
 *****************************************************************************/
bool operator != (card& temp1, card& temp2)
{
    if (temp1.faceValue != temp2.faceValue)
    {
        return true;
    }
    return false;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This is a overloaded operator that compares the lhs and rhs 
  * and returns true if lhs is greater than equal to rhs
  * 
  * @param[in,out] temp1 - a struct of type card.
  * @param[in,out] temp2 - another struct of type card.
  *
  * @returns true if true or false otherwise.
  *
  * @par Example
  * @verbatim
    card temp1,temp2;
    if (temp1 >= temp2)
    { 
      // do something
    }
    @endverbatim
 *****************************************************************************/


bool operator >= (card& temp1, card& temp2)
{
    if (temp1 > temp2 || temp1 == temp2)
    {
        return true;
    }
    return false;
}


/** ***************************************************************************
  * @author Aryan Raval
  *
  * @par Description
  * This is a overloaded operator that compares the lhs and rhs 
  * and returns true if lhs is less than equal to rhs
  * 
  * @param[in,out] temp1 - a struct of type card.
  * @param[in,out] temp2 - another struct of type card.
  *
  * @returns true if true or false otherwise.
  *
  * @par Example
  * @verbatim
    card temp1,temp2;
    if (temp1 <= temp2)
    { 
      // do something
    }
    @endverbatim
 *****************************************************************************/


bool operator <= (card& temp1, card& temp2)
{
    if (temp1 < temp2 || temp1 == temp2)
    {
        return true;
    }
    return false;
}
