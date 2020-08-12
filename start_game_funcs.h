#ifndef HEADER_H
#define HEADER_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	typedef struct question{//to c file
		int id;
		char question[300];
		char answers[4][300];
		int right_answer;//uc
		char adding_date[11];
		char author[32];
		int complexity;//enum
	}singleQuestion;

	typedef struct questions{
		singleQuestion info;
		struct questions *next;
	}sQuestions;

	void fill_questions(sQuestions **head);
 	void print_questions(sQuestions *p);
 	void free_mem(sQuestions **head);
 	void delete_question(sQuestions **head);
 	void adding_question(sQuestions **head);
 	void game(sQuestions **all);

 	//////////////////////////////////////////
 	//
 	// Попълва се свързания списък с данни от 
 	//двуичен файл. Не се изисква връщана стой-
 	//ност поради използването на двоен указател.
 	//
 	// Функцията получава указателн към първия
 	//елемент на списъка.
 	//////////////////////////////////////////

 	void fill_questions(sQuestions **head){
 		sQuestions *temp_quiz;
 		FILE *fp=fopen("questions.bin", "rb");
 		if (fp==NULL)
 		{
 			fprintf(stderr, "Problem opening question file!\n");
 			system("pause");
 			fclose(fp);
 			exit(1);
 		}
 		while(1){
 			
 			if(!(temp_quiz=(sQuestions*)malloc(sizeof(sQuestions)))){
 				fprintf(stderr, "Problem allocating memory\ntry restaring your PC");
 				system("pause");
 				exit(13);
 			}
 			if(1!=fread(&temp_quiz->info, sizeof(singleQuestion), 1, fp)){
 				break;
 			}
 
 			temp_quiz->next=NULL;
 			
 			if (*head==NULL)
 			{
 				*head=temp_quiz;
 			}
 			else{
 				while(*head!=NULL){
					head=&(*head)->next;
				}
 				*head=temp_quiz;
 			}	
 		}	
 	}

 	//////////////////////////////////////////
 	//
 	// Изкарваме на екрана данните записани в 
 	//структурата.
 	//
 	// Функцията получава указателн към първия
 	//елемент на списъка.
 	//////////////////////////////////////////
 	void print_questions(sQuestions *p){
 		while(p!=NULL){
 			printf("Question %d: %s\n", p->info.id, p->info.question);
 			printf("Answers %s\n\t%s\n\t%s\n\t%s\n", p->info.answers[0], p->info.answers[1], p->info.answers[2], p->info.answers[3]);
 			printf("Right answer number %d\n", p->info.right_answer);
 			printf("Adding date %s\n", p->info.adding_date);
 			printf("Author %s\n", p->info.author);
 			printf("Complexity %d\n", p->info.complexity);
 			p=p->next;
 		}
 	}

 	//////////////////////////////////////////
 	//
 	// Освобождаваме запазанета памет, преди 
 	//приключването на програмата.
 	//
 	// Функцията получава указателн към първия
 	//елемент на списъка.
 	//////////////////////////////////////////
 	void free_mem(sQuestions **head){
 		sQuestions *p;
 		while(*head!=NULL){
 			p=*head;
 			free(head);
 			head=&p->next;
 		}
 	}

 	//////////////////////////////////////////
 	//
 	// Изтриваме избран елемент по подадено ID
 	//и освобождаваме заетата памет.
 	// 
 	// Функцията получава указателн към първия
 	//елемент на списъка.
 	//////////////////////////////////////////
 	void delete_question(sQuestions **head){
 		printf("Enter ID of the question: ");
 		int tempID;
 		if(1!=scanf("%d", &tempID)){
			perror(NULL);
			free_mem(head);
			system("pause");
			exit(4);
		}
		sQuestions* p=*head;
		sQuestions* temp=NULL;		
		while(p!=NULL){//merge 2 whiles
			if (p->info.id==tempID)
			{
				temp=p;
				break;
			}
			p=p->next;
		}
		if (temp==NULL)
		{
			printf("No match\n");
			return;
		}
		p=*head;
		if (p->info.id==tempID)
		{
			*head=p->next;
			free(p);
			return;
		}
		while(p!=NULL){
			if (p->next==temp)
			{
				*head=temp->next;
				free(temp);
				return;
			}
			p=p->next;
		}
 	}

 	//////////////////////////////////////////
 	//
 	// Добавя се елемент към края на свързаният
 	//списък и се създава запазане памет за него.
 	// 
 	// Функцията получава указателн към първия
 	//елемент на списъка.
 	//////////////////////////////////////////
 	void adding_question(sQuestions **head){
 		sQuestions *p=*head;
 		while(p->next!=NULL){
 			p=p->next;
 			
 		}
 		sQuestions* new_quest;
 		if(!(new_quest=(sQuestions*)malloc(sizeof(sQuestions)))){
 			fprintf(stderr, "Problem allocating memory\ntry restaring your PC");
 			system("pause");
 			exit(13);
 		}
 		new_quest->info.id=(p->info.id)+1;
 		printf("Enter question: ");
		if(1!=scanf(" %[^\n]%*c", new_quest->info.question)){
			fprintf(stderr, "Error enetering data!\n");
			system("pause");
			exit(5);
		}
		printf("Eneter answers to be chosen from. \n");
		for (int i = 0; i < 4; ++i)
		{
			printf("Enter answer nuber %d: ", i+1);
			if(1!=scanf("%[^\n]%*c", new_quest->info.answers[i])){
				fprintf(stderr, "Error enetering data!\n");
				system("pause");
				exit(6);
			}
		}
		printf("Eneter correct answer (by number): ");
		if(1!=scanf("%d", &new_quest->info.right_answer)){
			fprintf(stderr, "Error enetering data!\n");
			system("pause");
			exit(7);
		}
		printf("Enter date:");
		if(1!=scanf(" %[^\n]%*c", &new_quest->info.adding_date)){
			fprintf(stderr, "Error enetering data!\n");
			system("pause");
			exit(8);
		}
		printf("Enter author: ");
		if(1!=scanf("%[^\n]%*c", &new_quest->info.author)){
			fprintf(stderr, "Error enetering data!\n");
			exit(9);
		}
		printf("Enter complexity (0 to 2): ");
		do{
			if(1!=scanf("%d", &new_quest->info.complexity)){
				fprintf(stderr, "Error enetering data!\n");
				system("pause");
				exit(10);
			}
			if(1>new_quest->info.complexity || new_quest->info.complexity>3){
				printf("Enter a number from 1 to 3 \n");
			}
		}while(1>new_quest->info.complexity || new_quest->info.complexity>3);
		new_quest->next=NULL;
		p->next=new_quest;
 	}

 	//////////////////////////////////////////
 	//
 	// След избиране на 15 поредни правилни
 	//отговора потребителя приключва успешно играта
 	// и програмата го връща към менято за избор.
 	//
 	// Функцията получава указателн към първия
 	//елемент на списъка.
 	//////////////////////////////////////////

 	void game(sQuestions **all){
 		sQuestions *quiz;
 		int question_answerd[15];//descr
 		int count_past_questions=0;
 		for (int i = 0; i < 15; ++i)
 		{
 			quiz=*all;
 			printf("Question number %d\n", i+1);
 			if (i<6)
 			{
 				int cnt=0;
 				while(quiz!=NULL){
 					cnt++;
 					if (cnt>15)
 					{
 						question_answerd[0]=0;
 					}
 					if (quiz->info.complexity==0)
 					{
 						cnt=0;
 						for (int j = 0; j < 15; ++j)
 						{
 							if (quiz->info.id==question_answerd[j])
 							{
 								cnt++;
 							}
 						}
 						if (!cnt)
 						{
 							question_answerd[count_past_questions]=quiz->info.id;
 							count_past_questions++;
 							printf("%s\n", quiz->info.question);
 							printf("1: %s\t2: %s\n3: %s\t4: %s\n", quiz->info.answers[0], quiz->info.answers[1], quiz->info.answers[2], quiz->info.answers[3]);
 							printf("Complexity %d Right answer %d\n", quiz->info.complexity, quiz->info.right_answer);
 							int choice;
							do{
								fflush(stdin);
								if(1!=scanf("%d", &choice)){
									
								}
								if(1>choice || choice>4){
								printf("Enter a number from 1 to 4 \n");
								}
							}while(1>choice || choice>4);
							if (choice==quiz->info.right_answer)
							{
								break;
							}
							else{
								printf("End of your game!\n");
								free_mem(all);
								system("pause");
								exit(12);
							}
 						}
 					}
 					quiz=quiz->next;
 				}

 				system("cls");
 			}
 			else if (i>5 && i<11)
 			{
 				int cnt=0;
 				while(quiz!=NULL){
 					cnt++;
 					if (cnt>15)
 					{
 						question_answerd[0]=0;
 					}
 					if (quiz->info.complexity==1)
 					{
 						int cnt=0;
 						for (int j = 0; j < 15; ++j)
 						{
 							if (quiz->info.id==question_answerd[j])
 							{
 								cnt++;
 							}
 						}
 						if (!cnt)
 						{
 							question_answerd[count_past_questions]=quiz->info.id;
 							count_past_questions++;
 							question_answerd[0]=quiz->info.id;
 							printf("%s\n", quiz->info.question);
 							printf("1: %s\t2: %s\n3: %s\t4: %s\n", quiz->info.answers[0], quiz->info.answers[1], quiz->info.answers[2], quiz->info.answers[3]);
 							printf("Complexity %d Right answer %d\n", quiz->info.complexity, quiz->info.right_answer);
 							int choice;
							do{
								if(1!=scanf("%d", &choice)){
									fprintf(stderr, "Problem entering data\n");
									system("pause");
									exit(11);
								}
								if(1>choice || choice>4){
								printf("Enter a number from 1 to 4 \n");
								}
							}while(1>choice || choice>4);
							if (choice==quiz->info.right_answer)
							{
								break;
							}
							else{
								printf("End of your game!\n");
								free_mem(all);
								system("pause");
								exit(12);
							}
 						}
 					}
 					quiz=quiz->next;
 				}
 				
 				system("cls");
 			}
 			else
 			{
 				while(1){
 					if (quiz==NULL)
 					{
 						quiz=*all;
 						while(1){
 							if (quiz->info.complexity==2)
 							{
 								for (int i = 0; i < 15; ++i)
 								{
 									if (question_answerd[i]==quiz->info.id)
 									{
 										question_answerd[i]=0;
 									}
 								}
 								break;
 							}
 							quiz=quiz->next;
 						}
 					}
 					if (quiz->info.complexity==2)
 					{
 						int cnt=0;
 						for (int j = 0; j < 15; ++j)
 						{
 							if (quiz->info.id==question_answerd[j])
 							{
 								cnt++;
 							}
 						}
 						if (quiz->next==NULL && cnt>0)
 						{
 							for (int i = 0; i < 15; ++i)
 							{
 								if (quiz->info.id==question_answerd[i])
 								{
 									for (sQuestions* p = *all; p!=NULL; p=p->next)
 									{
 										if (p->info.complexity==2)
 										{
 											quiz=p;
 										}
 									}
 									cnt=0;
 								}
 							}
 						}
 						if (!cnt)
 						{
 							question_answerd[count_past_questions]=quiz->info.id;
 							count_past_questions++;
 							printf("%s\n", quiz->info.question);
 							printf("1: %s\t2: %s\n3: %s\t4: %s\n", quiz->info.answers[0], quiz->info.answers[1], quiz->info.answers[2], quiz->info.answers[3]);
 							printf("Complexity %d Right answer %d\n", quiz->info.complexity, quiz->info.right_answer);
 							int choice;
							do{
								if(1!=scanf("%d", &choice)){
									fprintf(stderr, "Problem entering data\n");
									system("pause");
									exit(11);
								}
								if(1>choice || choice>4){
								printf("Enter a number from 1 to 4 \n");
								}
							}while(1>choice || choice>4);
							if (choice==quiz->info.right_answer)
							{
								break;
							}
							else{
								printf("End of your game!\n");
								free_mem(all);
								system("pause");
							}
 						}
 					}
 					quiz=quiz->next;
 				}
 				system("cls");
 			}
 		}
 		printf("Congratulations you have won the game\n");
 		free_mem(all);
 	}
#endif