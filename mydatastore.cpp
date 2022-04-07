#include "mydatastore.h"
#include <map>

MyDataStore::~MyDataStore() {
  for (std::vector<Product *>::iterator it = products.begin(); 
       it != products.end(); ++it) { // iterate through all products and deallocate each product
    delete (*it);
  }
  for (std::vector<User *>::iterator it2 = users.begin(); it2 != users.end();
       ++it2) { // iterate through all users and deallocate each user
    delete (*it2);
  }
}

void MyDataStore::addProduct(Product *p) {
  products.push_back(p); // add to list of products
  std::set<std::string> setOfKeywords = p->keywords(); // find keywords for given product
  for (std::set<std::string>::iterator it = setOfKeywords.begin(); 
       it != setOfKeywords.end(); ++it) { // go through each keyword and add current product as a product related to each of its keywords
    if (keywordToProduct.find(*it) == keywordToProduct.end()) { // check if the keyword exists in the map or not, if it doesn't...
      std::set<Product *> listOfProducts;
      listOfProducts.insert(p);
      keywordToProduct.insert(
          std::pair<std::string, std::set<Product *> >(*it, listOfProducts));
    } else { // if it already is in the map just relate it to the product
      std::set<Product *> *setOfProducts =
          &(keywordToProduct.find(*it)->second);
      setOfProducts->insert(p);
    }
  }
}

void MyDataStore::addUser(User *u) {
  std::vector<Product *> userProducts;
  users.push_back(u); // add to list of users
  nameToUserObject.insert(std::pair<std::string, User *>(u->getName(), u)); // relate name to user object
  carts.insert(std::pair<std::string, std::vector<Product *> >(u->getName(),
                                                              userProducts)); // relate the username to an empty cart that will be used later
}

std::vector<Product *> MyDataStore::search(std::vector<std::string> &terms,
                                           int type) {

  std::vector<Product *> toRet; //instantiate some variables to help us later
  std::set<Product *> setOfHits;
  std::set<Product *> relatedSet;

  if (keywordToProduct.find(terms.at(0)) != keywordToProduct.end()) { // create the list of hits based on the first keyword
    setOfHits = keywordToProduct.find(terms.at(0))->second;
  }

  for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end();
       ++it) {
    if (keywordToProduct.count(*it) == 1) { //if the current search term is a keyword in the map
      if (type == 0) { // AND
        relatedSet = keywordToProduct.find(*it)->second;
        setOfHits = setIntersection(setOfHits, relatedSet);
      } else { // OR
        relatedSet = keywordToProduct.find(*it)->second;
        setOfHits = setUnion(setOfHits, relatedSet);
      }
    }
  }

  for (std::set<Product *>::iterator it2 = setOfHits.begin();
       it2 != setOfHits.end(); ++it2) { // once you've find all the results, add them to a vector to return and display
    toRet.push_back(*it2);
  }

  return toRet;
}

void MyDataStore::dump(std::ostream &ofile) { // dump based on instructed formatting
  ofile << "<products>" << std::endl; 
  for (std::vector<Product *>::iterator it = products.begin();
       it != products.end(); ++it) {
    (*it)->dump(ofile);
  }
  ofile << "</products>" << std::endl;
  ofile << "<users>" << std::endl;
  for (std::vector<User *>::iterator it2 = users.begin(); it2 != users.end();
       ++it2) {
    (*it2)->dump(ofile);
  }
  ofile << "</users>" << std::endl;
}

void MyDataStore::addHitToCart(std::string nameOfUser, Product *productHit) {
  if (nameOfUser == "" || nameToUserObject.count(nameOfUser) == 0) { // ensure the specified name is valid
    std::cout << "Invalid request" << std::endl;
  } else { // if it is, add it to the specified user's cart
    carts.find(nameOfUser)->second.push_back(productHit);
  }
}

void MyDataStore::viewUserCart(std::string nameOfUser) {
  if (nameOfUser == "" || nameToUserObject.count(nameOfUser) == 0) { // ensure the specified name is valid
    std::cout << "Invalid username" << std::endl;
  } else {
    std::vector<Product *> productsInDaCart = carts.find(nameOfUser)->second;

    int itemNo = 1;
    while (!productsInDaCart.empty()) { // while it is not empty, display each item
      std::cout << std::endl;
      std::cout << "Item " << itemNo << std::endl;
      Product *currentProduct = productsInDaCart.front(); // peek to the first item added to the cart...FIFO
      productsInDaCart.erase(productsInDaCart.begin());
      std::cout << currentProduct->displayString();
      std::cout << std::endl;
      itemNo++;
    }
  }
}

void MyDataStore::buyUserCart(std::string nameOfUser) {
  if (nameOfUser == "" || nameToUserObject.count(nameOfUser) == 0) { // ensure the specified name is valid
    std::cout << "Invalid username" << std::endl;
  } else {
    User *currentUser = nameToUserObject.find(nameOfUser)->second;
    std::vector<Product *> *currentCart = &(carts.find(nameOfUser)->second);

    for (std::vector<Product *>::iterator it = currentCart->begin(); // check every item in the cart and see if it can be purchased
         it != currentCart->end(); ++it) {
      double balance = currentUser->getBalance();
      double priceOfProduct = (*it)->getPrice();
      double amountInStock = (*it)->getQty();
      if ((balance - priceOfProduct) > 0 && amountInStock > 0) { // if it can be purchased...purchase it and update all variables as necessary
        currentUser->deductAmount(priceOfProduct);
        (*it)->subtractQty(1);
        currentCart->erase(it);
        it--;
      }
    }
  }
}