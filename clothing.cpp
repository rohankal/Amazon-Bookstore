#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string name, const std::string size,
                   const std::string brand, double price, double quantity)
    : Product("clothing", name, price, quantity) {
  size_ = size;
  brand_ = brand;
}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {

  std::set<std::string> setName = parseStringToWords(name_); // call parseStringToWords() on important information related to clothing and return them as keywords
  std::set<std::string> brandName = parseStringToWords(brand_);
  std::set<std::string> toRet = setUnion(setName, brandName);

  return toRet;
}

std::string Clothing::displayString() const {
  // display key information related to clothing products
  std::string toRet = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ +
                      "\n" + std::to_string(price_) + " " +
                      std::to_string(qty_) + " left.";
  return toRet;
}

void Clothing::dump(std::ostream &os) const {
  // dump key information related to clothing products
  os << category_ << "\n"
     << name_ << "\n"
     << price_ << "\n"
     << qty_ << "\n"
     << size_ << "\n"
     << brand_ << "\n";
}
