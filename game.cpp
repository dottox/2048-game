/* ############################ INTRODUCCION ############################ */
/*                                                                        */
/*                               2048 JUEGO                               */
/*                Realizado por I. Suarez y J. M. Rodriguez               */
/*          Segundo laboratorio de Principios de Programación 2023        */
/*                                                                        */
/* ###################################################################### */


#include "core.cpp"

/*############################# VARIABLES #############################*/

const int MAX_USERS = 10;
const int ACTUAL_YEAR = 2023;
const int MIN_YEAR = ACTUAL_YEAR - 120;

int board[4][4] = {0}, boardLast[4][4] = {0}, score = 0, lastScore = 0, actualActiveUsers = 0, actualInactiveUsers = 0, responseStatus = 0;

bool firstTurn = true, changeDetected = true, victory = false, defeat = false, isRegret = false;

char lastMovement = ' ';

string response = " ", actualPlayer = " ";

player activeUsers[MAX_USERS], inactiveUsers[MAX_USERS];




/*############################# FUNCIONES #############################*/

bool menu();
bool submenu_usuario();
bool submenu_jugar();
bool submenu_informes();

void showTitle();
void resetBools();

int game();
void genRandom();
void move(char movement);

void showBoard();
void cleanBoard(int theBoard[][4]);
void copyBoard(int firstBoard[][4], int secondBoard[][4]);

bool isFull();
int stringDigit(string a);
void waitUntilImput();
void cleanScreen();

void cleanInactiveUser(int indice);
void cleanActiveUser(int indice);


/*############################# CODIGO. #############################*/

int main() {

    bool active = false;

    
    do {
        active = menu();
    } while (active == true);
            
    return 0;
}





bool menu() {
    string xstring;

    cleanScreen();
    showTitle();
    switch(responseStatus) {
        case 1:
            cout << "\033[31m" << response << "\033[31m" << endl << endl;
            break;
        case 2:
            cout << response << score << endl << endl;
            break;
    }
    responseStatus = 0;
    
    printf("\033[92m\nBienvenido/a a 2048, seleccione:\n\n  (1)\033[0m Gestion Usuario.\n  \033[92m(2)\033[0m Jugar.\n  \033[92m(3)\033[0m Informes.\n\033[31m  (x)\033[0m Cerrar.\n\n\033[92mRespuesta:\033[0m ");
  
    getline(cin, xstring);
    switch(xstring[0]) {
        case '1': /* Gestion Usuario */
            bool usuario_status;
            do {
                usuario_status = submenu_usuario();
            } while (usuario_status);
            return true;
            break;
        
        case '2': /* Opcion: jugar */
            bool jugar_status;
            do {
            jugar_status = submenu_jugar();
            } while (jugar_status);
            return true;
            break;
        
        case '3': /* Informes */
            bool informes_status;
            do {
            informes_status = submenu_informes();
            } while (informes_status);
            return true;
            break;
        case 'x': /* Opcion: cerrar */
            cleanScreen();
            printf("\033[92m\n[ Nos vemos, gracias por jugar ]\n\n");
            return false;
            break;
        default: /* Opcion: error */
            return true;
            break;        
    }
}


