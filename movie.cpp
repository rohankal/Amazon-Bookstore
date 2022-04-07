#include "movie.h"
#include "util.h"

Movie::Movie(const std::string name, const std::string genre,
             const std::string rating, double price, double quantity)
    : Product("movie", name, price, quantity) {
  genre_ = genre;
  rating_ = rating;
}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {

  std::set<std::string> setName = parseStringToWords(name_); // call parseStringToWords() on important information related to movies and return them as keywords
  std::set<std::string> genreName = parseStringToWords(genre_);
  std::set<std::string> toRet = setUnion(setName, genreName);
  toRet.insert(rating_);

  return toRet;
}

std::string Movie::displayString() const {
  // display key information about movies
  std::string toRet = name_ + "\n" + "Genre: " + genre_ +
                      " Rating: " + rating_ + "\n" + std::to_string(price_) +
                      " " + std::to_string(qty_) + " left.";
  return toRet;
}

void Movie::dump(std::ostream &os) const {
  // dump key information about movies
  os << category_ << "\n"
     << name_ << "\n"
     << price_ << "\n"
     << qty_ << "\n"
     << genre_ << "\n"
     << rating_ << "\n";
}
