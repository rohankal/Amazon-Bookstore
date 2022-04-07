#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <set>
#include <string>

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T> &s1, std::set<T> &s2) {

  typename std::set<T> toRet;
  for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) { // loop through the entirety of a single set
    typename std::set<T>::iterator it2 = s2.find(*it); // check if it exists within the other set
    if (it2 != s2.end()) { // if the item is in both...add it to the intersection set
      toRet.insert(*it); 
    }
  }

  return toRet;
}
template <typename T> std::set<T> setUnion(std::set<T> &s1, std::set<T> &s2) {
  typename std::set<T> toRet;
  for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) { // loop through the entirety of a single set and add it to the union set
    toRet.insert(*it);
  }
  for (typename std::set<T>::iterator it2 = s2.begin(); it2 != s2.end(); // loop through the entire other set and add it to the union set...overlaps will be ignored because of set<T>
       ++it2) {
    toRet.insert(*it2);
  }

  return toRet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from
// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s);

// Removes any trailing whitespace
std::string &rtrim(std::string &s);

// Removes leading and trailing whitespace
std::string &trim(std::string &s);
#endif