bool submenu_usuario() {
    int num, i;
    bool usedAlias = false;
    string xstring;
    
    cleanScreen();
    showTitle();
    printf("\n\033[92m[ Menu: Gestion Usuario ]\033[0m\n\n  \033[92m(1)\033[0m Alta de usuario.\n  \033[92m(2)\033[0m Baja de usuario.\n  \033[31m(x)\033[0m Atras\n\n\033[92mRespuesta:\033[0m ");
    getline(cin, xstring);
            
    switch (xstring[0]) {
        case '1': {

            if (actualActiveUsers >= MAX_USERS) {
                response = "\n-- Se alcanzo el limite de usuarios --";
                responseStatus = 1;
                return false;
            }

            do {
                cleanScreen();
                showTitle();
                printf("\n\033[92mIngrese su alias \033[0m(3-11 caracteres) ('cancelar' para salir)\n\n- ");
                getline(cin, xstring); 
                
            } while (xstring.size() < 3 || xstring.size() > 11);
            
            for (int i = 0; i < actualActiveUsers; i++) {
                if (xstring == activeUsers[i].alias) {
                    response = "\n --ERROR. Ese alias ya está en uso.--";
                    responseStatus = 1;
                    return false;
                }
                else if (xstring == inactiveUsers[i].alias) {
                    activeUsers[actualActiveUsers] = inactiveUsers[i];
                    actualActiveUsers++;
                    cleanInactiveUser(i);
                    response = "\n\033[38;5;46mSe ha reactivado el usuario, bienvenido devuelta.\033[0m";
                    responseStatus = 1;
                    return false;
                }
            }

            if (xstring == "cancelar")
                return true;
            
            activeUsers[actualActiveUsers].alias = xstring;
            
            do {
            cleanScreen();
            showTitle();
            printf("\n\033[92mIngrese su nombre \033[0m(3-11 caracteres)\n\n- ");
            getline(cin, xstring);
            } while (xstring.size() < 3 || xstring.size() > 11);
            
            activeUsers[actualActiveUsers].name = xstring;
            
            do {
            cleanScreen();
            showTitle();
            printf("\n\033[92mIngrese su apellido \033[0m(3-11 caracteres)\n\n- ");
            getline(cin, xstring);
            } while (xstring.size() < 3 || xstring.size() > 11);
            
            activeUsers[actualActiveUsers].surname = xstring;
            
            
            do {
            cleanScreen();
            showTitle();
            printf("\n\033[92mIngrese su día de nacimiento \033[0m(del 1 al 31)\n\n- ");
            getline(cin, xstring);
            num = stringDigit(xstring);
            } while (num < 1 || num > 31);
            
            activeUsers[actualActiveUsers].birthday.day = num;
            
            
            do {
            cleanScreen();
            showTitle();
            printf("\n\033[92mIngrese su mes de nacimiento \033[0m(del 1 al 12)\n\n- ");
            getline(cin, xstring);
            num = stringDigit(xstring);
            } while (num < 1 || num > 12);
            
            activeUsers[actualActiveUsers].birthday.month = num;
            

            do {
            cleanScreen();
            showTitle();
            printf("\n\033[92mIngrese su año de nacimiento \033[0m(del %i al %i)\n\n- ", MIN_YEAR, ACTUAL_YEAR);
            getline(cin, xstring);
            num = stringDigit(xstring);
            } while (num < MIN_YEAR || num > ACTUAL_YEAR);
            
            activeUsers[actualActiveUsers++].birthday.year = num;

            response = "\n\033[38;5;46mSe ha activado con exito el usuario\033[0m";
            responseStatus = 1;
            
            return false;
        } /* Alta de Usuario */
            break;
        case '2': {
            
            if (actualActiveUsers == 0) {
                response = "\n-- No hay usuarios registrados aun --";
                responseStatus = 1;
                return false;
            }

            if (actualInactiveUsers >= MAX_USERS) {
                response = "\n-- Se alcanzo el limite de usuarios inactivos --";
                responseStatus = 1;
                return false;
            }
            
            do {
            cleanScreen();

            printf("\n\033[92m[ Lista de Usuarios ]\n\n\033[0m");
            for (int p = 0; p < actualActiveUsers; p++) {
                cout << "- \033[93m" << activeUsers[p].alias << "\033[0m" << endl;
            }
                
            printf("\n\n\033[92mIngrese el alias a dar de baja \n\033[0m('cancelar' para salir)\n\n- ");
            getline(cin, xstring);

            if (xstring == "cancelar") {
                response = "\n-- Servicio de baja cancelado --";
                responseStatus = 1;
                return false;
            }
                
            for (i = 0; i < actualActiveUsers; i++) {
                if (xstring == activeUsers[i].alias) {
                    usedAlias = true;
                    cleanScreen();
                    break;
                }
            }
            } while (!usedAlias);

            showTitle();
            cout << "\n\033[92m¿Deseas dar de baja a... \033[93m" << activeUsers[i].alias << "\033[92m?\033[0m" << endl;
            printf("\n\033[92m  (1)\033[0m Si, estoy seguro\n\033[92m  \033[0mPresione otra tecla para cancelar\n\n\033[92mRespuesta: \033[0m");
            getline(cin, xstring);

            if (xstring[0] == '1') {
                response = "\n\033[38;5;245mSe ha dado de baja al usuario con exito.\033[0m";
                responseStatus = 1;
                inactiveUsers[actualInactiveUsers++] = activeUsers[i];
                cleanActiveUser(i);
                
            }
            else {
                response = "\n-- Servicio de baja cancelado --";
                responseStatus = 1;
            }

            return false;
        } /* Baja de usuario */
            break;
        case 'x': {
            response = "\nVolviendo al menu...";
            responseStatus = true;
            return false;
            break;
        default:
            return true;
            break;
        } /* Atras */
    }
}


