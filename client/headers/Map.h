#ifndef MAP_H
#define MAP_H

#include <QGraphicsItem>
#include <iostream>
/*!
 * \file Map.h
 * \brief Classe répresentant une carte
 * \author Roland.B
 */

#define MAP_SIZE 30                         /*!< Taille par defaut de la carte */
#define FREE 0                              /*!< Représente un espace libre*/
#define BLOCK 1                             /*!< Represente un block*/
#define AVATAR 2                            /*!< Représente un avatar*/
#define BULLET 3                            /*!< Représente une balle*/

using namespace std;

class Map{

private:
   quint32 _tab[30][30];                    /*!< Tableau 2D de quint32*/
public:
    /*!
       *\brief Constructeur par defaut d'une map
     */
    Map();
	/*!
        *\brief Constructeur par defaut d'une map avec parametre
        *\param quint32 tab[][]
        */
    Map(quint32 tab[30][30]);
	/*!
		*\brief Fonction qui retourne une valeur significative (0,1,2) d'une case de la map
        *\param int, int
		*/
    quint32 getValSig(int x, int y);
	/*!
        *\brief Fonction qui permet d'inserer un élément significatif à la Map
        *\param quint32,int,int
        *\return void
		*/
    void insererEltSig(quint32 elt,int x,int y);
	/*!
        *\brief Fonction qui supprime une valeur différente de 0 dans le tableau
        *\param int,int
        *\return void
		*/
    void deleteElt(int x,int y);
    /*!
        *\brief Fonction qui retourne la taille de la map
        *\return int
        */
    int getSize(){
        return MAP_SIZE;
    }
    /*!
      *\brief Seter qui permet la mise à jour du tableau 2D
      *\param quint32 tab[][]
      *\return void
      */
    void setTable(quint32 tab[30][30]);
};

#endif //MAP_H
