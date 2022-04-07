#include "product.h"

class Movie : public Product {

public:
  Movie(const std::string name, const std::string genre,
        const std::string rating, double price, double quantity);
  ~Movie();
  std::set<std::string> keywords() const;
  std::string displayString() const;
  void dump(std::ostream &os) const;

private:
  std::string genre_;
  std::string rating_;
};
