/** **************************************************************************
 * @file
 * 
 * @brief Contains the clear, empty, size, findbyFreq, findbyFirstLetter,
 * findLongest, findMostFrequent, getFrequency, printbyLetter, printbyLength, 
 * and printbyFrequency functions for the wordFreq class
 ****************************************************************************/

#include "wordFreq.h"

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Checks if the wordFreq single linked list is empty or not
 *
 * @returns true if empty, false otherwise
 *
 *****************************************************************************/
bool wordFreq::empty()
{
    if (headptr == nullptr) return true;

    return false;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Gets the size of the wordFreq list
 *
 * @returns size of the wordFreq single linked list
 *
 *****************************************************************************/
int wordFreq::size()
{
    node* temp = headptr;
    int size = 0;

    while (temp != nullptr)
    {
        size++;
        temp = temp->next;
    }

    return size;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Searchs through the list for the most frequent word
 *
 * @returns largest frequency, 0 if empty list
 *
 *****************************************************************************/
int wordFreq::findMostFrequent()
{
    node* temp = headptr;
    int mostFrequent = 0;

    while (temp != nullptr)
    {
        if (temp->frequency > mostFrequent)
        {
            mostFrequent = temp->frequency;
        }

        temp = temp->next;
    }

    return mostFrequent;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Searchs through the list for the longest word
 * 
 * @returns length of longest word in the list
 *
 *****************************************************************************/
int wordFreq::findLongest()
{
    node* temp = headptr;
    int len = 0;

    while (temp != nullptr)
    {
        if (temp->word.length() > len)
        {
            len = (int)temp->word.length();
        }

        temp = temp->next;
    }

    return len;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Checks the list if a word has the same frequency.
 * 
 * @param[in] freq - frequency of word to search for
 *
 * @returns true if found, false otherwise
 *
 *****************************************************************************/
bool wordFreq::findbyFreq(int freq)
{
    node* temp = headptr;

    while (temp != nullptr)
    {
        if (temp->frequency == freq)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Checks the list if a word starts with the given character.
 *
 * @param[in] c - char of first letter
 * 
 * @returns true if found, false otherwise
 *
 *****************************************************************************/
bool wordFreq::findbyFirstLetter(char c)
{
    node* temp = headptr;

    while (temp != nullptr)
    {
        if (temp->word.at(0) == c)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Gets the frequency for a given word
 *
 * @param[in] word - word to get frequency for
 *
 * @returns frequency for searched word, 0 if not found
 *
 *****************************************************************************/
int wordFreq::getFrequency(string word)
{
    node* temp = headptr;

    while (temp != nullptr)
    {
        if (temp->word.compare(word))
        {
            return temp->frequency;
        }
    }

    return 0;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Clears all node from the list, frees memory
 *
 *****************************************************************************/
void wordFreq::clear()
{
    node* curr = headptr;
    node* next;

    while (curr != nullptr)
    {
        next = curr->next;

        delete curr;

        curr = next;
    }

    headptr = nullptr;
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Prints the wordFreq list based on frequency of the words in the list
 * 
 * @param[out] out - ostream to output to
 *
 *****************************************************************************/
void wordFreq::printbyFrequency(ostream& out)
{
    string header = "********************************************************************************";
    int i, j, mostFrequent = findMostFrequent(), longest = findLongest();
    node* temp;
    vector<string> validWords;

    for (i = 1; i <= mostFrequent; i++)
    {
        if (findbyFreq(i))
        {
            validWords.clear();

            temp = headptr;

            while (temp != nullptr)
            {
                if (temp->frequency == i)
                {
                    validWords.push_back(temp->word);
                }

                temp = temp->next;
            }

            sort(validWords.begin(), validWords.end());

            out << header << endl;
            out << "* Words with frequency " << i << endl;
            out << header << endl;
            for (j = 0; j < validWords.size(); j++)
            {
                out << left << setw(longest + 2) << validWords.at(j) << " ";
                if (j != 0 && (j+1) % (int)floor(header.length() / (longest + 2)) == 0) out << endl;
            }
            out << endl << endl;
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Prints the wordFreq list based on the length of the words in the list.
 * 
 * @param[out] out - ostream to output to
 *
 *****************************************************************************/
void wordFreq::printbyLength(ostream& out)
{
    string header = "********************************************************************************";
    int i, j, mostFrequent = findMostFrequent(), longest = findLongest();
    node* temp;
    vector<string> validWords;

    for (i = 1; i <= longest; i++)
    {
        if (findbyLength(i))
        {
            validWords.clear();

            temp = headptr;

            while (temp != nullptr)
            {
                if (temp->word.length() == i)
                {
                    validWords.push_back(temp->word);
                }

                temp = temp->next;
            }

            sort(validWords.begin(), validWords.end());

            out << header << endl;
            out << "* Words of length " << i << endl;
            out << header << endl;
            for (j = 0; j < validWords.size(); j++)
            {
                out << left << setw(longest + 2) << validWords.at(j) << " ";
                if (j != 0 && (j+1) % (int)floor(header.length() / (longest + 2)) == 0) out << endl;
            }
            out << endl << endl;
        }
    }
}

/** ***************************************************************************
 * @author Adam Kraus
 *
 * @par Description:
 * Prints the wordFreq list based on the first letter of the words in the list, from A to Z.
 * 
 * @param[out] out - ostream to output to
 *
 *****************************************************************************/
void wordFreq::printbyLetter(ostream& out)
{
    string header = "********************************************************************************";
    int i, j, mostFrequent = findMostFrequent(), longest = findLongest();
    node* temp;
    vector<string> validWords;

    for (i = 'a'; i <= 'z'; i++)
    {
        if (findbyFirstLetter(i))
        {
            validWords.clear();

            temp = headptr;

            while (temp != nullptr)
            {
                if (temp->word.at(0) == i)
                {
                    validWords.push_back(temp->word);
                }

                temp = temp->next;
            }

            sort(validWords.begin(), validWords.end());

            out << header << endl;
            out << "* Words beginning with the letter " << (char)i << endl;
            out << header << endl;
            for (j = 0; j < validWords.size(); j++)
            {
                out << left << setw(longest + 2) << validWords.at(j) << " ";
                if (j != 0 && j % (int)floor(header.length() / (longest + 2)) == 0) out << endl;
            }
            out << endl << endl;
        }
    }
}