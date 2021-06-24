#include <stdio.h>
#include <unistd.h>

void fill(char *cp, int size, char c)
{
	for (int i = 0; i < size; i++) {
		cp[i] = c;
	}
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
		if (cp[i] == '#') {
			if (i < size*(size -1)) {
				neighbours[i + size]++; 
				if ((i + 1) % size > 0)
					neighbours[i + size + 1]++; 
				if (i % size > 0)
					neighbours[i + size - 1]++; 
			}
			if (i > size) {
				neighbours[i - size]++; 
				if ((i + 1) % size > 0)
					neighbours[i - size + 1]++; 
				if (i % size > 0)
					neighbours[i - size - 1]++; 
			}
			if ((i + 1) % size > 0)
				neighbours[i + 1]++; 
			if (i % size > 0)
				neighbours[i - 1]++; 
		}
	}
	for (int i = 0; i < size*size; i++) {
		if (cp[i] == '.')
			cp[i] = (neighbours[i] == 3)?'#':'.';
		if (cp[i] == '#')
			cp[i] = (neighbours[i] == 2 || neighbours[i] == 3)?'#':'.';
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
	for (int i = 0; i < num; i++) {
		int col = 0, row = 0;
		draw(cel, size);
		printf("Choose position of cell %d, on the form COL ROW.\n", i);
		s = scanf("%d %d", &col, &row);
		if (s < 0 || row < 0 || col < 0 || row >= size || col >= size) {
			i--;
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
	for (int i = 0; i < num; i++) {
		sleep(1);
		life_cycle(cel, size);
		draw(cel, size);
	}
	return 0;
}
