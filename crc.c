#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "crc.h"

/* Polynome Generateur: x^4+x+1 */
char polyGenerateur[6]= "10110";
char tmp[6] ="";


void operationXor(char *polyGenerateur, char * tmp){
	for(int i = 0 ; i<5;i++){
		if(tmp[i]==polyGenerateur[i] ){
			tmp[i] = '0';
		}
		else{
			tmp[i] = '1';
		}
	}
}

void obtenirMessageSansFanion(char * messageSansFanion,int longueurMessage,char * trame){
     
    for(int i=0; i<longueurMessage ;i++){ // 8*6 = 48 bits
            messageSansFanion[i] = trame[8*3+i];
     }
}

void multiplierParPolyGenerateur(char * messageSansFanion,int longueurMessage){
    
    for(int i =longueurMessage;i<longueurMessage+4;i++ ){
		messageSansFanion[i] ='0';
    }
}

void decalage(char *tmp, char bitSuivant){
   
	for(int i=0; i<4;i++){
		tmp[i] = tmp[i+1];
	}
	tmp[4] = bitSuivant;
}

void diviser(char *dividende,char * trame){
    
	for(int i=0; i<5;i++){
		tmp[i] = trame[i]; 
		//tmp : cette variable prend les 5 premiers bits de la trame sans Fanion, pour la division avec le PolyneGenerator
	}
	tmp[5]='\0';
	for(int i=0;i< strlen(dividende)-strlen(tmp) ;i++){
		if(tmp[0]=='0'){
			decalage(tmp,dividende[5+i]);
		}
		else {
			operationXor(polyGenerateur,tmp);
			decalage(tmp,dividende[5+i]);
		}}
	if(tmp[0]=='1'){
		operationXor(polyGenerateur,tmp);

	}
	// Alors nous avons le reste de la division srocker dans la variable tmp
}

void obtenirMessageAvecReste(char * messageAvecReste,int messageLength,char * trame){
        
        for(int i=0;i<28;i++){
            if(i<messageLength){
                messageAvecReste[i] = trame[8*3+i];// 8*3 pour passer les 3 octets (fanion ,@dest,cmd)
            }
        }
        messageAvecReste[24]=trame[8*6+4];
        messageAvecReste[25]=trame[8*6+5];
        messageAvecReste[26]=trame[8*6+6];
        messageAvecReste[27]=trame[8*6+7];
        messageAvecReste[28] = '\0';

}
	
int validerCRC(char *trame){
    
	char messageAvecReste[29];
	int messageLength = 24;
    	obtenirMessageAvecReste(messageAvecReste,messageLength,trame);
	diviser(messageAvecReste,trame);
	printf("\nTrame Recu : \n  Reste  : %s \n  Message Avec Reste : %s \n",tmp, messageAvecReste);
	return verifierReste(tmp);
}

int verifierReste(char *tmp){
	for(int i =0;i<5;i++){
		if(tmp[i]!='0')return 0;
	}
	return 1;
}

void calculerCRC(char * trame){

    char messageSansFanion[8*3+1+4]; // 8*6 + \0 = 49  || +4 bits (X^4 * messageSansFanion)
    int longueurMessage = 3*8;// 3*8 longueurMessage
    messageSansFanion[8*3]='\0';
    
    obtenirMessageSansFanion(messageSansFanion,longueurMessage,trame);
    
    multiplierParPolyGenerateur(messageSansFanion,longueurMessage);
    
    messageSansFanion[longueurMessage+4]='\0';
    
    printf("\nMessage sans Fanion : %s \n", messageSansFanion);
    diviser(messageSansFanion,trame);
	printf("Trame Envoye : \n  Reste  : %s \n  Message sans Fanion : %s \n",tmp, messageSansFanion);
	for(int i = 0;i<4;i++){
		trame[48+4+i]=tmp[i+1] ;
	}
	printf("\nLe message qui doit etre envoye : %s \n",trame);
}
