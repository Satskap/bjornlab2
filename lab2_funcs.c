
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "lab2.h"
#include "lab2_funcs.h"

//Lokala variabler deklareras i funktionen. Varje funktion deklarar den mängd variabler som den använder själv.
//Find_var och find_arr specifierar vilken av de hård-kodade variablerna som ska manipuleras i funktionen
//Conditions för input_array == 0 betyder att detta "name" ej hittades i listan. Motsvarande för input_var == 0. Om båda är 0 ges felmeddelande pga fel syntax.
//För funktioner som stöder både arrays och variabler kollar funktionen först om "name" är en array i arrs, om inte kollar funktionen om "name" det är en variabel i vars



//Denna funktion sätter alla värden i en array eller en variabel till ett specifikt värde "setpoint".
//Loopa genom ARRAY_LEN, eftersom bara en viss längd av arrayer behöver stödjas

int set_value(char name, double setpoint)
{
    matlab_arr_t *input_array;
    matlab_var_t *input_var;
    input_array = malloc(sizeof(matlab_arr_t));
    input_var = malloc(sizeof(matlab_var_t));
    input_array = find_arr(name);

    if(input_array == 0)
    {
        input_var = find_var(name);
        if (input_var == 0)
        {
            printf("Syntax Error. Please use A,B,C,D,R,X,Y,a,b,c,d,r,x,y as your variables.");
        }
        else
        {
            input_var->v = setpoint;
        }
    }
    else
    {
        for(int j = 0; j<ARRAY_LEN; j++)
        {
            input_array->v[j] = setpoint;
        }
    }

    printf("\n");
    return 0;


}

//Denna funktion rensar en variabel eller array och sätter alla dess element till 0.
//Loopa genom ARRAY_LEN
int clear_value(char name)
{
    matlab_arr_t *input_array;
    matlab_var_t *input_var;
    input_array = malloc(sizeof(matlab_arr_t));
    input_var = malloc(sizeof(matlab_var_t));
    input_array = find_arr(name);
    if(input_array == 0)
    {
        input_var = find_var(name);
        if (input_var == 0)
        {
            printf("Syntax Error. Please use A,B,C,D,R,X,Y,a,b,c,d,r,x,y as your variables.");
        }
        else
        {
            input_var->v = 0.0000;
        }
    }
    else
    {
        for(int j = 0; j<ARRAY_LEN; j++)
        {
            input_array->v[j] = 0.0000;
        }
    }

    printf("\n");
    return 0;

}


//Denna funktion printar värdet på en variabel eller alla värden i en array till kommandotolken.
int show_value(char name)
{
    matlab_arr_t *input_array;
    matlab_var_t *input_var;
    input_array = malloc(sizeof(matlab_arr_t));
    input_var = malloc(sizeof(matlab_var_t));
    input_array = find_arr(name);

    if(input_array == 0)
    {
        input_var = find_var(name);
        if (input_var == 0)
        {
            printf("Syntax Error. Please use A,B,C,D,R,X,Y,a,b,c,d,r,x,y as your variables.");
        }
        else
        {
           printf("%f ", input_var->v);
        }
    }
    else
    {
        for(int j = 0; j<ARRAY_LEN; j++)
        {
            printf("%f ", input_array->v[j]);
        }
    }

    printf("\n");
    return 0;
}


//Denna funktion utför en serie olika beräkningar beroende på vad "smooth_operator" är.
//För arrays stöds + och -. För variabler stödjs +,-,* och /. Inga mixade typer. Skriver felmeddelande om fel operator ges.
//Conditions för om det är variabler eller arrays görs med ett "or" condition för att alla måste vara av samma typ.
int calc_value(char equals, char input, char smooth_operator, char input2)
{
    matlab_arr_t *input_array;
    matlab_arr_t *input_array2;
    matlab_arr_t *equals_array;
    matlab_var_t *input_var;
    matlab_var_t *input_var2;
    matlab_var_t *equals_var;

    input_array = malloc(sizeof(matlab_arr_t));
    input_array2 = malloc(sizeof(matlab_arr_t));
    equals_array = malloc(sizeof(matlab_arr_t));
    input_var = malloc(sizeof(matlab_var_t));
    input_var2 = malloc(sizeof(matlab_var_t));
    equals_var = malloc(sizeof(matlab_var_t));

    input_array = find_arr(input);
    input_array2 = find_arr(input2);
    equals_array = find_arr(equals);
    //printf("%c %c %c",equals_array->n, input_array->n, input_array2->n);
    if((equals_array == 0) || (input_array == 0) || (input_array2 == 0))
    {
        input_var = find_var(input);
        input_var2 = find_var(input2);
        equals_var = find_var(equals);
        if((equals_var == 0) || (input_var == 0) || (input_var2 == 0))
        {
            printf("Syntax error. Please use A,B,C,D,R,X,Y,a,b,c,d,r,x,y as your variables, and do not mix values and arrays.");
        }
        else
        {
            if (smooth_operator == '+')
            {
                equals_var->v = input_var->v + input_var2->v;
            }
            else if (smooth_operator == '-')
            {
                equals_var->v = input_var->v - input_var2->v;
            }
            else if (smooth_operator == '*')
            {
                equals_var->v = input_var->v * input_var2->v;
            }
            else if (smooth_operator == '/')
            {
                 equals_var->v = input_var->v / input_var2->v;
            }
            else
            {
                printf("Incorrect Operator.");
            }
        }

    }
    else
    {
        if (smooth_operator == '+')
        {
            for(int j = 0; j<ARRAY_LEN; j++)
            {
            equals_array->v[j] = input_array->v[j] + input_array2->v[j];
            }
        }

        else if (smooth_operator == '-')
        {
            for(int j = 0; j<ARRAY_LEN; j++)
            {
            equals_array->v[j] = input_array->v[j] - input_array2->v[j];
            }
        }
        else
        {
            printf("Incorrect Operator for array math.");
        }
    }
    printf("\n");
    return 0;
}

