#include "sqlhelper.h"
#include <string>

using namespace std;

void SqlHelper::openDatabase() {
    EXEC SQL CONNECT TO 'csdb3@lamp.wlan.hwr-berlin.de' USER csdb3 IDENTIFIED BY csdb3;
    EXEC SQL WHENEVER SQLERROR SQLPRINT;
    EXEC SQL WHENEVER SQLWARNING SQLPRINT;
}

void SqlHelper::insertQuestions(Question *q) {
    EXEC SQL BEGIN DECLARE SECTION;
    int category = q->category;
    const char* question = q->question.c_str();
    const char* correct = q->correct.c_str();
    const char* wrong1 = q->wrong1.c_str();
    const char* wrong2 = q->wrong2.c_str();
    const char* wrong3 = q->wrong3.c_str();
    EXEC SQL END DECLARE SECTION;
    EXEC SQL INSERT INTO "quiz" VALUES (:category, :question, :correct, :wrong1, :wrong2, :wrong3);
    EXEC SQL COMMIT;
}

Question* SqlHelper::getQuestion(int questionId) {
    EXEC SQL BEGIN DECLARE SECTION;
    int category;
    int qid = questionId;
    char question[64];
    char correct[64];
    char wrong1[64];
    char wrong2[64];
    char wrong3[64];
    EXEC SQL END DECLARE SECTION;
    EXEC SQL SELECT qid, category, question, correct, wrong1, wrong2, wrong3 INTO :qid, :category, :question, :correct, :wrong1, :wrong2, :wrong3 FROM quiz WHERE qid = :qid;
    return new Question(category, string(question), string(correct), string(wrong1), string(wrong2), string(wrong3), qid);
}

void SqlHelper::deleteQuestion(int questionId) {
    EXEC SQL BEGIN DECLARE SECTION;
    int qid = questionId;
    EXEC SQL END DECLARE SECTION;
    EXEC SQL DELETE FROM quiz WHERE qid = :qid;
    EXEC SQl COMMIT;
}

void SqlHelper::updateQuestion(Question *q) {
    EXEC SQL BEGIN DECLARE SECTION;
    int category = q->category;
    int qid = q->qid;
    char question[64];
    char correct[64];
    char wrong1[64];
    char wrong2[64];
    char wrong3[64];
    EXEC SQL END DECLARE SECTION;
    strcpy(question, q->question.c_str());
    strcpy(correct, q->correct.c_str());
    strcpy(wrong1, q->wrong1.c_str());
    strcpy(wrong2, q->wrong2.c_str());
    strcpy(wrong3, q->wrong3.c_str());

    EXEC SQL UPDATE quiz SET correct = :correct, question = :question, wrong1 = :wrong1, wrong2 = :wrong2, wrong3 = :wrong3, category = :category WHERE qid = :qid;
    EXEC SQl COMMIT;
}

void SqlHelper::insertCategory(Category *c) {
    EXEC SQL BEGIN DECLARE SECTION;
    const char* name = c->name.c_str();
    EXEC SQL END DECLARE SECTION;
    EXEC SQL INSERT INTO "category" ("name") VALUES (:name);
    EXEC SQL COMMIT;
}