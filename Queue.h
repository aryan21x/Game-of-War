/** **************************************************************************
 * @file
 * @brief  Contains ADT Queue template.
 ****************************************************************************/


#ifndef __Queue_H__
#define __Queue_H__

 /**
      * @brief An ADT template named Queue to hold the deck of cards.
 */
template <class TY>
class Queue
{
public:
    Queue();
    ~Queue();

    bool enque(TY& card);
    bool deque(TY& card);

    bool front(TY& card);
    bool isEmpty();

    int size();
    void clear();

    void print(ostream& out);

    template <class TY>  // overloading operator for output
    friend ostream& operator << (ostream& out,Queue<TY> &temp);

private:

    struct node /**<Contains the element of current node and address of other*/
    {
        TY value;    /**< The value contains the element of type TY. */
        node* next;  /**< Contains the address of next node. */
    };
    node* headptr;   /**< Points towards the first element in the Queue. */
    node* tailptr;   /**< Points towards the last element in the Queue. */
};


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * A contrustor the creates an instance of class Queue.
 *
 *
 * @par Example
 * @verbatim
   // automatically called
   @endverbatim
 *****************************************************************************/


template <class TY>
Queue<TY> ::Queue()  // constructor
{
    headptr = nullptr;
    tailptr = nullptr;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * A destructor for the class Queue that deletes the Queue automatically and
 * frees up storage.
 *
 *
 * @par Example
 * @verbatim
   // is being called automatically
   @endverbatim
 *****************************************************************************/


template <class TY>
Queue<TY> :: ~Queue()  // destructor
{
    
    node* temp = headptr;
    while (temp != nullptr)  // linked list traversal
    {
        headptr = headptr->next;
        delete temp;
        temp = headptr;
    }
    headptr = nullptr;
    tailptr = nullptr;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This function tells us whether a Queue is empty or not.
 *
 *
 * @returns true if empty false otherwise.
 *
 * @par Example
 * @verbatim
   Queue<card> temp;
   card s;
   bool ans;
   ans = temp.isempty();  // would be true
   temp.enque(s);
   ans = temp.isempty(); // would be false
   @endverbatim
 *****************************************************************************/


template <class TY>
bool Queue<TY>::isEmpty() // checks if Queue is empty or not
{
    if (headptr == nullptr)
    {
        return true;
    }
    return false;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * Adds an element to the end of the Queue using a linked list
 *
 * @param[in,out] card - element to be inserted inside the Queue.
 *
 * @returns true if successful and false otherwise.
 *
 * @par Example
 * @verbatim
   card s;
   Queue<card> temp;
   temp.enque(s); // temp would now contain s
   @endverbatim
 *****************************************************************************/


template <class TY>
bool Queue<TY>::enque(TY& card)  // to insert an item in Queue from behind
{
    node* temp = new(nothrow) node;

    if (temp == nullptr)  // failed memory allocation
    {
        return false;
    }
    temp->value = card;
    temp->next = nullptr;

    if (isEmpty())  // if Queue is empty
    {
        headptr = temp;
        tailptr = temp;
    }
    else
    {
        tailptr->next = temp;
        tailptr = temp;  // tailptr now points towards new item in the end
    }

    return true;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This function removes an element from the front of the Queue using a linked 
 * list.
 *
 * @param[in,out] card - removed element would be stored in this.
 *
 * @returns true if successful and false otherwise.
 *
 * @par Example
 * @verbatim
   card s;
   Queue<card> temp;
   temp.enque(s); // temp would now contain s
   temp.deque(s); // temp doesn't contain s anymore
   @endverbatim
 *****************************************************************************/


template <class TY>
bool Queue<TY>::deque(TY& card) // removing a card from the front of Queue
{
    node* temp = headptr;

    if (isEmpty())
    {
        return false;
    }

    headptr = headptr->next;

    card = temp->value;
    delete temp;

    return true;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This funtion gives us the top in other words the most front element
 * of the Queue.
 *
 * @param[in,out] card - variable where the top element would be stored.
 *
 * @returns true if successful and false otherwise.
 *
 * @par Example
 * @verbatim
   card s,p;
   Queue<card> temp;
   temp.enque(s); // temp would now contain s
   temp.top(p);  // p now contains s
   @endverbatim
 *****************************************************************************/


template <class TY>
bool Queue<TY>::front(TY& card) // front card of the Queue
{
    if (isEmpty())
    {
        return false;
    }
    card = headptr->value;
    return true;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This function provides us the size of the Queue.
 *
 *
 * @returns an ineger value size of the Queue.
 *
 * @par Example
 * @verbatim
   card s,t;
   Queue<card> temp;
   int size;
   temp.enque(s);
   temp.enque(t);

   size = temp.size(); // would be 2
   @endverbatim
 *****************************************************************************/


template <class TY>
int Queue<TY>::size()  // size of the Queue
{
    node* curr = headptr;
    int count = 0;

    while (curr != nullptr)
    {
        count++;
        curr = curr->next;
    }
    return count;
}


/** ***************************************************************************
 * @author Aryan Raval
 *
 * @par Description
 * This function allows us to Voluntarily clear an Queue if we want.
 *
 *
 * @par Example
 * @verbatim
   Queue<card> temp;
   card s;
   temp.enque(s);
   temp.clear(); // temp doesn't contain anything anymore
   @endverbatim
 *****************************************************************************/


template< class TY>
void Queue<TY>::clear()  // voluntary clearing of the Queue if needed
{
    node* temp = headptr;
    while (temp != nullptr)
    {
        headptr = headptr->next;
        delete temp;
        temp = headptr;
    }
}


/** ***************************************************************************
   * @author Aryan Raval
   *
   * @par Description
   * This functions prints out the content of a Queue to the screen in 
   * the required format.
   *
   * @param[in,out] out - ostream to print on the screen.
   *
   *
   * @par Example
   * @verbatim
     card s;
     s.faceValue = 0;
     s.suit = 1;
     Queue<card> temp;
     temp.enque(s);
     temp.print(cout); // AD
     @endverbatim
   *****************************************************************************/


template <class TY>
void Queue<TY>::print(ostream& out) // for priting a Queue with Cards
{
    node* temp = headptr;
    while (temp != nullptr)
    {
        if (temp->value.faceValue == 0)
            out << "A";

        else if (temp->value.faceValue == 9)
            out << "T";

        else if (temp->value.faceValue == 10)
            out << "J";

        else if (temp->value.faceValue == 11)
            out << "Q";

        else if (temp->value.faceValue == 12)
            out << "K";

        else
            out << temp->value.faceValue + 1;

        if (temp->value.suit == 0)
        {
            out << "H";
        }

        else if (temp->value.suit == 1)
        {
            out << "D";
        }

        else if (temp->value.suit == 2)
        {
            out << "C";
        }

        else
        {
            out << "S";
        }

        if (temp->next != nullptr)
        {
            out << " ";
        }
        temp = temp->next;
    }
}


/** ***************************************************************************
   * @author Aryan Raval
   *
   * @par Description
   * This is a overloaded operator that prints the content of a Queue
   * to the screen.
   *
   * @param[in,out] out - ostream to print on the screen.
   * @param[in,out] temp - the Queue to be printed on screen.
   *
   * @returns ostream as reference
   *
   * @par Example
   * @verbatim
     card s;
     s.faceValue = 0;
     s.suit = 1;
     Queue<card> temp;
     temp.enque(s);
     cout << temp; // AD
     @endverbatim
   *****************************************************************************/


template <class TY>
ostream& operator << (ostream& out, Queue<TY> &temp) // overloading Queue
{
    temp.print(out);
    return out;
}

#endif