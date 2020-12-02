/** **************************************************************************
 * @file
 * 
 * @brief Utility functions
 ****************************************************************************/

#include "prog2.h"

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Trims punctuation from the front and end of a string.
 *
 * @param[in,out] word - word to be trimmed
 *
 *****************************************************************************/
void trimPunct(string& word)
{
    string::iterator it;

    //handle empty/all punct
    if (word.empty()) return;
    bool empty = true;
    for (it = word.begin(); it != word.end(); it++)
    {
        if (!ispunct(*it)) empty = false;
    }
    if (empty)
    {
        word = "";
        return;
    }

    //trim end
    for (it = word.end() - 1; it != word.begin(); --it)
    {
        if (!ispunct(*it))
        {
            word.erase(it + 1, word.end());
            break;
        }
    }

    //trim front
    for (it = word.begin(); it != word.end(); it++)
    {
        if (!ispunct(*it))
        {
            word.erase(word.begin(), it);
            break;
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Converts the word to all lowercase.
 *
 * @param[in,out] word - word to be converted
 *
 *****************************************************************************/
void wordToLower(string& word)
{
    int i;
    string newWord = "";

    for (i = 0; i < word.size(); i++)
    {
        newWord.push_back(tolower(word.at(i)));
    }

    word = newWord;
}