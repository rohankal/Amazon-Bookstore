#include "product.h"

class Clothing : public Product {

public:
  Clothing(const std::string name, const std::string size,
           const std::string brand, double price, double quantity);
  ~Clothing();
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream &os) const;

private:
  std::string size_;
  std::string brand_;
};
