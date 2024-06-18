//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 7.1
// Drzewo AVL
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

//DEKLARACJA STRUKTURY DRZEWA AVL
struct DrzewoAVL
{
	int wartosc;
	int wysokosc;
	struct DrzewoAVL *lewo;
	struct DrzewoAVL *prawo;
};

//FUNCKJA ZEBY SPRAWDZIC CZY DRZEWO JEST PUSTE
int CzyPusteDrzewoAVL(struct DrzewoAVL *korzen)
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
bool CzyJestWDrzewie(struct DrzewoAVL* korzen, int dana)
{
    if(korzen == NULL)
    {
        return false;
    }
    if(korzen->wartosc == dana)
    {
        return true;
    }
    
    bool szukaj1 = CzyJestWDrzewie(korzen->lewo, dana);
    
    if(szukaj1)
    {
        return true;
    }

    bool szukaj2 = CzyJestWDrzewie(korzen->prawo, dana);
    
    return szukaj2;
}

//FUNCKJA NA RYSOWANIE DRZEWA WRAZ ODSTEPAMI ABY DRZEWO LADNIE WYGLADALO
void RysowanieDrzewa(struct DrzewoAVL* korzen, int spacja)
{
    if (korzen == NULL)
    {
        return;
    }
    spacja = spacja + SPACE;
    RysowanieDrzewa(korzen->prawo, spacja);
    cout<<endl;
    
    for (int i = SPACE; i < spacja; i++)
    {
        cout<<" ";
    }
    cout << korzen->wartosc << endl;
    RysowanieDrzewa(korzen->lewo, spacja);
}

//FUNKCJA ABY WYPISAC W STYLU VLR (PRE-ORDER, PREFIKSOWE)
void Preorder(struct DrzewoAVL *korzen)
{
    if (korzen == NULL)
    {
		return;
	}

    cout << korzen->wartosc << " ";
    Preorder(korzen->lewo);
    Preorder(korzen->prawo);
}

//FUNKCJA ABY WYPISAC W STYLU LVR (IN-ORDER, INFIKSOWE)
void Inorder(struct DrzewoAVL *korzen)
{
    if (korzen == NULL)
    {
    	return;
	}
	
    Inorder(korzen->lewo);
    cout << korzen->wartosc << " ";
    Inorder(korzen->prawo);
}

//FUNKCJA ABY WYPISAC W STYLU LRV (POST-ORDER, POSTFIKSOWE)
void Postorder(struct DrzewoAVL *korzen)
{
    if (korzen == NULL)
    {
		return;
	}
	
    Postorder(korzen->lewo);
    Postorder(korzen->prawo);
    cout << korzen->wartosc << " ";
}

//FUNKCJA ZWRACA POZIOM (WYSOKOSC) DRZEWA
int Poziom(struct DrzewoAVL *korzen) 
{
    if(korzen == NULL)
    {
        return 0;
    }
    return korzen->wysokosc;
}

//WLASNORECZNA FUNKCJA MAKS - ODPOWIEDNIK FUNKCJI WBUDOWANEJ MAX()
int Maks(int liczba1, int liczba2) 
{
    if(liczba1 > liczba2)
	{
        return liczba1;
    }
	else
	{
        return liczba2;
    }
}

//FUNCKJA ZWRACA BALANS DRZEWA MIEDZY WEZLAMI
int Balans(struct DrzewoAVL *korzen)
{
    if(korzen == NULL)
    {
    	return 0;
	}
	
    return Poziom(korzen->lewo) - Poziom(korzen->prawo);
}

//UTWORZENIE WEZLA W DRZEWIE
struct DrzewoAVL *Wezel(int dana) 
{
	//PRZYDZIELENIE PAMIECI
    struct DrzewoAVL *tymczasowa = (struct DrzewoAVL*)malloc(sizeof(struct DrzewoAVL));
    
    tymczasowa->wartosc = dana;
    tymczasowa->wysokosc = 1;
    tymczasowa->lewo = NULL;
    tymczasowa->prawo = NULL;
    
    return tymczasowa;
}

