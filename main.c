#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

typedef struct mynumber{
  uint64_t number;
  int tabnumber[1000];
  int taille;
   }mynumber;

uint64_t power(int n, int k){
  uint64_t pow=1;
  for(int i=0;i<k;i++)
    pow*=n;
  return pow;
}

void decalage(mynumber* tab, int rang){
  int i=rang-1,mataille=tab->taille;
  for (int j=mataille-1;j>=0;j--){
    tab->tabnumber[i]=tab->tabnumber[j];
    i--;
  }
  for(int j=0;j<(rang-mataille);j++) tab->tabnumber[j]=0;
  tab->taille=rang;
  
}
  
mynumber* convert(int nombre, mynumber* tab){
   tab=malloc(sizeof(mynumber));
 
  tab->number=nombre;
  
    div_t division=div(nombre,2);
    int valeur=division.quot;
   int i=0,taille=0;
   while (valeur!=0){
    tab->tabnumber[i]=division.rem;
    division=div(valeur,2);
    valeur=division.quot;
    i++;
    taille++;
  }
  tab->tabnumber[i]=division.rem;
  taille++;
  tab->taille=taille;
    int inter=0; int k=taille;
  for (int i=0;i<(taille/2);i++){
    inter=tab->tabnumber[i];
    tab->tabnumber[i]=tab->tabnumber[k-1];
    tab->tabnumber[k-1]=inter;
    k--;
    }

return tab;
}

uint64_t addition(mynumber* struct1, mynumber* struct2){
  if(struct1->taille>struct2->taille)
    decalage(struct2,struct1->taille);
   
  else if (struct2->taille>struct1->taille)
    decalage(struct1,struct2->taille);
  int ret=0; int l=0; int* result=malloc(1000*sizeof(int));
  for (int i=struct1->taille-1;i>=0;i--){
    int tmp=struct1->tabnumber[i]+struct2->tabnumber[i]+ret;
  if (tmp==2){
    result[l]=0;
    ret=1;
    l++;
  }
  else if(tmp==3){
    result[l]=1;
    ret=1;
    l++;
  }
  else {
    result[l]=tmp;
    l++;
    ret=0;
  }
  }
  if (ret==1) result[l]=1;
  struct1->taille=l+1;
  int k=l+1; uint64_t add=0;
   for(int i=k;i>=0;i--)
    add=add+result[i]*power(2,i);
  return add;
}

int main(int argc,char** argv){
  
  uint64_t a=0; uint64_t b=0;
  printf("donner les nombres\n");
  scanf("%lu %lu",&a,&b);
  mynumber* struct1=convert(a,struct1);
  mynumber* struct2=convert(b,struct2);
   uint64_t moi=addition(struct1,struct2);
   printf("la somme vaut %lu \n",moi);
  
  return 0;
}

    
