/**
 * \file Lista.cpp
 * 
 * Ez a fájl tartalmazza a Lista osztály tagfüggvényeinek definícióját.
 */   

#include <iostream>
#include <fstream>
#include <exception>

#include "Lista.hpp"
#include "Movie.hpp"
#include "FamilyMovie.hpp"
#include "Documentary.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::stoi;
using std::ofstream;
using std::ifstream;
using std::ios_base;

/**
 * @details Ennek a tagfüggvénynek a segítségével tudunk új elemeket hozzáadni a láncolt listához. 
 * Kezdetben 3 különböző műfajú filmet különböztetünk meg: családi filmet, dokumentum filmet és egyéb kategóriába tartozó filmet.
 * Paraméterként átadjuk a függvénynek azokat az adatokat, amelyekkel létre tudunk hozni egy adott műfajú filmet. Lehetséges, hogy a megadott
 * 6 paraméter közül csak 4-et használunk (az egyéb műfajú filmek esetén), ilyenkor a többi paraméter dummy paraméter lesz. A függvény kezdetben létrehoz egy
 * új ListaElemre mutató pointert. Ezután el kell döntenünk, hogy az adott elem milyen filmet fog tárolni. Ehhez a megadott "g" paraméter segítségével meghatározzuk
 * a film műfaját, majd ez alapján hozunk létre egy új film objektumot (dinamikusan), amit rögtön a ListaElemhez adunk. Mivel egyszerre több film hozzáadása nem lehetséges, ezért a következő
 * ListaElemre mutató pointert NULL-ra állítjuk. Ezután, ha az eredeti lista elejére mutató pointer (eleje) NULL, akkor egyszerűen csak egyenlővé tesszük vele az "uj" pointert, hiszen ilyenkor
 * ezek megegyeznek. Egyéb esetben az eredeti lista végéhez adjuk az új létrehozott elemet.
 */
void Lista::add(string g, string t, unsigned int l, unsigned int d, unsigned int a, string c){

    ListaElem* uj = new ListaElem();

    if(g == "csaladi"){
        uj->fp = new FamilyMovie(g, t, l, d, a);
        uj->kov = nullptr;
    }
    else{
        if(g == "dokumentum"){
            uj->fp = new Documentary(g, t, l, d, c);
            uj->kov = nullptr;
        }
        else{
            uj->fp = new Movie(g, t, l, d);
            uj->kov = nullptr;
        }
    }

    if(eleje == nullptr){eleje = uj;}
    else{
        ListaElem* temp = eleje;
        while(temp->kov != nullptr){temp = temp->kov;}
        temp->kov = uj;
    }
}

/**
 * @details Ennek a tagfüggvénynek a segítségével tudjuk a lista dinamikusan foglalt részeit felszabadítani.
 * Egyszerűen csak végiglépkedünk a listán, majd felszabadítjuk a dinamikusan foglalt, ListaElem-ekben tárolt, film objektumokat, majd a szintén dinamikusan foglalt ListaElemeket is.
 * A felszabadítás végeztével a lista elejére mutató pointert NULL-ra állítjuk, ezzel jelezve, hogy a lista üres. 
 */
void Lista::felszab(){
    ListaElem* temp = eleje;

    while(temp != nullptr){
        ListaElem* kov = temp->kov;
        delete temp->fp;
        delete temp;
        temp = kov;
    }

    eleje = nullptr;
}

/**
 * @details Ennek a tagfüggvénynek a segítségével ki tudjuk íratni a lista tartalmát a képernyőre.
 * Ha a lista elejére mutató pointer NULL, akkor a lista üres. Egyéb esetben végiglépkedünk a listán, és
 * meghívjuk az elemek által tárolt film objektumok show() tagfüggvényét, amely a tényleges kiíratást végzi.
 */
void Lista::print(){

    if(eleje == nullptr){cout << "Az adatbazis ures.\n" << endl;}

    ListaElem* temp;

    unsigned int sorszam = 1;

    for(temp = eleje; temp; temp = temp->kov){
        cout << sorszam++ << ". ";
        temp->fp->show();
        cout << endl;
    }

    cout << endl;
}

