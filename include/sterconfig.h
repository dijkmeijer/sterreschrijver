#ifndef STERCONFIG_H
#define STERCONFIG_H


class sterconfig
{
    public:
        /** Default constructor */
        sterconfig();
        /** Default destructor */
        virtual ~sterconfig();
        int ster; // hip nr van de ster
        int jaar; // datum
        int maand;// datum
        int dag;// datum
        int uur;// datum
        double minute;// datum
        double locatie_alt;
        double locatie_lon;
        double motorstand_x; // positie van de motor x richting
        double motorstand_y; // positie van de motor x richting
        double belichtingstijd;
        int stappen; // aantal stappen in de beweging
        char DXFfile[265];
        double beeldbreedte;
        double beeldhoogte;
        double brandpuntafstand;

    protected:
    private:
};

#endif // STERCONFIG_H
