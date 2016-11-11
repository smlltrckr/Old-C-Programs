/***************************************************************
    This program will produce a sales chart for a company.
        Written by: Sam Rucker
        Date: 10/18/12
****************************************************************/
#include <stdio.h>

#define beap  325.00
#define cesp  127.50
#define aubp  18.95

int main ( void )
{
//Local Definitions
        char    L1;
        char    L2;
        char    LR1;
        char    LR2;

        double  unitbea1;
        double  unitces1;
        double  unitaub1;

        double  unitbea2;
        double  unitces2;
        double  unitaub2;

        double  ttlbea;
        double  ttlces;
        double  ttlaub;

        double  gsbea;
        double  gsces;
        double  gsaub;
        double  cpdbea;
        double  cpdces;
        double  cpdaub;

        const double beacom = 22;
        const double cescom = 15;
        const double aubcom = 20;

//Statements
    //Getting Data (input)
        printf  ("What is your sales region?\n\n");
        scanf   (" %c%c", &L1, &L2);
        printf  ("How many Basic Encylopedia were sold?\n\n");
        scanf   ("%lf", &unitbea1);
        printf  ("How many Child Supplements were sold?\n\n");
        scanf   ("%lf", &unitces1);
        printf  ("How Many Annual Updates were sold?\n\n");
        scanf   ("%lf", &unitaub1);

        printf  ("What is your sales region?\n\n");
        scanf   (" %c%c", &LR1, &LR2);
        printf  ("How many Basic Encylopedia were sold?\n\n");
        scanf   ("%lf", &unitbea2);
        printf  ("How many Child Supplements were sold?\n\n");
        scanf   ("%lf", &unitces2);
        printf  ("How Many Annual Updates were sold?\n\n");
        scanf   ("%lf", &unitaub2);
    //Calculations
        ttlbea  =   unitbea1 + unitbea2;
        ttlces  =   unitces1 + unitces2;
        ttlaub  =   unitaub1 + unitaub2;

        gsbea   =   ttlbea * beap;
        gsces   =   ttlces * cesp;
        gsaub   =   ttlaub * aubp;

        cpdbea  =   gsbea * beacom / 100;
        cpdces  =   gsces * cescom / 100;
        cpdaub  =   gsaub * aubcom / 100;



    //Print Section (output)
        printf  ("                            MONTHLY SALES CHART\n\n");

        printf  ("                      Basic         Child     Annual\n");

        printf  ("      Region      Encyclopedia    Supplement  Update\n\n");

        printf  ("Units sold  %c%c         %3.0lf         %3.0lf         %3.0lf\n",
                    L1, L2, unitbea1, unitces1, unitaub1);

        printf  ("(by region) %c%c         %3.0lf         %3.0lf         %3.0lf\n",
                    LR1, LR2, unitbea2, unitces2, unitaub2);

        printf  ("                      -----       -----       -----\n");

        printf  ("Total units sold:      %3.0lf         %3.0lf         %3.0lf\n\n",
                    ttlbea, ttlces, ttlaub);

        printf  ("Price/unit:           $%6.2lf     $%6.2lf     $%6.2lf\n",
                    beap, cesp, aubp);

        printf  ("Gross Sales:       $%9.2lf  $%9.2lf  $%9.2lf\n",
                    gsbea, gsces, gsaub);

        printf  ("Commission rate:        %2.0lf%%         %2.0lf%%         %2.0lf%%\n",
                    beacom, cescom, aubcom);

        printf  ("Commission paid:    $%8.2lf   $%8.2lf   $%8.2lf  ",
                    cpdbea, cpdces, cpdaub);
    return 0;
}
/***************************************************************************************
    Output Test 1
What is your sales region?

CA
How many Basic Encylopedia were sold?

150
How many Child Supplements were sold?

120
How Many Annual Updates were sold?

105
What is your sales region?

TX
How many Basic Encylopedia were sold?

225
How many Child Supplements were sold?

200
How Many Annual Updates were sold?

150
                            MONTHLY SALES CHART

                      Basic         Child     Annual
      Region      Encyclopedia    Supplement  Update

Units sold  CA         150         120         105
(by region) TX         225         200         150
                      -----       -----       -----
Total units sold:      375         320         255

Price/unit:           $325.00     $127.50     $ 18.95
Gross Sales:       $121875.00  $ 40800.00  $  4832.25
Commission rate:        22%         15%         20%
Commission paid:    $26812.50   $ 6120.00   $  966.45

*******************************************************************************************
    Output Test 2
What is your sales region?

AZ
How many Basic Encylopedia were sold?

160
How many Child Supplements were sold?

100
How Many Annual Updates were sold?

95
What is your sales region?

IL
How many Basic Encylopedia were sold?

140
How many Child Supplements were sold?

110
How Many Annual Updates were sold?

80
                            MONTHLY SALES CHART

                      Basic         Child     Annual
      Region      Encyclopedia    Supplement  Update

Units sold  AZ         160         100          95
(by region) IL         140         110          80
                      -----       -----       -----
Total units sold:      300         210         175

Price/unit:           $325.00     $127.50     $ 18.95
Gross Sales:       $ 97500.00  $ 26775.00  $  3316.25
Commission rate:        22%         15%         20%
Commission paid:    $21450.00   $ 4016.25   $  663.25
Process returned 0 (0x0)   execution time : 16.115 s
Press any key to continue.
*/
