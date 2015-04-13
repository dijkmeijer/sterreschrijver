#ifndef _NOVAS_EXTRA
#define _NOVAS_EXTRA

#include <novas.h>

typedef struct
{
    cat_entry star;
    double Vmag;
} star_rec;

double HMS_double(char *str);
int fill_cat_entry(char *s, int t, cat_entry *star);

#endif
