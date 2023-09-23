/** **************************************************************************
 * @file
 * @brief  Function prototypes for overloading operators.
 ****************************************************************************/

#ifndef __Card__H__
#define __Card__H__


 /**
      * @brief Holds the facevalue and suit of a playing card.
 */

struct card
{
    int faceValue;  /**< Holds the facevalue of the playing card. */
    int suit;    /**< Holds the suit of the playing card. */
};

istream &operator >> (istream &fin, card& temp);

ostream &operator << (ostream & fout, card & temp);

bool operator < (card& temp1, card& temp2);

bool operator > (card& temp1, card& temp2);

bool operator == (card& temp1, card& temp2);

bool operator != (card& temp1, card& temp2);

bool operator >= (card& temp1, card& temp2);

bool operator <= (card& temp1, card& temp2);

#endif