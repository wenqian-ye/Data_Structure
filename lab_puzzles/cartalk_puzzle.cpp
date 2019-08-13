/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    ifstream wordsFile(word_list_fname);
    string word_0;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word_0)) {
            int origin_len = word_0.size();

            if (origin_len == 5){
                string word_1 = word_0.substr(1,origin_len-1);
                string word_2 = word_0.substr(0,1)+word_1.substr(1,origin_len-2);
                if (d.homophones(word_0,word_1) && d.homophones(word_0,word_2)){
                    std::tuple<std::string, std::string, std::string> homo = std::make_tuple (word_0,word_1,word_2);
                    ret.push_back(homo);
                }
            }
        }
    }
    return ret;
}
