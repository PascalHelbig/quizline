#include "question.h"

Question::Question() { }

Question::Question(int category, const char *question, const char *correct, const char *wrong1, const char *wrong2,
                   const char *wrong3) {
    Question::category = category;
    Question::question = question;
    Question::correct = correct;
    Question::wrong1 = wrong1;
    Question::wrong2 = wrong2;
    Question::wrong3 = wrong3;
}