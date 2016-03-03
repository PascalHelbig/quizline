#include <string>
#include "category.h"

Category::Category(int cid, std::string name) {
    Category::cid = cid;
    Category::name = name;
}

Category::Category(std::string name) {
    Category::name = name;
}