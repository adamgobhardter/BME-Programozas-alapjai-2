/**
 * \file test.cpp
 * 
 * Ez a fájl tartalmazza a teljes adatbázis teszteléséhez szükséges függvények definícióját.
 * Fontos, hogy a tesztelő függvények a megadott és feltöltött teszt adatbázissal (test_database.txt) operálnak. Helyes működésük csak ennek használatával garantált.
 * A tesztesetek csak abban az estben hajtódnak végre, ha a main.cpp fájlban a TESZT makró definiálva van.
 * A listából való törlés és a felszabadító függvény esetén a dinamikus memória felszabadításának sikerességét a Memtrace nevű, inkludált eszköz végzi, és a program végrehajtása után hibaüzenetet ad, amennyiben nem megfelelő működést tapasztalt.
 */ 

#include "gtest_lite.h"
#include "test.hpp"

using std::cout;
using std::endl;

/**
 * @details A függvény végigiterál a láncolt listán, és minden listaelemnél egy alapértelmezetten lenullázott számlálóhoz hozzáad egyet.
 */ 
int count(ListaElem *eleje){
    
    int db = 0;
    ListaElem *aktualis = eleje;
    
    while(aktualis != nullptr)
    {
        db += 1;
        aktualis = aktualis ->kov;
    }

    return db;
}

/**
 * @details A függvény megegyezik a Lista.cpp fájlban definiálttal. Az egyetlen különbség, hogy jelen esetben a függvény megszámlálja a megadott műfajjal megegyező
 * műfajú filmeket, ahelyett, hogy kiírná azok adatait.
 */ 
int filter_count(ListaElem* eleje, string h){

    int db = 0;

    ListaElem* temp;
    for(temp = eleje; temp; temp = temp->kov){
        if(temp->fp->get_mufaj() == h){
           ++db;
        }
    }

    return db;
}

/**
 * @details A függvény megegyezik a Lista.cpp fájlban definiálttal. Az egyetlen különbség, hogy jelen esetben a függvény megszámlálja a megadott címmel megegyező
 * című filmeket, ahelyett, hogy kiírná azok adatait.
 */ 
int search_count(ListaElem* eleje, string o){

    int db = 0;

    ListaElem* temp;
    for(temp = eleje; temp; temp = temp->kov){
        if(temp->fp->get_cim() == o){
            ++db;
        }
    }

    return db;
}

/**
 * @details Ellenőrizzük, hogy ősosztály, illetve a két származtatott osztály konstruktora helyesen működik-e.
 */ 
void test_0(){
    
    TEST(Test_0, konstruktor){
        Lista l2;
        EXPECT_EQ(l2.get_eleje(), nullptr) << "Nem jol mukodik a default konstruktor." << endl;

        Movie m;
        EXPECT_EQ("", m.get_mufaj()) << "Nem jol mukodik a default konstruktor (Movie)." << endl;
        EXPECT_EQ("", m.get_cim()) << "Nem jol mukodik a default konstruktor (Movie)." << endl;
        EXPECT_EQ(0, static_cast<int>(m.get_hossz())) << "Nem jol mukodik a default konstruktor (Movie)." << endl;
        EXPECT_EQ(0, static_cast<int>(m.get_kiadas())) << "Nem jol mukodik a default konstruktor (Movie)." << endl;

        FamilyMovie fm;
        EXPECT_EQ("", fm.get_mufaj()) << "Nem jol mukodik a default konstruktor (FamilyMovie)." << endl;
        EXPECT_EQ("", fm.get_cim()) << "Nem jol mukodik a default konstruktor (FamilyMovie)." << endl;
        EXPECT_EQ(0, static_cast<int>(fm.get_hossz())) << "Nem jol mukodik a default konstruktor (FamilyMovie)." << endl;
        EXPECT_EQ(0, static_cast<int>(fm.get_kiadas())) << "Nem jol mukodik a default konstruktor (FamilyMovie)." << endl;
        EXPECT_EQ(0, static_cast<int>(fm.get_korhatar())) << "Nem jol mukodik a default konstruktor (FamilyMovie)." << endl;

        Documentary d;
        EXPECT_EQ("", d.get_mufaj()) << "Nem jol mukodik a default konstruktor (Documentary)." << endl;
        EXPECT_EQ("", d.get_cim()) << "Nem jol mukodik a default konstruktor (Documentary)." << endl;
        EXPECT_EQ(0, static_cast<int>(d.get_hossz())) << "Nem jol mukodik a default konstruktor (Documentary)." << endl;
        EXPECT_EQ(0, static_cast<int>(d.get_kiadas())) << "Nem jol mukodik a default konstruktor (Documentary)." << endl;
        EXPECT_EQ("", d.get_leiras()) << "Nem jol mukodik a default konstruktor (Documentary)." << endl;

    }END
    cout << endl;
}