//Denna funktion utför samma sak som linspace.
//Från ett start och stop värde genererar en array med lika steglängd som definieras av (start-stop)/(ARRAY_LEN-1). Detta för att sista värdet ska vara precis lika med "stop".
//Loopa genom ARRAY_LEN och använd step*j som den ökande additionen.
int array(char name, double start, double stop)
{
    matlab_arr_t *input_array;
    input_array = malloc(sizeof(matlab_arr_t));
    input_array = find_arr(name);
    if (input_array == 0)
    {
        printf("Syntax error. Please use A,B,C,R,X,Y as your arrays.");
    }
    else
    {
        double step = (stop - start) / (ARRAY_LEN-1);
        for(int j = 0; j<ARRAY_LEN; j++)
        {
        input_array->v[j] = start + step*j;
        }
    }

    printf("\n");
    return 0;


}

//Denna funktion tar en array "name" och beräknar sin-värdet för alla dess element. Detta skrivs över till en annan array "name2" (name och name2 är namnen på arrayerna).
int sin_calc(char name, char name2)
{
    matlab_arr_t *input_array;
    matlab_arr_t *equals_array;
    input_array = malloc(sizeof(matlab_arr_t));
    equals_array = malloc(sizeof(matlab_arr_t));
    input_array = find_arr(name);
    equals_array = find_arr(name2);
    if((input_array == 0) || (equals_array == 0))
    {
        printf("Syntax error. Please use A,B,C,R,X,Y as your arrays.\n");
    }
    else
    {
        for(int j = 0; j<ARRAY_LEN; j++)
        {
            equals_array->v[j] = sin(input_array->v[j]);
        }
    }
    printf("\n");
    return 0;
}

//Denna funktion printar alla variabler i listan vars, genom att printa vars.n och vars.v enl. för-definerade struktar.
void show_vars(void)
{
    for(int i = 0; i < 6; i++)
    {
        printf("%c is equal to: %fl\n",vars[i].n, vars[i].v);
    }
}

//Denna funktionen printar de första 50 raderna i en csv fil vars namn ges av "filename" (detta för att endast en längd behöver stödjas).
//fgets sätter c_s till en rad i "filename" och sen printas c_s den till kommandotolken
//Stäng sen filen
void showCSV(char filename[50])
{
    FILE *file;
    char c_s[20];
    if((file = fopen ( filename, "r"))== NULL)
    {
        printf("Can't open file for reading\n");
        return;
    }
    for(int j = 0; j<ARRAY_LEN; j++)
    {
        fgets(c_s, sizeof(c_s), file);
        printf("%s",c_s);
    }
    fclose(file);
    printf("\n");
    return;
}


//Denna funktion sätter raderna av en csv-fil till motsvaradne element i en double array "name".
//Precis som innan används fgets.
//atof() gör en sträng till en double
void importCSV(char name, char filename[50])
{
    matlab_arr_t *input_array;
    input_array = malloc(sizeof(matlab_arr_t));
    input_array = find_arr(name);
    FILE *file;
    double csvvalue;
    char c_s[20];
    if((file = fopen ( filename, "r"))== NULL)
    {
        printf("Can't open file for reading\n");
        return;
    }

    if (input_array == 0)
    {
        printf("Syntax error. Please use A,B,C,R,X,Y as your arrays.\n");
    }
    else
    {
        for(int j = 0; j<ARRAY_LEN; j++)
        {
            fgets(c_s, sizeof(c_s), file);
            csvvalue = atof(c_s);
            //printf("%fl", csvvalue);
            input_array->v[j] = csvvalue;
        }
    }
    fclose(file);
    printf("\n");
    return;
}

//Denna funktion sätter de första 50 raderna i en csv fil till motsvarade element i en double array.
//snprintf används här för att göra en double till en sträng så fputs kan sätta värdet till en rad i "filename".
void exportCSV(char name, char filename[50])
{
    matlab_arr_t *input_array;
    input_array = malloc(sizeof(matlab_arr_t));
    input_array = find_arr(name);
    FILE *file;
    double csvvalue;
    char c_s[20];
    if((file = fopen ( filename, "w"))== NULL)
    {
        printf("Can't open file for reading\n");
        return;
    }

    if (input_array == 0)
    {
        printf("Syntax error. Please use A,B,C,R,X,Y as your arrays.\n");
    }
    else
    {
        for(int j = 0; j<ARRAY_LEN; j++)
        {
            csvvalue = input_array->v[j];
            snprintf(c_s, 20, "%f", csvvalue);
            //printf("%s", c_s);
            fputs(c_s, file);
            fputs("\n", file);
        }
    }
    fclose(file);
    printf("\n");
    return;

}

