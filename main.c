#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct mynumber{
  unsigned long number;
  int* tabnumber;
} mystruct;

mystruct tab={0,NULL};
  
mystruct convert(unsigned long number, mystruct mynumber){
  int valeur,taille=0;
  mynumber.number=number;
  mynumber.tabnumber=malloc(sizeof(int));
  div_t division=div(number,2);
  valeur=division.quot;
  int i=0;
  while (valeur!=0){
    mynumber.tabnumber[i]=division.rem;
    division=div(valeur,2);
    valeur=division.quot;
    i++;
    taille++;
  }
  mynumber.tabnumber[i]=division.rem;
  taille++;
  int inter=0, k=taille;
  for (int i=0;i<(taille/2);i++){
    inter=mynumber.tabnumber[i];
    mynumber.tabnumber[i]=mynumber.tabnumber[k-1];
    mynumber.tabnumber[k-1]=inter;
    k--;
  }
  printf("\n le nombre d'élément est: %d\n ",taille);
  for (int j=0;j<taille;j++) printf("%d  ",mynumber.tabnumber[j]);
  return mynumber;
}
    
int main(){
  
  convert(14.0,tab);
  return 0;
}

    
