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

/*void changeQuestionPart(int _id, string partText, const char* partName, char* _part){
    EXEC SQL BEGIN DECLARE SECTION;
    const char* part;
    int id;
    EXEC SQL END DECLARE SECTION;
    cout << "alte " << partText <<": " << _part << endl;
    string tempPart;
    cout << "neue " << partText <<": ";
    getline(cin , tempPart);
    if(tempPart != ""){
        strcpy(_part, tempPart.c_str());
    };
    part = _part;
    id = _id;
    EXEC SQL UPDATE quiz SET partName = :part WHERE id = :id;
}*/

int main() {
    EXEC SQL CONNECT TO 'csdb3@lamp.wlan.hwr-berlin.de' USER csdb3 IDENTIFIED BY csdb3;
    string input;
    do {
        cout << endl << "q - schließen" << endl;
        cout << "e - eintragen" << endl;
        cout << "a [id] - anzeigen" << endl;
        cout << "l [id] - löschen" << endl;
        cout << "b [id] - bearbeiten" << endl;
        getline(cin, input);

        input = removeSpaces(input);
        int id;
        istringstream ss(input.substr(1));
        ss >> id;

        EXEC SQL BEGIN DECLARE SECTION;
        int category;
        int qid = id;
        char question[64];
        char correct[64];
        char wrong1[64];
        char wrong2[64];
        char wrong3[64];
        EXEC SQL END DECLARE SECTION;

        switch (input[0]) {
            case 'e':
                createQuestion();
                break;
            case 'a':
                if (input.substr(1) == "") {
                    getQuestions();
                } else {
                    cout << endl;

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
            case 'l':
                if (input.substr(1) == "") {
                    cout << "Welche Frage wollen Sie löschen?" << endl;
                    string selectedId;
                    getQuestions();
                    do
                    {
                        cout << "Bitte wählen Sie die ID aus!" << endl ;
                        cout << "Durch q können Sie abbrechen!" << endl;
                        getline(cin, selectedId);
                        if ( selectedId == "q" || selectedId == "Q")
                        {
                            break;
                        }
                        istringstream ss(selectedId);
                        ss >> qid;
                        if (qid == 0)
                        {
                            cout << selectedId << " ist keine gueltige ID!" << endl;
                        }
                    }
                    while(qid == 0); //ToDo Abfrage, ob ID vorhanden ist

                }
                EXEC SQL DELETE FROM quiz WHERE qid = :qid;
                EXEC SQl COMMIT;
                break;
            case 'b':

                if (input.substr(1) == "") {
                    cout << "Welche Frage wollen Sie bearbeiten?" << endl;
                    string selectedId;
                    getQuestions();
                    do
                    {
                        cout << "Bitte wählen Sie die ID aus!" << endl ;
                        cout << "Durch q können Sie abbrechen!" << endl;
                        getline(cin, selectedId);
                        if ( selectedId == "q" || selectedId == "Q")
                        {
                            break;
                        }
                        istringstream ss(selectedId);
                        ss >> qid;
                        if (qid == 0)
                        {
                            cout << selectedId << " ist keine gueltige ID!" << endl;
                        }
                    }
                    while(qid == 0); //ToDo Abfrage, ob ID vorhanden ist
                }

                EXEC SQL SELECT qid, category, question, correct, wrong1, wrong2, wrong3 INTO :qid, :category, :question, :correct, :wrong1, :wrong2, :wrong3 FROM quiz WHERE qid = :qid;
                ////////Frage
                cout << "alte Frage: " << question << endl;
                string tempQuestion;
                cout << "neue Frage: ";
                getline(cin , tempQuestion);
                if(tempQuestion != ""){
                    strcpy(question, tempQuestion.c_str());
                }
                EXEC SQL UPDATE quiz SET question = :question WHERE qid = :qid;
                /////Antwort richtig
                cout << "alte richtige Antwort: " << correct << endl;
                string tempCorrect;
                cout << "neue richtige Antwort: ";
                getline(cin , tempCorrect);
                if(tempCorrect != ""){
                    strcpy(correct, tempCorrect.c_str());
                }
                EXEC SQL UPDATE quiz SET correct = :correct WHERE qid = :qid;

                /////Antwort falsch 1
                cout << "alte falsche Antwort 1: " << wrong1 << endl;
                string tempWrong1;
                cout << "neue falsche Antwort 1: ";
                getline(cin , tempWrong1);
                if(tempWrong1 != ""){
                    strcpy(wrong1, tempWrong1.c_str());
                }
                EXEC SQL UPDATE quiz SET wrong1 = :wrong1 WHERE qid = :qid;

                /////Antwort falsch 2
                cout << "alte falsche Antwort 2: " << wrong2 << endl;
                string tempWrong2;
                cout << "neue falsche Antwort 2: ";
                getline(cin , tempWrong2);
                if(tempWrong2 != ""){
                    strcpy(wrong2, tempWrong2.c_str());
                }
                EXEC SQL UPDATE quiz SET wrong2 = :wrong2 WHERE qid = :qid;

                /////Antwort falsch 3
                cout << "alte falsche Antwort 3: " << wrong3 << endl;
                string tempWrong3;
                cout << "neue falsche Antwort 3: ";
                getline(cin , tempWrong3);
                if(tempWrong3 != ""){
                    strcpy(wrong3, tempWrong3.c_str());
                }
                EXEC SQL UPDATE quiz SET wrong3 = :wrong3 WHERE qid = :qid;
                /////Kategorie
                cout << "alte Kategorie: " << category << endl;
                int tempCategory;
                string tempCategoryString;
                cout << "neue Kategorie (1-" << MAX_CATEGORIES << "): ";
                do {
                    getline(cin, tempCategoryString);
                    istringstream ss(tempCategoryString);
                    ss >> tempCategory;
                } while ((tempCategory < 1 || tempCategory > MAX_CATEGORIES) && tempCategoryString != "");
                category = tempCategory;

                EXEC SQL UPDATE quiz SET category = :category WHERE qid = :qid;

/*
                changeQuestionPart(qid, "falsche Antwort_1", "wrong1", wrong1);
                changeQuestionPart(qid, "falsche Antwort_2", "wrong2", wrong2);
                changeQuestionPart(qid, "falsche Antwort_3", "wrong3", wrong3);
*/


                //cout << "Kategorie: " << category << endl;
                EXEC SQl COMMIT;
                break;
        }
    } while(input != "q");

    //insertQuestion(0, "Wie alt ist...", "jung geblieben", "alt", "tot", "baby");
    return 0;
}