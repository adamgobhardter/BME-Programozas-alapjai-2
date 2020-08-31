#ifndef TEST_HPP
#define TEST_HPP

/**
 * \file test.hpp
 * 
 * Ez a fájl tartalmazza a teszteléshez szükséges függvények deklarációit.
 */ 

#include <iostream>
#include "Lista.hpp"

/**
 * @brief A láncolt lista elemeinek megszámlálására szolgáló függvény.
 * @param eleje - A lista első elemére mutató pointer.
 * @return A láncolt listában tárolt elemek száma.
 */ 
int count(ListaElem* eleje);

/**
 * @brief Megszámlálja a listában található, paraméterként megadott műfajjal megegyező műfajú filmeket.
 * @param eleje - A lista első elemére mutató pointer.
 * @param h - A keresett műfaj.
 * @return A láncolt listában tárolt, megadott műfajú filmek száma.
 */ 
int filter_count(ListaElem* eleje, string h);

/**
 * @brief Megszámlálja a listában található, paraméterként megadott címmel megegyező című filmeket.
 * @param eleje - A lista első elemére mutató pointer.
 * @param o - A keresett cím.
 * @return A láncolt listában tárolt, megadott című filmek száma.
 */ 
int search_count(ListaElem* eleje, string o);

/**
 * @brief A Lista osztály alapértelmezett konstruktorának tesztelése.
 */ 
void test_0();

/**
 * @brief A fájlból való beolvasás sikerességének tesztelése.
 */ 
void test_1();

/**
 * @brief A listához való hozzáadás sikerességének tesztelése.
 */ 
void test_2();

/**
 * @brief A listából való törlés sikerességének tesztelése.
 */ 
void test_3();

/**
 * @brief A megadott műfajú filmek kiszűrésének tesztelése.
 */ 
void test_4();

/**
 * @brief Megadott című filmek keresésének tesztelése.
 */ 
void test_5();

/**
 * @brief A fájlba való kiíratás sikerességének tesztelése.
 */ 
void test_6();

/**
 * @brief A read() függvény kivétel dobásának ellenőrzése.
 */ 
void test_7();

#endif // TEST_HPP