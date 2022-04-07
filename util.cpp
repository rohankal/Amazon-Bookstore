#include "util.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;
std::string convToLower(std::string src) {
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
  rawWords = trim(rawWords); // clean up the input a little bit
  rawWords = convToLower(rawWords);
  set<string> toRet;
  int begin;
  int end;
  int stringSize;
  while (rawWords != "" && rawWords.length() >= 2) { // make sure the current string is not empty and not less than 2 characters long
    stringSize = rawWords.length();
    begin = rawWords.find_first_of(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"); // make sure the term is alphanumeric, find the first instance of a valid character
    end = rawWords.find_first_not_of(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"); // find the first instance of an invlaid character
    if (end < 0) {
      toRet.insert(rawWords);
      break;
    }
    string toAdd = rawWords.substr(begin, end); // splice the valid substring and add it to the list of terms
    if (toAdd.length() >= 2) {
      toRet.insert(toAdd);
    }
    rawWords = rawWords.substr(end + 1, stringSize - 1); // update the overall string we are looking at
  }
  return toRet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(),
                       std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       std::not1(std::ptr_fun<int, int>(std::isspace)))
              .base(),
          s.end());
  return s;
}

// trim from both ends
std::string &trim(std::string &s) { return ltrim(rtrim(s)); }
