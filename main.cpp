#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_CATEGORIES = 3;

void insertQuestion(int ctg, const char* quest, const char* cor, const char* wr1, const char* wr2, const char* wr3) {
    cout << "inserted " << quest << endl;
    EXEC SQL BEGIN DECLARE SECTION;
    int category;
    const char* question;
    const char* correct;
    const char* wrong1;
    const char* wrong2;
    const char* wrong3;
    EXEC SQL END DECLARE SECTION;
    category = ctg;
    question = quest;
    correct = cor;
    wrong1 = wr1;
    wrong2 = wr2;
    wrong3 = wr3;

    EXEC SQL INSERT INTO "quiz" VALUES (:category, :question, :correct, :wrong1, :wrong2, :wrong3);
    EXEC SQL COMMIT;
}

string removeSpaces(string input) {
    int length = input.length();
    for (int i = 0; i < length; i++) {
        if(input[i] == ' ') {
            input.erase(i, 1);
            length--;
            i--;
        }
    }
    return input;
}

void createQuestion() {
    string question;
    string answer;
    string wrong1;
    string wrong2;
    string wrong3;
    string categoryString;
    int category;

    cout << endl << "Bitte eingeben" << endl;
    cout << "Deine Frage: ";
    getline(cin, question);

    cout << "Richtige Antwort: ";
    getline(cin, answer);

    cout << "Falsche Antwort 1: ";
    getline(cin, wrong1);

    cout << "Falsche Antwort 2: ";
    getline(cin, wrong2);

    cout << "Falsche Antwort 3: ";
    getline(cin, wrong3);

    do {
        cout << "Kategorie (1-" << MAX_CATEGORIES << "): ";
        getline(cin, categoryString);
        istringstream ss(categoryString);
        ss >> category;
    } while (category < 1 || category > MAX_CATEGORIES);
    insertQuestion(category, question.c_str(), answer.c_str(), wrong1.c_str(), wrong2.c_str(), wrong3.c_str());
}

void getQuestions() {
    cout << endl;
    EXEC SQL BEGIN DECLARE SECTION;
    int category;
    int qid;
    char question[64];
    EXEC SQL END DECLARE SECTION;

    EXEC SQL DECLARE cur CURSOR FOR SELECT qid, category, question FROM quiz;
    EXEC SQL OPEN cur;
    EXEC SQL WHENEVER NOT FOUND DO break;
    while (1) {
        EXEC SQL FETCH cur INTO :qid, :category, :question;
        cout << qid << " - " << question << " (" << category << ")" << endl;
    }
    EXEC SQL CLOSE cur;
}

int main() {
    EXEC SQL CONNECT TO 'csdb3@lamp.wlan.hwr-berlin.de' USER csdb3 IDENTIFIED BY csdb3;
    string input;
    do {
        cout << endl << "q - schließen" << endl;
        cout << "e - eintragen" << endl;
        cout << "a [id] - anzeigen" << endl;
        getline(cin, input);

        input = removeSpaces(input);
        switch (input[0]) {
            case 'e':
                createQuestion();
                break;
            case 'a':
                if (input.substr(1) == "") {
                    getQuestions();
                } else {
                    int id;
                    istringstream ss(input.substr(1));
                    ss >> id;
                    cout << endl;
                    EXEC SQL BEGIN DECLARE SECTION;
                    int category;
                    int qid = id;
                    char question[64];
                    char correct[64];
                    char wrong1[64];
                    char wrong2[64];
                    char wrong3[64];
                    EXEC SQL END DECLARE SECTION;
                    EXEC SQL SELECT qid, category, question, correct, wrong1, wrong2, wrong3 INTO :qid, :category, :question, :correct, :wrong1, :wrong2, :wrong3 FROM quiz WHERE qid = :qid;
                    cout << "Id: " << qid << endl;
                    cout << "Frage: " << question << endl;
                    cout << "Antwort: " << correct << endl;
                    cout << "falsche Antwort: " << wrong1 << endl;
                    cout << "falsche Antwort: " << wrong2 << endl;
                    cout << "falsche Antwort: " << wrong3 << endl;
                    cout << "Kategorie: " << category << endl;
                }
                break;
        }
    } while(input != "q");

    //insertQuestion(0, "Wie alt ist...", "jung geblieben", "alt", "tot", "baby");
    return 0;
}