//FUNCKJA NA WPROWADZENIE ROTACJI W DRZEWIE AVL W PRAWO
struct DrzewoAVL *RotujWPrawo(struct DrzewoAVL *korzen) 
{
    struct DrzewoAVL *temp = korzen->lewo;
    struct DrzewoAVL *temp2 = temp->prawo;
    
    temp->prawo = korzen;
    korzen->lewo = temp2;
    
    //WARUNKI ROTACJI W PRAWO
    if(Poziom(temp->lewo) > Poziom(temp->prawo))
    {
    	temp->wysokosc = Poziom(temp->lewo)+1;
	}
    
    if(Poziom(temp->lewo) < Poziom(temp->prawo))
    {
    	temp->wysokosc = Poziom(temp->prawo)+1;
	}
    
    if(Poziom(korzen->lewo) > Poziom(korzen->prawo))
    {
    	korzen->wysokosc = Poziom(korzen->lewo)+1;
	}
    
    if(Poziom(korzen->lewo) < Poziom(korzen->prawo))
    {
    	korzen->wysokosc = Poziom(korzen->prawo)+1;
	}
    
    return temp;
};

//FUNCKJA NA WPROWADZENIE ROTACJI W DRZEWIE AVL W LEWO
struct DrzewoAVL *RotujWLewo(struct DrzewoAVL *korzen) 
{
    struct DrzewoAVL *temp = korzen->prawo;
    struct DrzewoAVL *temp2 = temp->lewo;
    
    temp->lewo = korzen;
    korzen->prawo = temp2;
    
    //WARUNKI ROTACJI
    if(Poziom(korzen->lewo) > Poziom(korzen->prawo))
    {
    	korzen->wysokosc = Poziom(korzen->lewo)+1;
	}
    
    if(Poziom(korzen->lewo) < Poziom(korzen->prawo))
    {
    	korzen->wysokosc = Poziom(korzen->prawo)+1;
	}
    
    if(Poziom(temp->lewo) > Poziom(temp->prawo))
    {
    	temp->wysokosc = Poziom(temp->lewo)+1;
	}
    
    if(Poziom(temp->lewo) < Poziom(temp->prawo))
    {
    	temp->wysokosc = Poziom(temp->prawo)+1;
	}
    
    return temp;
};

//FUNCKJA NA DODAWANIE ELEMENTU DO DRZEWA
struct DrzewoAVL *DodajDoDrzewa(struct DrzewoAVL *korzen, int dana) 
{
    if(korzen == NULL)
    {
		return Wezel(dana);   	
	}
    if(dana < korzen->wartosc)
    {
    	korzen->lewo = DodajDoDrzewa(korzen->lewo,dana);
	}
    else if(dana >= korzen->wartosc)
    {
    	korzen->prawo = DodajDoDrzewa(korzen->prawo,dana);
	}
    else
    {
    	return korzen;	
	}

	//SPRAWDZENIE I WYKONANIE BALANSU PO DODANIU NOWEGO WEZLA DO DRZEWA
    korzen->wysokosc = 1 + Maks(Poziom(korzen->lewo), Poziom(korzen->prawo));
    int balans = Balans(korzen);
    
    if(balans > 1 && dana < korzen->lewo->wartosc)
    {
    	return RotujWPrawo(korzen);	
	}
        
    if(balans < -1 && dana >= korzen->prawo->wartosc)
    {
    	return RotujWLewo(korzen);
	}
    
    if(balans > 1 && dana > korzen->lewo->wartosc) 
	{
        korzen->lewo = RotujWLewo(korzen->lewo);
        return RotujWPrawo(korzen);
    }
    if(balans < -1 && dana <= korzen->prawo->wartosc) 
	{
        korzen->prawo = RotujWPrawo(korzen->prawo);
        return RotujWLewo(korzen);
    }
    
    return korzen;
}

//FUNKCJA NA ZNALEZENIE NAJMNIEJSZEGO WEZLA (POTRZEBNE DO USUWANIA)
struct DrzewoAVL *NajmniejszyWezel(struct DrzewoAVL *korzen) 
{
    struct DrzewoAVL *tymczasowa = korzen;
    