bool submenu_jugar() {
    int x2, i, numberMatches, num;
    string reply;
    bool finded = false;

    if (actualActiveUsers == 0) {
        response = "\n-- No hay usuarios activos aun --";
        responseStatus = 1;
        return false;
    }
    
    srand(time(NULL));
    resetBools();
    cleanBoard(board);
    cleanBoard(boardLast);
    genRandom();
    
    cleanScreen();
    showTitle();

    printf("\n\033[92m[ Lista de Usuarios ]\n\n\033[0m");
    for (int p = 0; p < actualActiveUsers; p++) {
        cout << "- \033[93m" << activeUsers[p].alias << "\033[0m" << endl;
    }
    
    printf("\n\n\033[92mIngrese su alias para jugar.\033[0m\n\n- ");
    getline(cin, reply);

    for (i = 0; i < actualActiveUsers; i++) {
        if (reply == activeUsers[i].alias) {
            finded = true;
            break;
        }
    }

    if (!finded) {
        cleanScreen();
        showTitle();
        response = "\n-- No se encontro al usuario. --";
        responseStatus = true;
        return false;
    }

    actualPlayer = activeUsers[i].alias;
    numberMatches = activeUsers[i].matchesPlayed;

    do {
        cleanScreen();
        showTitle();
        printf("\n\033[92mIngrese el día \033[0m(del 1 al 31)\n\n- ");
        getline(cin, reply);
        if (!stringDigit(reply))
            num = 0;
        else
            num = stringDigit(reply);
    } while (num < 1 || num > 31);
    activeUsers[i].history[numberMatches].date.day = num;
            
    do {
        cleanScreen();
        showTitle();
        printf("\n\033[92mIngrese el mes \033[0m(del 1 al 12)\n\n- ");
        getline(cin, reply);
        if (!stringDigit(reply))
            num = 0;
        else
            num = stringDigit(reply);
    } while (num < 1 || num > 12);
    activeUsers[i].history[numberMatches].date.month = num;

    do {
        cleanScreen();
        showTitle();
        printf("\n\033[92mIngrese el año \033[0m(del 1900 al %i)\n\n- ", ACTUAL_YEAR);
        getline(cin, reply);
        if (!stringDigit(reply))
            num = 0;
        else
            num = stringDigit(reply);
    } while (num < 1900 || num > ACTUAL_YEAR);
    activeUsers[i].history[numberMatches].date.year = num;

    if (num < activeUsers[i].birthday.year) {
        response = "\n-- ¿Juega la partida antes de nacer? --";
        responseStatus = 1;
        cleanScreen();
        return false;
    }

    int my_time = time(NULL);
    activeUsers[i].history[numberMatches].time.hours = (((my_time/60)/60)%24)-3;
    activeUsers[i].history[numberMatches].time.minutes = ((my_time/60)%60);
            
    x2 = game();
    switch (x2) {
        case 1:
            cleanScreen();
            response = "\n\033[38;5;46mGanaste!\nPuntuacion Final: \033[0m";
            responseStatus = 2;
            activeUsers[i].history[numberMatches].result = "\033[92mVictoria\033[0m";
            activeUsers[i].history[numberMatches].scoreMatch = score;
            activeUsers[i].matchesPlayed++;
            break;
        case 0:
            cleanScreen();
            response = "\n\033[38;5;161mPerdiste!\nPuntuacion Final: \033[0m";
            responseStatus = 2;
            activeUsers[i].history[numberMatches].result = "\033[31mDerrota\033[0m";
            activeUsers[i].history[numberMatches].scoreMatch = score;
            activeUsers[i].matchesPlayed++;
            break;
        case -1:
            cleanScreen();
            response = "\n\033[38;5;245mAbandonaste!\nPuntuacion Final: \033[0m";
            responseStatus = 2;
            activeUsers[i].history[numberMatches].result = "\033[38;5;245mAbandono\033[0m";
            activeUsers[i].history[numberMatches].scoreMatch = score;
            activeUsers[i].matchesPlayed++;
            break;
        default:
            printf("ERROR\nRegresando al menú\n\n");
            break;
    }
    getchar();
    return false;
}


