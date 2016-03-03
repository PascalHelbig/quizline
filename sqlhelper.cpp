#include "sqlhelper.h"

void SqlHelper::openDatabase() {
    EXEC SQL CONNECT TO 'csdb3@lamp.wlan.hwr-berlin.de' USER csdb3 IDENTIFIED BY csdb3;
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