#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct record{
    char time[6];
    char title[50];
    char note[500];
};

void addPage(){

	system("cls");
	
    FILE *page;       //file pointer
    char choice = 'Y';
    struct record e;
    char filename[15];

    printf("\n\n\t\t--------------------------\n");
    printf("\t\t* WELCOME TO THE ADD MENU *");
    printf("\n\t\t----------------------------\n\n");
    printf("\n\n\tENTER DATE OF YOUR RECORD:[yyyy-mm-dd]:");

    fflush(stdin);
    gets(filename);    // date as filename
    
    page = fopen(filename, "ab+");  
	 
    if (page == NULL){
        page=fopen(filename,"wb+");
        if(page==NULL){
            printf("\nSYSTEM ERROR...");
            printf("\nPRESS ANY KEY TO EXIT");
            return;
        }
    }
    while (choice=='Y'|| choice=='y'){
    
    	printf ("\n\tENTER TIME:[hh:mm]: ");
    	fflush(stdin);         // clear the output buffer
        scanf("%s",e.time);

        printf("\n\tENTER TITLE: ");
        fflush(stdin);
        gets(e.title);
            
        printf("\n\tNOTE: ");
        fflush(stdin);
        gets(e.note);
            
        fwrite (&e, sizeof (e), 1, page);     //fwrite(&structure variable , size of structure variable, no of records, file pointer);
        printf("\nYOUR ENTRY IS ADDED...\n");
        printf ("\n\tADD ANOTHER ENTRY...(Y/N)");
        fflush(stdin);
        choice = getchar();
    }
	fflush(stdin);
    fclose(page);
    printf("\n\n\tPRESS ANY KEY TO EXIT....");
    getch();
}

void viewPage(){
	system("cls");
	
    FILE *page;
    struct record e;
    char filename[14], choice;
	int ch;
    
    printf("\n\n\t\t-----------------------------\n");
    printf("\t\t* HERE IS THE VIEWING MENU *");
    printf("\n\t\t-------------------------------\n\n");

    do{
        printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[yyyy-mm-dd]:");
		fflush(stdin);
        gets(filename);
       
	    page = fopen(filename, "rb");

        if (page == NULL){
            puts("\nTHE RECORD DOES NOT EXIST...\n");
            printf("PRESS ANY KEY TO EXIT...");
            getch();
        }
		else{
            printf("\nTHE RECORD FOR %s IS:",filename);

            while (fread (&e, sizeof (e), 1, page) == 1){
                printf("\n");
                printf("\nTIME: %s",e.time);
                printf("\n\nTITLE: %s",e.title);
                printf("\n\nNOTE: %s",e.note);
                printf("\n");
            }
        }
        printf("\nWant to continue : \n");
        scanf("%c", &choice);
    }while(choice=='Y'||choice=='y');

	fclose (page);
    return;
}