/**
 * @details Ennek a tagfüggvénynek a segítségével egy, paraméterként megadott című filmet távolíthatunk el a listából.
 * Ha a lista üres, a függvény egyből visszatér, hiszen ilyenkor nincs mit kitörölni. Ha a lista legelső eleme az, amit ki kell törölni, akkor a 2. ListaElemre
 * mutató pointert elmentjük, majd felszabadítjuk az első elemet és az általa tárolt film objektumot is. Ezután a lista elejére mutató pointert egyenlővé tesszük
 * az elmentett pointerrel (ami most az első elem lett). Egyéb esetben végiglépkedünk a listán, majd, ha az adott elem által tárolt film objektum címe megegyezik a a paraméterként megadottal,
 * akkor felszabadítjuk mind a film objektumot, mind az azt tároló ListaElemet. Ebben az esetben az első két elem ponterét kell "megjegyeznünk". A "temp" pointer fog majd a törlendő elemre mutatni.
 * ha megtaláltuk az elemet, akkor összekapcsoljuk a törlendő ListaElem előtti és utáni elemeket, majd elvégezzük a törlést. Ha a listában nem szerepel a törölni kívánt film, akkor a függvény nem tesz semmit (visszatér).
 * A függvény értesíti a felhasználót, ha az adatbázis üres, a keresett című film nem található, illetve, ha a törlés sikeresen megtörtént.
 */
void Lista::remove(string m){
    
    if(eleje == nullptr){
        cout << "Az adatbazis ures." << endl;
        return;
    }

    if(eleje->fp->get_cim() == m){

        ListaElem* temp = eleje->kov;
        delete eleje->fp;
        delete eleje;

        eleje = temp;

        cout << "Sikeres torles." << endl;

        return;
    }

    ListaElem* temp = nullptr;
    ListaElem* elozo;

    for(temp = eleje->kov, elozo = eleje; temp; elozo = temp, temp = temp->kov){
        if(temp->fp->get_cim() == m){
            
            elozo->kov = temp->kov;
            delete temp->fp;
            delete temp;

            cout << "Sikeres torles." << endl;

            return;
        }
    }

    cout << "Az adatbazisban nem talalhato ilyen cimu film." << endl;

    return;
}

/**
 * @details Ennek a tagfüggvénynek a segítségével ki tudjuk íratni a paraméterként megadott című film(ek) adatait a képernyőre.
 * Először végiglépkedünk a listán, és, ha az aktuális ListaElem által tartalmazott film címe megegyezik a paraméterkén kapott címmel,
 * akkor meghívjuk a film objektum show() tagfüggvényét, amely a tényleges kiíratást végzi. Az iteráció során figyeljük, hogy volt-e 
 * egyezés; ha nem volt, akkor erről tájékoztatjuk a felhasználót.
 */ 
void Lista::search(string o){

    bool van = false;
    unsigned int sorszam = 1;

    ListaElem* temp;
    for(temp = eleje; temp; temp = temp->kov){
        if(temp->fp->get_cim() == o){

            cout << sorszam++ << ". ";
            temp->fp->show();
            cout << endl;

            van = true;
        }
    }

    if(!van){cout << "Nincs ilyen cimu film az adatbazisban.\n" << endl;}
}

/**
 * @details Ennek a tagfüggvénynek a segítségével ki tudjuk íratni a képernyőre a paraméterként megadott műfajú filmek címét.
 * Először végiglépkedünk a listán, és, ha az aktuális ListaElem által tartalmazott film műfaja megegyezik a paraméterkén kapott műfajjal, akkor
 * kiíratjuk az adott film címét. Az iteráció során figyeljük, hogy volt-e min. 1 egyezés; ha nem volt, akkor erről tájékoztatjuk a felhasználót.
 */
void Lista::filter(string h){

    bool van = false;
    unsigned int sorszam = 1;

    ListaElem* temp;
    for(temp = eleje; temp; temp = temp->kov){
        if(temp->fp->get_mufaj() == h){
            cout << sorszam++ << ". ";
            cout << temp->fp->get_cim() << "\n" << endl;
            van = true;
        }
    }

    if(!van){cout << "Nincs ilyen mufaju film az adatbazisban.\n" << endl;}
}

