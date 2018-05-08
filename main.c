#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <omp.h>

typedef struct mynumber{
  uint64_t number;
  int tabnumber[30000];
  int taille;
   }mynumber;

uint64_t power(int n, int k){

  uint64_t pow=1;
    #pragma omp parallel for
  for(int i=0;i<k;i++)
    pow*=n;
  return pow;
}

void decalage_droite(mynumber* tab, int rang){
  int i=rang-1,mataille=tab->taille;
  for (int j=mataille-1;j>=0;j--){
    tab->tabnumber[i]=tab->tabnumber[j];
    i--;
  }
  for(int j=0;j<(rang-mataille);j++) tab->tabnumber[j]=0;
  tab->taille=rang;
  
}
  
mynumber* convert(uint64_t nombre, mynumber* tab){
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
#pragma omp parallel
  if(struct1->taille>struct2->taille)
    decalage_droite(struct2,struct1->taille);
   
  else if (struct2->taille>struct1->taille)
    decalage_droite(struct1,struct2->taille);
 
  int ret=0; int l=0; int* result=malloc(1000*sizeof(int));
#pragma omp parallel for firstprivate(ret,l,result)
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
   #pragma omp barrier
  return add;
}


uint64_t  produit_un_chiffre(mynumber* tab,int n){
  int t[tab->taille]; int l=0;
  for (int i=tab->taille-1;i>=0;i--){
    t[i]=tab->tabnumber[i]*n;
    l++;
  }
  uint64_t prod=0; int  poids=tab->taille-1;
  for(int j=0;j<tab->taille;j++){
    prod=prod+t[j]*power(2,poids-j);
  }
  return prod;
}


uint64_t produit_total(mynumber* tab1, mynumber* tab2){
  int** tab=malloc(sizeof(int*)*tab2->taille);
  mynumber** t1=malloc(sizeof(mynumber*));
  uint64_t produit=0; int decale=0;

  for( int i=tab2->taille-1;i>=0;i--)
    {
      int size=0;
      mynumber* p=malloc(sizeof(mynumber));
      t1[i]=malloc(sizeof(mynumber)*20);
      uint64_t masse=produit_un_chiffre(tab1,tab2->tabnumber[i]);
      printf("le nombre est %lu\n ",masse);
     mynumber* q=convert(masse,p);
     
       t1[i]=q;
       printf("la taille de q est %d ",q->taille);
       printf("avant changement taille %d \n",t1[i]->taille);
         for (int j=0;j<t1[i]->taille;j++)
	      printf("%d ", t1[i]->tabnumber[j]);
	  printf("\n");
     
    
       if (i>0)
	 {
	   size=t1[i]->taille+decale;
	   printf("taille decalage %d\n",size);
	     t1[i]->taille=t1[i]->taille+decale;
	     for(int m=1;m<=decale;m++)
	   t1[i]->tabnumber[size-1+m]=0; 
	 }
       else size=t1[i]->taille;
       printf("apres changement la taille est %d et le pas %d \n",size,decale);
         for (int j=0;j<size;j++)
	      printf("%d ", t1[i]->tabnumber[j]);
	  printf("\n");
      
       free(p);
       free(q);
       decale++;
    }
    
       for(int i=0;i<tab2->taille-2;i++)
	   
	     produit=produit+addition(t1[i],t1[i+1]);
      
  return produit;
}

uint64_t substract(mynumber* tab1, mynumber* tab2){
  decalage_droite(tab2,tab1->taille);
  int ret=0,l=0,tmp=0;  int* result=malloc(1000*sizeof(int));
   for (int i=tab1->taille-1;i>=0;i--){
    
    tmp=tab1->tabnumber[i]-tab2->tabnumber[i]-ret;
    if(tmp<=-1){
      tmp=1;
      ret=1;
    }
    result[l]=tmp;
    l++;
	}
   if (tmp==1) result[l+1]=tmp;
    int k=l+1; uint64_t sub=0;
   for(int i=k;i>=0;i--)
    sub=sub+result[i]*power(2,i);
  return sub;
}

int main(int argc,char** argv){
  
  uint64_t a=0; uint64_t b=0;
  printf("donner les nombres\n");
  scanf("%lu %lu",&a,&b);
  mynumber* struct1=convert(a,struct1);
  mynumber* struct2=convert(b,struct2);
  uint64_t prod=produit_total(struct1,struct2);
  printf("\n");
  //  printf("le produit vaut %lu\n",prod);
  uint64_t moi=addition(struct1,struct2);
  printf("\n la somme vaut %lu \n",moi);  
  return 0;
}

    
