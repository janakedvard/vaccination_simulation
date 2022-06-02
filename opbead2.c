 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void dataToFile();
void deleteFromFile();
void modify();
void newList();
int mornsess();
void handler(int signum){
	printf("HARCRA_FEL\n");
}
struct person{
	int id;
	char fname[20];
	char lname[20];
	int year;
	int phonenum;
	char yon[5];
	char vaccinated[10];

};


int main (int argc, char** argv){

	int v=1;
	while(v!=0){
	printf("\n0.Exit\n1.Entering data\n2.Delete from file\n3.Modify data\n4.New list\n5. Morning session \n ");
	scanf("%d", &v);
	switch(v){
		case 1:
			dataToFile();
			break;
		case 2:
			deleteFromFile();
			break;
        case 3:
            modify();
            break;
        case 4:
            newList();
            break;
	case 5:
	    mornsess();
        default:
            printf("Out of range!\n");
            break;
	}



	}

}
void dataToFile(){
	FILE *outfile;

	outfile = fopen("datas.txt", "a");
    if (outfile == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

	struct person p1;
	printf("ID: ");
	scanf("%d", &(p1.id));
	printf("First name: ");
	scanf("%s", &(p1.fname));
	printf("Last name: ");
	scanf("%s",&(p1.lname));
	printf("Year if birth: ");
	scanf("%d", &(p1.year));
	printf("Phone number: ");
	scanf("%d", &(p1.phonenum));
	printf("Willing to pay (yes or no): ");
	scanf("%s", &(p1.yon));
	printf("Is vaccinated? ");
	scanf("%s", &(p1.vaccinated));


	fprintf(outfile, "%d %s %s %d %d %s %s\n",p1.id, p1.fname, p1.lname, p1.year, p1.phonenum, p1.yon, p1.vaccinated);




	fclose(outfile);

}

void deleteFromFile(){

	int idtodelete;
	printf("Enter the id of the data that you want to delete\n");
	scanf("%d", &idtodelete);
	FILE *outfile = fopen("datas.txt", "r+");
    if (outfile == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
	FILE *newoutfile = fopen("temp.txt", "a+");
    if (newoutfile == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

	struct person p2;

	while(fscanf(outfile, "%d %s %s %d %d %s %s", &(p2.id), &(p2.fname), &(p2.lname), &(p2.year), &(p2.phonenum), &(p2.yon),&(p2.vaccinated)) == 7){
        printf("alert\n");

		if(p2.id != idtodelete){

            fprintf(newoutfile, "%d %s %s %d %d %s %s\n",p2.id, p2.fname, p2.lname, p2.year, p2.phonenum, p2.yon,p2.vaccinated);


		}
	}


	fclose(outfile);
	fclose(newoutfile);

    remove("datas.txt");
    rename("temp.txt", "datas.txt");

}

void modify(){

    printf("Enter the id of the data that you want to modify\n");
    int idToModify;
    scanf("%d", &idToModify);
    struct person p3;
    p3.id=idToModify;

    printf("First name: ");
	scanf("%s", &(p3.fname));
	printf("Last name: ");
	scanf("%s",&(p3.lname));
	printf("Year if birth: ");
	scanf("%d", &(p3.year));
	printf("Phone number: ");
	scanf("%d", &(p3.phonenum));
	printf("Willing to pay (yes or no): ");
	scanf("%s", &(p3.yon));
	printf("Is vaccinated? ");
	scanf("%s", &(p3.vaccinated));


    struct person p4;
    FILE *outfile = fopen("datas.txt", "r+");
    if (outfile == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
	FILE *newoutfile = fopen("temp.txt", "a+");
    if (newoutfile == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    while(fscanf(outfile, "%d %s %s %d %d %s %s", &(p4.id), &(p4.fname), &(p4.lname), &(p4.year), &(p4.phonenum), &(p4.yon),&(p4.vaccinated)) == 7){
        printf("alert\n");

		if(p4.id != idToModify){

            fprintf(newoutfile, "%d %s %s %d %d %s %s\n",p4.id, p4.fname, p4.lname, p4.year, p4.phonenum, p4.yon, p4.vaccinated);


		}else{

            fprintf(newoutfile, "%d %s %s %d %d %s %s\n",p3.id, p3.fname, p3.lname, p3.year, p3.phonenum, p3.yon, p3.vaccinated);

            }
	}


	fclose(outfile);
	fclose(newoutfile);

    remove("datas.txt");
    rename("temp.txt", "datas.txt");


}

void newList(){

    FILE *fptr;

    char  c;

    fptr = fopen("datas.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }


    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);


}


int mornsess(){
	signal(SIGUSR1, handler);
	int fd[2];
	if(pipe(fd)==-1){
		printf("An error occured!\n");
		exit(0);}
	int fd_2[2];
	if(pipe(fd_2)==-1){
		printf("An error occured!\n");
		exit(0);}
	struct person p;
	struct person people[10];
	FILE *file;
	file = fopen("datas.txt", "r+");
	if(file == NULL){printf("file cannot be opened\n");
	exit(0);}
	int db = 0;
	int i =0;
	while(fscanf(file, "%d %s %s %d %d %s %s", &(p.id), &(p.fname), &(p.lname),&(p.year), &(p.phonenum), &(p.yon), &(p.vaccinated))==7 && i<10){
		printf("id: %d  name: %s %s , phone: %d, yon: %s, Vaccinated: %s  year: %d \n", p.id, p.fname, p.lname, p.phonenum,p.yon, p.vaccinated, p.year );
		if((strcmp(p.vaccinated,"OLTVA"))){

			people[db].id=p.id;
			strcpy(people[db].fname,p.fname);
			strcpy(people[db].lname,p.lname);
			people[db].year=p.year;
			people[db].phonenum=p.phonenum;
			strcpy(people[db].yon,p.yon);
			strcpy(people[db].vaccinated,p.vaccinated);
			printf("NINCS OLTVA: id: %d  name: %s %s , phone: %d, yon: %s, Vaccinated: %s  year: %d \n", people[db].id, people[db].fname, people[db].lname, people[db].phonenum,people[db].yon, people[db].vaccinated, people[db].year );
			db++;
			i++;
		}
	}
	fclose(file);
	printf("db: %d\n", db);
	if(db<4){printf("Not enough patient!\n");
		exit(0);}


	int pid1 = fork();
	


	if(pid1>0){
		int pid2 = fork();

		if(pid2 > 0){
		
		if(db<9){
		pause();
		if(db>5){db=5;}
		int j;
		for(j=0; j<db; j++){
			printf("ELKÜLDVE ID: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people[j].id, people[j].fname, people[j].lname, people[j].year, people[j].phonenum, people[j].yon, people[j].vaccinated);
			write(fd[1], &people[j], sizeof(struct person));
			}

		sleep(2);
		close(fd[1]);
		struct person p0;
		struct person people3[db];
		int a=0;
		int idk;

			while((idk =read(fd[0], &people3[a], sizeof(struct person)))> 0 ){
			printf("parent receive: ");
				printf("ID: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people3[a].id, people3[a].fname, people3[a].lname, people3[a].year, people3[a].phonenum, people3[a].yon, people3[a].vaccinated);


			a++;


		}
		FILE *newfile;
		newfile = fopen("datas.txt", "r+");
		FILE *tempfile;
		tempfile=fopen("temp.txt","a+");
		int b;
		while(fscanf(newfile, "%d %s %s %d %d %s %s", &(p0.id), &(p0.fname), &(p0.lname),&(p0.year), &(p0.phonenum), &(p0.yon), &(p0.vaccinated))==7){
			int init = 0;
			for(b=0; b<a; b++){
			strcpy(people3[b].vaccinated,"OLTVA");
			if(p0.id == people3[b].id){
				fprintf(tempfile, "%d %s %s %d %d %s %s\n",people3[b].id, people3[b].fname, people3[b].lname, people3[b].year, people3[b].phonenum, people3[b].yon, people3[b].vaccinated );
				init = 1;
			}
			}
			if(init == 0){
				fprintf(tempfile, "%d %s %s %d %d %s %s\n",p0.id, p0.fname, p0.lname, p0.year, p0.phonenum, p0.yon, p0.vaccinated );

			}


		}
		fclose(newfile);
		fclose(tempfile);
		remove("datas.txt");
		rename("temp.txt", "datas.txt");

		close(fd[0]);


		}else{
		pause();

		int j;
		for(j=0; j<5; j++){
			printf("ELKÜLDVE ID 1 GYEREKNEK: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people[j].id, people[j].fname, people[j].lname, people[j].year, people[j].phonenum, people[j].yon, people[j].vaccinated);
			write(fd[1], &people[j], sizeof(struct person));
			}
		int k;
		for(k=5; k<db; k++){
			printf("ELKÜLDVE ID 2 GYEREKNEK: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people[k].id, people[k].fname, people[k].lname, people[k].year, people[k].phonenum, people[k].yon, people[k].vaccinated);
			write(fd_2[1], &people[k], sizeof(struct person));
			}
		sleep(2);
		close(fd[1]);
		close(fd_2[1]);
		struct person p0;
		struct person people4[db];
		int a=0;
		int idk;

			while((idk =read(fd[0], &people4[a], sizeof(struct person)))> 0 ){
			printf("parent receive from 1 gyerek: ");
				printf("ID: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people4[a].id, people4[a].fname, people4[a].lname, people4[a].year, people4[a].phonenum, people4[a].yon, people4[a].vaccinated);


			a++;
			}
			
			while((idk =read(fd_2[0], &people4[a], sizeof(struct person)))> 0 ){
			printf("parent receive from 2 gyerek: ");
				printf("ID: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people4[a].id, people4[a].fname, people4[a].lname, people4[a].year, people4[a].phonenum, people4[a].yon, people4[a].vaccinated);


			a++;
			}

		FILE *newfile;
		newfile = fopen("datas.txt", "r+");
		FILE *tempfile;
		tempfile=fopen("temp.txt","a+");
		int b;
		while(fscanf(newfile, "%d %s %s %d %d %s %s", &(p0.id), &(p0.fname), &(p0.lname),&(p0.year), &(p0.phonenum), &(p0.yon), &(p0.vaccinated))==7){
			int init = 0;
			for(b=0; b<a; b++){
			strcpy(people4[b].vaccinated,"OLTVA");
			if(p0.id == people4[b].id){
				fprintf(tempfile, "%d %s %s %d %d %s %s\n",people4[b].id, people4[b].fname, people4[b].lname, people4[b].year, people4[b].phonenum, people4[b].yon, people4[b].vaccinated );
				init = 1;
			}
			}
			if(init == 0){
				fprintf(tempfile, "%d %s %s %d %d %s %s\n",p0.id, p0.fname, p0.lname, p0.year, p0.phonenum, p0.yon, p0.vaccinated );

			}


		}
		fclose(newfile);
		fclose(tempfile);
		remove("datas.txt");
		rename("temp.txt", "datas.txt");

		close(fd[0]);
		close(fd_2[0]);
		}
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);

		}else{
			if(db<9){
				waitpid(getppid(), NULL, 0);
				exit(0);
			}else{
		struct person people3[5];
		int i;
		for(i=0; i<db-5; i++){
			read(fd_2[0], &people3[i], sizeof(struct person));
			printf("2.GYEREK MEGKAPVA: ID: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people3[i].id, people3[i].fname, people3[i].lname, people3[i].year, people3[i].phonenum, people3[i].yon, people3[i].vaccinated);

		}

		int k;
		for(k=0; k<db-5; k++){
			srand(time(NULL));
			int randnum=rand() % 100+1;
			if(randnum<90){
			int wr = write(fd_2[1], &people3[k], sizeof(struct person) );
			}
			sleep(1);
		}
		close(fd_2[0]);
		close(fd_2[1]);

		exit(0);
			}
		}




	}
	else{


		kill(getppid(), SIGUSR1);
		struct person people2[5];
		int child_db;
		if(db<=5){
			child_db=db;}
			else{
				child_db = 5;
			}
		int i;
		printf("1.gyereknél DB: %d", child_db);
		for(i=0; i<child_db; i++){
			read(fd[0], &people2[i], sizeof(struct person));
			printf("1.GYEREK MEGKAPVA: ID: %d Name: %s %s Year of birth: %d Phonenum: %d Willing to pay: %s Vaccinated: %s\n",people2[i].id, people2[i].fname, people2[i].lname, people2[i].year, people2[i].phonenum, people2[i].yon, people2[i].vaccinated);

		}

		int k;
		for(k=0; k<child_db; k++){
			srand(time(NULL));
			int randnum=rand() % 100+1;
			if(randnum<90){
			int wr = write(fd[1], &people2[k], sizeof(struct person) );
			}
			sleep(1);
		}
		close(fd[0]);
		close(fd[1]);
		sleep(2);
		exit(0);



	}
	return 0;


}