bool submenu_informes() {
    int p, num, replyDate_day, replyDate_month ,replyDate_year;
    string reply;
    bool noMatches = true;
    cleanScreen();
    showTitle();
    printf("\n\033[92m[ Menu: Informes ]\033[0m\n\n  \033[92m(1)\033[0m Listado de usuarios.\n  \033[92m(2)\033[0m Listado de todas las partidas jugadas.\n  \033[92m(3)\033[0m Listado de partidas por usuario.\n  \033[92m(4)\033[0m Listado de partidas por fecha.\n  \033[31m(x)\033[0m Atras.\n\n\033[92mRespuesta:\033[0m ");

    getline(cin, reply);
    
    switch(reply[0]) {
        case '1': {
            cleanScreen();
            showTitle();
            
            if (actualActiveUsers > 0) {
                printf("\033[92m[ Listado de Usuarios ]\n\n\033[0m");
                for (int i = 0; i < actualActiveUsers; i++) {
                    cout << "\033[94mAlias: \033[93m" << activeUsers[i].alias << endl;
                    cout << "\033[94mNombre: \033[0m" << activeUsers[i].name << " " << activeUsers[i].surname << endl;
                    cout << "\033[94mFecha de nacimiento: \033[0m" << activeUsers[i].birthday.day << "/" << activeUsers[i].birthday.month << "/" << activeUsers[i].birthday.year << endl << endl;
                }
            }
            else {
                printf("\033[31m[No hay usuarios activos]\033[0m\n");
            }

            waitUntilImput();
            return true;
        } /* Listado de usuarios */
            break;
        case '2': {
            cleanScreen();
            showTitle();

            if (actualActiveUsers == 0) {
                printf("\033[31m[No hay usuarios activos]\033[0m\n");
                waitUntilImput();
                return true;
            }
            else {
                for (int p = 0; p < actualActiveUsers; p++) {
                    if (activeUsers[p].matchesPlayed > 0) {
                        noMatches = false;
                        cout << "\n\033[94mUsuario: \033[93m" << activeUsers[p].alias << "\033[0m" << endl << endl;
                        for (int m = 0; m < activeUsers[p].matchesPlayed; m++) {
                            cout << "\033[94m○  Resultado: \033[0m" << activeUsers[p].history[m].result << endl;
                            cout << "\033[94m○  Puntaje: \033[0m" << activeUsers[p].history[m].scoreMatch << endl;
                            cout << "\033[94m○  Fecha: \033[0m" << activeUsers[p].history[m].date.day << "/" << activeUsers[p].history[m].date.month << "/" << activeUsers[p].history[m].date.year << " " << activeUsers[p].history[m].time.hours << ":" << activeUsers[p].history[m].time.minutes << endl << endl;   
                        }
                            
                            cout << "--------------------" << endl;
                    }
                }
            }

            
            if (noMatches && actualActiveUsers > 0) {
                printf("\033[31m[No hay partidas para mostrar]\033[0m\n");
            }
            
            waitUntilImput();
            return true;
        } /* Listado de todas las partidas jugadas */
            break;
        case '3': {
            cleanScreen();
            showTitle();

            if (actualActiveUsers == 0) {
                printf("\033[31m[No hay usuarios activos]\033[0m\n");
                waitUntilImput();
                return true;
            }
            else {

                printf("\n\033[92m[ Lista de Usuarios ]\n\n\033[0m");
                for (int p = 0; p < actualActiveUsers; p++) {
                    cout << "- \033[93m" << activeUsers[p].alias << "\033[0m" << endl;
                }
                printf("\n\033[92mIngrese el alias a consultar.\033[0m\n\n- ");
                
                getline(cin, reply);

                for (p = 0; p < actualActiveUsers; p++) {
                    if (reply == activeUsers[p].alias) {
                        break;
                    }
                }
                if (reply != activeUsers[p].alias) {
                    response = "-- No se encontró el alias --";
                    responseStatus = true;
                    return false;
                }

                if (activeUsers[p].matchesPlayed == 0) {
                    cleanScreen();
                    showTitle();
                    printf("\033[31m[No hay partidas registradas]\033[0m\n");
                    waitUntilImput();
                    return true;
                }
                
                cleanScreen();
                showTitle();
                cout << "\033[94mUsuario: \033[93m" << activeUsers[p].alias << "\033[0m" << endl << endl;

                for (int m = 0; m < activeUsers[p].matchesPlayed; m++) {
                    cout << "\033[94m○  Resultado: \033[0m" << activeUsers[p].history[m].result << endl;
                    cout << "\033[94m○  Puntaje: \033[0m" << activeUsers[p].history[m].scoreMatch << endl;
                    cout << "\033[94m○  Fecha: \033[0m" << activeUsers[p].history[m].date.day << "/" << activeUsers[p].history[m].date.month << "/" << activeUsers[p].history[m].date.year << " " << activeUsers[p].history[m].time.hours << ":" << activeUsers[p].history[m].time.minutes << endl << endl;
                }

                printf("\n\n\033[92m[Presione enter para continuar]\033[0m");
                getchar();
                return true;
            }
        } /* Listado de partidas por usuario */
            break;
        case '4': {
            cleanScreen();
            showTitle();
            
            if (actualActiveUsers == 0) {
                printf("\033[31m[No hay usuarios activos]\033[0\n");
                waitUntilImput();
                return true;
            }
            else {
                
                do {
                    printf("\n\033[92mIngrese el dia a buscar \033[0m(del 1 al 31)\n\n- ");
                    getline(cin, reply);
                    num = stringDigit(reply);
                } while (num < 1 || num > 31);
                replyDate_day = num;

                cleanScreen();
                showTitle();
                
                do {
                    printf("\n\033[92mIngrese el mes a buscar \033[0m(del 1 al 12)\n\n- ");
                    getline(cin, reply);
                    num = stringDigit(reply);
                } while (num < 1 || num > 12);
                replyDate_month = num;

                cleanScreen();
                showTitle();
                
                do {
                    printf("\n\033[92mIngrese el año a buscar \033[0m(del 1900 al %i)\n\n- ", ACTUAL_YEAR);
                    getline(cin, reply);
                    num = stringDigit(reply);
                } while (num < 1900 || num > ACTUAL_YEAR);
                replyDate_year = num;

                cleanScreen();
                showTitle();
                printf("\n\033[92m[ Partidas de la fecha: %i/%i/%i ]\033[0m\n\n", replyDate_day, replyDate_month, replyDate_year);

                for (int p = 0; p < actualActiveUsers; p++) {
                    for (int m = 0; m < activeUsers[p].matchesPlayed; m++) {
                        if (activeUsers[p].history[m].date.day == replyDate_day && activeUsers[p].history[m].date.month == replyDate_month && activeUsers[p].history[m].date.year == replyDate_year) {
                            noMatches = false;
                            cout << "\033[94mAlias: \033[93m" << activeUsers[p].alias << endl;
                            cout << "\033[94mPuntaje: \033[0m" << activeUsers[p].history[m].scoreMatch << endl;
                            cout << "\033[94mResultado: \033[0m" << activeUsers[p].history[m].result << endl;
                            cout << "\033[94mNumero de partida: \033[0m" << m+1 << endl;
                            cout << "\033[94mFecha: \033[0m" << activeUsers[p].history[m].date.day << "/" << activeUsers[p].history[m].date.month << "/" << activeUsers[p].history[m].date.year << " " << activeUsers[p].history[m].time.hours << ":" << activeUsers[p].history[m].time.minutes << endl << endl;
                        }   
                    }
                }

                if (noMatches)
                    printf("\033[31m[No hay partidas en esa fecha]\033[0m\n");
                
                waitUntilImput();
                return true;
            }
        } /* Listado de partidas por fecha */
            break;
        case 'x': {
            response = "\nVolviendo al menu...";
            responseStatus = true;
            return false;
        default:
            return true;
        }
    }
}





