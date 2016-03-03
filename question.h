#include <string>

#ifndef QUIZLINE_QUESTION_H
#define QUIZLINE_QUESTION_H
class Question {
public:
    Question();
    Question(int category, std::string question, std::string correct, std::string wrong1, std::string wrong2, std::string wrong3);
    Question(int category, std::string question, std::string correct, std::string wrong1, std::string wrong2, std::string wrong3, int qid);

    int qid;
    int category;
    std::string question;
    std::string correct;
    std::string wrong1;
    std::string wrong2;
    std::string wrong3;
private:
    void init(int category, std::string question, std::string correct, std::string wrong1, std::string wrong2, std::string wrong3, int qid);
};
#endif //QUIZLINE_QUESTION_H
