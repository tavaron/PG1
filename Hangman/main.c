//      ------------------------------------------------------------------------
//      
//      Datei: main.c
//      
//      Name:		Marius Christ
//      Matr.-Nr.:	954402
//      Datum:		24.11.2011 v0.1
//      geaendert:	24.11.2011
//      
//      Beschreibung: !!!
//      
//      Eingabe: !!!
//      
//      Ausgabe: !!!
//      
//      ------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <time.h>


WINDOW* hangwin;

int drawHangman(WINDOW* win, int left, int yshift, int xshift);
int splashScreen();
int newGame();
char* getWord();
int read_liste();
void checkLetter();
int toupper();
int isalpha();

int woerter = 0;
char words[40][20];

int main(int argc, char** argv)
{
	char c;
	initscr();
	curs_set(0);
	noecho();
	atexit((void*)endwin);
	
	int y, x;
	getmaxyx(stdscr, y, x);
	if(y<24||x<80) {
		mvprintw(0, 0, "Terminal zu klein!");
		mvprintw(1, 0, "80x24 erforderlich!");
		mvprintw(2, 0, "Beende Programm...");
		return(1);
	}
	
	c = splashScreen();
	hangwin = newwin(14, 10, 0, x-15);
	do
	{
		c = toupper(c);
		if(c == 'N')
			while(newGame() == 1);
		else if(c == 'O')
			;
		else if(c == 'E')
			break;
		
		getmaxyx(stdscr, y, x);
		int left = (x/2) - 10;
		int ceiling = (y/2) - 6;
		wclear(stdscr);
		
		mvprintw(ceiling   , left, "++++++++++++++++++++");
		mvprintw(ceiling+1 , left, "+                  +");
		mvprintw(ceiling+2 , left, "+ N - Neues Spiel  +");
		mvprintw(ceiling+3 , left, "+                  +");
		mvprintw(ceiling+4 , left, "+ O - Optionen     +");
		mvprintw(ceiling+5 , left, "+                  +");
		mvprintw(ceiling+6 , left, "+ E - Ende         +");
		mvprintw(ceiling+7 , left, "+                  +");
		mvprintw(ceiling+8 , left, "+ Wörter: %2d      +", woerter);
		mvprintw(ceiling+9 , left, "+                  +");
		mvprintw(ceiling+10, left, "++++++++++++++++++++");
		
		refresh();
	}while( (c=getch()) != 24);
	
	return 0;
}

int splashScreen()
{
	int y, x;
	int max_y, max_x;
	
	clear();
	read_liste();
	getmaxyx(stdscr, max_y, max_x);
	y=max_y/2-5;
	x=max_x/2-24;
	
	mvaddstr(y,x+11,"@");
	mvaddstr(y+1,x+11,"@");
	mvaddstr(y+2,x+11,"@");
	mvaddstr(y+3,x,"@@@\\ /@@@ @@@\\ /@@@\\  @@@\\ /@@@\\");
	mvaddstr(y+4,x,"@  @ @    @  @ @   @  @  @ @   @");
	mvaddstr(y+5,x,"@  @ @    @  @ @   @  @  @ @   @");
	mvaddstr(y+6,x,"@  @ \\@@@ @  @ \\@@@/@ @  @ \\@@@@");
	mvaddstr(y+7,x+31,"@");
	mvaddstr(y+8,x+28,"@@@@");
	
	mvaddstr(y+9, x+10, "Press ENTER...");
	
	drawHangman(stdscr, 1, 0, 15);
	refresh();
	while(getch()!=10);
	clear();
	return 0;
}

int drawHangman(WINDOW* win, int left, int yshift, int xshift)
{
	int y, x;
	int max_y, max_x;
	
	wclear(hangwin);
	getmaxyx(win,max_y, max_x);
	if(max_y<14||max_x<10) {
		mvwprintw(win, 0, 0, "Fenster zu klein!");
		return 1;
	}
	
	y=max_y/2-5+yshift;
	x=max_x/2-4+xshift;
	if(left<=4){
		mvwaddstr(win, y+9, x, "/======\\");
	}
	if(left<=3){
		mvwaddstr(win, y+0, x+2, "@");
		mvwaddstr(win, y+1, x+2, "@");
		mvwaddstr(win, y+2, x+2, "@");
		mvwaddstr(win, y+3, x+2, "@");
		mvwaddstr(win, y+4, x+2, "@");
		mvwaddstr(win, y+5, x+2, "@");
		mvwaddstr(win, y+6, x+2, "@");
		mvwaddstr(win, y+7, x+2, "@");
		mvwaddstr(win, y+8, x+1, "/@\\");
	}
	if(left<=2){
		mvwaddstr(win, y+0, x+3, "=====");
		mvwaddstr(win, y+1, x+3, "/");
	}
	if(left<=1){
		mvwaddstr(win, y+1, x+5, "\\_/");
		mvwaddstr(win, y+2, x+6, "|");
		mvwaddstr(win, y+3, x+6, "|");
		mvwaddstr(win, y+4, x+6, "$");
	}
	if(left<=0) {
		mvwaddstr(win, y+4, x+7, "o");
		mvwaddstr(win, y+5, x+5, "-/-");
		mvwaddstr(win, y+6, x+5, "/\\");
	}
	refresh();
	return 0;
}

int read_liste() {
	woerter = 0;
	FILE* f = fopen("liste.txt", "r");
	do {
		
		int i = 0;
		while( ((words[woerter][i] = toupper(fgetc(f)))!= 10 && words[woerter][i] != EOF && 	((words[woerter][i] >= 65 && words[woerter][i] <= 90) || (words[woerter][i] >= 97 && words[woerter][i] <= 122)) ))
		{ i++; }
		if(words[woerter][i] == EOF)
			break;
		else if(words[woerter][i]!=10)
			while(fgetc(f)!=10);
		words[woerter][i]='\0';
		//printw("%s\n", words[woerter]);
		woerter++;
	} while(woerter<40);
	
	printw("Woerter: %d\n", woerter);
	return woerter;
}

char* getWord()
{
	srand(time(NULL));
	
	int r;
	if(woerter==0)
	return "none";
	r = rand() % woerter;
	return (char*)words[r];
}

int newGame()
{
	static char *wort, *tmpwort;
	tmpwort = wort;
	if(woerter<=1)
		while(tmpwort == wort)
			wort = getWord();
	char c;
	int i = 0;
	
	drawHangman(hangwin, 1, 0, 0);
	
	mvprintw(1,1,"Wort mit %d Buchstaben: ",strlen(wort));
	for(i=0;i<strlen(wort);i++)
		printw("-");
	refresh();
	while((c=getch())!= 18&&c!=24)
	{
		mvprintw(1,1,"Wort mit %d Buchstaben: ",strlen(wort));
		if(isalpha((int)c))
			checkLetter();
		else
		{
			mvprintw(3,1, "Es werden nur Buchstaben akzeptiert");
			mvprintw(4,1, "Neustart mit STRG+R");
			mvprintw(5,1, "Beenden mit STRG+X");
		}
			
	}
	clear();
	return 0;
}

void checkLetter()
{}
