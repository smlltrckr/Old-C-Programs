/**********************************************
A class has up to 50 students. There are up
to 10 candidates numbered from 0 to 9 (use
these numbers instead of names for now).
One class might have 43 students and 5
candidates, another class might have 32
students and 6 candidates, etc. The data
file contains numbers from 0 to 9, each one
representing one vote for that candidate,
as shown below. Assume that each candidate
gets at least one vote.

0 3 3 2 3 0 4 2 4 4 2 0 0 0 4 2 3 3 3 3 0
2 0 0 1 1 1 2 3 4 4 0 3 4 0 0 3 3 4 4 4 4 0

Write to another file the number of students
in the class and the number of candidates
followed by the list of candidates, the
number of votes each received, and the
percentage of the total vote each received
sorted (SELECTION SORT) in order from the
winner to the person with the fewest votes.

Written by: Sam Rucker
Date......: 1/16/2013

**********************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 50
#define MAX_CAND 10

void strtElec (void);

int countVotes (int votes[]);

int sortVotes (int votes [], int cnd[], int vt [], int stud);

void wrtRes (int cnd[], int vt[], int stud, int cnt);

void endElec (void);

int main ( void )
{
//  Local Declarations
    int votes [MAX_ELEMENTS];
    int cnd[MAX_CAND] = {0};
    int vt[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int stud, cnt;

//  Statements
    strtElec ();
    stud = countVotes (votes);
    cnt = sortVotes (votes, cnd, vt, stud);
    wrtRes (cnd, vt, stud, cnt);
    endElec ();

    return 0;
}

void strtElec ()
{
//  Statements
    printf ("CIS15BG HW 1\nBy: Sam Rucker\n");
    printf ("Lets tally the votes\n");

    return;
}

int countVotes (int votes[])
{
//  Local Declarations
    FILE* fpBallot;
    int i = 0;
    int tly;

//  Statements
    fpBallot = fopen ("VOTES.TXT", "r");

    if (fpBallot == NULL)
    {
        printf("The file could not be read\n");
        exit(100);
    }

    while (i < (MAX_ELEMENTS - 1) && fscanf (fpBallot, "%d ", &tly) != EOF)
    {
        votes[i] = tly;
        i++;
    }

    return i;
}

int sortVotes (int votes [], int cnd[], int vt [], int stud)
{
//  Local Declarations
    int cur, wall, sml, tmp;
    int a, b, cntr, rnr;
    int big, c, sccur;
    int sctmp, nmtmp;


//  Statements
    for (wall = 0; wall < stud - 1; wall++)
    {
        sml = wall;
        for (cur = wall + 1; cur < stud; cur++)
        {
            if (votes [cur] > votes [sml])
            {
                sml = cur;
            }// if
        }// for

        tmp = votes [wall];
        votes [wall] = votes [sml];
        votes [sml] = tmp;
    }//for

    for (a = 0, b = 0, cntr = 0, rnr = 1; a < stud; a++)
    {
        if (votes [a] != votes[a + 1])
        {
            cnd[b] = rnr;
            rnr = 1;
            b++;
            cntr++;
        }//if
        else
        {
            rnr++;
        }//else
    }//for

    for (c = 0; c < cntr; c++)
    {
        big = c;
        for (sccur = big + 1; sccur < cntr; sccur++)
        {
            if (cnd [sccur] > cnd [c])
            {
                big = sccur;
            }//if
        }//for

        sctmp = cnd [big];
        nmtmp = vt [big];
        cnd [big] = cnd [c];
        vt [big] = vt [c];
        cnd [c] = sctmp;
        vt [c] = nmtmp;
    }//for

    return cntr;
}

void wrtRes (int cnd[], int vt[], int stud, int cnt)
{
//  Local Declarations
    FILE* fpResults;
    int d;
    double pct;

//  Statements
    fpResults = fopen ("ELECTION.TXT", "w");

    if (fpResults == NULL)
    {
        printf("Could not write to file!\n");
        exit(100);
    }

    fprintf(fpResults, "Number of students..: %d\n", stud);
    fprintf(fpResults, "Number of candidates: %2d\n", cnt);

    for (d = 0; d < cnt; d++)
    {
        pct = (cnd [d] / (double)stud) * 100;
        fprintf (fpResults, "Candidate Number %d:", vt[d]);
        fprintf (fpResults, "Votes Recieved: %3d Percentage: %5.2lf\n", cnd[d], pct);
    }

    fclose (fpResults);

    return;
}

void endElec (void)
{
//  Statements
    printf ("The tally has been completed");

    return;
}
/****************************************************
Results:
CIS15BG HW 1
By: Sam Rucker
Lets tally the votes
The tally has been completed
****************************************************/
