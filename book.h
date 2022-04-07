#include "product.h"

class Book : public Product {

public:
  Book(const std::string name, const std::string author, const std::string isbn,
       double price, double quantity);
  ~Book();
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream &os) const;

private:
  std::string author_;
  std::string isbn_;
};
