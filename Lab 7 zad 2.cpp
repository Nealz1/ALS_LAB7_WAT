//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 7.2
// Drzewo RB
//
//  WCY21IX4S0  Miksiewicz Pawel
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#define SPACE 10

using namespace std;

//DEKLARACJA STRUKTURY DRZEWA RB
struct DrzewoRB 
{
    int wartosc;
    char kolorDrzewa;
    struct DrzewoRB *potomekDrzewa[2];
};

struct DrzewoRB *korzen = NULL;

//FUNCKJA ZEBY SPRAWDZIC CZY DRZEWO JEST PUSTE
int CzyPusteDrzewoRB(struct DrzewoRB *korzen)
{
    if (korzen == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//FUNCKJA SPRAWDA CZY SZUKANA DANA JEST W DRZEWIE, JESLI TAK, ZWROCI TRUE, JESLI NIE, ZWROCI FALSE
bool CzyJestWDrzewie(struct DrzewoRB* korzen, int dana)
{
    if(korzen == NULL)
    {
        return false;
    }
    if(korzen->wartosc == dana)
    {
        return true;
    }
    
    bool szukaj1 = CzyJestWDrzewie(korzen->potomekDrzewa[0], dana);
    
    if(szukaj1)
    {
        return true;
    }

    bool szukaj2 = CzyJestWDrzewie(korzen->potomekDrzewa[1], dana);
    
    return szukaj2;
}

//UTWORZENIE WEZLA W DRZEWIE
struct DrzewoRB *Wezel(int a) //utworzenie wezla
{
    struct DrzewoRB *tymczasowa;
    tymczasowa = (struct DrzewoRB*)malloc(sizeof(struct DrzewoRB));
    
    tymczasowa->wartosc = a;
    tymczasowa->kolorDrzewa = 'R';
    tymczasowa->potomekDrzewa[0] = tymczasowa->potomekDrzewa[1]=NULL;
    return tymczasowa;
}

//FUNCKJA NA DODAWANIE ELEMENTU DO DRZEWA
void DodajDoDrzewa(int a) 
{
    struct DrzewoRB *temp[98], *ptr, *tymczasowa, *xPtr, *yPtr;
    int tab[98], indeks;
    int ht = 0;
    ptr=korzen;
    
    if (!korzen) 
	{
        korzen=Wezel(a);
        return;
    }
    temp[ht] = korzen;
    tab[ht++] = 0;
    while(ptr != NULL) 
	{
        if (ptr->wartosc == a) 
		{
            cout << "Nie mozna dodac duplikatu" << endl;
            return;
        }
        
        indeks = (a-ptr->wartosc)>0?1:0;
        temp[ht] = ptr;
        ptr = ptr->potomekDrzewa[indeks];
        tab[ht++] = indeks;
    }
    
    temp[ht-1]->potomekDrzewa[indeks] = tymczasowa=Wezel(a);
    
    while ((ht>=3) && (temp[ht-1]->kolorDrzewa == 'R')) 
	{
        if (tab[ht-2 ]== 0) 
		{
            yPtr = temp[ht-2]->potomekDrzewa[1];
            if (yPtr!=NULL && yPtr->kolorDrzewa == 'R') 
			{
                temp[ht-2]->kolorDrzewa='R';
                temp[ht-1]->kolorDrzewa=yPtr->kolorDrzewa='B';
                ht=ht-2;
            }
			else
			{
                if(tab[ht-1]==0) 
				{
                    yPtr=temp[ht-1];
                }
				else
				{
                    xPtr = temp[ht-1];
                    yPtr = xPtr->potomekDrzewa[1];
                    xPtr->potomekDrzewa[1] = yPtr->potomekDrzewa[0];
                    yPtr->potomekDrzewa[0] = xPtr;
                    temp[ht-2]->potomekDrzewa[0] = yPtr;
                }
                
                xPtr = temp[ht-2];
                xPtr->kolorDrzewa = 'R';
                yPtr->kolorDrzewa = 'B';
                xPtr->potomekDrzewa[0] = yPtr->potomekDrzewa[1];
                yPtr->potomekDrzewa[1] = xPtr;
                if (xPtr == korzen) 
				{
                    korzen = yPtr;
                }
				else 
				{
                    temp[ht-3]->potomekDrzewa[tab[ht-3]]=yPtr;
                }
                break;
            }
        }
		else
		{
            yPtr = temp[ht-2]->potomekDrzewa[0];
            if ((yPtr != NULL) && (yPtr->kolorDrzewa == 'R'))
			{
                temp[ht-2]->kolorDrzewa = 'R';
                temp[ht-1]->kolorDrzewa = yPtr->kolorDrzewa='B';
                ht = ht-2;
            }
			else
			{
                if(tab[ht-1] == 1)
				{
                    yPtr = temp[ht-1];
                }
				else
				{
                    xPtr = temp[ht-1];
                    yPtr = xPtr->potomekDrzewa[0];
                    xPtr->potomekDrzewa[0] = yPtr->potomekDrzewa[1];
                    yPtr->potomekDrzewa[1] = xPtr;
                    temp[ht-2]->potomekDrzewa[1] = yPtr;
                }
                xPtr = temp[ht-2];
                yPtr->kolorDrzewa = 'B';
                xPtr->kolorDrzewa = 'R';
                xPtr->potomekDrzewa[1] = yPtr->potomekDrzewa[0];
                yPtr->potomekDrzewa[0] = xPtr;
                if (xPtr == korzen) 
				{
                    korzen = yPtr;
                }
				else
				{
                    temp[ht-3]->potomekDrzewa[tab[ht-3]] = yPtr;
                }
                break;
            }
        }
    }
    korzen->kolorDrzewa='B';
}

//FUNKCJA ABY WYPISAC W STYLU VLR (PRE-ORDER, PREFIKSOWE)
void Preorder(struct DrzewoRB *korzen)
{
    if(korzen != NULL)
	{
        cout << korzen->wartosc << korzen->kolorDrzewa << " ";
        Preorder(korzen->potomekDrzewa[0]);
        Preorder(korzen->potomekDrzewa[1]);
    }
}

//FUNKCJA ABY WYPISAC W STYLU LVR (IN-ORDER, INFIKSOWE)
void Inorder(struct DrzewoRB *korzen)
{//przejscie drzewa inorder
    if(korzen!=NULL) 
	{
        Inorder(korzen->potomekDrzewa[0]);
        cout << korzen->wartosc << korzen->kolorDrzewa << " ";
        Inorder(korzen->potomekDrzewa[1]);
    }
}

//FUNKCJA ABY WYPISAC W STYLU LRV (POST-ORDER, POSTFIKSOWE)
void Postorder(struct DrzewoRB *korzen)
{
    if(korzen!=NULL) 
	{
        Postorder(korzen->potomekDrzewa[0]);
        Postorder(korzen->potomekDrzewa[1]);
        cout << korzen->wartosc << korzen->kolorDrzewa << " ";
    }
}

//FUNCKJA NA RYSOWANIE DRZEWA WRAZ ODSTEPAMI ABY DRZEWO LADNIE WYGLADALO
void RysujDrzewo(struct DrzewoRB *korzen, int spacja)
{ 
    struct DrzewoRB* walker=korzen;
    if(walker==NULL)
    {
    	return;
	}
    spacja = spacja + SPACE;
    RysujDrzewo(korzen->potomekDrzewa[1], spacja);
    cout << endl;
    
    for(int i = SPACE; i < spacja; i++)
	{ 
        cout << " ";
    }
    cout << korzen->wartosc << korzen->kolorDrzewa << " "; //wypisanie wartosci wezla na ekranie
    RysujDrzewo(walker->potomekDrzewa[0],spacja); //wypisanie lewgo poddrzewa
}

//FUNCKJA NA WYSZUKIWANIE DANEGO ELEMENTU Z DRZEWA I WYPISANIE SCIEZKI DO SZUKANEJ DANEJ
struct DrzewoRB* Wyszukaj(struct DrzewoRB *korzen, int dana)
{
    if(korzen == NULL || korzen->wartosc == dana)
    {
        cout << korzen ->wartosc;
        return korzen;
    }
    else if(dana > korzen->wartosc)
    {
        cout << korzen->wartosc << "-->";
        return Wyszukaj(korzen->potomekDrzewa[1], dana);
    }
    else
    {
        cout << korzen->wartosc << "-->";
        return Wyszukaj(korzen->potomekDrzewa[0], dana);
    }
};

//FUNKCJA NA ZNALEZENIE NAJMNIEJSZEGO WEZLA (POTRZEBNE DO USUWANIA)
struct DrzewoRB* NajmniejszyWezel(struct DrzewoRB* drzewko)
{
    struct DrzewoRB* tymczasowa = drzewko;

    while(tymczasowa && tymczasowa->potomekDrzewa[0] != NULL)
    {
        tymczasowa = tymczasowa->potomekDrzewa[0];
    }
    return tymczasowa;
};

//FUNKCJA NA USUNIECIE DANEGO ELEMENTU Z DRZEWA I ZWROCENIE STRUKTURY PO USUNIECIU DRZEWA
struct DrzewoRB* UsunWezel(struct DrzewoRB* korzen, int dana)
{
    if(korzen == NULL)
    {
        return korzen;
    }
    if(dana < korzen->wartosc)
    {
        korzen->potomekDrzewa[0] = UsunWezel(korzen->potomekDrzewa[0], dana);
    }
    else if(dana > korzen->wartosc)
    {
        korzen->potomekDrzewa[1] = UsunWezel(korzen->potomekDrzewa[1], dana);
    }
    else
    {
        if(korzen->potomekDrzewa[0] == NULL && korzen->potomekDrzewa[1] == NULL)
        {
            return NULL;
        }
        else if(korzen->potomekDrzewa[0] == NULL)
        {
            struct DrzewoRB* tymczasowa = korzen->potomekDrzewa[1];
            free(korzen);
            return tymczasowa;
        }
        else if(korzen->potomekDrzewa[1] == NULL)
        {
            struct DrzewoRB* tymczasowa = korzen->potomekDrzewa[0];
            free(korzen);
            return tymczasowa;
        }
        
        struct DrzewoRB* tymczasowa = NajmniejszyWezel(korzen->potomekDrzewa[1]);
        korzen->wartosc = tymczasowa->wartosc;
        korzen->potomekDrzewa[1] = UsunWezel(korzen->potomekDrzewa[1], tymczasowa->wartosc);
    }
    return korzen;
};

//FUNCKJA USUWA DANE Z DRZEWA
void UsunCaleDrzewoRB(struct DrzewoRB* korzen)
{
    if (korzen == NULL)
    {
       return;
    }

    UsunCaleDrzewoRB(korzen->potomekDrzewa[0]);
    UsunCaleDrzewoRB(korzen->potomekDrzewa[1]);
    free(korzen);
}

//FUNKCJA WYWOLUJE INNA FUNKCJE DO USUWANIE DRZEWA I ZAMIENIA USUNIETE ZNAKI NA NULL
void UsunDrzewoRB(struct DrzewoRB** korzen)
{
    UsunCaleDrzewoRB(*korzen);
    *korzen = NULL;
}

//ROTACJA W LEWO
void RotujLewo(struct DrzewoRB *x) 
{
    struct DrzewoRB *y = x->potomekDrzewa[1];
    x->potomekDrzewa[1] = y->potomekDrzewa[0];
    y->potomekDrzewa[0] = x;
    x = y;
}

//ROTACJA W PRAWO
void RotujPrawo(struct DrzewoRB *x) 
{
    struct DrzewoRB *y = x->potomekDrzewa[0];
    x->potomekDrzewa[0] = y->potomekDrzewa[1];
    y->potomekDrzewa[1] = x;
    x = y;
}

//BALANSOWANIE DRZEWA PO USUNIECIU
void Balansuj(struct DrzewoRB *korzen) 
{
    struct DrzewoRB *rodzenstwo;
    while (korzen != korzen && korzen->kolorDrzewa == 'B') 
	{
        if (korzen == korzen->potomekDrzewa[0]->potomekDrzewa[1]) 
		{
            RotujLewo(korzen);
            korzen = korzen->potomekDrzewa[1];
        } 
		else if (korzen == korzen->potomekDrzewa[1]->potomekDrzewa[0]) 
		{
            RotujPrawo(korzen);
            korzen = korzen->potomekDrzewa[0];
        }
        rodzenstwo = korzen->potomekDrzewa[korzen == korzen->potomekDrzewa[0] ? 1 : 0];
        if (rodzenstwo->kolorDrzewa == 'R') 
		{
            rodzenstwo->kolorDrzewa = 'B';
            korzen->potomekDrzewa[korzen == korzen->potomekDrzewa[0] ? 0 : 1]->kolorDrzewa = 'R';
            if (korzen == korzen->potomekDrzewa[0])
                RotujPrawo(korzen);
            else
                RotujLewo(korzen);
            korzen = korzen;
        } 
		else 
		{
            if (rodzenstwo->potomekDrzewa[0]->kolorDrzewa == 'B' &&
                rodzenstwo->potomekDrzewa[1]->kolorDrzewa == 'B') {
                rodzenstwo->kolorDrzewa = 'R';
                korzen = korzen->potomekDrzewa[korzen == korzen->potomekDrzewa[0] ? 0 : 1];
            } 
			else 
			{
                if (korzen == korzen->potomekDrzewa[0]) 
				{
                    if (rodzenstwo->potomekDrzewa[1]->kolorDrzewa == 'B') 
					{
                        rodzenstwo->potomekDrzewa[0]->kolorDrzewa = 'B';
                        rodzenstwo->kolorDrzewa = 'R';
                        RotujPrawo(rodzenstwo);
                        rodzenstwo = korzen->potomekDrzewa[1];
                    }
                } 
				else 
				{
                    if (rodzenstwo->potomekDrzewa[0]->kolorDrzewa == 'B') 
					{
                        rodzenstwo->potomekDrzewa[1]->kolorDrzewa = 'B';
                        rodzenstwo->kolorDrzewa = 'R';
                        RotujLewo(rodzenstwo);
                        rodzenstwo = korzen->potomekDrzewa[0];
                    }
                }
                rodzenstwo->kolorDrzewa = korzen->kolorDrzewa;
                korzen->kolorDrzewa = 'B';
                if (korzen == korzen->potomekDrzewa[0]) 
				{
                    rodzenstwo->potomekDrzewa[1]->kolorDrzewa = 'B';
                    RotujLewo(korzen);
                } 
				else 
				{
                rodzenstwo->potomekDrzewa[0]->kolorDrzewa = 'B';
				RotujPrawo(korzen);
				}
				korzen = korzen;
			}
		}	
	}
korzen->kolorDrzewa = 'B';
}

int main()
{
    int opcja, wartosc;
    int petla = 1;
    while (petla) //petla, ktora wyswietla opcje do wyboru
    {
    	system("cls");
        cout << "Drzewo RB" << endl;
		cout << "Wybierz operacje:" << endl;
    	cout << "1. Dodaj wezel z klawiatury." << endl;
        cout << "2. Usun wezel." << endl;
        cout << "3. Szukaj wezla." << endl;;
        cout << "4. Usun cale drzewo." << endl;
        cout << "5. Rysuj drzewo." << endl;
		cout << "6. Wypisanie wezlow drzewa w kolejnosci VLR, LVR, LRV." << endl;
        cout << "0. Koniec dzialania." << endl;
		cout << "Operacja:" << endl;
        
        cin >> opcja;

		system("cls");
        switch (opcja) // opcje do wyboru
        {
        	case 0: //KONIEC PROGRAMU
            		cout << "Koniec pracy programu." << endl;
            		exit(0);
      				break;
            case 1: //DODAWANIE DO WEZLA Z KLAWIATURY
                	cout << "1. Dodawanie wezla\n\nPodaj liczbe:" << endl;
                	cin >> wartosc;
                	DodajDoDrzewa(wartosc);
                	printf("\n\n");
                	break;
                	
            case 2: //USUWANIE DANEGO WEZLA Z DRZEWA
                	cout << "2. Usun wezel \n\nPodaj wezel do usuniecia" << endl;
                	cin >> wartosc;
                    cout << endl;
                	if(CzyJestWDrzewie(korzen, wartosc) == true)
                    {
                        korzen = UsunWezel(korzen, wartosc);
                        cout << "Usunieto pomyslnie wezel." << endl << endl;
                        if (CzyJestWDrzewie(korzen, wartosc) == true)
						{
    						struct DrzewoRB *temp;
   	 						temp = korzen;
    						if ((temp->potomekDrzewa[0] == NULL) || (temp->potomekDrzewa[1] == NULL))
   							{
        						korzen = temp->potomekDrzewa[temp->potomekDrzewa[1] == NULL];
    						}
    						else
    						{
        						struct DrzewoRB *nastepnik;
        						nastepnik = temp->potomekDrzewa[1];
        						while (nastepnik->potomekDrzewa[0] != NULL)
        						{
            						nastepnik = nastepnik->potomekDrzewa[0];
        						}
        						korzen->wartosc = nastepnik->wartosc;
        						korzen->potomekDrzewa[1] = UsunWezel(korzen->potomekDrzewa[1], nastepnik->wartosc);
    						}
    							Balansuj(temp);
						}
                    }
                    else
                    {
                        cout << "Wprowadzony wezel nie znajduje sie w liscie." << endl << endl;
                    }
                	break;
            case 3: //SZUKANIE WEZLA W DRZEWIE
                	cout << "3. Szukaj wezla\n\nPodaj szukany wezel i wyswietl sciezke do niego." << endl;
                	cin >> wartosc;
                	cout << endl;
                	if(CzyJestWDrzewie(korzen, wartosc))
                    {
                    	cout << "Sciezka:" << endl;
                        Wyszukaj(korzen, wartosc);
                        cout << endl << endl;
                    }
                    else
                    {
                        cout << "Podany wezel nie znajduje sie w drzewie." << endl << endl;
                    }
                	break;
            case 4: //USUWANIE CALEGO DRZEWA
            		cout << "4. USUWANIE CALEGO DRZEWA." << endl << endl;
            		UsunDrzewoRB(&korzen);
                    cout << "Pomyslnie usunieto cale drzewo." << endl << endl;
            		break;
            case 5: //RYSOWANIE DRZEWA
            		cout << "5. RYSOWANIE DRZEWA." << endl;
					RysujDrzewo(korzen,0);
					cout << endl;

                	break;
            case 6: //WYPISYWANIE WEZLOW DRZEWA W KOLEJNOSCI VLR, LVR, LRV
                	cout << "VLR - pre-order, przejscie wzdluzne, prefiksowe" << endl;
      	      		Preorder(korzen);
      	      		cout << endl;
      	      	
    				cout << endl << "LVR - in-order, przejscie poprzeczne, infiksowe" << endl;
      	      		Inorder(korzen);
      	      		cout << endl;
      	      	
    				cout << endl << "LRV - post-oder, przejscie wsteczne, postfiksowe" << endl;
      	     		Postorder(korzen);
                	break;
            default:
              		cout << "Wpisano bledny numer operacji. Sprobuj ponownie." << endl;
                break;
        }
		system("pause");
	}	
return 0;
}
