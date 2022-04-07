#include "book.h"
#include "util.h"

Book::Book(const std::string name, const std::string author,
           const std::string isbn, double price, double quantity)
    : Product("book", name, price, quantity) {
  author_ = author;
  isbn_ = isbn;
}

Book::~Book() {}

std::set<std::string> Book::keywords() const {

  std::set<std::string> setName = parseStringToWords(name_); // call parseStringToWords() on important information related to books and return them as keywords
  std::set<std::string> authorName = parseStringToWords(author_);
  std::set<std::string> toRet = setUnion(setName, authorName);
  toRet.insert(isbn_);

  return toRet;
}

std::string Book::displayString() const {

  // display key information about the book product
  std::string toRet = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ +
                      "\n" + std::to_string(price_) + " " +
                      std::to_string(qty_) + " left.";
  return toRet;
}

void Book::dump(std::ostream &os) const {
  // dump key information about the book product

  os << category_ << "\n"
     << name_ << "\n"
     << price_ << "\n"
     << qty_ << "\n"
     << isbn_ << "\n"
     << author_ << "\n";
}
