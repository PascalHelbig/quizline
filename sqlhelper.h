#include "question.h"

#ifndef QUIZLINE_SQLHELPER_H
#define QUIZLINE_SQLHELPER_H
class SqlHelper {
public:
    static void openDatabase();
    static void insertQuestions(Question* q);
    static Question* getQuestion(int questionId);
    static void deleteQuestion(int questionId);
};
#endif //QUIZLINE_SQLHELPER_H
