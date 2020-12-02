/** **************************************************************************
 * @file
 * 
 * @brief Main file
 ****************************************************************************/
 /** **************************************************************************
  * @mainpage Program 2 - Word Frequency
  *
  * @section course_section Course Information
  *
  * @authors Adam Kraus, Lochlan Munro
  *
  * @par Professor:
  *         Roger L. Schrader
  *
  * @par Course:
  *         CSC215 - M002 - Programming Techniques
  *
  * @par Location:
  *         Classroom Building - 203
  *
  * @date Due November 6, 2020
  *
  * @section program_section Program Information
  *
  * @details
  * This program takes in a text file with words and outputs information based 
  * on the frequency of the words in the text file.
  * 
  * This program is started at the command line with 3 necessary arguments, 
  * and 1 optional argument. The 3 necessary arguments include the file that 
  * has all the words, and 2 files that hold a list of the words based on 
  * their first letter and then a list of the words based on the optional 
  * argument. The optional argument is used to determine whether to output
  * words based on frequency, length, or both.
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      none - a straight compile and link with no external libraries.
  *
  * @par Usage:
    @verbatim
    c:\> prog3.exe inputfile outputWords outputStats -[option]
             inputfile   - filename containing our words/story
             outputWords - filename to output words in increasing order
             outputStats - filename to output stats for words based on option
             [option]    - option to change output of stats, "f" for frequency, "l" for length, can use multiple options in any order (ex: -fl)
    @endverbatim
  *
  * @section todo_bugs_modification_section Todo, Bugs, and Modifications
  *
  *****************************************************************************/

#include "prog2.h"
#include "wordFreq.h"

  /** ***************************************************************************
   * @author Adam Kraus, Lochlan Munro
   *
   * @par Description:
   * Main function. Takes command-line input and uses it to collect data
   * about wordcounts in given files, outputting that data to two other files.
   * 
   * An acceptable number of command line arguments (4 or 5) is
   * checked for. An error is output if the number is not 4 or 5. If an option 
   * code was provided, it is confirmed to be valid. If it is not, an error is 
   * output. 
   * 
   * The input, first output (words), and second output (stats) files are all
   * opened and confirmed to have opened properly. The input file is looped
   * through, and each word in it is added to the words linked list with a
   * counter incremented for each repetition. if any failure occurs modifiying
   * the list, an error is output an the program exits.
   * 
   * The words list is output to the first output file useing printbyLetter. The 
   * list is output again to the second output file, this time in the format 
   * specified in the command line.
   * 
   * The memory of the list is freed up, and all files are closed.
   *
   * @param[in] argc - number of command line arguments supplied.
   * @param[in] argv - 2D char array of command line arguments.
   *
   * @returns exit code
   *
   *****************************************************************************/
int main(int argc, char** argv)
{
    string option, inputFile, outputWords, outputStats, word;
    ifstream fin;
    ofstream fout1, fout2;
    wordFreq words;

    // check command line arguments
    if (argc < 4 || argc > 5)
    {
        cout << "Usage: prog2.exe inputFile outputWords outputStats [option]" << endl;
        exit(0);
    }


    //get the commandline option
    //default is -f
    if (argc == 5)
        option = argv[4];
    else
        option = "-f";

    // check option output error and quit if invalid
    if (option != "-f" && option != "-l"
        && option != "-fl" && option != "-lf")
    {
        cout << "Invalid option: " << option << endl;
        exit(0);
    }

    inputFile = argv[1];
    outputWords = argv[2];
    outputStats = argv[3];
    
    // open/check input file
    fin.open(inputFile, ios::in);
    if (!fin.is_open())
    {
        cout << "Unable to open file: " << inputFile << endl;
        exit(0);
    }

    // open/check output words file
    fout1.open(outputWords, ios::out);
    if (!fout1.is_open())
    {
        cout << "Unable to open file: " << outputWords << endl;
        exit(0);
    }

    // open/check output stats file
    fout2.open(outputStats, ios::out);
    if (!fout2.is_open())
    {
        cout << "Unable to open file: " << outputStats << endl;
        exit(0);
    }

    //loop through the file, word by word
    while (fin >> word)
    {
        //format words for consistancy
        trimPunct(word);
        wordToLower(word);

        if (word.empty()) continue;

        //add or increment word in list
        //output error and quit if unsuccesfull
        if (words.findbyWord(word))
        {
            if (!words.increment(word))
            {
                cout << "Unable to increment word: " << word << endl;
                exit(0);
            }
        }
        else {
            if (!words.insert(word))
            {
                cout << "Unable to insert word: " << word << endl;
                exit(0);
            }
        }
    }

    //print words to first output file
    words.printbyLetter(fout1);

    //print stats to second output file
    //in option-specified format
    if (option == "-f")
    {
        words.printbyFrequency(fout2);
    }
    else if (option == "-l")
    {
        words.printbyLength(fout2);
    }
    else if (option == "-fl")
    {
        words.printbyFrequency(fout2);
        words.printbyLength(fout2);
    }
    else if (option == "-lf")
    {
        words.printbyLength(fout2);
        words.printbyFrequency(fout2);
    }

    // clear list, free memory
    words.clear();
    fin.close();
    fout1.close();
    fout2.close();
}