
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "lab2.h"
#include "lab2_funcs.h"
//#include "lab2_funcs.c"
matlab_arr_t arrs[6];
matlab_var_t vars[6];
int processLine(char line[50]);
int main(int argc, char *argv[])
{
    //Sätt strukt-variabler till pointers för att ge tillgång till deras värden i andra funktioner
    //Allokera minne till att sätta deras värden
    //Sen sätt dem i arrs[] eller vars[] så vi kan hitta dem, och för lättare hantering
    matlab_arr_t *A, *B, *C, *R, *X, *Y;
    A = malloc(sizeof(matlab_arr_t));
    B = malloc(sizeof(matlab_arr_t));
    C = malloc(sizeof(matlab_arr_t));
    R = malloc(sizeof(matlab_arr_t));
    X = malloc(sizeof(matlab_arr_t));
    Y = malloc(sizeof(matlab_arr_t));
    A->n = 'A';
    B->n = 'B';
    C->n = 'C';
    R->n = 'R';
    X->n = 'X';
    Y->n = 'Y';
    arrs[0] = *A;
    arrs[1] = *B;
    arrs[2] = *C;
    arrs[3] = *R;
    arrs[4] = *X;
    arrs[5] = *Y;


    matlab_var_t *a, *b, *c, *r, *x, *y;
    a = malloc(sizeof(matlab_arr_t));
    b = malloc(sizeof(matlab_arr_t));
    c = malloc(sizeof(matlab_arr_t));
    r = malloc(sizeof(matlab_arr_t));
    x = malloc(sizeof(matlab_arr_t));
    y = malloc(sizeof(matlab_arr_t));
    a->n = 'a';
    b->n = 'b';
    c->n = 'c';
    r->n = 'r';
    x->n = 'x';
    y->n = 'y';
    vars[0] = *a;
    vars[1] = *b;
    vars[2] = *c;
    vars[3] = *r;
    vars[4] = *x;
    vars[5] = *y;

    //Buffer för kommandotolk kommandon
    char line[50];
    while(argc)
    {
        //Läs i kommandotolken, från stdin till line
        //Line skickas till processLine där kommandot sorteras och rätt funktion anberopas
        fgets(line, sizeof(line), stdin);
        processLine(line);
    }

    return 0;
}

//Tar in in line som input
//Identifierar första strängen som namnet på vilken funktion som ska tillakallas
//Med rätt funktions-namn vet vi vilka typer och hur många parameterar som bör finnas i line
//Funktionen kallas med dessa parameterar
//Name används till olika char-inputs, value till double-inputs. Filename används när fuktions-input är en fil.
int processLine(char line[50])
{

        char buffer[50];
        char smooth_operator;
        double value;
        double value2;
        char name4;
        char name3;
        char name2;
        char name;
        char filename[50];
        sscanf(line, "%s", buffer);
        if (strcmp(buffer, "Set") == 0)
        {
            if (sscanf(line, "%s %c %lf ", buffer, &name, &value) != 3)
            {
                //Ovan if-sats ser till att rätt mängd inputs ges till den specifika funktionen
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                //Funktions-callet sker i "else" för alla funktioner
                set_value(name, value);
            }
        }
       else if (strcmp(buffer, "Clear") == 0)
        {
            if(sscanf(line, "%s %c", buffer, &name) != 2)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                clear_value(name);
            }
        }

        else if (strcmp(buffer, "Show") == 0)
        {
            if(sscanf(line, "%s %c", buffer, &name) != 2)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                show_value(name);
            }
        }

        else if (strcmp(buffer, "Calc") == 0)
        {
            if(sscanf(line, "%s %c %c %c %c %c", buffer ,&name3, &name4, &name, &smooth_operator, &name2) != 6)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                calc_value(name3, name, smooth_operator, name2);
            }
        }

        else if (strcmp(buffer, "Sin") == 0)
        {
            if(sscanf(line, "%s %c %c", buffer , &name, &name2) != 3)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                 sin_calc(name, name2);
            }
        }

        else if (strcmp(buffer, "Array") == 0)
        {
            if(sscanf(line, "%s %c %lf %lf", buffer ,&name, &value, &value2) != 4)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                array(name, value, value2);
            }
        }

        else if (strcmp(buffer, "Show_vars") == 0)
        {
            show_vars();
        }

        else if (strcmp(buffer, "ShowCSV") == 0)
        {
            if(sscanf(line, "%s %s", buffer, filename) != 2)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                showCSV(filename);
            }
        }

        else if (strcmp(buffer, "ImportCSV") == 0)
        {
            if(sscanf(line, "%s %c %s", buffer, &name, filename) != 3)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                importCSV(name, filename);
            }
        }

        else if (strcmp(buffer, "ExportCSV") == 0)
        {
            if(sscanf(line, "%s %c %s", buffer, &name, filename) != 3)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                exportCSV(name, filename);
            }
        }
        else if (strcmp(buffer, "Event") == 0)
        {
            if(sscanf(line, "%s %c %c", buffer, &name, &name2) != 3)
            {
                printf("Wrong number of inputs, or wrong kind of inputs.\n");
            }
            else
            {
                event(name, name2);
            }
        }

        else if ((strcmp(buffer, "Help") == 0)||(strcmp(buffer, "help") == 0))
        {
            printhelp();
        }
        else if (strcmp(buffer, "Exit") == 0)
        {
            exit(0);
        }
        else
        {
            //I fall t.ex funktionen som kallas inte existerar, ge detta felmeddelande.
            printf("I think you misspelled something.\n");
        }
}
