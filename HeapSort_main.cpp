// Heapsort (sortowanie przez kopcowanie)
#include <iostream>

/*
 U mnie korzen i ostatni element sa zamieniane miejscami.
 Zapisywany przez nas ostatni indeks tabeli z liczba jest zmniejszany o 1.
 Dzieki temu poprzedni korzen jest za koncem kopca, ale nadal w tablicy
*/

int numer_rodzica(int indeks);
void zamien(long t[], int indeks_1, int indeks_2); //zamienia miejscami elementy kopca
void wypisz_stan(long t[], int koniec); //wypisze aktualny stan kopca
void wypisz_posortowane(long t[], int ile); //wypisze posortowane liczby
void zbuduj_kopiec(long t[], int koniec); //zrobi pojedyncze przejscie po kopcu i po kolei zamienia miejscami element z jego rodzicem
bool sprawdz_kopiec(long t[], int koniec); //sprawdza czy kopiec jest poprawny

int main()
{
    int ilosc_przypadkow_testowych = 0;
    int ilosc; //ile jest liczb do posortowania
    int a; //potrzebne do petli
    int ostatni_indeks; //na ktorym indeksie w tablicy konczy sie kopiec
    int kolejne_rozmiary[] = { 1, 3, 7, 15, 31, 63, 127, 255 };
    int rozmiar; //rozmiar tablicy z kopcem
    //pierwsza liczba w pliku to ilosc przypadkow testowych
    std::cin >> ilosc_przypadkow_testowych;
    //ta petla bada kolejne przypadki testowe
    while (ilosc_przypadkow_testowych > 0)
    {
        std::cin >> ilosc; //pierwsza liczba w linijce
        rozmiar = 1;
        //dobieranie rozmiaru tabeli z kopcem
        for (a = 0; a < 6; a++)
        {
            if (ilosc == kolejne_rozmiary[a])
            {
                rozmiar = kolejne_rozmiary[a];
                break;
            }
            else if (ilosc <= kolejne_rozmiary[a + 1])
            {
                rozmiar = kolejne_rozmiary[a + 1];
                break;
            }
        }
        //tworzenie tabeli z liczbami/kopcem
        long* tabela = new long[rozmiar];
        //wczytanie liczb do tabeli
        for (a = 0; a < ilosc; a++)
        {
            std::cin >> tabela[a];
        }
        //kopcowanie i sortowanie
        ostatni_indeks = ilosc - 1;
        //ten do{}while() pracuje az skoncza sie elementy w kopcu
        do {
            //ponizsze do{}while() buduje kopiec i sprawdza go
            //ostatecznym rezultatem jest poprzwny kopiec
            do {
                //moze byc potrzebne by 'przeszla' kilka razy po kopcu, by go uporzadkowac
                zbuduj_kopiec(tabela, ostatni_indeks);
            } while (!sprawdz_kopiec(tabela, ostatni_indeks));
            wypisz_stan(tabela, ostatni_indeks); //wypisuje utworzony poprawny kopiec
            zamien(tabela, 0, ostatni_indeks); //wyrzuca korzen na sam koniec
            ostatni_indeks--; //przesuwa koniec kopca
        } while (ostatni_indeks >= 1);
        //koniec tego przypadku
        wypisz_posortowane(tabela, ilosc);
        delete[] tabela;
        tabela = NULL;
        ilosc_przypadkow_testowych -= 1; //kolejny przypadek zbadany
    }
    return 0;
}

//=====================================
//            FUNKCJE
//=====================================

int numer_rodzica(int indeks)
{
    if (indeks % 2 == 0)
    {
        return (indeks - 2) / 2;
    }
    else
    {
        return (indeks - 1) / 2;
    }
}

void zamien(long t[], int indeks_1, int indeks_2)
{
    long tymczasowy = t[indeks_1];
    t[indeks_1] = t[indeks_2];
    t[indeks_2] = tymczasowy;
    return;
}

void wypisz_stan(long t[], int koniec)
{
    int x = 0;
    while (x <= koniec)
    {
        std::cout << t[x] << " ";
        x++;
    }
    std::cout << std::endl;
    return;
}

void wypisz_posortowane(long t[], int ile)
{
    int x = 0;
    while (x < ile)
    {
        std::cout << t[x] << " ";
        x++;
    }
    std::cout << std::endl << std::endl;
    return;
}

//ta funckja aktualnie nie robi poprawnego kopca
void zbuduj_kopiec(long t[], int koniec)
{
    int a, rodzic;
    //roznie postepujemy zaleznie od tego, czy kopiec ma ponad 2 elementy
    if (koniec >= 2)
    {
        //od ostatniego elementu do pierwszego zamienia mijescami
        //rodzica z dzieckiem, jesli jest to konieczne
        for (a = koniec; a >= 0; a--)
        {
            rodzic = numer_rodzica(a);
            if (t[a] > t[rodzic])
            {
                zamien(t, a, rodzic);
            }
        }
    }
    else
    {
        //sprawdzane jesli kopiec ma tylko 2 elementy
        if (t[0] < t[1])
        {
            zamien(t, 0, 1);
        }
    }
    return;
}

bool sprawdz_kopiec(long t[], int koniec)
{
    bool poprawny = true;
    int dziecko;
    int nr = 0; //to bedzie indeks na ktory aktualnie patrzymy
    while (nr > koniec) //sprawdzamy kolejne elementy tabeli az do konca
    {
        //sprawdzanie dzieci
        //zdarza sie ze indeks dziecka wypada poza tabela
        dziecko = 2 * nr + 1;
        if (dziecko >= koniec || (dziecko + 1) >= koniec)
        {
            break;
        }
        //sprawdza pierwsze dziecko
        if (t[dziecko] > t[nr])
        {
            poprawny = false;
            break; //nie ma potrzeby dalej sprawdzac
        }
        dziecko++; //sprawdzi drugie dziecko
        if (t[dziecko] > t[nr])
        {
            poprawny = false;
            break;
        }
        nr++;
    }
    return poprawny;
}
