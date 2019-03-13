#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moto.h"

FILE *fi, *fo;
int Nr_Moto = 0;
bool Fisier; //true daca e fisier si false daca e consola
Moto *Elem;

void Nucleu()
{ //aici se afla nucleul intregului program! de aici puteam apela orice functie (NU DIN MAIN!)
  // pentru a evita multe erori care apar

    Info_user();

    int nr = Nr_Moto; //numarul de motociclete

    Afisare_cerinta_9(nr, Elem);

    qsort(Elem,nr,sizeof(struct caract_moto),cmpsort);

    //Afisare_date(Elem);

    Cerinta_10_a(nr, Elem);
    Cerinta_10_c(nr, Elem);

    //Afisare_date(Elem);

    Sterg_vocale(nr, Elem);

    Afisare_date(Elem);
}

void Info_user(){
    int Select1, Select2;

    printf("Alegeti modul de citire/scriere:\n");
    printf("1. Fisiere\n2. Consola\n");
    while (scanf("%d", &Select1) && Select1 != 1 && Select1 != 2);
    printf("Ati ales varianta %d!\n", Select1);

    printf("\n\nAlegeti modul de memorare a datelor:\n");
    printf("1. Vector de N motociclete\n");
    printf("2. Vector cu un numar necunoscut de motociclete\n");
    printf("3. Alocare dinamica pentru N motociclete\n");
    printf("4. Alocare dinamica pentru un numar necuoscut de motociclete\n");
    while (scanf("%d", &Select2) && (Select2 < 1 || Select2 > 4));

    printf("Ati ales tipul de memorare %d!\n", Select2);
    printf("\n\n");

    if (Select1 == 1)
      {
        char Nume_file_input[50], Nume_file_output[50];
        printf("Introduceti numele fisierului de input: ");
        scanf("%s", Nume_file_input);

        while ((fi = fopen(Nume_file_input, "w")) == 0)
          {
            printf("Eroare citire fisier! (Nu aveti creat acest fisier in folder!)\n");
            printf("Introduceti numele fisierului de input: ");
            scanf("%s", Nume_file_input);
          }

        printf("Introduceti numele fisierului de output: ");
        scanf("%s", Nume_file_output);
        fo = fopen(Nume_file_output, "w");

        Fisier = true;
        Citire_date_fisier(Select2);
        fclose(fi);

     }
        else
           {
             Fisier = false;
             printf("Introduceti datele:\n");
             Citire_date_consola(Select2);
            }
}

void Citire_date_fisier(int Selected)
{
    switch (Selected)
    {
        case 1:
            { //cazul in care avem vector cu numar n de elemente
                int i, rand; //rand nu are nici o valoare aici, dar trebuie declarat pentru functia Citire_moto_fisier
                fscanf(fi, "%d", &Nr_Moto);

                Moto Vector[Nr_Moto];

              for (i = 0; i < Nr_Moto; ++i)
                {
                    Citire_moto_fisier(&Vector[i], &rand);
                }

              get_Vector(Vector);
              break;
            }

        case 2:
            { //cazul in care avem un vector un numar necunoscut de elemente
                int isEOF = 0;
                Moto Vector[1010]; //declaram un vector cu un numar de elemente (random)

                while (1)
                 {
                    Citire_moto_fisier(&Vector[Nr_Moto], &isEOF);
                    if (isEOF) break;
                    ++Nr_Moto;
                 }

              get_Vector(Vector);
              break;
            }

        case 3:
            {  // caazul in care folosim alocarea dinamica pentru N motociclete
                int i, rand;
                fscanf(fi, "%d", &Nr_Moto);

                Moto* Vector = (Moto *)malloc(Nr_Moto * sizeof(Moto));

                for (i = 0; i < Nr_Moto; ++i)
                 {
                    Citire_moto_fisier(&Vector[i], &rand);
                 }

                    get_Vector(Vector);
                    break;
            }

        case 4:
            {
                // cazul in care se foloseste alocarea dinamica pentru nr. necunoscut de motociclete
                int isEOF = 0;

                Moto* Vector = (Moto *)malloc(sizeof(Moto)); //incepem cu o singura caract_moto

                while (1)
                  {
                    Citire_moto_fisier(&Vector[Nr_Moto], &isEOF);
                    if (isEOF) break;
                    ++Nr_Moto;
                    Vector = realloc(Vector, (Nr_Moto + 1) * sizeof(Moto));
                 }

                get_Vector(Vector);
                break;
            }
    }
}

