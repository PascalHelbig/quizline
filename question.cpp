#include "question.h"
#include <string>

Question::Question() { }

Question::Question(int category, std::string question, std::string correct, std::string wrong1, std::string wrong2,
                   std::string wrong3) {
    Question::category = category;
    Question::question = question;
    Question::correct = correct;
    Question::wrong1 = wrong1;
    Question::wrong2 = wrong2;
    Question::wrong3 = wrong3;
}