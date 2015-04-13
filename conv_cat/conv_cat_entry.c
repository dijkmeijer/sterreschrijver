#include <stdio.h>
#include <stdlib.h>
#include <novas.h>
#include <Novasextra.h>



int main()
{
    star_rec star;
    FILE *fp;
    FILE *ofp;
    int rec_count=0;
    int fieldcount=0;
    int i = 0;
    char s_tmp[50];
    char c;
    fp=fopen("cat_entry.txt", "r");
    ofp=fopen("cat_entry.cat", "wb");

    while ('$' != (c = fgetc(fp)))
    {
		if (ferror(fp) != 0)
		exit(0);
		printf("%c%d", c, ferror(fp));
        if(c!='\n' && c!='\t')
            s_tmp[i++] = c;
        else
        {
            s_tmp[i]='\0';
            i=0;
            fill_cat_entry(s_tmp, fieldcount, &star.star);
            if(fieldcount==7)
                star.Vmag=atof(s_tmp);
            fieldcount++;
            if (fieldcount==8)
            {
                fieldcount=0;
                fwrite(&star, sizeof(star_rec), 1, ofp);
                printf("%s\t%s\t%10ld\t%8.4f\t%8.4f\t%10.4f\t%10.4f\t%8.4f\n",
                      star.star.starname, star.star.catalog, star.star.starnumber, 
					  star.star.ra, star.star.dec, star.star.promora, star.star.promodec, star.star.parallax);
                rec_count++;
            //    fwrite(&star, sizeof(cat_entry), 1, ofp);
            }
        }




    }
    fclose(fp);
    fclose(ofp);
    printf("aantal records: %d\n", rec_count);
    return 0;
}
