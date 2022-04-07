#include "datastore.h"
#include "util.h"
#include <map>
#include <set>

class MyDataStore : public DataStore {
public:
  ~MyDataStore();
  void addProduct(Product *p);
  void addUser(User *u);
  std::vector<Product *> search(std::vector<std::string> &terms, int type);
  void dump(std::ostream &ofile);
  void addHitToCart(std::string nameOfUser, Product *productHit);
  void viewUserCart(std::string nameOfUser);
  void buyUserCart(std::string nameOfUser);

private:
  std::vector<Product *> products; // keep track of all products
  std::vector<User *> users; // keep track of all users
  std::map<std::string, std::set<Product *> > keywordToProduct; // maps each keyword to a list of products who share that keyword
  std::map<std::string, User *> nameToUserObject; // maps names of users to their user objects
  std::map<std::string, std::vector<Product *> > carts; // maps names of users to their shopping carts
};
