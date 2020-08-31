/**
 * \file main.cpp
 * 
 * Ez a fájl tartalmazza az adatbázis működését vezérlő main() függvény és egyéb járulékos függvények definícióját/deklarációját, illetve itt hajtódnak végre a tesztesetek is.
 */

#include <iostream>
#include <exception>

#include "Lista.hpp"
#include "Movie.hpp"
#include "FamilyMovie.hpp"
#include "Documentary.hpp"
#include "test.hpp"
#include "gtest_lite.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::bad_alloc;

#define TESZT

/**
 * @brief A függvény megjeleníti a képernyőn a felhasználó által választható opciókat.
 */ 
void options();

/**
 * @brief Ez a függvény fogadja a felhasználó által választott menüpont sorszámát.
 * @param l - Az eredeti lista, amivel a program futása közben dolgozunk (felszabadítás miatt kell érvénytelen input esetén).
 * @return A felhasználó döntése.
 */ 
unsigned int choice(Lista l);

/**
 * @brief A teljes adatbázis vezérlését végzi a korábban megírt függvények felhasználásával.
 */ 
int main(){

    try{
        Lista list;
    
        list.read("film_database.txt");

        int valasztas;
        string valasz;

        string mufaj, leiras = "", cim;
        unsigned int hossz, kiadas, korhatar = 0;

        do
        {
            options();
            valasztas = choice(list);

        switch(valasztas){

            case 1:

                list.print();

                break;

            case 2:

                do{

                    cin.ignore();
                    cout << "Mufaj: ";
                    getline(cin, mufaj);
                    cout << endl;
                    cout << "Cim: ";
                    getline(cin, cim);
                    cout << endl;
                    cout << "Hossz (perc): ";
                    cin >> hossz;

                    if(cin.fail()){
                        
                        list.save("film_database.txt");
                        list.felszab();
                        throw "\n\nHibas bemenet. A program leall.\n";
                    }

                    cout << endl;
                    cout << "Kiadas: ";
                    cin >> kiadas;

                    if(cin.fail()){
                        
                        list.save("film_database.txt");
                        list.felszab();
                        throw "\n\nHibas bemenet. A program leall.\n";
                    }

                    if(mufaj == "csaladi"){
                        cout << endl;
                        cout << "Korhatar: ";
                        cin >> korhatar;

                        if(cin.fail()){
                            
                            list.save("film_database.txt");
                            list.felszab();
                            throw "\n\nHibas bemenet. A program leall.\n";
                        }

                        cout << endl;

                        list.add(mufaj, cim, hossz, kiadas, korhatar, leiras);

                    }
                    else{
                        if(mufaj == "dokumentum"){
                            cout << endl;
                            cin.ignore();
                            cout << "Leiras: ";
                            getline(cin, leiras);
                            cout << endl;

                            list.add(mufaj, cim, hossz, kiadas, korhatar, leiras);
                        }
                        else{
                            cout << endl;
                            list.add(mufaj, cim, hossz, kiadas, korhatar, leiras);
                        }
                    }

                cout << "Szeretne tovabbi filmeket hozzaadni? ";
                cin >> valasz;
                cout << endl;

                }while(valasz == "igen");

                break;

            case 3:

                do{
                    cin.ignore();

                    cout << "A torlendo film cime: ";
                    getline(cin, cim);

                    cout << endl;

                    list.remove(cim);

                    cout << "\nSzeretne tovabbi filmeket torolni? ";
                    cin >> valasz;
                    cout << endl;

                }while(valasz == "igen");;

                break;

            case 4:

                cin.ignore();
                
                cout << "Mely mufaj szerint tortenjen a szures? ";
                getline(cin, mufaj);
                cout << endl;

                list.filter(mufaj);

                break;

            case 5:

                cin.ignore();
                
                cout << "A keresett film cime: ";
                getline(cin, cim);
                cout << endl;

                list.search(cim);

                break;

            default:
                break;
            }

        }while(valasztas != 6);

        if(list.get_eleje() != nullptr){
            list.save("film_database.txt");
            list.felszab();
        }

        cout << "Sikeres kilepes, viszontlatasra!" << endl;

    }catch(bad_alloc& ba){
        
        cerr << "\nHiba tortent memoriafoglalas kozben. A program leall.\n" << endl;
        cerr << ba.what();
        exit(1);
    }
    catch(const char* p){
        cerr << p;
        exit(1);
    }
    catch(...){
        cerr << "\nVaratlan kivetel keletkezett. A program leall.\n" << endl;
        exit(1);
    }

    #ifdef TESZT
        try{
            test_0();
            test_1();
            test_2();
            test_3();
            test_4();
            test_5();
            test_6();
            test_7();
        }
        catch(...){
            cerr << "\nVaratlan kivetel keletkezett teszteles soran. A program leall.\n" << endl;
            exit(1);
        }
    #endif

    return 0;
}

void options(){

    cout << "FILMTAR\n" << endl;
    cout << "1. Teljes adatbazis megjelenitese" << endl;
    cout << "2. Uj film(ek) felvetele" << endl;
    cout << "3. Meglevo film(ek) torlese" << endl;
    cout << "4. Mufaj szerinti szures" << endl;
    cout << "5. Kereses" << endl;
    cout << "6. Kilepes\n" << endl;
}

/**
 * @details A függvény felszólítja a felhasználót, hogy válaszzon a menüből. Ha a felhasználó választott, akkor visszatér a választással.
 * Amennyiben nem létezik a választott menüpont, akkor a felhasználónak lehetősége van újra választani. A függvény ellenőrzi az érvénytelen inputokat
 * (pl. ha szám helyett karaktert adunk meg), és, ha ilyet kap, akkor erről értesíti a felhasználót, és befejezi a program végrehajtását.  
 */ 
unsigned int choice(Lista l){

    unsigned int valasztas;

    cout << "Kerem valasszon a menubol (1-6): ";
    cin >> valasztas;

    if(cin.fail()){
        l.felszab();
        throw "\n\nHibas bemenet. A program leall.\n";
    }

    cout << endl;

    while(valasztas == 0 || valasztas > 6)
    {
        cout << "A kivalasztott menupont nem letezik!\n\n";

        cout << "Kerem valasszon ujra a menubol (1-6): ";
        cin >> valasztas;

        if(cin.fail()){
            l.felszab();
            throw "\n\nHibas bemenet. A program leall.\n";
        }

        cout << endl;
    }

    return valasztas;
}