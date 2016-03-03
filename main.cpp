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

void insertCategory(const char* ctg) {
    EXEC SQL BEGIN DECLARE SECTION;
    const char* cat;
    EXEC SQL END DECLARE SECTION;
    cat = ctg;
    cout << cat;

    EXEC SQL INSERT INTO "category" ("name") VALUES (:cat);
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

void createCategory() {
    string categoryString;

    cout << endl << "Bitte Kategoriebezeichnung eingeben: ";
    getline(cin, categoryString);

    insertCategory(categoryString.c_str());
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

void getCategories() {
    cout << endl;
    EXEC SQL BEGIN DECLARE SECTION;
    int cid;
    char name[64];
    EXEC SQL END DECLARE SECTION;

    EXEC SQL DECLARE cur2 CURSOR FOR SELECT cid, name FROM category;
    EXEC SQL OPEN cur2;
    EXEC SQL WHENEVER NOT FOUND DO break;
    while (1) {
        EXEC SQL FETCH cur2 INTO :cid, :name;
        cout << cid << " - " << name << endl;
    }
    EXEC SQL CLOSE cur2;
}

int main() {
    EXEC SQL CONNECT TO 'csdb3@lamp.wlan.hwr-berlin.de' USER csdb3 IDENTIFIED BY csdb3;
    string input;
    do {
        cout << endl << "q - schließen" <<  endl;
        cout <<  "////////Fragen///////////////////////Kategorien//////////" <<  endl;
        cout << "1 - Frage eintragen" <<  "        //    5 - Kategorie eintragen" << endl;
        cout << "2 [id] - Frage anzeigen" << "    //    6 [id] - Kategorie anzeigen" << endl;
        cout << "3 [id] - Frage löschen" << "     //    7 [id] - Kategorie löschen" <<endl;
        cout << "4 [id] - Frage bearbeiten" << "  //    8 [id] - Ka tegorie bearbeiten" << endl;
/*        //////////category
        cout << "5 - Kategorie eintragen" << endl;
        cout << "6 [id] - Kategorie anzeigen" << endl;
        cout << "7 [id] - Kategorie löschen" << endl;
        cout << "8 [id] - Kategorie bearbeiten" << endl;*/
        getline(cin, input);

        input = removeSpaces(input);
        int id;
        istringstream ss(input.substr(1));
        ss >> id;

        EXEC SQL BEGIN DECLARE SECTION;
        int category;
        int qid = id;
        int cid = id;
        char question[64];
        char correct[64];
        char wrong1[64];
        char wrong2[64];
        char wrong3[64];
        char name[64];
        EXEC SQL END DECLARE SECTION;

        switch (input[0]) {
            case '1':
                createQuestion();
                break;
            case '2':
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
            case '3':
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

            case '5':
                createCategory();
                break;
            case '6':
                if (input.substr(1) == "") {
                    getCategories();
                } else {
                    cout << endl;

                    EXEC SQL SELECT cid, name INTO :cid, :category FROM category WHERE cid = :cid;
                    cout << "Id: " << cid << endl;
                    cout << "Kategoriebezeichnung: " << category << endl;
                }
                break;
            case '7':
                if (input.substr(1) == "") {
                    cout << "Welche Kategorie wollen Sie löschen?" << endl;
                    string selectedcId;
                    getCategories();
                    do
                    {
                        cout << "Bitte wählen Sie die ID aus!" << endl ;
                        cout << "Durch q können Sie abbrechen!" << endl;
                        getline(cin, selectedcId);
                        if ( selectedcId == "q" || selectedcId == "Q")
                        {
                            break;
                        }
                        istringstream ss(selectedcId);
                        ss >> cid;
                        if (cid == 0)
                        {
                            cout << selectedcId << " ist keine gueltige ID!" << endl;
                        }
                    }
                    while(cid == 0); //ToDo Abfrage, ob ID vorhanden ist

                }
                EXEC SQL DELETE FROM category WHERE cid = :cid;
                EXEC SQl COMMIT;
                break;
            case '8':
                if (input.substr(1) == "") {
                    cout << "Welche Kategorie wollen Sie bearbeiten?" << endl;
                    string selectedcId;
                    getCategories();
                    do
                    {
                        cout << endl << "Bitte wählen Sie die ID aus!" << endl ;
                        cout << "Durch q können Sie abbrechen!" << endl;
                        getline(cin, selectedcId);
                        if ( selectedcId == "q" || selectedcId == "Q")
                        {
                            break;
                        }
                        istringstream ss(selectedcId);
                        ss >> cid;
                        if (cid == 0)
                        {
                            cout << selectedcId << " ist keine gueltige ID!" << endl;
                        }
                    }
                    while(cid == 0); //ToDo Abfrage, ob ID vorhanden ist
                }

                EXEC SQL SELECT cid, name INTO :cid, :name FROM category WHERE cid = :cid;
                ////////Frage
                {
                cout << "alte Kategoriebezeichnung: " << name << endl;
                string tempName;
                cout << "neue Kategoriebezeichnung: ";
                getline(cin , tempName);
                if(tempName != ""){
                    strcpy(name, tempName.c_str());
                }
                }
                cout << "neue Kategoriebezeichnung: ";

                EXEC SQL UPDATE category SET name = :name WHERE cid = :cid;
                EXEC SQl COMMIT;
                break;

            case '4':
                if (input.substr(1) == "") {
                    cout << "Welche Frage wollen Sie bearbeiten?" << endl;
                    string selectedId;
                    getQuestions();
                    do
                    {
                        cout << endl << "Bitte wählen Sie die ID aus!" << endl ;
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

                /////Antwort richtig
                cout << "alte richtige Antwort: " << correct << endl;
                string tempCorrect;
                cout << "neue richtige Antwort: ";
                getline(cin , tempCorrect);
                if(tempCorrect != ""){
                    strcpy(correct, tempCorrect.c_str());
                }

                /////Antwort falsch 1
                cout << "alte falsche Antwort 1: " << wrong1 << endl;
                string tempWrong1;
                cout << "neue falsche Antwort 1: ";
                getline(cin , tempWrong1);
                if(tempWrong1 != ""){
                    strcpy(wrong1, tempWrong1.c_str());
                }

                /////Antwort falsch 2
                cout << "alte falsche Antwort 2: " << wrong2 << endl;
                string tempWrong2;
                cout << "neue falsche Antwort 2: ";
                getline(cin , tempWrong2);
                if(tempWrong2 != ""){
                    strcpy(wrong2, tempWrong2.c_str());
                }

                /////Antwort falsch 3
                cout << "alte falsche Antwort 3: " << wrong3 << endl;
                string tempWrong3;
                cout << "neue falsche Antwort 3: ";
                getline(cin , tempWrong3);
                if(tempWrong3 != ""){
                    strcpy(wrong3, tempWrong3.c_str());
                }

                /////Kategorie
                cout << "alte Kategorie: " << category << endl;
                int tempCategory;
                string tempCategoryString;
                do {
                    cout << "neue Kategorie (1-" << MAX_CATEGORIES << "): ";
                    getline(cin, tempCategoryString);
                    istringstream ss(tempCategoryString);
                    ss >> tempCategory;
                } while ((tempCategory < 1 || tempCategory > MAX_CATEGORIES) && tempCategoryString != "");
                // Überspringen, wenn Kategorie mit Enter verlassen wurde:
                if (tempCategoryString != "") {
                    category = tempCategory;
                }

                EXEC SQL UPDATE quiz SET correct = :correct, question = :question, wrong1 = :wrong1, wrong2 = :wrong2, wrong3 = :wrong3, category = :category WHERE qid = :qid;
                EXEC SQl COMMIT;
                break;

        }
    } while(input != "q");

    //insertQuestion(0, "Wie alt ist...", "jung geblieben", "alt", "tot", "baby");
    return 0;
}