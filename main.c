#include <stdio.h>
#include <unistd.h>

void fill(char *cp, int size, char c)
{
	while (size)
		cp[--size] = c;
}

void draw(char *cel, int size)
{
	printf("\x1b[1H");
	for (int i = 0; i < size*size; i++) {
		printf("%c", cel[i]);
		if ((i + 1) % size == 0)
			printf("\n");
	}
}

void life_cycle(char *cp, int size)
{
	char neighbours[size*size];
	fill(neighbours, size*size, 0);
	for (int i = 0; i < size*size; i++) {
		for (int n = 0; n < 9; n++) {
			if (n == 4)
				continue;
			if (cp[i + ((n/3)-1)*size + ((n%3)-1)] == '#')
				neighbours[i]++;
		}
	}
	for (int i = 0; i < size*size; i++) {
		if (neighbours[i] == 3)
			cp[i] = '#';
		else if (neighbours[i] !=2)
			cp[i] = '.';
	}
}

int main()
{
	int size = 20;
	char cel[size*size];
	fill(cel, size*size, '.');
	draw(cel, size);
	int num;
	int s;
	do {
		printf("How many cells ought live by phase 0?\n");
		s = scanf("%d", &num);
	} while (num < 1 || s < 0);
	while (num) {
		int col = 0, row = 0;
		draw(cel, size);
		printf("Choose position of cell %d, on the form COL ROW.\n", num--);
		s = scanf("%d %d", &col, &row);
		if (s < 0 || row < 0 || col < 0 || row >= size || col >= size) {
			num++;	
			continue;
		}
		cel[size*row + col] = '#';
	}
	draw(cel, size);
	do {
		printf("How many cycles?\n");
		s = scanf("%d", &num);
	} while (num < 1 || s < 0);
	draw(cel, size);
	for (;num; num--) {
		sleep(1);
		life_cycle(cel, size);
		draw(cel, size);
	}
	return 0;
}
