#ifndef MOVIE_HPP
#define MOVIE_HPP

/**
 * \file Movie.hpp
 * 
 * Ez a fájl tartalmazza a Movie ősosztály deklarációját, illetve az osztály tagfüggvényeinek definícióját.
 */

#include <iostream>
#include <fstream>

using std::string;
using std::ofstream;

/// Movie alaposztály.
class Movie{

    string mufaj, cim;
    unsigned int hossz, kiadas;

    public:

        /// Alapértelmezett és paraméteres konstruktor.
        /// @param m - Műfaj megnevezése, alapértelmezett érték: üres sztring.
        /// @param c - Cím megnevezése, alapértelmezett érték: üres sztring.
        /// @param h - Hossz megadása, alapértelmezett érték: 0.
        /// @param k - Kiadás évének megadása. Alapértelmezett érték: 0.
        explicit Movie(string m = "", string c = "", unsigned int h = 0, unsigned int k = 0) : mufaj(m), cim(c), hossz(h), kiadas(k) {}
        
        /// Virtuális destruktor az öröklés miatt.
        virtual ~Movie() {}

        /// Cím lekérdezése.
        /// @return Cím.
        string get_cim()const{return cim;}

        /// Műfaj lekérdezése.
        /// @return Műfaj. 
        string get_mufaj()const{return mufaj;}
        
        /// Hossz lekérdezése.
        /// @return Hossz.
        unsigned int get_hossz()const{return hossz;}
        
        /// Kiadás lekérdezése.
        /// @return Kiadás.
        unsigned int get_kiadas()const{return kiadas;}

        /// Virtuális függvény, amely megjeleníti a Movie típusú filmek alapadatait.
        virtual void show(){
            std::cout << mufaj  << " " << cim << " " << hossz << " " << kiadas; 
        }

        /// Virtuális függvény, amely kiírja a Movie típusú filmek alapadatait a megadott stream-re.
        /// @param f - Stream, ahová az adatok kiírásra kerülnek (output stream referencia).
        virtual void print_in_file(ofstream& f){
            f << mufaj << "\t" << cim << "\t" << hossz << "\t" << kiadas << "\n";
        }
};

#endif // MOVIE_HPP