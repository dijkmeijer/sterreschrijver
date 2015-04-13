#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Novasextra.h"

double HMS_double(char *str)
{
    double D[3];
    char tmp[15];
    int i, j, n, it;
    n=0;
    j=0;
    it=0;
    int sign=1;
    tmp[0]='\0';
    i=it;
    while(str[it]==' ')
        it++;
    if(str[it]=='-'){
        sign=-1;
        it++;
    }
    for (i=it; i<= strlen(str); i++)
    {
        tmp[n++]=str[i];
        if((str[i]== ' ') || (str[i]== '\0'))
        {
            tmp[n]='\0';
            D[j++]=atof(tmp);
            n=0;
           // printf("%s - ", tmp);
        }
    }
  //  printf("\n");
    return sign*(D[0]+D[1]/60.+D[2]/3600.);

}

int fill_cat_entry(char *s, int t, cat_entry *star){
    strcpy(star->catalog, "HIP");
    star->radialvelocity=0.;
    switch(t){
        case 0: strcpy(star->starname, s); break;
        case 1: star->starnumber=atoi(s); break;
        case 2: star->ra=HMS_double(s); break;
        case 3: star->dec=HMS_double(s); break;
        case 4: star->promora=atof(s); break;
        case 5: star->promodec=atof(s); break;
        case 6: star->parallax=atof(s); break;
        }
return 0;
}

//int main(){return 0;}


/*
            strcpy(star.starname,"unknown");
            strcpy(star.catalog,"HIP");
            star.starnumber=atoi(HR.HIP);
            star.ra=atof(HR.RAdeg);
            star.dec=atof(HR.DEdeg);
            star.promora=atof(HR.pmRA);
            star.promodec=atof(HR.pmDE);
            star.parallax=atof(HR.Plx);
            star.radialvelocity=0.;

*/