void editPage(){
	system("cls");

    FILE *page ;
    struct record e ;
    char choice,filename[14];
    int num;

    printf("\n\n\t\t-----------------------------\n");
    printf("\t\t* WELCOME TO THE EDITING MENU *");
    printf("\n\t\t-------------------------------\n\n");

    do{
        printf("\n\tENTER THE DATE OF RECORD TO BE EDITED:[yyyy-mm-dd]:");
        fflush(stdin);
        gets(filename);

        page = fopen (filename, "rb+");
        if (page == NULL){
            printf("\nRECORD DOES NOT EXISTS:") ;
            printf("\nPRESS ANY KEY TO GO BACK");
            getch();
            return;
        }

        while (fread(&e, sizeof (e), 1, page) == 1){

                printf("\nYOUR OLD RECORD WAS AS:");
                printf("\nTIME: %s",e.time);
                printf("\nTITLE: %s",e.title);
                printf("\nNOTE: %s",e.note);
                
                printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");
                printf("\n1.TIME.");
                printf("\n2.TITLE.");
                printf("\n3.NOTE.");
                printf("\n4.WHOLE RECORD.");
                printf("\n5.GO BACK TO MAIN MENU.");

                do{
                    printf("\n\tENTER YOUR CHOICE:");
                    fflush(stdin);
                    scanf("%d",&num);
                    fflush(stdin);
                    
                    switch(num){
                    case 1:
                        printf("\nENTER THE NEW DATA:");
                        printf("\nNEW TIME:[hh:mm]:");
                        gets(e.time);
                        break;
                        
                    case 2:
                        printf("\nENTER THE NEW DATA:");
                        printf("\nNEW TITLE:");
                        gets(e.title);
                        break;
                    case 3:
                        printf("ENTER THE NEW DATA:");
                        printf("\nNOTE:");
                        gets(e.note);
                        break;

                    case 4:
                        printf("\nENTER THE NEW DATA:");
                        printf("\nNEW TIME:[hh:mm]:");
                        gets(e.time);
                        printf("\nNEW TITLE:");
                        gets(e.title);
                        printf("\nNOTE:");
                        gets(e.note);
                        break;

                    case 5:
                        printf("\nPRESS ANY KEY TO GO BACK...\n");
                        getch();
                        return ;
                        break;

                    default:
                        printf("\nYOU TYPED SOMETHING ELSE...TRY AGAIN\n");
                        break;
                    }
                }while(num<1||num>5);
                
                fseek(page,sizeof(e),SEEK_CUR);   // to move or change the position of the file pointer to a specified offset
                fwrite(&e,sizeof(e),1,page);
                fseek(page,sizeof(e),SEEK_CUR);
                fread(&e,sizeof(e),1,page);
				break;
            }
        
        system("cls");
        printf("\n\t\tEDITING COMPLETED...\n");
        printf("--------------------\n");
        printf("THE NEW RECORD IS:\n");
        printf("--------------------\n");

        printf("\nTIME: %s",e.time);
        printf("\nTITLE: %s",e.title);
        printf("\nNOTE: %s",e.note);

        fclose(page);

	    printf("\nWOULD YOU LIKE TO TRY AGAIN...(Y/N)");
        scanf("%c",&choice);

    }while(choice=='Y'||choice=='y');

    fclose(page);

    printf("\nFILE IS EDITED...\n");
    printf("\tPRESS ENTER TO EXIT EDITING MENU.");
    getch();
}

void deletePage( ){
    system("cls");
    
    FILE *page ;
    struct record file ;
    char filename[15], choice='Y';

    printf("\n\n\t\t-----------------------\n");
    printf("\t\t* WELCOME TO DELETE MENU*");
    printf("\n\t\t-------------------------\n\n");

    while (choice == 'Y'){
    	printf("\n\tENTER THE DATE OF RECORD TO BE DELETED:[yyyy-mm-dd]:");
            fflush(stdin);
            gets(filename);
            page = fopen (filename, "wb" ) ;          
           if ( page == NULL ){
                printf("\nTHE FILE DOES NOT EXISTS");
                printf("\nPRESS ANY KEY TO GO BACK.");
                getch();
                return ;
            }
            fclose(page);
            remove(filename);
            printf("\nDELETED SUCCESFULLY...");
    	printf("\n\tDO YOU LIKE TO DELETE ANOTHER RECORD.(Y/N):");
    	fflush(stdin);
    	scanf("%c",&choice);
	}
	printf("\n\n\tPRESS ANY KEY TO EXIT...");
    getch();
}



int main(){

    int d;
    char pass[8], password[8] = "Run@123";
    password[7]='\0';

    printf("\n******************************************************************************************************\n");
    printf("\t\t\t\t\tPersonal Diary\n");
    printf("\n******************************************************************************************************\n");


    while(1){
    		int p = 0;
            printf("Enter your password:\n");
            while(p<7){
				pass[p]=getch();
				printf("*");
				p++;
			}
            
            if(!strcmp(pass,password)){
                while(1){
                    printf("\n\t\tMain Menu:\n");
                    printf("[1] Add new page\n");
                    printf("[2] View Page\n");
                    printf("[3] Edit page\n");
                    printf("[4] Delete page\n");
                    printf("[5] Exit\n");

                    printf("\nEnter your choice:");
                    scanf("%d",&d);

                    switch (d)
                    {
                    case 1: {
                        addPage();
                    }
                        break;
                    case 2: {
                        viewPage();
                    }
                        break;
                    case 3: {
                        editPage();
                    }
                        break;
                    case 4: {
                        deletePage(); 
                    }
                        break;
                    case 5: {
                        printf("Thank You !!\n");
                        exit(0);                        
                    }
                        break;
                    
                    default:{
                        printf("Wrong choice entered\n");
                        printf("Choose again\n\n");
                    }
                        break;
                    }
                }
        	}
            else{
                printf("Incorrect Password. Try Again\n");
                continue;   
            }
    }
	return 0;
}