void showTitle() {
    printf("\n ######  ######  ##   #  ######\n ##\033[38;5;220m##\033[0m##  \033[38;5;39m######  ##   #  ######\033[0m\n      #  ##   #  ##   #  ##   #\n \033[38;5;39m######  ##   #  ######  ######\033[0m\n ##      ##   #       #  ##   #\n \033[38;5;39m######  ######       #  ######\033[0m\n ######  ######       #  ######\n\n");
}


void resetBools() {
    score = lastScore = 0;
    firstTurn = changeDetected = true;
    victory = defeat = isRegret = false;
    lastMovement = ' ';
}





int game() {
    char movement;
    
    while (true) {
        if (victory)
            return 1;
        else if (defeat)
            return 0;
        
        if (changeDetected && !isRegret) {
            genRandom();
        }
        
        cleanScreen();        
        showBoard();
        cin >> movement;

        if (movement == 'q')
            return -1;
        
        lastMovement = movement;
        
        move(movement);
    }
}


void genRandom() {
    int randRow, randCol,x;
    do {
        randRow=rand()%4;
        randCol=rand()%4;
    } while(board[randRow][randCol]!=0);
    x=rand()%4;
    if(x==0)
        x=4;
    else
        x=2;
    board[randRow][randCol]=x;
}


