#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int x;
	int y;
} Direct, Point;
typedef struct
{
	int rows;
	int cols;
} RectSize;
Direct direct[] = {{1, 0}, 
	{0, 1}, {-1, 0}, {0, -1}};
void spiral(const int m, const int n)
{
	int* p = (int*)malloc(m * n * sizeof(int));
	int i = 1, j;
	RectSize rs;
	rs.rows = m;
	rs.cols = n;
	int indexDirect = 1;
	Point currPt = {n-1, -1};
	Direct currDirect = direct[indexDirect];
	int wlen = 0;
	while(i <= m * n)
	{
		currPt.x += currDirect.x;
		currPt.y += currDirect.y;
		p[currPt.y * n + currPt.x] = i++;
		wlen++;
		if(wlen == rs.cols)
		{
			indexDirect = (indexDirect + 1) % 4;
			currDirect = direct[indexDirect];
		}
		else if(wlen == (rs.rows + rs.cols - 1))
		{
			indexDirect = (indexDirect + 1) % 4;
			currDirect = direct[indexDirect];
			rs.rows--;
			rs.cols--;
			wlen = 0;
		}
	}
	for(i = 0; i < m; ++i)
	{
		for(j = 0; j < n; ++j)
		{
			printf("%3d ", p[i * n + j]);
		}
		printf("\n");
	}
	free(p);
	p = NULL;
}

int main()
{
	int m, n;
	printf("input(m,n):");
	scanf("%d%d", &m, &n);
	spiral(m, n);
	return 0;
}


