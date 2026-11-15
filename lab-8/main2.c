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

static double now_s(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}


int main(int argc, char *argv[])

{
	int rows = atoi(argv[1]);
	int columns = atoi(argv[2]);
	int wind = atoi(argv[3]);



	int **forest_current = create_forest(rows, columns);
	int **forest_next = create_forest(rows, columns);

	srand(time(NULL));

	// ЛЕС
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (rand() % 100 < 10) {
				forest_current[i][j] = 3;
			}
			else if (rand() % 100 < 70) {
				forest_current[i][j] = 1;
			}
			else
			{
				forest_current[i][j] = 0;
			}
		}
	}

	// СТАРТ
	for (int i = 0; i < rows; i++) {
		if (forest_current[i][0] == 1) {
			forest_current[i][0] = 2;
		}
	}

	int burn_total = 0;
    double total_time = 0.0;
	// ЦИКЛ ТИКОВ

	for (int tick = 0; tick < 25; tick++) {

		int burn = 0;
		printf("\033[H\033[J");
		printf("ТИК: %d\n", tick);
        double t0 = now_s();
        
		// РАСЧЕТ НЕКСТ ТИКА
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (forest_current[i][j] == 2) {
					burn_total++;
					burn++;
					forest_next[i][j] = 0;
				}
				else if (forest_current[i][j] == 0)
				{
					forest_next[i][j] = 0;
				}
				else if (forest_current[i][j] == 1)
				{
					int fire = 0;
					if (i > 0 && forest_current[i - 1][j] == 2 && rand() % 100 < wind) fire = 1;
					if (i < rows - 1 && forest_current[i + 1][j] == 2 && rand() % 100 < 10) fire = 1;
					if (j > 0 && forest_current[i][j - 1] == 2 && rand() % 100 < wind) fire = 1;
					if (j < columns - 1 && forest_current[i][j + 1] == 2 && rand() % 100 < 10) fire = 1;

					if (fire == 1) {
						forest_next[i][j] = 2;
					}
					else {
						forest_next[i][j] = 1;
					}
				}
				else if (forest_current[i][j] == 3)
				{
					forest_next[i][j] = 3;
				}
			}
		}


		// ПЕРЕВОД НОВОГО ТИКА В СТАРТОВЫЙ

		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				forest_current[i][j] = forest_next[i][j];
			}
		}
		
        total_time += now_s() - t0;
        
		// ВЫВОД ТИКА
		for (int i = 0; i < rows; i++) {
			printf("\n");
			for (int j = 0; j < columns; j++) {
				if (forest_current[i][j] == 1) {
					printf("T");
				}
				else if (forest_current[i][j] == 0)
				{
					printf(".");
				}
				else if (forest_current[i][j] == 2)
				{
					printf("t");
				}
				else if (forest_current[i][j] == 3)
				{
					printf("~");
				}
			}
		}
		
		printf("\nТИК: %d | СГОРЕЛО ЗА ТИК: %d | СГОРЕЛО ВСЕГО: %d\n", tick, burn, burn_total);
		
		fflush(stdout);
		usleep(200000);
	}

	free_forest(forest_current, rows);
	free_forest(forest_next, rows);
	printf("\nДеревьев сожжено: %d\n", burn_total);
	printf("Затрачено времени: %.6f sec\n", total_time);

	return 0;
}