    while (tymczasowa->lewo != NULL)
    {
    	tymczasowa = tymczasowa->lewo;
	}
        
    return tymczasowa;
};

//FUNKCJA NA USUNIECIE DANEGO ELEMENTU Z DRZEWA I ZWROCENIE STRUKTURY PO USUNIECIU DRZEWA
struct DrzewoAVL *UsunWezel(struct DrzewoAVL *korzen, int dana)
{
	//SZUKANIE DANEJ DO USUNIECIA
    if(korzen == NULL)
    {
    	return korzen;
	}
    if(dana < korzen->wartosc)
    {
    	korzen->lewo = UsunWezel(korzen->lewo,dana);
	}
    else if(dana > korzen->wartosc)
    {
    	korzen->prawo = UsunWezel(korzen->prawo,dana);
	}
    else
	{
        if((korzen->lewo == NULL) || (korzen->prawo == NULL)) 
		{
            struct DrzewoAVL *temp = korzen->lewo ? korzen->lewo : korzen->prawo;
            if(temp == NULL) 
			{
                temp = korzen;
                korzen = NULL;
            }
			else
			{
				*korzen = *temp;
			}
            free(temp);
        }
		else
		{
            struct DrzewoAVL *temp = NajmniejszyWezel(korzen->prawo);
            korzen->wartosc = temp->wartosc;
            korzen->prawo = UsunWezel(korzen->prawo, temp->wartosc);
        }
    }
    if(korzen == NULL)
    {
    	return korzen;
	}

	//SPRAWDZENIE I WYKONANIE BALANSU PO USUNIECIU DANEJ
    korzen->wysokosc = 1 + Maks(Poziom(korzen->lewo), Poziom(korzen->prawo));
    int balans = Balans(korzen);
    
    if(balans > 1 && Balans(korzen->lewo) >= 0)
    {
    	return RotujWPrawo(korzen);
	}
	
    if(balans > 1 && Balans(korzen->lewo) < 0)
	{
        korzen->lewo = RotujWLewo(korzen->lewo);
        return RotujWPrawo(korzen);
    }
    
    if(balans< -1 && Balans(korzen->prawo) <= 0)
    {
    	return RotujWLewo(korzen);
	}
	
    if(balans < -1 && Balans(korzen->prawo) > 0) 
	{
        korzen->prawo = RotujWPrawo(korzen->prawo);
        return RotujWLewo(korzen);
    }
    
    return korzen;
};

//FUNCKJA NA WYSZUKIWANIE DANEGO ELEMENTU Z DRZEWA I WYPISANIE SCIEZKI DO SZUKANEJ DANEJ
struct DrzewoAVL* Wyszukaj(struct DrzewoAVL *korzen, int dana)
{
	//WARUNKI ABY WYKONAC SCIEZKI DO SZUKANEJ LICZBY
    if(korzen == NULL || korzen->wartosc == dana)
    {
        cout << korzen ->wartosc;
        return korzen;
    }
    else if(dana > korzen->wartosc)
    {
        cout << korzen->wartosc << "-->";
        return Wyszukaj(korzen->prawo, dana);
    }
    else
    {
        cout << korzen->wartosc << "-->";
        return Wyszukaj(korzen->lewo, dana);
    }
};

//FUNCKJA USUWA (ZWALNIA PAMIEC) DANE Z CALEGO DRZEWA
void UsunCaleDrzewoAVL(struct DrzewoAVL* korzen)
{
    if (korzen == NULL)
    {
       return;
    }

    UsunCaleDrzewoAVL(korzen->lewo);
    UsunCaleDrzewoAVL(korzen->prawo);
    free(korzen);
}

//FUNKCJA WYWOLUJE INNA FUNKCJE DO USUWANIE DRZEWA I ZAMIENIA USUNIETE ZNAKI NA NULL
void UsunDrzewoAVL(struct DrzewoAVL** korzen)
{
    UsunCaleDrzewoAVL(*korzen);
    *korzen = NULL;
}

