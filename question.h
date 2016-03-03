#ifndef QUIZLINE_QUESTION_H
#define QUIZLINE_QUESTION_H
class Question {
public:
    Question();
    Question(int category, const char* question, const char* correct, const char* wrong1, const char* wrong2, const char* wrong3);

    int category;
    const char* question;
    const char* correct;
    const char* wrong1;
    const char* wrong2;
    const char* wrong3;
};
#endif //QUIZLINE_QUESTION_H
