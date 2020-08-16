/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

// using std::string;
// using std::vector;
// using std::ifstream;

using namespace std;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            string sorted = word;
            sort(sorted.begin(), sorted.end());
            dict[sorted].push_back(word);
        }
    }

    wordsFile.close();
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(string str : words){
        string sorted = str;
        sort(sorted.begin(), sorted.end());
        dict[sorted].push_back(str);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string sorted = word;
    sort(sorted.begin(), sorted.end());

    if(dict.find(sorted) == dict.end()) return vector<string>();

    return dict.find(sorted)->second;


}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    if (dict.size() == 0) return vector<vector<string>>();

    vector<vector<string>> answer;

    for(auto vec : dict){
        if(vec.second.size() > 1) answer.push_back(vec.second);
    }

    return answer;
}
