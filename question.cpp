#include "question.h"
#include <string>

Question::Question() { }

void Question::init(int category, std::string question, std::string correct, std::string wrong1, std::string wrong2,
                    std::string wrong3, int qid) {
    Question::category = category;
    Question::question = question;
    Question::correct = correct;
    Question::wrong1 = wrong1;
    Question::wrong2 = wrong2;
    Question::wrong3 = wrong3;
    Question::qid = qid;
}

Question::Question(int category, std::string question, std::string correct, std::string wrong1, std::string wrong2,
                   std::string wrong3) {
    init(category, question, correct, wrong1, wrong2, wrong3, -1);
}

Question::Question(int category, std::string question, std::string correct, std::string wrong1, std::string wrong2,
                   std::string wrong3, int qid) {
    init(category, question, correct, wrong1, wrong2, wrong3, qid);
}