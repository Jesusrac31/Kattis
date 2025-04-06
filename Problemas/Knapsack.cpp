#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef pair<int, int> pii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones vector
#define PB(a) push_back(a);

bool sort_func(int a, int b) {
    if (a < b) {
        return true;
    } else {
        return false;
    }
}
#define ord(vect) sort(vect.begin(), vect.end(), sort_func);

#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
#define B begin();
#define E end();
#define copia(v1, v2)                                                                                                                    \
    ;                                                                                                                                                        \
    copy(v1.begin(), v1.end(), back_inserter(v2));

// Funciones map
#define F first;
#define S second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

void Imprime(vi vect) {
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << "\n";
}

void Imprime2d(vector<vector<pair<int, bool>>> vect) {
    for (int j = 0; j<vect.size(); j++){
        for (int i = 0; i < vect[j].size(); i++) {
                cout << vect[j][i].first << " " <<vect[j][i].second << "\t\t";
        }
        cout << "\n";
    }
}

void Imprime_set(set<int> s) {
    copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int maximo_comun_divisor(int a, int b) {
    int temporal; // Para no perder b
    while (b != 0) {
        temporal = b;
        b = a % b;
        a = temporal;
    }
    return a;
}

int minimo_comun_multiplo(int a, int b) {
    return (a * b) / maximo_comun_divisor(a, b);
}

bool isNumeric(string const &str) {
    auto it = str.begin();
    while (it != str.end() && isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

vi lee(int n) {
    int el;
    vi vect;
    for (int i = 0; i < n; i++) {
        cin >> el;
        vect.PB(el);
    }
    return (vect);
}

void create_tabs(int n){
    while(n--){
        cout << "\t";
    }
}

int columnas;

int dosd2one (int x, int y){
    return x*columnas+y;
}

//Completa la tabla de dinammic programming
int ResuelveDP(vector<int>& solsDP, vector<pii>& objs, int C, int n){
    for (int i = 1; i<=C; i++){
        for (int j = 1; j<=n; j++){
            if (objs[j-1].second<=i){
                solsDP[dosd2one(i, j)] = max(solsDP[dosd2one(i, j-1)], solsDP[dosd2one(i-objs[j-1].second, j-1)]+objs[j-1].first);
            } else {
                solsDP[dosd2one(i, j)] = solsDP[dosd2one(i, j-1)];
            }
        }
    }
    return 0;
}

int solve(int C, int n) {
    // Code aquí
    vector<pii> objs;
    pii el;
    for (int i = 0; i<n; i++){
        cin >> el.first >> el.second;
        objs.PB(el);
    }
    columnas = n+1;
    vector<int> solsDP ((C+1)*(n+1), 0);
    ResuelveDP(solsDP, objs, C, n);

    vector<int> solucion;
    int weight = C;
    for (int i = n; i>0; i--){
        if (solsDP[dosd2one(weight, i)] > solsDP[dosd2one(weight, i-1)]){
            solucion.PB(i-1);
            weight-=objs[i-1].second;   
        }
    }
    cout << solucion.size() << endl;
    Imprime(solucion);
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int C, n;
    while (cin >> C >> n) {
        solve(C, n);
    }
    return 0;
}
