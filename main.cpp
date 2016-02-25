#include <iostream>
#include <string>

using namespace std;

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
        cin >> input;
    } while(input != "q");

    //insertQuestion(0, "Wie alt ist...", "jung geblieben", "alt", "tot", "baby");
    return 0;
}