//MAIN
int main()
{
	//DEKLARACJA STRUKTURY, INTA DO OPERACJI, 
	struct DrzewoAVL* korzen = NULL;
	int opcja, wartosc;
	int petla = 1;
	
	while(petla)
	{
		system("cls");
		cout << "Drzewo AVL" << endl;
		cout << "Wybierz operacje:" << endl;
    	cout << "1. Dodaj wezel z klawiatury." << endl;
    	cout << "2. Usun wezel." << endl;
    	cout << "3. Szukaj wezla." << endl;
    	cout << "4. Usun cale drzewo." << endl;
    	cout << "5. Rysuj drzewo." << endl;
   		cout << "6. Wypisanie wezlow drzewa w kolejnosci VLR, LVR, LRV." << endl;
   		cout << "0. Koniec dzialania." << endl;
		cout << "Operacja:" << endl;
		
    	cin >> opcja;

		system("cls");
    	switch (opcja)
    	{
    	case 0: //KONIEC PROGRAMU
            	cout << "Koniec pracy programu." << endl;
            	exit(0);
      			break;
      			
    	case 1: //DODAWANIE DO WEZLA Z KLAWIATURY
      			cout << "1. Dodawanie wezla\n\nPodaj liczbe:" << endl;
	      		cin >> wartosc;
                korzen = DodajDoDrzewa(korzen, wartosc);
	      		cout<<endl;
    			break;
    			
    	case 2: //USUWANIE DANEGO WEZLA Z DRZEWA
    			if(CzyPusteDrzewoAVL(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
                    cout << "2. Usun wezel \n\nPodaj wezel do usuniecia" << endl;
                    cin >> wartosc;
                    cout << endl;
                    
                    if(CzyJestWDrzewie(korzen, wartosc))
                    {
                        korzen = UsunWezel(korzen, wartosc);
                        cout << "Usunieto pomyslnie wezel." << endl << endl;
                    }
                    else
                    {
                        cout << "Wprowadzony wezel nie znajduje sie w drzewie." << endl << endl;
                    }

      			}
      			break;
      			
    	case 3: //SZUKANIE WEZLA W DRZEWIE
    			if(CzyPusteDrzewoAVL(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
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
                }
      			break;
      			
      	case 4: //USUWANIE CALEGO DRZEWA
                if(CzyPusteDrzewoAVL(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
                else
                {
                    cout << "4. USUWANIE CALEGO DRZEWA." << endl << endl;
                    UsunDrzewoAVL(&korzen);
                    cout << "Pomyslnie usunieto cale drzewo." << endl << endl;
                }
      			break;
      			
      	case 5: //RYSOWANIE DRZEWA
      			if(CzyPusteDrzewoAVL(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
      				cout << "5. RYSOWANIE DRZEWA." << endl << endl;
     				RysowanieDrzewa(korzen, 1);
      				cout << endl;
      			}
      			break;
      			
    	case 6: //WYPISYWANIE WEZLOW DRZEWA W KOLEJNOSCI VLR, LVR, LRV
    			if(CzyPusteDrzewoAVL(korzen) == 1)
    			{
    				cout << "Drzewo jest puste. Najpierw dodaj liczby do drzewa." << endl << endl;
				}
				else
				{
    				cout << "6. Wypisanie wezlow drzewa w kolejnosci VLR, LVR, LRV." << endl << endl;
    			
    				cout << "VLR - pre-order, przejscie wzdluzne, prefiksowe" << endl;
      	      		Preorder(korzen);
      	      		cout << endl;
      	      	
    				cout << endl << "LVR - in-order, przejscie poprzeczne, infiksowe" << endl;
      	      		Inorder(korzen);
      	      		cout << endl;
      	      	
    				cout << endl << "LRV - post-oder, przejscie wsteczne, postfiksowe" << endl;
      	     		Postorder(korzen);
      	     		cout << endl << endl;
      	     	}
    			break;
    			
    	default: //PRZYPADEK GDY WPISZEMY INTA NIE ZE WSKAZANYCH OPERACJI
      			cout << "Wpisano bledny numer operacji. Sprobuj ponownie." << endl;
    	}
    system("pause");
	}
	
return 0;
}
