#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <curses.h>

#define LOCAL_ESCAPE_KEY 27
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51

char* set_time(struct tm* lt);
int month(int nm);
int day_new_month(struct tm* lt);
void print_month(int nm, int dnm, int day);
void evreday();
void printdir();
int readf();

int main()
{
	struct tm* lt;
        char* tmp;	
	char tp;
	const time_t timer = time(NULL);

	lt=localtime(&timer); 
	tmp=set_time(lt);
	printf("----------------------\n");
	printf(" %s\n",tmp);
	printf("----------------------\n");
	
	int nm=month(lt->tm_mon+1);
	
	int dnm=day_new_month(lt);

	print_month(nm,dnm,lt->tm_mday);
	
	
	printf("----------------------\n");
	printf("1)Создать заметку.\n");
	printf("2)Вывести заметки.\n");
	printf("3)Выйти\n");
	printf("----------------------\n");
	switch(tp=getchar()){
		case KEY_1:
			evreday();
			break;
		case KEY_2:
			readf();
			break;
		case KEY_3:
			exit(-1);
			break;
	}
	return 0;
}

void evreday(){
	
	
	
	FILE* ptrfile_txt;
	char* txtbuff = (char*)malloc(300*sizeof(char));
	char data[24];    
	char ch;
	printf("Введите число:месяц:год\n");
	scanf("%s",data);
	strcat(data,".txt");
	
	
	ptrfile_txt=fopen(data,"w+");
	
	fflush(stdin);
//	initscr();	
//	keypad(stdscr,TRUE);
	printf("Введите текст\n (Нажмите ESC для выхода!)\n");
//0x1B
	while((ch=getchar())!=LOCAL_ESCAPE_KEY){
		   fputc(ch,ptrfile_txt);
	}
	fprintf(ptrfile_txt,"%s\n",txtbuff);
	fclose(ptrfile_txt);
//	endwin();	
	main();

}

 
char* set_time(struct tm* lt){
	
	char buff[40];
	char* tmp=(char*)malloc(sizeof(buff));

	strftime(buff,40,"%d.%m.%Y %H:%M:%S", lt);
	strcpy(tmp,buff);
	return (tmp);
}

int month(int nm){
	return 28+(nm+(nm/8))%2+2%nm+2*(1/nm);
}

int day_new_month(struct tm* lt){
	
	int leapy, years, days;
	
	years=lt->tm_year-1970;
	leapy=(years-1)/4;
	days=years*365+leapy;
	
	return days%7+1;

}

void printdir(){
	
	system("ls *.txt");
	printf("----------------------\n");

}

int readf(){

	printdir();
	
	char name[26];
	char bufftext[300];

	printf("----------------------\n");
	printf("Введите название файла!\n");
	printf("----------------------\n");
	scanf("%s",name);
	
	FILE* ptrfile=fopen(name,"r+");
	if(ptrfile==NULL){
		perror("Ошибка открытия файла!");
		return -1;
	}else{
		while(fgets(bufftext,300,ptrfile)!=NULL){
			printf("%s",bufftext);
		}
	}

	main();
	return 0;
}

void print_month(int nm, int dnm, int day)
{
	

	dnm=~dnm+1;
	
	for(int i=0; i<dnm; i++){
		printf("   ");
	}
	for(int i=1;i<=nm; i++){
		
		if(i==day)
			printf("\x1b[30m\x1b[47m%3d\x1b[0m",i);
		else
			printf("%3d",i);
		
		if((dnm+i)%7==0){ printf("\n"); }
		
	}
	printf("\n");

}
