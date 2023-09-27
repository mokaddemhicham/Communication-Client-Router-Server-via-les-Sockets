#ifndef CRC_H
#define CRC_H

extern char polyGenerateur[6];
extern char tmp[6];


/*************************************   calculerCRC  ******************************************

        la fonction `calculerCRC` permet de calculer le reste et l'ajouter à la fin de la trame a envoyer.
        Parametres : char * trame: la trame
 
*************************************************************************************************/

void calculerCRC(char * trame);

/*************************************   validerCRC  ******************************************

        cette fonction permet de verifier la validiter d'une trame reçu => (Trame valide ssi reste = 0).
        Parametres: char * trame: la trame
        elle renvoie 1 ssi la trame est valide (Reste = 0), renvoie 0 sinon.
     
*************************************************************************************************/

int validerCRC(char *trame);

/*************************************   operationXor  ******************************************

        le role de cette fonction est de calculer le xor de 5 premiers bits de PolyGenerateur
        et 5 bit du tmp est stoke le resultat dans tmp.
        elle prend comme parametre => char *polyGenerateur : le polynome génerateur , char * tmp : chaîne temporaire.
      
*************************************************************************************************/

void operationXor(char *polyGenerateur, char *tmp);

/***************************************   decalage  ********************************************

        cette fonction permet de decaler les bits par un bit et ajouter le bite suivant a la fin.
        Parametres : char* bitSuivant : le bit suivant , char * tmp : chaîne temporaire.
        
*************************************************************************************************/

void decalage(char *tmp, char bitSuivant);

/*******************************   obtenirMessageSansFanion  ***********************************

        l'objectif de cette fonction est de prendre le message du trame.
        Parametre : char * messageSansFanion: tableau de message ,
        int longueurMessage: la longeur du msg , char * trame: la trame
        
***********************************************************************************************/

void obtenirMessageSansFanion(char *messageSansFanion, int longueurMessage, char *trame);

/*******************************   multiplierParPolyGenerateur  ***********************************

        Cette fonction permet de multiplier le message par x^4.
        Parametres: char * messageSansFanion: tableau de message , int longueurMessage: la longeur du message
        
***********************************************************************************************/

void multiplierParPolyGenerateur(char *messageSansFanion, int longueurMessage);

/***************************************   diviser  ********************************************

        cette fonction permet de faire la division binaire modulo 2.
        Parametres : char *dividende: le dividende , char * trame : trame.
        
***********************************************************************************************/

void diviser(char *dividende, char *trame);

/************************************   verifierReste  ******************************************

        cette fonction permet de vérifier si le reste de la division = 0 ou non,
        elle prend en paramètre un tableau contient le reste de la division
        et elle compare chaque élément du tableau s'il = 0 ou non.
        Parametres : char *tmp: tableau contient le reste de la division
        renvoie = 1 si le reste = 0 et 0 sinon.
        
***********************************************************************************************/

int verifierReste(char *tmp);

/********************************   obtenirMessageAvecReste  ***********************************

        cette fonction permet de extraire le (message + reste de la division) du trame.
        Parametres : char * messageAvecReste : message + reste
        int messageLength :longeur du message , char * trame; la trame
      
***********************************************************************************************/

void obtenirMessageAvecReste(char *messageAvecReste, int longueurMessage, char *trame);

#endif

