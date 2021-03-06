#include "question.h"
#include "category.h"

#ifndef QUIZLINE_SQLHELPER_H
#define QUIZLINE_SQLHELPER_H
class SqlHelper {
public:
    static void openDatabase();
    static void insertQuestions(Question* q);
    static Question* getQuestion(int questionId);
    static void deleteQuestion(int questionId);
    static void updateQuestion(Question* q);

    static void insertCategory(Category* c);
    static bool existCategory(int cid);
};
#endif //QUIZLINE_SQLHELPER_H
