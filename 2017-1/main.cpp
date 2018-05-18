#include <iostream>
#include <cstring>
#include <queue>

#define max(a, b) ((a > b) ? (a) : (b))
#define min(a, b) ((a < b) ? (a) : (b))

using namespace std;

struct bstate
{
	int a;
	int b;
};

class bucket
{
public:
	bucket(int ma, int mb);
	int* A, *B;
	int MA;
	int MB;
	int get(int a, int b);
	void set(int a, int b, int n);
};

bucket::bucket(int ma, int mb):
	MA(ma), MB(mb)
{
	A = new int[MB * 2 + 2];
	B = new int[MA * 2 + 2];

	memset(A, 0xff, MB * 2 + 2);
	memset(B, 0xff, MA * 2 + 2);
}

int bucket::get(int a, int b)
{
	if (a == 0)
	{
		return A[b];
	}
	else if (a == MA)
	{
		return A[MB + 1 + b];
	}
	else if (b == 0)
	{
		return B[a];
	}
	else if (b == MB)
	{
		return B[MA + 1 + a];
	}

	return -1;
}

void bucket::set(int a, int b, int n)
{
	if (a == 0)
	{
		A[b] = n;
	}
	if (a == MA)
	{
		A[MB + 1 + b] = n;
	}
	if (b == 0)
	{
		B[a] = n;
	}
	if (b == MB)
	{
		B[MA + 1 + a] = n;
	}
}

int main(void)
{
	int a, b, c, d;
	cin >> a >> b >> c >> d;

	bucket bt(a, b);
	
	bt.set(0, 0, 0);

	queue<bstate> lq;
	lq.push({ 0, 0 });

	while (!lq.empty())
	{
		bstate bs = lq.front();
		lq.pop();

		int t = bt.get(bs.a, bs.b);
		if (t < 0) continue;

		if (bs.a < a && (bt.get(a, bs.b) < 0 || bt.get(a, bs.b) > t + 1))
		{
			bt.set(a, bs.b, t + 1);
			lq.push({ a, bs.b });
		}
		if (bs.a > 0 && (bt.get(0, bs.b) < 0 || bt.get(0, bs.b) > t + 1))
		{
			bt.set(0, bs.b, t + 1);
			lq.push({ 0, bs.b });
		}
		if (bs.b < b && (bt.get(bs.a, b) < 0 || bt.get(bs.a, b) > t + 1))
		{
			bt.set(bs.a, b, t + 1);
			lq.push({ bs.a, b });
		}
		if (bs.b > 0 && (bt.get(bs.a, 0) < 0 || bt.get(bs.a, 0) > t + 1))
		{
			bt.set(bs.a, 0, t + 1);
			lq.push({ bs.a, 0 });
		}
		if (bs.a > 0 && bs.b < b &&
			(bt.get(max(0, (bs.b + bs.a) - b), min(b, bs.a + bs.b)) < 0 
			|| bt.get(max(0, (bs.b + bs.a) - b), min(b, bs.a + bs.b)) > t + 1))
		{
			bt.set(max(0, (bs.b + bs.a) - b), min(b, bs.a + bs.b), t + 1);
			lq.push({ max(0, (bs.b + bs.a) - b), min(b, bs.a + bs.b) });
		}
		if (bs.b > 0 && bs.a < a &&
			(bt.get(min(a, bs.a + bs.b), max(0, (bs.b + bs.a) - a)) < 0
			|| bt.get(min(a, bs.a + bs.b), max(0, (bs.b + bs.a) - a)) > t + 1))
		{
			bt.set(min(a, bs.a + bs.b), max(0, (bs.b + bs.a) - a), t + 1);
			lq.push({ min(a, bs.a + bs.b), max(0, (bs.b + bs.a) - a) });
		}
	}

	cout << ((bt.get(c, d) >= 0) ? bt.get(c, d) : -1) << endl;
	system("pause");
	return 0;
}