#include <iostream>
#include <string>
#include <sstream>
#include "question.h"
#include "category.h"
#include "sqlhelper.h"

using namespace std;

const int MAX_CATEGORIES = 3;

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


void createCategory() {
    Category* category = new Category();
    cout << endl << "Bitte Kategoriebezeichnung eingeben: ";
    getline(cin, category->name);
    SqlHelper::insertCategory(category);
}

void getQuestions(int catNumber) {
    cout << endl;
    EXEC SQL BEGIN DECLARE SECTION;
    int category;
    int qid;
    char question[64];
    int sqlCatNumber = catNumber;
    EXEC SQL END DECLARE SECTION;

    if (catNumber == -1) {
        EXEC SQL DECLARE cur CURSOR FOR SELECT qid, category, question FROM quiz ORDER BY qid;
        EXEC SQL OPEN cur;

        EXEC SQL WHENEVER NOT FOUND DO break;
        int lineCounter = 0;
        string userAction;
        do{
            EXEC SQL FETCH cur INTO :qid, :category, :question;
            cout << qid << " - " << question << " (" << category << ")" << endl;
            lineCounter++;
            if (lineCounter == 5)
            {
                cout << "Durch Enter mehr anzeigen. Alles andere zum Abbrechen." << endl;
                getline(cin,userAction);
                if (userAction == "")
                {
                    lineCounter = 0;
                }
            }
        }while(lineCounter < 5);
        EXEC SQL CLOSE cur;
    }
    else
    {
        EXEC SQL DECLARE cur3 CURSOR FOR SELECT qid, category, question FROM quiz WHERE category = :sqlCatNumber ORDER BY qid;
        EXEC SQL OPEN cur3;

        EXEC SQL WHENEVER NOT FOUND DO break;
        int lineCounter = 0;
        string userAction;
        do{
            EXEC SQL FETCH cur3 INTO :qid, :category, :question;
            cout << qid << " - " << question << " (" << category << ")" << endl;
            lineCounter++;
            if (lineCounter == 5)
            {
                cout << "Durch Enter mehr anzeigen. Alles andere zum Abbrechen." << endl;
                getline(cin,userAction);
                if (userAction == "")
                {
                    lineCounter = 0;
                }
            }
        }while(lineCounter < 5);
        EXEC SQL CLOSE cur3;
    }


}

void getQuestion(int id) {
    Question* q = SqlHelper::getQuestion(id);
    cout << endl;
    cout << "Id: " << q->qid << endl;
    cout << "Frage: " << q->question << endl;
    cout << "Antwort: " << q->correct << endl;
    cout << "falsche Antwort: " << q->wrong1 << endl;
    cout << "falsche Antwort: " << q->wrong2 << endl;
    cout << "falsche Antwort: " << q->wrong3 << endl;
    cout << "Kategorie: " << q->category << endl;
}

void getCategories() {
    cout << endl;
    EXEC SQL BEGIN DECLARE SECTION;
    int cid;
    char name[64];
    EXEC SQL END DECLARE SECTION;

    EXEC SQL DECLARE cur2 CURSOR FOR SELECT cid, name FROM category ORDER BY cid;
    EXEC SQL OPEN cur2;
    EXEC SQL WHENEVER NOT FOUND DO break;
    while (1) {
        EXEC SQL FETCH cur2 INTO :cid, :name;
        cout << cid << " - " << name << endl;
    }
    EXEC SQL CLOSE cur2;
}

void createQuestion() {
    Question* q = new Question();

    cout << endl << "Bitte eingeben" << endl;
    cout << "Deine Frage: ";
    getline(cin, q->question);

    cout << "Richtige Antwort: ";
    getline(cin, q->correct);

    cout << "Falsche Antwort 1: ";
    getline(cin, q->wrong1);

    cout << "Falsche Antwort 2: ";
    getline(cin, q->wrong2);

    cout << "Falsche Antwort 3: ";
    getline(cin, q->wrong3);

    string categoryString;
    bool found;
    do {
        cout << "Kategorie wählen:";
        getCategories();
        getline(cin, categoryString);
        istringstream ss(categoryString);
        ss >> q->category;
        found = SqlHelper::existCategory(q->category);
    } while(!found);
    SqlHelper::insertQuestions(q);
}

void deleteQuestion(int id) {
    string selectedId;
    while(id == -1) { //ToDo Abfrage, ob ID vorhanden ist
        cout << "Welche Frage wollen Sie löschen?" << endl;
        getQuestions(-1);
        cout << "Bitte wählen Sie die ID aus!" << endl ;
        cout << "Durch q können Sie abbrechen!" << endl;
        getline(cin, selectedId);
        if ( selectedId == "q" || selectedId == "Q") {
            return;
        }
        istringstream ss(selectedId);
        ss >> id;
        if (id == -1) {
            cout << selectedId << " ist keine gueltige ID!" << endl;
        }
    }
    cout << "Wollen sie die Frage " << id << " wirklich löschen? (y/N)" << endl;
    string confirm;
    getline(cin, confirm);
    if (confirm == "y") {
        SqlHelper::deleteQuestion(id);
    }
}