void Citire_date_consola(int Selected)
{
    switch (Selected)
     {
        case 1:
          {
            int i, rand;
            scanf("%d", &Nr_Moto);

            Moto Vector[Nr_Moto];

            for (i = 0; i < Nr_Moto; ++i)
              {
                Citire_moto_consola(&Vector[i], &rand);
              }

                get_Vector(Vector);
                break;
          }

        case 2:
           {
            printf("Deoarece ati ales Consola + Citirea pana la EOF, tastati combinatia CTRL+Z (Windows) sau CTRL+D (Linux) pentru a marca EOF-ul!!!\n");
            int isEOF = 0;
            Moto Vector[1010];

            while (1)
              {
                Citire_moto_consola(&Vector[Nr_Moto], &isEOF);
                if (isEOF) break;
                ++Nr_Moto;
              }

            get_Vector(Vector);
            break;
          }

        case 3:
           {
            int i, rand;
            scanf("%d", &Nr_Moto);

            Moto* Vector = (Moto *)malloc(Nr_Moto * sizeof(Moto));

            for (i = 0; i < Nr_Moto; ++i)
                {
                  Citire_moto_consola(&Vector[i], &rand);
                }

             get_Vector(Vector);
             break;
           }

        case 4:
           {
             printf("Deoarece ati ales Consola + Citirea pana la EOF, tastati combinatia CTRL+Z (Windows) sau CTRL+D (Linux) pentru a marca EOF-ul!!!\n");
             int isEOF = 0;

             Moto* Vector = (Moto *)malloc(sizeof(Moto));

             while (1)
              {
                Citire_moto_consola(&Vector[Nr_Moto], &isEOF);
                if (isEOF) break;
                ++Nr_Moto;
                Vector = realloc(Vector, (Nr_Moto + 1) * sizeof(Moto));
             }

             get_Vector(Vector);
             break;
           }
      }
}

void Citire_moto_fisier(Moto *P, int *isEOF)
{

    int has_attach, type, d, m, y;

    char c = getc(fi);
    if (c == EOF)
      {
        *isEOF = 1;
        return ;
      }

    while (c == ' ' || c == '\n') c = getc(fi); //Citirea caracterului ce determina categoria
    P->Categorie = c;

    fscanf(fi, "%d", &P->An_fabricatie);
    fscanf(fi, "%lf", &P->Pret_motocicleta);
    fscanf(fi, "%d", &has_attach);
    P->Attach = (has_attach ? true : false); //stabileste valoarea pentru attach(citind ca integer pe has_attach) si daca e 1, atunci e cu attach, daca 0 e fara
    fscanf(fi, "%d", &type);
    P->Tip_moto = (type == 0 ? offroad : city); //stabileste valoarea din enum pentru tipul motocicletei
    fscanf(fi, "%lf", &P->Extra_info.Greutate); //nu conteaza ce variabila (Greutate/Viteza maxima) citim, fiindca au aceeasi valoare (union)
    fscanf(fi, "%d%d%d", &d, &m, &y); //citirea pentru campul de biti (nu se poate lua adresa din acel camp, de aia folosim alta metoda ajutatoare)
    P->ZLA.zi = d, P->ZLA.luna = m, P->ZLA.an = y;// assignam valorilor din campul de biti valoarea corespunzatoare

    fscanf(fi,"%s", P->Marca_moto); //citirea fara spatii
    c = getc(fi); //skip la spatiu

    fgets(P->Tara_origine, 30, fi); //citirea cu spatii
    if (P->Tara_origine[strlen(P->Tara_origine) - 1] == '\n' || P->Tara_origine[strlen(P->Tara_origine) - 1] == ' ')
        P->Tara_origine[strlen(P->Tara_origine) - 1] = 0; //sterge newlineul sau spatiul de la sfarsti daca exista
}

void Citire_moto_consola(Moto *P, int *isEOF)
{

    int has_attach, type, d, m, y;

    char c = getchar();
    if (c == EOF)
      {
        *isEOF = 1;
        return ;
      }

    while (c == ' ' || c == '\n' || c == '\t')
      {
        c = getchar();
        if (c == EOF)
        {
          *isEOF = 1;
          return ;
        }
      }
    P->Categorie = c;

    scanf("%d", &P->An_fabricatie);
    scanf("%lf", &P->Pret_motocicleta);
    scanf("%d", &has_attach);
    P->Attach = (has_attach ? true : false);
    scanf("%d", &type);
    P->Tip_moto = (type == 0 ? offroad : city);
    scanf("%lf", &P->Extra_info.Greutate);
    scanf("%d%d%d", &d, &m, &y);
    P->ZLA.zi = d, P->ZLA.luna = m, P->ZLA.an = y;

    scanf("%s", P->Marca_moto);
    scanf("%[^\n]s", P->Tara_origine);
}

void get_Vector(Moto* P)
{ //ne permite sa avem vectorul in format global (putem lucra cu el indiferent cum a fost creat)

    int i;
    Elem = (Moto *) malloc(Nr_Moto * sizeof(Moto));

    for(i = 0; i < Nr_Moto; i++)
      {
        Elem[i] = P[i];
      }
}

