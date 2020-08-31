#ifndef FAMILYMOVIE_HPP
#define FAMILYMOVIE_HPP

/**
 * \file FamilyMovie.hpp
 * 
 * Ez a fájl tartalmazza a FamilyMovie származtatott osztály deklarációját és az osztály tagfüggvényeinek definícióját is.
 */

#include "Movie.hpp"

/// FamilyMovie származtatott osztály.
class FamilyMovie : public Movie{
    
    unsigned int korhatar;

    public:

        /// Alapértelmezett és paraméteres konstruktor.
        /// @param m - Műfaj megnevezése, alapértelmezett érték: üres sztring.
        /// @param c - Cím megnevezése, alapértelmezett érték: üres sztring.
        /// @param h - Hossz megadása, alapértelmezett érték: 0.
        /// @param k - Kiadás évének megadása. Alapértelmezett érték: 0.
        /// @param kor - Korhatár megadása. Alapértelmezett érték: 0.
        explicit FamilyMovie(string m = "",  string c = "", unsigned int h = 0, unsigned int k = 0, unsigned int kor = 0) : Movie(m, c, h, k), korhatar(kor) {}

        /// Korhatár lekérdezése.
        /// @return Korhatár.
        unsigned int get_korhatar()const{return korhatar;}
        
        /// Függvény, amely megjeleníti a FamilyMovie típusú filmek alapadatait.
        void show(){
            Movie::show();
            std::cout << " " << korhatar;
        }

        /// Függvény, amely kiírja a FamilyMovie típusú filmek alapadatait a megadott stream-re.
        /// @param f - Stream, ahová az adatok kiírásra kerülnek (output stream referencia).
        void print_in_file(ofstream& f){
            f << get_mufaj() << "\t" << get_cim() << "\t" << get_hossz() << "\t" << get_kiadas() << "\t" << korhatar << "\n";
        }
};

#endif // FAMILYMOVIE_HPP