void editQuestion(int id) {
    string selectedId;
    while (id == -1) {
        cout << "Welche Frage wollen Sie bearbeiten?" << endl;
        getQuestions(-1);
        cout << endl << "Bitte wählen Sie die ID aus!" << endl ;
        cout << "Durch q können Sie abbrechen!" << endl;
        getline(cin, selectedId);
        if ( selectedId == "q" || selectedId == "Q") {
            return;
        }
        istringstream ss(selectedId);
        ss >> id;
        if (id == -1) {
            cout << selectedId << " ist keine gueltige ID!" << endl;
        }
    }
    Question* q = SqlHelper::getQuestion(id);
    string temp;

    ////////Frage
    cout << "alte Frage: " << q->question << endl << "neue Frage: ";
    getline(cin , temp);
    q->question = temp == "" ? q->question : temp;

    /////Antwort richtig
    cout << "alte richtige Antwort: " << q->correct << endl << "neue richtige Antwort: ";
    getline(cin , temp);
    q->correct = temp == "" ? q->correct : temp;

    /////Antwort falsch 1
    cout << "alte falsche Antwort 1: " << q->wrong1 << endl << "neue falsche Antwort 1: ";
    getline(cin , temp);
    q->wrong1 = temp == "" ? q->wrong1 : temp;

    /////Antwort falsch 2
    cout << "alte falsche Antwort 2: " << q->wrong2 << endl << "neue falsche Antwort 2: ";
    getline(cin , temp);
    q->wrong2 = temp == "" ? q->wrong2 : temp;

    /////Antwort falsch 3
    cout << "alte falsche Antwort 3: " << q->wrong3 << endl << "neue falsche Antwort 3: ";
    getline(cin , temp);
    q->wrong3 = temp == "" ? q->wrong3 : temp;

    /////Kategorie
    cout << "alte Kategorie: " << q->category << endl;
    int tempCategory;
    bool found;
    do {
        cout << "neue Kategorie: ";
        getCategories();
        getline(cin, temp);
        istringstream ss(temp);
        ss >> tempCategory;
        found = SqlHelper::existCategory(tempCategory);
    } while (!found && temp != "");
    // Überspringen, wenn Kategorie mit Enter verlassen wurde:
    q->category = temp == "" ? q->category : tempCategory;

    SqlHelper::updateQuestion(q);
}
void questionByCategory(){
    string categoryName;
    int categoryId;
    getCategories();
    cout << "Bitte wählen Sie eine Kategorienummer aus: ";
    getline(cin , categoryName);
    istringstream ss(categoryName);
    ss >> categoryId;
    getQuestions(categoryId);
}

int main() {
    SqlHelper::openDatabase();
    string input;
    string confirm;
    do {
        cout << endl << endl << endl;
        cout << "         Fragen         " << "                  Kategorien" <<  endl;
        cout << "1      - Frage eintragen" << "   //    6      - Kategorie eintragen" << endl;
        cout << "2 [id] - Frage anzeigen" << "    //    7 [id] - Kategorie anzeigen" << endl;
        cout << "3 [id] - Frage löschen" << "     //    8 [id] - Kategorie löschen" <<endl;
        cout << "4 [id] - Frage bearbeiten" << "  //    9 [id] - Kategorie bearbeiten" << endl;
        cout << "5      - Alle Fragen einer Kategorie anzeigen lassen" << endl;
        cout << "q      - schließen" <<  endl;

        getline(cin, input);

        input = removeSpaces(input);
        if (input == "") {
            input = " ";
        }
        int id;
        istringstream ss(input.substr(1));
        ss >> id;
        id = input.substr(1) == "" ? -1 : id;

        EXEC SQL BEGIN DECLARE SECTION;
        int category;
        int cid = id;
        char name[64];
        EXEC SQL END DECLARE SECTION;

        switch (input[0]) {
            case '1':
                createQuestion();
                break;
            case '2':
                if (input.substr(1) == "") {
                    getQuestions(-1);
                } else {
                    getQuestion(id);
                }
                break;
            case '3':
                deleteQuestion(id);
                break;
            case '4':
                editQuestion(id);
                break;
            case '5':
                questionByCategory();
                break;
            case '6':
                createCategory();
                break;
            case '7':
                if (input.substr(1) == "") {
                    getCategories();
                } else {
                    cout << endl;

                    EXEC SQL SELECT cid, name INTO :cid, :category FROM category WHERE cid = :cid;
                    cout << "Id: " << cid << endl;
                    cout << "Kategoriebezeichnung: " << category << endl;
                }
                break;
            case '8':
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
                cout << "Wollen sie die Kategorie " << cid << " wirklich löschen? (y/N)" << endl;
                getline(cin, confirm);
                if (confirm == "y") {
                    EXEC SQL DELETE FROM category WHERE cid = :cid;
                    EXEC SQl COMMIT;
                }
                break;
            case '9':
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
        }
    } while(input != "q");

    //insertQuestion(0, "Wie alt ist...", "jung geblieben", "alt", "tot", "baby");
    return 0;
}