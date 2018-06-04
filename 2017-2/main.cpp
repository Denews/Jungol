#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

#define max(a,b) (((a) > (b))?(a):(b))
#define min(a,b) (((a) < (b))?(a):(b))

using namespace std;

int groupCount = 0;

int N = 0;
int K = 0;

class Pos
{
public:
	int parent;
	int t;
	int rank;

	Pos()
	{
		parent = -1;
		t = 0;
		rank = 0;
	}
};

Pos * G;

void make_set(int n)
{
	Pos& a = G[n];
	if (a.parent == -1)
	{
		a.parent = n;
		groupCount += 1;
	}
}

int find(int n)
{
	Pos& a = G[n];

	if (n != a.parent)
	{
		a.parent = find(a.parent);
	}

	return a.parent;
}

bool uni(int a, int b)
{
	int c = find(a);
	int d = find(b);
	if (c != d)
	{
		if (G[c].rank < G[d].rank)
		{
			G[c].parent = d;
		}
		else if (G[c].rank > G[d].rank)
		{
			G[d].parent = c;
		}
		else
		{
			G[c].parent = d;
			G[d].rank += 1;
		}

		groupCount -= 1;
		return true;
	}
	return false;
}

int main(void)
{
	int result = 1;

	queue<int> q1, q2;

	scanf("%d %d", &N, &K);

	G = new Pos[N * N];

	const int dx[] = { 1, -1, 0, 0 };
	const int dy[] = { 0, 0, 1, -1 };

	for (int i = 0; i < K; i++)
	{
		int a, b;

		scanf("%d %d", &a, &b);

		a -= 1;
		b -= 1;

		const int tpos = b * N + a;

		make_set(tpos);
		q1.push(tpos);
	}

	while (groupCount > 1)
	{
		result = G[q1.front()].t + 2;
		while (!q1.empty())
		{
			const int pos = q1.front();
			q1.pop();

			const int x = pos % N;
			const int y = pos / N;
			const int time = G[y * N + x].t;

			for (int i = 0; i < 4; i++)
			{
				const int tx = x + dx[i];
				const int ty = y + dy[i];
				const int tpos = ty * N + tx;

				if (tx < 0 || tx >= N || ty < 0 || ty >= N)
				{
					continue;
				}

				if (G[tpos].parent != -1)
				{
					if (uni(pos, tpos))
					{
						int tresult = max(G[pos].t, G[tpos].t);
						result = min(result, tresult);
					}
				}
			}

			q2.push(pos);
		}
		
		if (groupCount < 2)
		{
			break;
		}

		while (!q2.empty())
		{
			const int pos = q2.front();
			q2.pop();

			const int x = pos % N;
			const int y = pos / N;
			const int time = G[y * N + x].t;

			for (int i = 0; i < 4; i++)
			{
				const int tx = x + dx[i];
				const int ty = y + dy[i];
				const int tpos = ty * N + tx;

				if (tx < 0 || tx >= N || ty < 0 || ty >= N)
				{
					continue;
				}

				if (G[tpos].parent == -1)
				{
					make_set(tpos);
					uni(pos, tpos);
					q1.push(tpos);
					G[tpos].t = time + 1;
				}
			}
		}
	}

	printf("%d", result);

	delete[] G;

	return 0;
}