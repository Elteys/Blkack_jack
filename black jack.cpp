#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

void draw_card(int figura_input, int kolor_input)
{
	SetConsoleOutputCP(CP_UTF8); // Ustawienie kodowania konsoli na UTF-8

	string figura[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

	string kolor[4] = {
		u8" \u2660",	//Pik (♠)
		u8" \u2665",	//Kier (♥)
		u8" \u2666",	//Karo (♦)
		u8" \u2663"		//Trefl (♣)
	};

	string kolor_tekstu;

	if (kolor_input == 1 || kolor_input == 2)
	{
		kolor_tekstu = "\033[91m"; //czerwony
	}
	else
	{
		kolor_tekstu = "\033[90m"; //czarny
	}

	cout << " ___" << endl;
	if (figura_input == 9)
	{
		cout << "|" << kolor_tekstu << figura[figura_input] << "\033[0m" << " |" << endl;
	}
	else
	{
		cout << "|" << kolor_tekstu << figura[figura_input] << "\033[0m" << "  |" << endl;
	}
	cout << "|" << kolor_tekstu << kolor[kolor_input] << "\033[0m" << " |" << endl;
	cout << "|___|" << endl;
}

void draw_hide_card()
{
	SetConsoleOutputCP(CP_UTF8); // Ustawienie kodowania konsoli na UTF-8

	string figura[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };

	string kolor[4] = {
		u8" \u2660",	//Pik (♠)
		u8" \u2665",	//Kier (♥)
		u8" \u2666",	//Karo (♦)
		u8" \u2663"		//Trefl (♣)
	};

	cout << " ___" << endl;
	cout << "|" << "   |" << endl;
	cout << "|" << "   |" << endl;
	cout << "|___|" << endl;
}

void setSrandSeedMilliseconds() {
	SYSTEMTIME st;
	GetSystemTime(&st);
	srand(st.wMilliseconds);
}

int obliczanie_punktow(int wartosc_figury, int wynik) {

	int punkty;

	switch (wartosc_figury) {
	case 0:
		if (wynik + 11 <= 21) //WPROWADZIC MOZLIWOSC MANIPUALCJI WARTOSCIA AS-A!!
		{
			punkty = 11; //AS
		}
		else
		{
			punkty = 1; //AS
		}
		break;
	case 10:
		punkty = 10; //walet
		break;
	case 11:
		punkty = 10; //dama
		break;
	case 12:
		punkty = 10; //król
		break;
	default:
		punkty = wartosc_figury + 1;
		break;
	}

	return wynik + punkty;
}

class Stol
{
public:
	int dostepne_karty[13][4] = {
	{1, 1, 1, 1}, // As

	{1, 1, 1, 1}, // 2

	{1, 1, 1, 1}, // 3

	{1, 1, 1, 1}, // 4

	{1, 1, 1, 1}, // 5

	{1, 1, 1, 1}, // 6

	{1, 1, 1, 1}, // 7

	{1, 1, 1, 1}, // 8

	{1, 1, 1, 1}, // 9

	{1, 1, 1, 1}, // 10

	{1, 1, 1, 1}, // Walet

	{1, 1, 1, 1}, // Dama

	{1, 1, 1, 1} // Król
	};

	int koljenosc_karty[13][4] = {
	   {0, 0, 0, 0}, // As
	   {0, 0, 0, 0}, // 2
	   {0, 0, 0, 0}, // 3
	   {0, 0, 0, 0}, // 4
	   {0, 0, 0, 0}, // 5
	   {0, 0, 0, 0}, // 6
	   {0, 0, 0, 0}, // 7
	   {0, 0, 0, 0}, // 8
	   {0, 0, 0, 0}, // 9
	   {0, 0, 0, 0}, // 10
	   {0, 0, 0, 0}, // Walet
	   {0, 0, 0, 0}, // Dama
	   {0, 0, 0, 0}  // Król
	};

	int koljenosc_karty_krupier[13][4] = {
		{0, 0, 0, 0}, // As
		{0, 0, 0, 0}, // 2
		{0, 0, 0, 0}, // 3
		{0, 0, 0, 0}, // 4
		{0, 0, 0, 0}, // 5
		{0, 0, 0, 0}, // 6
		{0, 0, 0, 0}, // 7
		{0, 0, 0, 0}, // 8
		{0, 0, 0, 0}, // 9
		{0, 0, 0, 0}, // 10
		{0, 0, 0, 0}, // Walet
		{0, 0, 0, 0}, // Dama
		{0, 0, 0, 0}  // Król
	};

	int koljenosc_karty_gracz = 1;
	int kolejnosc_karty_krupier = 1;

	const int HIDE_1 = 1; //1 dla ukrytej pierwszej karty, 0 dla drugiej, 3 dla zadnej
	int wynik_krupiera = 0; //finalny wynik krupiera

	int generowanie_nowej_karty_krupier(int wynik, int runda, bool pass) {
		int wartosc_figury;
		int kolor;
		int kolejnosc = 1; //zerowanie licznika kolejnosci
		int wyniki[2];
		int wynik_krupiera_odkryta_karta = 0;

		if (!(runda == 1) || pass) //nowa karta
		{
			do //wypisywanie kart na stole
			{
				for (int i = 0; i < 13; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (dostepne_karty[i][j] == 0 && koljenosc_karty_krupier[i][j] == kolejnosc)
						{
							if (!(kolejnosc == HIDE_1) || pass)
							{
								draw_card(i, j);
								cout << obliczanie_punktow(i, wynik) - wynik << " pkt" << endl;
								wynik_krupiera_odkryta_karta = obliczanie_punktow(i, 0);
							}
							else
							{
								draw_hide_card();
							}
						}
					}
				}

				kolejnosc++;

			} while (kolejnosc <= koljenosc_karty_gracz);

			if (pass)
			{
				while (wynik_krupiera < 17)
				{
					while (true)
					{
						wartosc_figury = rand() % 13;

						kolor = rand() % 4;

						if (dostepne_karty[wartosc_figury][kolor] == 1)
						{
							dostepne_karty[wartosc_figury][kolor] = 0;
							koljenosc_karty_krupier[wartosc_figury][kolor] = kolejnosc_karty_krupier;
							kolejnosc_karty_krupier++;
							break;
						}

					}

					wynik_krupiera = obliczanie_punktow(wartosc_figury, wynik_krupiera);

					Sleep(2000);
					draw_card(wartosc_figury, kolor);
					cout << obliczanie_punktow(wartosc_figury, wynik) - wynik << " pkt" << endl;
				}
			}

			return wynik_krupiera_odkryta_karta;
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				while (true)
				{
					wartosc_figury = rand() % 13;

					kolor = rand() % 4;

					if (dostepne_karty[wartosc_figury][kolor] == 1)
					{
						dostepne_karty[wartosc_figury][kolor] = 0;
						koljenosc_karty_krupier[wartosc_figury][kolor] = kolejnosc_karty_krupier;
						kolejnosc_karty_krupier++;
						break;
					}

				}

				if (i == HIDE_1 || HIDE_1 == 3)
				{
					draw_card(wartosc_figury, kolor);
					cout << obliczanie_punktow(wartosc_figury, wynik) - wynik << " pkt" << endl;
				}
				else
				{
					draw_hide_card();
				}

				wyniki[i] = obliczanie_punktow(wartosc_figury, 0);
			}

			wynik_krupiera = wynik + wyniki[0] + wyniki[1];

			return wyniki[1];
		}


	}

	int generowanie_nowej_karty(int wynik) { //nowa karta
		int wartosc_figury;
		int kolor;


		while (true)
		{
			wartosc_figury = rand() % 13;

			kolor = rand() % 4;

			if (dostepne_karty[wartosc_figury][kolor] == 1)
			{
				dostepne_karty[wartosc_figury][kolor] = 0;
				koljenosc_karty[wartosc_figury][kolor] = koljenosc_karty_gracz;
				koljenosc_karty_gracz++;
				break;
			}

		}

		draw_card(wartosc_figury, kolor);
		cout << obliczanie_punktow(wartosc_figury, wynik) - wynik << " pkt" << endl;

		return wartosc_figury;
	}

	int generowanie_kart(int wynik, int runda, bool pass) {

		int kolejnosc;
		int finalny_wynik;
		int wyniki[2];

		if (!(runda == 1) || pass)
		{
			kolejnosc = 1; //zerowanie licznika kolejnosci

			do //wypisywanie kart na stole
			{
				for (int i = 0; i < 13; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						if (dostepne_karty[i][j] == 0 && koljenosc_karty[i][j] == kolejnosc)
						{
							draw_card(i, j);
							cout << obliczanie_punktow(i, wynik) - wynik << " pkt" << endl;

						}
					}
				}

				kolejnosc++;

			} while (kolejnosc <= koljenosc_karty_gracz);

			if (pass)
			{
				return wynik;
			}
			else
			{
				return obliczanie_punktow(generowanie_nowej_karty(wynik), wynik); //generowanie nowej karty i zwracanie puktow

			}

		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				wyniki[i] = obliczanie_punktow(generowanie_nowej_karty(wynik), 0);
			}

			finalny_wynik = wynik + wyniki[0] + wyniki[1];

			return finalny_wynik;
		}
	}
};



