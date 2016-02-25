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

int main() {
    EXEC SQL CONNECT TO 'csdb3@lamp.wlan.hwr-berlin.de' USER csdb3 IDENTIFIED BY csdb3;
    string input;
    do {
        cout << endl << "q - schließen" << endl;
        cout << "i - eintragen" << endl;
        getline(cin, input);

        switch (input[0]) {
            case 'i':
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
                break;
        }
    } while(input != "q");

    //insertQuestion(0, "Wie alt ist...", "jung geblieben", "alt", "tot", "baby");
    return 0;
}