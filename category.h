#include <string>

#ifndef QUIZLINE_CATEGORY_H
#define QUIZLINE_CATEGORY_H
class Category {
public:
    Category();
    Category(std::string name);
    Category(int cid, std::string name);

    int cid;
    std::string name;
};

#endif //QUIZLINE_CATEGORY_H
