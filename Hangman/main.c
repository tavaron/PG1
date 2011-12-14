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
void init_liste();
char* getWord();

struct word {
	char s[40];
	struct word *next;
};
struct word *kopf, *ende;

void exitHandler() {
	endwin();
}

int main(int argc, char** argv)
{
	initscr();
	curs_set(0);
	noecho();
	atexit((void*)exitHandler);
	
	int y, x;
	getmaxyx(stdscr, y, x);
	if(y<24||x<80) {
		mvprintw(0, 0, "Terminal zu klein!");
		mvprintw(1, 0, "80x24 erforderlich!");
		mvprintw(2, 0, "Beende Programm...");
		return(1);
	}
	
	splashScreen();
	hangwin = newwin(14, 10, 0, x-15);
	while(newGame()!=1);
	return 0;
}

int splashScreen()
{
	int y, x;
	int max_y, max_x;
	
	clear();
	init_liste();
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
	
	wrefresh(win);
	refresh();
	return 0;
}

void init_liste() {
	// reserviere Speicher
	kopf = (struct word*) malloc(sizeof(struct word));
	ende = (struct word*) malloc(sizeof(struct word));
	
	// Wenn Speicher nicht reserviert werden konnte
	if(kopf == NULL || ende == NULL)
	{
		// werfe Fehler und beende mit Errorcode 1
		printw("Speicherplatzmangel...\n");
		getchar();
		exit(1);
	}
	// verkette Anfang mit Ende und baue Schleife am Ende
	kopf->next = ende->next = ende;
}

int read_liste() {
	int woerter = 0;
	struct eintrag *element, *tmp;
	element = (struct word*) malloc(sizeof(struct word));
	FILE* f = fopen("liste.txt", "r");
	do {
		char wort[40];
		int i = 0;
		while( ((wort[i] = fgetc(f)) >= 65 && wort[i] <= 90) || (wort[i] >= 97 && wort[i] <= 122) )
		{ i++; }
		if(wort[i]!=
		wort[i]='\0';
		while(fgetc(f)!=10);
		*element->s = wort;
		tmp = anfang->next;
		anfang->next = element;
		element->next = tmp;
	} while(element->next != element->next->next);
	
	return woerter;
}

char* getWord()
{
	FILE* f = fopen("liste.txt", "r");
	char* wort = malloc(sizeof(char)*40);
	wort = "none";
	int i = 0;
	int j = 0;
	int woerter = 0;
	char c;
	
	if(f == NULL)
	{
		printw("Wörterliste nicht gefunden!");
		getchar();
		exit(1);
	}
	
	while((c=fgetc(f)) != EOF)
	{
		if(c==10)
			woerter++;
	}
	printw("Woerter: %d", woerter);
	f = fopen("liste.txt", "r");
	
	srand(time(NULL));
	i = rand() % woerter + 1;
	
	while(i>0)
	{
		c = fgetc(f);
		if(c==10)
			i--;
	}
	
	while((c=fgetc(f))!=10)
	{
		wort[j] = c;
		j++;
	}
	
	wort[j] = '\0';
	
	return wort;
}

int newGame()
{
	char* wort = getWord();
	char c;
	//int length = strlen(wort);
	wclear(hangwin);
	drawHangman(hangwin, 1, 0, 0);
	mvprintw(1,1,"Wort mit %d Buchstaben:",strlen(wort));
	if((c=getch())== 24)
		exit(0);
	else if(c==18)
		return 0;
	
	return 0;
}