void Afisare_date_fisier(Moto *P)
{
    int i;
    for (i = 0; i < Nr_Moto; ++i)
      {
        if (i) fprintf(fo, "---------------------------------------------\n");
        fprintf(fo, "Motocicletei %d ii corespund urmatoarele date:\n", i + 1);
        fprintf(fo, "Categorie: %c\n", P[i].Categorie);
        fprintf(fo, "Marca: %s\n", P[i].Marca_moto);
        fprintf(fo, "Tara: %s\n", P[i].Tara_origine);
        fprintf(fo, "An fabricare: %d\n", P[i].An_fabricatie);
        fprintf(fo, "Pret: %lf\n", P[i].Pret_motocicleta);

        if (P[i].Attach == true) fprintf(fo, "Poate avea attach\n");
        else fprintf(fo, "Nu poate avea attach\n");

        if (P[i].Tip_moto == offroad)
          {
            fprintf(fo, "Tip offroad\n");
            fprintf(fo, "Greutatea: %lf\n", P[i].Extra_info.Greutate);
          }
        else
            {
               fprintf(fo, "Tip city\n");
               fprintf(fo, "Viteza maxima: %lf\n", P[i].Extra_info.Viteza_maxima);
            }

        fprintf(fo, "Inregistrare la data de: %d/%d/%d\n", P[i].ZLA.zi, P[i].ZLA.luna, P[i].ZLA.an);
      }
}



void Afisare_date_consola(Moto *P)
{
   int i;

    for ( i = 0; i < Nr_Moto; ++i)
    {
        printf("---------------------------------------------\n");
        printf("Motocicletei %d ii corespund urmatoarele date:\n", i + 1);
        printf("Categorie: %c\n", P[i].Categorie);
        printf("Marca: %s\n", P[i].Marca_moto);
        printf("Tara: %s\n", P[i].Tara_origine);
        printf("An fabricare: %d\n", P[i].An_fabricatie);
        printf("Pret: %lf\n", P[i].Pret_motocicleta);

        if (P[i].Attach == true) printf("Poate avea attach\n");
        else printf("Nu poate avea attach\n");

        if (P[i].Tip_moto == offroad)
          {
            printf("Tip offroad\n");
            printf("Greutatea: %lf\n", P[i].Extra_info.Greutate);
          }
        else
            {
              printf("Tip city\n");
              printf("Viteza maxima: %lf\n", P[i].Extra_info.Viteza_maxima);
            }

        printf("Inregistrare la data de: %d/%d/%d\n", P[i].ZLA.zi, P[i].ZLA.luna, P[i].ZLA.an);
    }
}

void Afisare_date(Moto *P)
{
    if (Fisier == true) Afisare_date_fisier(P);
       else Afisare_date_consola(P);
}

void Afisare_cerinta_9(int nr, Moto * P)
//afisez categoria pentru motociclete cu an de fabricatie mai mare sau egal cu 1997
{
    int i;
    for( i = 0; i < nr; i++)
        if(P[i].An_fabricatie >= 1997)
        {
            printf("Motocicleta cerintei 9 are categoria ");
            printf("%c ",P[i].Categorie);
        }

    printf("\n");

}


void Cerinta_10_a(int nr, Moto * P)
//s-a produs o eroare in citirea anului de fabricatiei
//prima motocicleta care are anul  egal cu 1998 este de fapt 2000
{
    int i;
    for(i = 0; i < nr; i++)
        if(P[i].An_fabricatie == 1998)
        {
            P[i].An_fabricatie = 2000;
            break;
        }
}

void Cerinta_10_c(int nr,Moto * P)
//prin noua lege prima motocicleta care are categoria A va deveni C
{
    int i;
    for( i = 0; i < nr; i++)
        if(P[i].Categorie=='A')
    {
        P[i].Categorie='C';
        break;
    }
}

int cmpsort(const void *p1,const void *p2)
//functia cmp din qsort,sortez elementele crescator dupa an de fabricatie.
// in cazul in care au aceelasi an se vor pune in ordine alfabetica a Categoriei
{
    struct caract_moto v1,v2;

    v1=*((struct caract_moto*)p1);
    v2=*((struct caract_moto*)p2);

    if(v1.An_fabricatie<v2.An_fabricatie) return -1;
        else
            if(v1.An_fabricatie>v2.An_fabricatie) return 1;
                else
                    {
                        char c1 = v1.Categorie;
                        char c2 = v2.Categorie;
                        char comp1[1], comp2[1];
                        comp1[0] = c1; comp2[0] = c2;
                        if(strcmp(comp1, comp2) < 0) return -1; //o functie pentru 12 este strcmp
                            else
                                if(strcmp(comp1, comp2))return 1;
                                    else
                                        return 0;
                    }

}

void Sterg_vocale(int nr, Moto * P)
//sterg vocalele din tara de provenienta a primei motociclete
//si adaug sirul obtinut la finalul sirului intial
//cerinta 10 b
{
    char p[101];
    strcpy(p, P[0].Tara_origine);//a doua functie pentru cerinta 12

    int i;
     for(i=0;i < strlen(p);i++) //strlen a 3 a functie pentru cerinta 12
     {

        if(strchr("aeoiu", p[i])) strcpy(p+i,p+i+1); //strchr a 4 a functie pentru cerinta 12
     }
     strcat(P[0].Tara_origine, p);//a 5a functie pentru 12

}