int main()
{
	bool exit = true;


	while (exit)
	{
		setSrandSeedMilliseconds();
		

		bool pass = false;
		int rozdanie = 1;
		int wynik = 0;
		int wynik_krupier_odkryta_karta = 0;
		int choose;
		Stol stol1;

		while (true)
		{
			if (pass)
			{
				cout << "	  \033[95mPASS\033[0m" << endl;
				cout << endl;

				cout << "-----------------------------" << endl;
				cout << "	Twoj stol" << endl;
				cout << "-----------------------------" << endl;
				Sleep(1000);

				stol1.generowanie_kart(wynik, rozdanie, pass);

				cout << "-----------------------------" << endl;
				cout << "	Krupier" << endl;
				cout << "-----------------------------" << endl;
				Sleep(1000);

				stol1.generowanie_nowej_karty_krupier(wynik_krupier_odkryta_karta, rozdanie, pass);
				Sleep(1000);
				cout << "-----------------------------" << endl;
				cout << endl;
				cout << "\033[32mTwoj wynik: \033[0m" << wynik << endl;
				Sleep(1000);
				cout << "\033[95mWynik krupiera: \033[0m" << stol1.wynik_krupiera << endl;
				Sleep(1000);

				if (wynik > stol1.wynik_krupiera || stol1.wynik_krupiera > 21) //wygrana
				{
					cout << endl;
					cout << "\033[93m#############################" << endl;
					cout << "#	WYGRALES!           #" << endl;
					cout << "#############################\033[0m" << endl;
					Sleep(5000);
					system("cls");
					break;
				}
				else if (wynik < stol1.wynik_krupiera) //przegrana
				{
					cout << endl;
					cout << "\033[91m#############################" << endl;
					cout << "#	PRZEGRALES!         #" << endl;
					cout << "#############################\033[0m" << endl;
					Sleep(5000);
					system("cls");
					break;
				}
				else if (wynik == stol1.wynik_krupiera) //remis
				{
					cout << endl;
					cout << "\033[94m#############################" << endl;
					cout << "#	   REMIS!           #" << endl;
					cout << "#############################\033[0m" << endl;
					Sleep(5000);
					system("cls");
					break;

				}	

			}
			else
			{
				cout << "	\033[95mRozdanie: \033[0m" << rozdanie << endl;
				cout << endl;

				cout << "-----------------------------" << endl;
				cout << "	Twoj stol" << endl;
				cout << "-----------------------------" << endl;

				wynik = stol1.generowanie_kart(wynik, rozdanie, pass);
				cout << endl;
				cout << "\033[32mTwoj wynik: \033[0m" << wynik << endl;

				cout << "-----------------------------" << endl;
				cout << "	Krupier" << endl;
				cout << "-----------------------------" << endl;

				wynik_krupier_odkryta_karta = stol1.generowanie_nowej_karty_krupier(wynik_krupier_odkryta_karta, rozdanie, pass);
				cout << endl;
				cout << "\033[32mWynik krupiera : \033[0m" << wynik_krupier_odkryta_karta << endl;


				if (wynik == 21)
				{
					cout << endl;
					cout << "\033[93m#############################" << endl;
					cout << "#	wygrales!           #" << endl;
					cout << "#	wynik: " << wynik << "           #" << endl;
					cout << "#############################\033[0m" << endl;
					Sleep(3000);
					break;
				}

				if (wynik > 21)
				{
					cout << endl;
					cout << "\033[91m#############################" << endl;
					cout << "#	przegrales!         #" << endl;
					cout << "#	wynik: " << wynik << "           #" << endl;
					cout << "#############################\033[0m" << endl;
					Sleep(3000);
					break;
				}

				cout << "-----------------------------" << endl;
				cout << "	1. Dobierz karte" << endl;
				cout << "	2. pass" << endl;
				cout << "	3. exit" << endl;
				cout << "	4. refresh" << endl;
				//cout << endl << "	wynik krupiera test: " << stol1.wynik_krupiera << endl;
				cout << "-----------------------------" << endl;

				cout << endl;
				cout << "---> ";
				cin >> choose;

				//wystwietlanie tablicy dostepnych kart
				/*
				cout << endl;
				for (int i = 0; i < 13; i++)
				{
					for (int j = 0; j < 4; j++)
					{
						cout << " " << stol1.dostepne_karty[i][j];
					}
					cout << endl;
				}
				cout << endl;
				*/


				if (choose == 1)
				{
					rozdanie++;
				}
				else if (choose == 2)
				{
					cout << endl;
					cout << "\033[95m-----------------------------" << endl;
					cout << "   passujesz z wynikiem: " << wynik << endl;
					cout << "-----------------------------\033[0m" << endl;

					Sleep(2000);
					system("cls");

					pass = true;
				}
				else if (choose == 3)
				{
					exit = false;
					break;
				}
				else if (choose == 4)
				{
					break;
				}

				system("cls");
			}
		}
	}

	return 0;

}

