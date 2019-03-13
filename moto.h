#ifndef MOTO_H_INCLUDED
#define MOTO_H_INCLUDED

typedef enum new_data_type{false, true} bool;

typedef struct caract_moto
{
    char Categorie; //caracter (A, B, C, etc.)
    char Tara_origine[30]; //sir de caracter cu spatii ( Republica Moldova)
    char Marca_moto[30]; //sir de catacter fara spatii ( Harley )

    int An_fabricatie; //numar intreg ( 1984 )
    double Pret_motocicleta; //numar cu virgula mobila ( 250.000)
    bool Attach; // variabila boolean (definita cu enum!)

    enum Type{ //enumeratie pentru tipul motocicletei
        offroad,
        city
    } Tip_moto;

    union Motocicleta{ //uniune imbricata
        double Viteza_maxima; //daca moto e de tip city
        double Greutate; //daca moto e de tip offroad
    } Extra_info;

    struct DMY{ //campuri pe biti pentru ziua, luni si anul inregistrarii motocicletei
        unsigned int zi : 5;
        unsigned int luna : 4;
        unsigned int an : 15;
    } ZLA;

} Moto;

void Nucleu();

void Info_user();

void Citire_date_fisier(int);
void Citire_date_consola(int);
void Citire_moto_fisier(Moto *, int*);
void Citire_moto_consola(Moto *, int*);

void get_Vector(Moto *);

void Afisare_date_fisier(Moto *);
void Afisare_date_consola(Moto *);
void Afisare_date(Moto *);

void Afisare_cerinta_9(int ,Moto *);
void Cerinta_10_a(int, Moto * P);
void Cerinta_10_c(int, Moto * P);

int cmpsort(const void *, const void *);

void Sterg_vocale(int, Moto *);


#endif // MOTO_H_INCLUDED
