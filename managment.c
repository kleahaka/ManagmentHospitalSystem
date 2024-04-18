#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct pacient{
    int id;
    char emriPacientit[100];
    char adresaPacientit[100];
    char semundje[50];
    char data[20];
}p;

struct doktor{
    int id;
    char emri[100];
    char adresa[100];
    char specializim[100];
    char data[20];
}d;

FILE *fp;

int main(){
  int ch;

  while(1){
    system("cls");
    printf("--HOSPITAL MANAGMENT SYSTEM--\n");
    printf("1.Pactientet e pranuar\n");
    printf("2.Lista pacineteve\n");
    printf("3.Pactienet e larguar\n");
    printf("4.Shto doktor\n");
    printf("5.Lista e doktoreve\n");
    printf("0.Exit\n\n");
    printf("Zgjidh: ");
    scanf("%d" , &ch);

    switch(ch){
    case 0:
       exit(0);
    case 1:
       pranoPacient();
       break;
    case 2:
       listaPacienteve();
       break;
    case 3:
       pacientetLarguar();
       break;
    case 4:
        shtoDoktor();
        break;
    case 5:
        listaDoktor();
        break;
    default:
        printf("Zgjedhje e pavlefshme....\n\n");
    }
    printf("\n\nShtyp nje buton per te vazhduar...");
    getch();
  }
  return 0;
}

void pranoPacient(){
    char myDate[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate , "%02d/%02d/%d" , tm.tm_mday , tm.tm_mon+1 , tm.tm_year+1900);
    strcpy(p.data , myDate);
    
    fp=fopen("pacient.txt" , "ab");

    printf("Fut id e pacientit: ");
    scanf("%d" , &p.id);

    printf("Fut emrin e pacientit: ");
    fflush(stdin);
    gets(p.emriPacientit);

    printf("Fut adresen e pacientit: ");
    fflush(stdin);
    gets(p.adresaPacientit);

    printf("Fut semundjen e pacientit: ");
    fflush(stdin);
    gets(p.semundje);

    printf("\n Pacienti u shtua me sukses");

    fwrite(&p , sizeof(p) , 1 ,fp);
    fclose(fp);
}

void listaPacienteve(){
    system("cls");
    printf("--Lista Pacienteve--\n\n");
    printf("%-10s %-30s %-30s %-20s %s\n" , "ID" , "EMRI PACIENTIT" , "ADRESA" , "SEMUNDJA" , "DATA");
    printf("---------------------------------------------------------------------------------------------------------------------------------");

    fp=fopen("pacient.txt" , "rb");
    while(fread(&p , sizeof(p), 1, fp) ==1){
        printf("%-10s %-30s %-30s %-20s %s\n" , p.id , p.emriPacientit , p.adresaPacientit , p.semundje , p.data);
    }
    fclose(fp);
}
void pacientetLarguar(){
    int id, f=0;
    system("cls");
    printf("--Pacientet e larguar--\n\n");
    printf("Fut id e pacientit e larguar: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("pacient.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&p, sizeof(p), 1, fp) == 1){

        if(id == p.id){
            f=1;
        }else{
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nPacienti u largua me sukses.");
    }else{
        printf("\n\nNuk gjendet !");
    }

    fclose(fp);
    fclose(ft);

    remove("pacient.txt");
    rename("temp.txt", "pacient.txt");

}

void shtoDoktor(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(d.data, myDate);

    int f=0;

    system("cls");
    printf("--SHTO DOKTOR--\n\n");

    fp = fopen("doctor.txt", "ab");

    printf("Fut id e doktorit: ");
    scanf("%d", &d.id);

    printf("Fut emrin e doktorit: ");
    fflush(stdin);
    gets(d.emri);

    printf("Fut adresen e doktrit: ");
    fflush(stdin);
    gets(d.adresa);

    printf("Doktor i specializuar ne: ");
    fflush(stdin);
    gets(d.specializim);

    printf("Doctor Added Successfully\n\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}



void listaDoktor(){
    system("cls");
    printf("--LISTA E DOKTOREVE\n\n");

    printf("%-10s %-30s %-30s %-30s %s\n", "id", "Emri", "Adresa", "Specalizim","Data");
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("doctor.txt", "rb");
    while(fread(&d, sizeof(d), 1, fp) == 1){
        printf("%-10d %-30s %-30s %-30s %s\n", d.id, d.emri, d.adresa, d.specializim, d.data);
    }

    fclose(fp);
}