/**
 * @details Beolvasás után megszámláljuk, hogy mennyi elem található a listában. Ha az megegyezik a fájlban található filmek számával, akkor a tesztet sikeresnek tekintjük.
 */ 
void test_1(){

    TEST(Test_1, beolvasas){
        Lista l2;

        EXPECT_NO_THROW(l2.read("test_database.txt")) << "A read() fuggveny kivetelt dobott." << endl;
        
        int elvart = 25;
        int kapott = count(l2.get_eleje());

        EXPECT_EQ(elvart, kapott) << "Nem sikerult a fajlbol valo beolvasas." << endl;

        l2.felszab();
    }END
    cout << endl;
}

/**
 * @details Létrehozunk egy ideiglenes listát, amihez hozzáadunk 3 filmet, majd megszámláljuk a létrejött láncolt lista elemeinek számát.
 * Ezenkívül leellenőrizzük, hogy valóban azok az értékek kerültek-e be a listába, amiket szerettünk volna. Ha mindkét ellenőrzés sikeres, akkor a tesztet sikeresnek tekintjük.
 */ 
void test_2(){

    TEST(Test_2, hozzaadas){
    
        Lista l2;
        l2.add("csaladi", "Fogoly", 55, 1999, 12, "");
        l2.add("dokumentum", "Gogol", 85, 2000, 0, "Gogol elete");
        l2.add("vigjatek", "Lobonc", 105, 2001, 0, "");

        int elvart = 3;
        int kapott = count(l2.get_eleje());
        EXPECT_EQ(elvart, kapott) << "Nem sikerult a listahoz valo hozzaadas. 0" << endl;

        EXPECT_EQ("Fogoly", l2.get_eleje()->fp->get_cim()) << "Nem sikerul a listahoz valo hozzaadas. 1" << endl;
        EXPECT_EQ("dokumentum", l2.get_eleje()->kov->fp->get_mufaj()) << "Nem sikerul a listahoz valo hozzaadas. 2" << endl;
        EXPECT_EQ(105, static_cast<int>(l2.get_eleje()->kov->kov->fp->get_hossz())) << "Nem sikerült a listahoz valo hozzaadas. 3"; // Castolni kell, különben unsigned <--> int. 


        l2.felszab();
    }END
    cout << endl;
}

/**
 * @details Létrehozunk egy ideiglenes listát, amihez hozzáadunk 3 filmet, majd leellenőrizzük a 3 lehetséges törlési lehetőséget a megmaradt elemek értékeinek ellenőrzésével.
 */ 
void test_3(){

    TEST(Test_3, torles){

        Lista l2;
        l2.add("csaladi", "Fogoly", 55, 1999, 12, "");
        l2.add("dokumentum", "Gogol", 85, 2000, 0, "Gogol elete");
        l2.add("vigjatek", "Lobonc", 105, 2001, 0, "");

        l2.remove("Fogoly");    // Törlés az elejéről.
        EXPECT_EQ("dokumentum", l2.get_eleje()->fp->get_mufaj()) << "Hibas torles (eleje)." << endl;
        EXPECT_EQ(2, count(l2.get_eleje())) << "A torles nem sikerult (eleje)." << endl;
        
        l2.remove("Lobonc");    // Törlés a végéről.
        EXPECT_EQ(l2.get_eleje()->kov, nullptr) << "Hibas torles (vege)." << endl;
        EXPECT_EQ(1, count(l2.get_eleje())) << "A torles nem sikerult (vege)." << endl;

        l2.add("csaladi", "Fogoly", 55, 1999, 12, "");
        l2.add("vigjatek", "Lobonc", 105, 2001, 0, "");

        l2.remove("Fogoly");    // Törlés a közepéről.
        EXPECT_EQ(105, static_cast<int>(l2.get_eleje()->kov->fp->get_hossz())) << "Hibas torles (kozepe)." << endl; // Castolni kell, különben unsigned <--> int.
        EXPECT_EQ(2, count(l2.get_eleje())) << "A torles nem sikerult (kozepe)." << endl;
        
        l2.felszab();
    }END
    cout << endl;
}

