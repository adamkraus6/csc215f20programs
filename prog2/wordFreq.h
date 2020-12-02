/** **************************************************************************
 * @file
 *
 * @brief Class Definition
 ****************************************************************************/

#include "prog2.h"

/**
 * @brief Hold the data for list of words
 */
class wordFreq
{
public:
    wordFreq();
    ~wordFreq();
    bool empty();
    int size();
    bool findbyWord(string word);
    bool findbyLength(int length);
    bool findbyFreq(int freq);
    bool findbyFirstLetter(char c);
    int findMostFrequent();
    int findLongest();
    bool insert(string word);
    bool remove(string word);
    bool increment(string word);
    bool decrement(string word);
    int getFrequency(string word);
    void clear();
    void printbyFrequency(ostream& out);
    void printbyLength(ostream& out);
    void printbyLetter(ostream& out);

private:
    /**
     * @brief Holds data about a node in the linked list.
     */
    struct node
    {
        string word;    /**< Unique word.                         */
        int frequency;  /**< Frequency for the word.              */
        node* next;     /**< Pointer to the next node in the list */
    };
    node* headptr;      /**< The head pointer for the linked list. */
};