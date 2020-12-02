/** *******************************************************************************
 * @file
 * 
 * @brief Contains the constructor, destructor, findbyWord, findbyLength, insert,
 * remove, increment, and decrement functions for the wordFreq class
 *********************************************************************************/

#include "wordFreq.h"

 /** ***************************************************************************
  * @author Lochlan Munro
  *
  * @par Description:
  * Default constructor
  *
  *****************************************************************************/
wordFreq::wordFreq()
{
    headptr = nullptr;
}

/** ***************************************************************************
 * @author Lochlan Munro
 *
 * @par Description:
 * Destructor, called when list goes out of scope
 *
 *****************************************************************************/
wordFreq::~wordFreq()
{
    node* ptr = headptr;

    while (headptr != nullptr)
    {
        headptr = headptr->next;
        delete ptr;
        ptr = headptr;
    }
}

/** ***************************************************************************
 * @author Lochlan Munro
 *
 * @par Description:
 * Checks if a given word exists in the list.
 *
 * @param[in] word - word to search for
 *
 * @returns true if found, false otherwise
 *
 *****************************************************************************/
bool wordFreq::findbyWord(string word)
{
    node* ptr = headptr;
    while (ptr != nullptr)
    {
        if (ptr->word.compare(word) == 0)
            return true;

        ptr = ptr->next;
    }

    return false;
}

/** ***************************************************************************
 * @author Lochlan Munro
 *
 * @par Description:
 * Checks if a any word has the given frequency in the list.
 *
 * @param[in] length - length to search for
 *
 * @returns true if found, false otherwise
 *
 *****************************************************************************/
bool wordFreq::findbyLength(int length)
{
    node* ptr = headptr;
    while (ptr != nullptr)
    {
        if (ptr->word.size() == length)
            return true;

        ptr = ptr->next;
    }

    return false;
}

/** ***************************************************************************
 * @author Lochlan Munro
 *
 * @par Description:
 * Inserts a word into the wordFreq list. Does not increment the frequency if the word exists.
 *
 * @param[in] word - word to insert into the list
 * 
 * @returns true if inserted, false otherwise
 *
 *****************************************************************************/
bool wordFreq::insert(string word)
{
    node* ptr = nullptr;
    ptr = new (nothrow) node;
    if (ptr == nullptr)
        return false;

    ptr->word.assign(word);
    ptr->frequency = 1;
    ptr->next = headptr;
    headptr = ptr;
    return true;
}

/** ***************************************************************************
 * @author Lochlan Munro
 *
 * @par Description:
 * Removes a word from the wordFreq list.
 *
 * @param[in] word - word to remove from the list
 *
 * @returns true if removed, false otherwise.
 *
 *****************************************************************************/
bool wordFreq::remove(string word)
{
    node* pptr = headptr;
    node* cptr = headptr;

    if (headptr == nullptr)
        return false;

    while (cptr != nullptr)
    {
        if (cptr->word.compare(word) == 0)
        {
            pptr->next = cptr->next;
            delete cptr;

            return true;
        }

        pptr = cptr;
        cptr = cptr->next;
    }

    return false;
}

/** ***************************************************************************
 * @author Lochlan Munro, Adam Kraus
 *
 * @par Description:
 * Increases the frequency for a word by 1.
 *
 * @param[in] word - word to increase frequency of.
 *
 * @returns true if incremented, false otherwise.
 *
 *****************************************************************************/
bool wordFreq::increment(string word)
{
    node* ptr = headptr;

    while (ptr != nullptr)
    {
        if (ptr->word.compare(word) == 0)
        {
            ptr->frequency++;
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}

/** ***************************************************************************
 * @author Lochlan Munro, Adam Kraus
 *
 * @par Description:
 * Decreases the frequency for a word by 1.
 *
 * @param[in] word - word to decrease frequency of.
 *
 * @returns true if decremented, false otherwise.
 *
 *****************************************************************************/
bool wordFreq::decrement(string word)
{
    node* ptr = headptr;

    while (ptr != nullptr)
    {
        if (ptr->word.compare(word) == 0)
        {
            if (ptr->frequency <= 1)
            {
                remove(word);
            }
            else {
                ptr->frequency--;
            }
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}