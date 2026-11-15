#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int **create_forest(int rows, int columns) {
    int **forest = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        forest[i] = (int *)malloc(columns * sizeof(int));
    }
    return forest;
}

void free_forest(int **forest, int rows) {
    for (int i = 0; i < rows; i++) {
        free(forest[i]);
    }
    free(forest);
}


int main()
{
    int rows, columns;
    scanf("%d %d", &rows, &columns);
    
    int **forest_current = create_forest(rows, columns);
    int **forest_next = create_forest(rows, columns);

    srand(time(NULL));

    // ЛЕС
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
              if (rand() % 100 < 10) {
                forest_current[i][j] = 3;
            }
            else if (rand() % 100 < 70){
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

    int burn = 0;

    // ЦИКЛ ТИКОВ
    
    for (int tick = 0; tick < 25; tick++) {
        
    printf("\033[H\033[J");
    printf("Tick: %d\n", tick);

    // РАСЧЕТ НЕКСТ ТИКА
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
        if (forest_current[i][j] == 2) {
            burn++;
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
                
                if (fire == 1 && (rand() % 100 < 60)){
                    forest_next[i][j] = 2;
                }
                else {forest_next[i][j] = 1;}
            }
                else if (forest_current[i][j] == 3) 
                    { forest_next[i][j] = 3; }
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
        else if (forest_current[i][j] == 3)
        {printf("~");}
        }
    }

    fflush(stdout);
    usleep(200000);          
    }
    
    free_forest(forest_current, rows);
    free_forest(forest_next, rows);
    printf("\nДеревьев сожжено: %d\n", burn);
    return 0;
}
