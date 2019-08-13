/**
 * @file pronounce_dict.cpp
 * Implementation of the PronounceDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "pronounce_dict.h"

#include <iterator>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>

using std::string;
using std::map;
using std::vector;
using std::ifstream;
using std::istream;
using std::istream_iterator;
using std::stringstream;

/**
 * Constructs a PronounceDict from a CMU pronunciation dictionary
 * file. See http://www.speech.cs.cmu.edu/cgi-bin/cmudict .
 * @param pronun_dict_filename Filename of the CMU pronunciation
 * dictionary.
 */
PronounceDict::PronounceDict(const string& pronun_dict_filename)
{
    ifstream pronun_dict_file(pronun_dict_filename);
    string line;
    if (pronun_dict_file.is_open()) {
        while (getline(pronun_dict_file, line)) {
            /* Used to break the line by whitespace. The CMU Dict does this for
             * separating words from their pronunciations. */
            stringstream line_ss(line);
            istream_iterator<string> line_begin(line_ss);
            istream_iterator<string> line_end;
            if (line[0] != '#' && *line_begin != ";;;") {
                /* Associate the word with the rest of the line
                 * (its pronunciation). */
                istream_iterator<string> temp_itr = line_begin;
                dict[*temp_itr] = vector<string>(++line_begin, line_end);
            }
        }
    }
    /* If it's not open then... well... just don't do anything for the sake
     * of simplicity. */
}

/**
 * Constructs a PronounceDict from a CMU std::map mapping the word
 * to a vector of strings which represent the pronunciation.
 * @param pronun_dict Maps a string word to a vector of strings
 * representing its pronunciation.
 */
PronounceDict::PronounceDict(const map<string, vector<string>>& pronun_dict)
    : dict(pronun_dict)
{
    /* Nothing to see here. */
}

/**
 * Uses the dictionary to determine if the two words are homophones.
 * @param word1 First word to be tested.
 * @param word2 Second word to be tested.
 * @return true if the two words are homophones, false otherwise (or
 * one or both words weren't in the dictionary).
 * Note: The word keys in the dictionary are stored in uppercase.
 */
bool PronounceDict::homophones(const string& word1, const string& word2) const
{
    /* Your code goes here! */
//    string word1_cp = word1;
//    string word2_cp = word2;
//    std::transform(word1_cp.begin(), word1_cp.end(), word1_cp.begin(), ::toupper);
//    std::transform(word2_cp.begin(), word2_cp.end(), word2_cp.begin(), ::toupper);
//    vector<string> pron1 = dict.find(word1_cp)->second;
//    vector<string> pron2 = dict.find(word2_cp)->second;
//    size_t len1 = pron1.size();
//    size_t len2 = pron2.size();
//    if (len1 == 0 || len2 == 0){
//        return false;
//    }
//
//    if (len1 != len2){
//        return false;
//    }
//    for (size_t i=0; i<len1; i++){
//        if (pron1[i] != pron2[i]){
//            return false;
//        }
//    }
//    // ???
//    return true;
    string temp1 = word1;
    string temp2 = word2;
    std::transform(word1.begin(), word1.end(), temp1.begin(), toupper);
    std::transform(word2.begin(), word2.end(), temp2.begin(), toupper);

    if(dict.find(temp1)!=dict.end() && dict.find(temp2)!=dict.end()){
        if(dict.find(temp1)->second==dict.find(temp2)->second){
            return true;
        }
    }
    else{
        return false;
    }
    return false;

}
