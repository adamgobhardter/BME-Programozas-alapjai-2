#ifndef LISTA_HPP
#define LISTA_HPP

/**
 * \file Lista.hpp
 * 
 * Ez a fájl tartalmazza a Lista és ListaElem osztályok deklarációját, illetve a Lista osztály tagfüggvényeinek deklarációját.
 */   

#include "memtrace.h"

#include "Movie.hpp"
#include "FamilyMovie.hpp"
#include "Documentary.hpp"

/// Osztály, amely a láncolt listának egy-egy elemét képviseli.
class ListaElem{

    public:

        Movie* fp;
        ListaElem* kov;
};

/// A láncolt listát megvalósító osztály.
class Lista{
    ListaElem* eleje;

    public:
        
        /// Alapértelmezett konstruktor, amely egy üres listát hoz létre.
        Lista() : eleje(nullptr) {}

        /// A láncolt lista elejének lekérdezése.
        /// @return A láncolt lista elejére mutató pointer.
        ListaElem* get_eleje()const{return eleje;}

        /// @brief Új elem hozzáadása a láncolt listához.
        /// @param g - Műfaj megnevezése.
        /// @param t - Cím megnevezése.
        /// @param l - Hossz megadása.
        /// @param d - Kiadás évének megadása.
        /// @param a - Korhatár megadása. Alapértelmezett érék 0.
        /// @param c - Leírás megadása.
        void add(string g, string t, unsigned int l, unsigned int d, unsigned int a, string c);

        /// @brief A láncolt lista felszabadítása.
        void felszab();

        /// @brief A láncolt lista elemek adatainak kiíratása. 
        void print();

        /// @brief Egy megadott című film kitörlése a láncolt listából.
        /// @param m - Cím megadása.
        void remove(string m);

        /// @brief Egy megadott című film megkeresése a láncolt listában, majd adatainak kiíratása.
        /// @param o - Cím megadása.
        void search(string o);

        /// @brief A láncolt listában megtalálható, megadott műfajú filmek címének kilistázása.
        /// @param h - Műfaj megadása.
        void filter(string h);

        /// @brief A láncolt lista elemek adatainak kiíratása fájlba.
        /// @param filename - A fájl neve, ahová az adatokat menteni szeretnénk. 
        void save(string filename);

        /// @brief Korábban kimentett láncolt lista elemek visszaolvasása láncolt listába.
        /// @param filename - A fájl neve, ahonnan az adatokat be szeretnénk olvasni.
        void read(string filename);
};

#endif //LISTA_HPP
