#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define rows 20
#define columns 20


int main()
{
    srand(time(NULL));
    int forest_current[rows][columns];
    int forest_next[rows][columns];
    
    // ЛЕС
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (rand() % 100 < 70){
                forest_current[i][j] = 1;
            }
            else
                {forest_current[i][j] = 0;}
                }
        }
    
    // СТАРТ
    for (int i = 0; i < rows; i++) {
        if (forest_current[i][0] == 1) {
            forest_current[i][0] = 2;
        }
    }



    // ЦИКЛ ТИКОВ
    
    for (int tick = 0; tick < 25; tick++) {
        
    printf("\033[H\033[J");
    printf("Tick: %d\n", tick);

    // РАСЧЕТ НЕКСТ ТИКА
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
        if (forest_current[i][j] == 2) {
            forest_next[i][j] = 0;
        }
        else if (forest_current[i][j] == 0)
            {forest_next[i][j] = 0;}
        else if (forest_current[i][j] == 1)
            {
                int fire = 0;
                if (i > 0 && forest_current[i - 1][j] == 2) fire = 1;
                if (i < rows - 1 && forest_current[i + 1][j] == 2) fire = 1;
                if (j > 0 && forest_current[i][j - 1] == 2) fire = 1;
                if (j < columns - 1 && forest_current[i][j + 1] == 2) fire = 1;
                
                if (fire == 1){
                    forest_next[i][j] = 2;
                }
                else {forest_next[i][j] = 1;}
            }
        }
    }


    // ПЕРЕВОД НОВОГО ТИКА В СТАРТОВЫЙ
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            forest_current[i][j] = forest_next[i][j];
        }
    }
           
    // ВЫВОД ТИКА
    for (int i = 0; i < rows; i++) {
        printf("\n");
        for (int j = 0; j < columns; j++) {
        if (forest_current[i][j] == 1){
            printf("T");
        }
        else if (forest_current[i][j] == 0)
            {printf(".");}
        else if (forest_current[i][j] == 2)
        {printf("t");}
        }
    }

    fflush(stdout);
    usleep(200000);          
    }

    return 0;
}