void move(char movement) {
    isRegret = false;
    
    switch(movement){
        case 'w':
            if (changeDetected) {
                copyBoard(board, boardLast);
                lastScore = score;
                firstTurn = false;
            }
            changeDetected = false;
            
            
            for (int y = 0; y < 4; y++) {
                
                for (int x = 0; x < 4; x++) {
                    for(int i = x+1; i < 4; i++) {
                        if (board[i][y] != board[x][y] && board[i][y] != 0)
                            break;
                        if (board[i][y] == board[x][y] && board[i][y] != 0 && board[x][y] != 0) {
                            board[i][y] = 0;
                            board[x][y] *= 2;
                            if (board[x][y] == 2048) {
                                victory = true;
                            }
                            score += board[x][y];
                            changeDetected = true;
                            break;
                        }
                    }
                }
                
                for (int x = 0; x < 4; x++) {
                    if (board[x][y] == 0) {
                        for (int i = x+1; i < 4; i++) {
                            if (board[i][y] != 0) {
                                board[x][y] = board[i][y];
                                board[i][y] = 0;
                                changeDetected = true;
                                break;
                            }
                        }  
                    }  
                }
            }
            
            break;

        case 's':
            if (changeDetected) {
                copyBoard(board, boardLast);
                lastScore = score;
                firstTurn = false;
            }
            changeDetected = false;
            
            for (int y = 0; y < 4; y++) {
                
                for (int x = 3; x >= 0; x--) {
                    for(int i = x-1; i >= 0; i--) {
                        if (board[i][y] != board[x][y] && board [i][y] != 0)
                            break;
                        if (board[i][y] == board[x][y] && board[i][y] != 0 && board[i][y] != 0 && board[x][y] != 0) {
                            board[i][y] = 0;
                            board[x][y] *= 2;
                            if (board[x][y] == 2048) {
                                victory = true;
                            }
                            score += board[x][y];
                            changeDetected = true;
                            break;
                        }
                    }
                }
                
                for (int x = 3; x >= 0; x--) {
                    if (board[x][y] == 0) {
                        for (int i = x-1; i >= 0; i--) {
                            if (board[i][y] != 0) {
                                board[x][y] = board[i][y];
                                board[i][y] = 0;
                                changeDetected = true;
                                break;
                            }
                        }  
                    }  
                }
            }
            break;

        case 'a':
            if (changeDetected) {
                copyBoard(board, boardLast);
                lastScore = score;
                firstTurn = false;
            }
            changeDetected = false;

            
            for (int x = 0; x < 4; x++) {
              
                for (int y = 0; y < 4; y++) {
                    for(int i = y+1; i < 4; i++) {
                        if (board[x][i] != board[x][y] && board[x][i] != 0)
                            break;
                        if (board[x][i] == board[x][y] && board[x][i] != 0 && board[x][i] != 0) {
                            board[x][i] = 0;
                            board[x][y] *= 2;
                            if (board[x][y] == 2048) {
                                victory = true;
                            }
                            score += board[x][y];
                            changeDetected = true;
                            break;
                        }
                    }
                }
                
                for (int y = 0; y < 4; y++) {
                    if (board[x][y] == 0) {
                        for (int i = y+1; i < 4; i++) {
                            if (board[x][i] != 0) {
                                board[x][y] = board[x][i];
                                board[x][i] = 0;
                                changeDetected = true;
                                break;
                            }
                        }  
                    }  
                }
            }
            break;

        case 'd':
            if (changeDetected) {
                copyBoard(board, boardLast);
                lastScore = score;
                firstTurn = false;
            }
            changeDetected = false;

            
            for (int x = 0; x < 4; x++) {
              
                for (int y = 3; y >= 0; y--) {
                    for(int i = y-1; i >= 0; i--) {
                        if (board[x][i] != board[x][y] && board[x][i] != 0)
                            break;
                        if (board[x][i] == board[x][y] && board[x][i] != 0 && board[x][y] != 0) {
                            board[x][i] = 0;
                            board[x][y] *= 2;
                            if (board[x][y] == 2048) {
                                victory = true;
                            }
                            score += board[x][y];
                            changeDetected = true;
                            break;
                        }
                    }
                }
                
                for (int y = 3; y >= 0; y--) {
                    if (board[x][y] == 0) {
                        for (int i = y-1; i >= 0; i--) {
                            if (board[x][i] != 0) {
                                board[x][y] = board[x][i];
                                board[x][i] = 0;
                                changeDetected = true;
                                break;
                            }
                        }  
                    }  
                }
            }
            break;
        case 'r':
            if (firstTurn)
                copyBoard(board, boardLast);
            copyBoard(boardLast, board);
            score = lastScore;
            isRegret = true;
            break;
        default:
            changeDetected = false;
            break;
    }

    if (!changeDetected && !firstTurn) {
        if (isFull()) {
            defeat = true;
        }
    }
    
}





