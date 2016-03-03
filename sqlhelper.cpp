#include "sqlhelper.h"

void SqlHelper::openDatabase() {
    EXEC SQL CONNECT TO 'csdb3@lamp.wlan.hwr-berlin.de' USER csdb3 IDENTIFIED BY csdb3;
}