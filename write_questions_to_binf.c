#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct questions{
	int id;
	char question[300];
	char answers[4][300];
	int right_answer;
	char adding_date[11];
	char author[32];
	int complexity;
}sQuestions;

enum error{success, error_enetering_question, error_enetering_answer, error_enetering_correct_answer, error_enetering_date, error_enetering_author, error_enetering_complexity, error_enetering_data_to_file};

int main(void)
{
	sQuestions temp;
	FILE *fp=fopen("questions.bin", "ab");
	if (fp==NULL)
	{
		perror(NULL);
		exit(1);
	}
	for (int i = 0; i < 15; ++i)
	{
		printf("Eneter information about question number %d\n", i+1);
		temp.id=i+1;
		printf("Enter question: ");
		if(1!=scanf(" %[^\n]%*c", temp.question)){
			fprintf(stderr, "Error enetering data!\n");
			fclose(fp);
			exit(error_enetering_question);
		}
		printf("Eneter answer to be chosen from. \n");
		for (int i = 0; i < 4; ++i)
		{
			printf("Enter answer nuber %d: ", i+1);
			if(1!=scanf("%[^\n]%*c", &temp.answers[i])){
				fprintf(stderr, "Error enetering data!\n");
				fclose(fp);
				system("pause");
				exit(error_enetering_answer);
			}
		}
		printf("Eneter correct answer (by number): ");
		if(1!=scanf("%d", &temp.right_answer)){
			fprintf(stderr, "Error enetering data!\n");
			fclose(fp);
			exit(error_enetering_correct_answer);
		}
		printf("Enter date:");
		if(1!=scanf(" %[^\n]%*c", temp.adding_date)){
			fprintf(stderr, "Error enetering data!\n");
			system("pause");
			fclose(fp);
			exit(error_enetering_date);
		}
		printf("Enter author: ");
		if(1!=scanf("%[^\n]%*c", &temp.author)){
			fprintf(stderr, "Error enetering data!\n");
			fclose(fp);
			exit(error_enetering_author);
		}
		printf("Enter complexity (0 to 2): ");
		if(1!=scanf("%d", &temp.complexity)){
			fprintf(stderr, "Error enetering data!\n");
			fclose(fp);
			exit(error_enetering_complexity);
		}
		if(1!=fwrite(&temp, sizeof(sQuestions), 1, fp)){
			fprintf(stderr, "Error enetering data!\n");
			fclose(fp);
			system("pause");
			exit(error_enetering_data_to_file);
		}
	}
	fclose(fp);
	system("pause");
	return success;
}