//Denna funktion upptäcker "events" i en array av doubles. Detta defineras som minst 10 konsekutiva värden över 0.5.
//Start och stop-index för "eventen" printas till kommandotolken.
//Eventen sparas i en double array vid namn "name2". Denna array sätts till 0 utanför de index som definerar eventen.
void event(char name, char name2)
{
    matlab_arr_t *input_array;
    matlab_arr_t *equals_array;
    input_array = malloc(sizeof(matlab_arr_t));
    equals_array = malloc(sizeof(matlab_arr_t));
    int start, stop, count = 0;

    input_array = find_arr(name);
    equals_array = find_arr(name2);
    if ((input_array == 0) || (equals_array == 0))
    {
        printf("Syntax error. Please use A,B,C,R,X,Y as your arrays.\n");
    }
    else
    {
        clear_value(name2);
        for(int j = 0; j<ARRAY_LEN; j++)
        {
            //Om ett värde över 0.5 upptäcks öka count. Om detta är första konsekutiva värdet över 0.5 så sätts start-index.
            if ((input_array->v[j]>=0.5) & (j != ARRAY_LEN - 1))
            {

                count++;
                if (count == 1)
                {
                    start = j;
                }
            }
            //Extra condition som en "or"-sats för om vi nått slutet på arrayen.
            else if ((input_array->v[j]<0.5) || (j == ARRAY_LEN - 1))
            {
                //Condition för om en event upptäckts
                if(count >= 10)
                {
                    stop = j;
                    printf("Start index is: %i\nStop index is: %i\n", start, stop);
                    //Denna extra sats används specifikt för om sista värdet är över 0.5, och ser till att start och stop indexet kan vara över hela längden av arrayen
                    //Specifikt att sista värdet i output arrayen också sätts korrekt.
                    //Testa detta med Set X 1, Event X Y. :)
                    if (input_array->v[j]>=0.5)
                    {
                        j++;
                    }
                    stop = j;
                    //I denna loop så sätt värden i index mellan start och stop i output arrayen till att matcha det i input-arrayen.
                    //Dvs sätts värdena i output arrayen till "signalen".
                    for(int i = start; i<stop; i++)
                    {
                        equals_array->v[i] = input_array->v[i];
                    }
                }
                count = 0;
            }

        }
    }
}

void printhelp(void)
{
    printf("Available Commands:\n        Help: shows this message.\n        Set <var> <value>: set variable/array <var> to value <value>.\n        Clear <var>: set variable/array <var> to zero.\n        Show <value>: Prints the contents of variable/array <var> \n");
    printf("        Calc <var> = <var> <operator> <var>: performs mathematical operations on two variables and sets the results to a third. Supports + and - for arrays and +,-,* and / for variables.\n");
    printf("        Array <var> <value> <value>: sets the values to an array to equi-distant values starting from the first given value to the second.\n");
    printf("        Sin <var> <var>: sets the values of the second array to the sinus of the corresponding index of the first given array.\n");
    printf("        Show_var: prints the values of the six given variables to the screen.\n");
    printf("        ShowCSV <filename>: Prints the contents of a csv-file with name <filename>.\n");
    printf("        ImportCSV <var> <filename>: Sets the values of array <var> to the contents of the corresponding lines in csv-file <filename>.\n");
    printf("        ExportCSV <var> <filename>: Sets the rows of csv-file <filename> to corresponding values of array <var>.\n");
    printf("        Event <var> <var>: Checks the first variable for events, defined by 10 consecutive values larger than 0.5. If an event is detected, it prints the index of the first and last element in the event, then sets the values in the second variable to the corresponding event.\n");
    printf("        Exit: exits the application, only what is in the csv-files will be saved.\n");
}
//Loopa igenom arrs och kollar på n-värdet vilket är dess namn som en char. Om detta är lika med name, returnerna arrs[i].
//Denna iterationen görs specifikt 6 gånger så där finns 6 hårdkodade arrayers och variabler.
//Om namne inte finns i arrs, returnerra 0.
matlab_arr_t * find_arr(char name)
{
    for (int i = 0; i < 6; i++)
    {
        if (name == arrs[i].n)
        {
           //printf("%i",i);
           return &arrs[i];
        }
    }
    return 0;
}

//Loopa igenom vars och kollar på n-värdet vilket är dess namn som en char. Om detta är lika med name, returnerna vars[i].
//Om namne inte finns i vars, returnerra 0.
matlab_var_t * find_var(char name)
{
    for (int i = 0; i < 6; i++)
    {
        if (name == vars[i].n)
        {
           return &vars[i];
        }
    }
    return 0;
}