/**
 * @details Ennek a tagfüggvénynek a segítségével a lista tartalmát tudjuk kiírni egy fájlba.
 * A függvény egy tetszőleges nevű fájlt nyit meg (vagy hoz létre, ha korábban nem létezett), és tartalmát egyből el is dobja (nincs már rá szükség, hiszen a program elindítása után a read() függvény már beolvasta a fájl tartalmát).
 * Ha a fájl megnyitása során hiba lépett fel, azt jelezzük a felhasználónak, majd a program végrehajtása befejeződik. Egyéb esetben végiglépkedünk a listán, és meghívjuk az összes elem 
 * által tartalmazott film objektum print_in_file() tagfüggvényét, amely a tényleges fájlba való kiíratást végzi.
 */ 
void Lista::save(string filename){

    ofstream f(filename, ios_base::out | ios_base::trunc);

    if(!f.good()){
        felszab();
        throw "Hiba tortent az adatbazis mentese soran. A program kilep.";
    }

    ListaElem* temp;
    for(temp = eleje; temp; temp = temp->kov){
        temp->fp->print_in_file(f);
    }

    f.flush();
    f.close();
}

/**
 * @details Ennek a tagfüggvénynek a segítségével egy létező fájlból tudunk korábban kimentett adatokat visszaolvasni egy listába.
 * A függvény a fájl megnyitását követően ellenőrzi, hogy a művelet sikeres volt-e. Ha nem, akkor erről értesíti a felhasználót, majd befejezi a program végrehajtását.
 * Sikeres megnyitást követően a függvény ellenőrzi a megnyitott fájl tartalmát. Ha az üres, akkor nem tesz semmit, egyből visszatér.
 * Egyéb esetben a kurzort a fájl elejére mozgatjuk (hiszen a beolvasás kurzortól indul, és kiíratás után a kurzor a fájl végén marad). Ezután megkezdődik a beolvasás,
 * ami egészen a fájl végéig (EOF) tart. Minden egyes beolvasott filmet egy új ListaElemben tárolunk el. A film típusát az első beolvasott adattal (műfaj) döntjük el, majd ez alapján adjuk hozzá
 * a ListaElemhez dinamikus foglalással. Ezt követően a függvény az eredeti listához adja a kész listaelemet. Ha a lista üres, akkor az elejéhez adja, egyéb esetben pedig a végéhez fűzi az elemet.
 * Ha a beolvasás befejeződött, a függvény automatikusan visszatér. Fontos, hogy kiíratás során, az utolsó kiírt film után keletkezik egy üres sor. Annak érdekében, hogy ezt ne olvassuk be, minden
 * új sor beolvasása előtt leellenőrizzük, hogy az első adat a sorban üres sztring-e. Ha igen, akkor az adott sort kihagyjuk (break), és befejezzük a beolvasást.
 * 
 * @warning A film_database.txt fájl külső, hibás módosítása során (pl. egy családi filmnek nem írunk be korhatárt) hibák jelentkezhetnek.
 */ 
void Lista::read(string filename){

    ifstream f(filename, ios_base::in);

    if(!f.good()){
        throw "Hiba tortent az adatbazis beolvasasa soran. A program kilep.";
    }

    f.seekg(0, f.end);
    size_t size = f.tellg();
    if(size == 0){
        f.close();
        return;
    }

    string mufaj, cim, hossz, kiadas, leiras, korhatar;
    f.seekg(0, f.beg);

    while(!f.eof()){

        ListaElem* uj = new ListaElem();

        getline(f, mufaj, '\t');

        if(mufaj == ""){
            delete uj;
            break;
        }

        getline(f, cim, '\t');
        getline(f, hossz, '\t');

        if(mufaj == "csaladi"){
            getline(f, kiadas, '\t');
            getline(f, korhatar);

            uj->fp = new FamilyMovie(mufaj, cim, stoi(hossz), stoi(kiadas),stoi(korhatar));
            uj->kov = nullptr;
        }
        else{
            if(mufaj == "dokumentum"){
                getline(f, kiadas, '\t');
                getline(f, leiras);

                uj->fp = new Documentary(mufaj, cim, stoi(hossz), stoi(kiadas), leiras);
                uj->kov = nullptr;
            }
            else{
                getline(f, kiadas);

                uj->fp = new Movie(mufaj, cim, stoi(hossz), stoi(kiadas));
                uj->kov = nullptr;
            }
        }

        if(eleje == nullptr){
            eleje = uj;
        }
        else{
            ListaElem* mozgo = eleje;
            while(mozgo->kov != nullptr){
                mozgo = mozgo->kov;
            }
            mozgo->kov = uj;
        }
    }

    f.close();
}
