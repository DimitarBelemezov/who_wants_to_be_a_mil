#include "start_game_funcs.h"

int main(void)
{
	sQuestions *quiz=NULL;
	fill_questions(&quiz);
	int start_loop=1;
	int choice;
	while(start_loop){
		printf("1-Edit, 2-Play, 3-Exit\n");
		printf("Enter your choice: ");
		do{
			fflush(stdin);
				if(1!=scanf("%d", &choice)){
			
				}
				if(1>choice || choice>3){
					printf("Enter a number from 1 to 3 \n");
				}
			}while(1>choice || choice>3);
		switch(choice){
			case 1:
					printf("1-Print all questions, 2-Deleting question, 3-Add question \n");
					printf("Enter your choice: ");
					int choice2;
					do{
						if(1!=scanf("%d", &choice2)){
							perror(NULL);
							free_mem(&quiz);
							exit(4);
						}
						if(1>choice2 || choice2>3){
						printf("Enter a number from 1 to 3 \n");
						}
					}while(1>choice2 || choice2>3);
					switch(choice2){
						case 1:
								print_questions(quiz);
								system("pause");
								system("cls");
								break;
						case 2:
								delete_question(&quiz);
								system("cls");
								break;
						case 3:
								adding_question(&quiz);
								system("pause");
								system("cls");
								break;
					}
				    break;
			case 2:
					game(&quiz);
					system("pause");
					system("cls");
					break;
			case 3:
					start_loop=0;
					free_mem(&quiz);
					break;
		}
	}
	return 0;
}






