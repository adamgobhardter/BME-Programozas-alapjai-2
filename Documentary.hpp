#ifndef DOCUMENTARY_HPP
#define DOCUMENTARY_HPP

/**
 * \file Documentary.hpp
 * 
 * Ez a fájl tartalmazza a Documentary származtatott osztály deklarációját, illetve az osztály tagfüggvényeinek definícióját is.
 */

#include "Movie.hpp"

/// Documetary származtatott osztály.
class Documentary : public Movie{
    
    string leiras;

    public:

        /// Alapértelmezett és paraméteres konstruktor.
        /// @param m - Műfaj megnevezése, alapértelmezett érték: üres sztring.
        /// @param c - Cím megnevezése, alapértelmezett érték: üres sztring.
        /// @param h - Hossz megadása, alapértelmezett érték: 0.
        /// @param k - Kiadás évének megadása. Alapértelmezett érték: 0.
        /// @param l - Leírás megadása. Alapértelmezett érték: üres sztring.
        explicit Documentary(string m = "", string c = "", unsigned int h = 0, unsigned int k = 0,  string l = "") : Movie(m, c, h, k), leiras(l) {}

        
        /// Leírás lekérdezése.
        /// @return Leírás.
        string get_leiras()const{return leiras;}
        
        /// Függvény, amely megjeleníti a Documentary típusú filmek alapadatait.
        void show(){
            Movie::show();
            std::cout << " " << leiras;
        }

        /// Függvény, amely kiírja a Documentary típusú filmek alapadatait a megadott stream-re.
        /// @param f - Stream, ahová az adatok kiírásra kerülnek (output stream referencia).
        void print_in_file(ofstream& f){
            f << get_mufaj() << "\t" << get_cim() << "\t" << get_hossz() << "\t" << get_kiadas() << "\t" << leiras << "\n";
        }
};

#endif // DOCUMENTARY_HPP
