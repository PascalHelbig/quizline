#include "question.h"

#ifndef QUIZLINE_SQLHELPER_H
#define QUIZLINE_SQLHELPER_H
class SqlHelper {
public:
    static void openDatabase();
    static void insertQuestions(Question* q);
};
#endif //QUIZLINE_SQLHELPER_H