void showBoard() {
    showTitle();
    printf("\n\033[92mPuntaje:\033[0m %i  | \033[92mUlt. movimiento:\033[0m %c\n", score, lastMovement);

    for(int x=0;x<4;x++){
        if (x == 0)
            printf("________________________________\n");
        printf("|      ||      ||      ||      |\n");
        for(int y=0;y<4;y++){
            
            switch (board[x][y]) {
                case 0:
                    printf("|      |");
                    break;
                case 2:
                case 4:
                case 8:
                    printf("|   \033[38;5;215m%i\033[0m  |", board[x][y]);
                    break;
                case 16:
                case 32:
                case 64:
                    printf("|  \033[38;5;190m%i\033[0m  |", board[x][y]);
                    break;
                case 128:
                case 256:
                case 512:
                    printf("| \033[38;5;126m%i\033[0m  |", board[x][y]);
                    break;
                case 1024:
                case 2048:
                    printf("| \033[38;5;196m%i\033[0m |", board[x][y]);
                    break;
            
            }
        }
        printf("\n|      ||      ||      ||      |\n");
        printf("--------------------------------\n");
  }
    
    printf("\n     \033[92m(w)\033[0m       \033[92m(r)\033[0m ult. mov.\n");
    printf(" \033[92m(a) (s) (d)\033[0m   \033[92m(q)\033[0m salir.\n\n");

    printf("\033[92mSu movimiento: \033[0m");
}


void cleanBoard(int theBoard[][4]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            theBoard[x][y] = 0;
        }
    }
}


void copyBoard(int firstBoard[][4], int secondBoard[][4]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            secondBoard[x][y] = firstBoard[x][y];
        }
    }
}





bool isFull() {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if ((board[x+1][y] == 0 || board[x+1][y] == board[x][y]) && x < 3)
                return false;
            else if ((board[x-1][y] == 0 || board[x-1][y] == board[x][y]) && x > 0)
                return false;
            else if ((board[x][y+1] == 0 || board[x][y+1] == board[x][y]) && y < 3)
                return false;
            else if ((board[x][y-1] == 0 || board[x][y-1] == board[x][y]) && y > 0)
                return false;
        }
    }

    return true;
}


int stringDigit(string a) {
    int num = 0;
    int size = a.size();

    for (int i = 0; i < size; i++) {
        if (!isdigit(a[i]))
            return 0;
    }

    for (int i = size - 1; i >= 0; i--) {
        num += (int(a[i]) - '0') * pow(10, size-1-i);
    }

    return num;

}


void waitUntilImput() {
    printf("\n\033[92m[Presione enter para continuar]\033[0m");
    getchar();
    return;
}

                    
void cleanScreen() {
    system("clear");
    return;
}


void cleanInactiveUser(int indice) {
    inactiveUsers[indice] = inactiveUsers[actualInactiveUsers-1];
    inactiveUsers[actualInactiveUsers-1].alias = ".";
    actualInactiveUsers--;
    return;
}

void cleanActiveUser(int indice) {
    activeUsers[indice] = activeUsers[actualActiveUsers-1];
    activeUsers[actualActiveUsers-1].alias = ".";
    actualActiveUsers--;
    return;
}


/*############################# TESTING #############################*/

/* En showTitle();

    for (int i = 0; i < actualActiveUsers; i++)
        cout << activeUsers[i].alias << " ";
    printf("\n");
    for (int i = 0; i < actualInactiveUsers; i++)
        cout << inactiveUsers[i].alias << " ";
    printf("\n");

*/