/**
 * @details A módosított visszatérési értékű szűrő függvény segítségével megszámláljuk, hogy hány, a megadott műfajjal megegyező műfajú film szerepel a listában. Ha a kapott érték megegyezik
 * az elvárttal, akkor a tesztet sikeresnek tekintjük.
 */ 
void test_4(){

    TEST(Test_4, szures){
        
        Lista l2;

        EXPECT_NO_THROW(l2.read("test_database.txt")) << "A read() fuggveny kivetelt dobott" << endl;

        int elvart = 7; // Akcio filmek száma.
        int kapott = filter_count(l2.get_eleje(), "akcio");
        EXPECT_EQ(elvart, kapott) << "Nem sikerult megtalalni az osszes filmet." << endl;

        l2.felszab();
    }END
    cout << endl;
}

/**
 * @details A módosított visszatérési értékű kereső függvény segítségével megszámláljuk, hogy hány, a megadott címmel megegyező című film szerepel a listában. Ha a kapott érték megegyezik
 * az elvárttal, akkor a tesztet sikeresnek tekintjük.
 */ 
void test_5(){

    TEST(Test_5, kereses){
        
        Lista l2;

        EXPECT_NO_THROW(l2.read("test_database.txt")) << "A read() fuggveny kivetelt dobott." << endl;

        int elvart = 2; // "A vonat" című filmek száma.
        int kapott = search_count(l2.get_eleje(), "A vonat");
        EXPECT_EQ(elvart, kapott) << "Nem sikerult az osszes megadott cimu filmet megtalalni." << endl;

        l2.felszab();
    }END
    cout << endl;
}

/**
 * @details Egy ideiglenes listába beolvassuk a test_database.txt fájl tartalmát, majd hozzáadunk plusz egy elemet. Ezután a listát visszamentjük a test_database.txt fájlba.
 * Ha a következő beolvasásnál egyel több eleme lesz a listának, mint korábban, akkor a tesztet sikeresnek tekintjük.
 */ 
void test_6(){

    TEST(Test_6, kiiratas){
        
        Lista l2;

        EXPECT_NO_THROW(l2.read("test_database.txt")) << "A read() fuggveny kivetelt dobott." << endl;

        l2.add("alma", "korte", 120, 2006, 0, "");

        l2.save("test_database.txt");
        
        l2.felszab();

        EXPECT_NO_THROW(l2.read("test_database.txt")) << "A read() fuggveny kivetelt dobott." << endl;

        int db = count(l2.get_eleje());
        EXPECT_EQ(26, db) << "Hibas kiiratas fajlba." << endl;

        l2.remove("korte");

        l2.save("test_database.txt");

        l2.felszab();

    }END

    cout << endl;
}

/**
 * @details Létrehozunk egy ideiglenes üres listát, majd megpróbáljuk ebbe a listába egy nem létező fájl tartalmát beolvasni. Ha a read() függvény kivételt dob, akkor a tesztet sikeresnek tekintjük.
 */ 
void test_7(){

    TEST(Test_7, read_throw){
        
        Lista l2;
        try{
            l2.read("nonexistent.txt");
        
            EXPECT_THROW(cout << "Hiba tortent az adatbazis beolvasasa soran. A program kilep.", const char*) << "A read() fuggveny nem dobott kivetelt." << endl;
        }
        catch(const char*){}
        
    }END
    cout << endl;
}