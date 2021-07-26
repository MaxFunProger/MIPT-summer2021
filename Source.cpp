#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <vector>
#define ll long long

using namespace std;
vector<ll> pows;


void pi(string s, vector<int>& p) {
	int n = s.size();

	for (int i = 1; i < n; ++i) {
		int j = p[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = p[j - 1];
		}
		if (s[i] == s[j])
			++j;
		p[i] = j;
	}


}

void z_function(string s, vector<int>& z) {
	int n = s.size();

	for (int i = 1, l = 0, r = 0; i < n; ++i) {
		if (i <= r) {
			z[i] = min(z[i - l], r - i + 1);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			++z[i];
		}
		if (i + z[i] - 1 > r)
			l = i, r = i + z[i] - 1;
	}

}

ll binpow(int a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return binpow(a, n - 1) * a;
	else {
		ll b = binpow(a, n / 2);
		return b * b;
	}
}

vector<ll> generate_hash(string s, int q, int mod) {
	vector<ll> h(s.size());
	for (int i = 0; i < s.size(); ++i) {
		if (i) {
			h[i] = (h[i - 1] + pows[i] * (s[i] - 'a')) % mod;
		}
		else {
			h[i] = s[i] - 'a';
		}
	}
	return h;
}
int mod = 1e9 + 7;


ll get_hash(vector<ll> h, int l, int r) {
	if (!l)
		return h[r];
	else
		return (h[r] - h[l - 1] + mod) % mod;
}

int d1[100010]; // odd
int d2[100010];
int n, x;
ll ans = 0;

int manaker(string s) {
	n = s.size();
	d1[0] = 1;
	x = 0;
	for (int i = 1; i < n; ++i) {
		int len;
		if (x + d1[x] - 1 < i)
			len = 1;
		else
			len = min(d1[2 * x - i], x + d1[x] - i);
		while (i - len >= 0 && i + len < n && s[i - len] == s[i + len])
			++len;
		d1[i] = len;
		if (i + d1[i] > x + d1[x])
			x = i;
	}

	d2[0] = 0;
	x = 0;
	for (int i = 1; i < n; ++i) {
		if (s[i] != s[i - 1])
			continue;
		int len;
		if (x + d2[x] - 1 < i)
			len = 1;
		else
			len = min(d2[2 * x - i], x + d2[x] - i);
		while (i - len - 1 >= 0 && i + len < n && s[i - len - 1] == s[i + len])
			++len;
		d2[i] = len;
		if (i + d2[i] > x + d2[x])
			x = i;
	}

	for (int i = 0; i < n; ++i) {
		ans += d1[i];
		ans += d2[i];
	}
	return ans - n;
}


string s, t;
int a, b, c, d;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> s;
	cout << manaker(s);


	return 0;
}