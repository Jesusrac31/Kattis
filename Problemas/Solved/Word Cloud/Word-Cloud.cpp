#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef pair<int, int> pii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones vector
#define PB(a) emplace_back(a);

bool sort_func(int a, int b) {
    if (a < b) {
        return true;
    } else {
        return false;
    }
}
#define ord(vect) sort(vect.begin(), vect.end());

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

void Imprime2d(vector<vi> vect) {
    for (int j = 0; j<vect.size(); j++){
        for (int i = 0; i < vect[j].size(); i++) {
                cout << vect[j][i] << " ";
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

int solve(int w, int n, int T) {
    // Code aquí
    
    vector<pair<string, int>> words;
    string el;
    int k;
    int most_frequent = 0;
    for (int i = 0; i<n; i++){
        cin >> el >> k;
        most_frequent = max(most_frequent, k);
        if (k>=5){
            words.PB((pair<string, int>{el, k}));
        }
    }
    //ord(words);
    int height_tot = 0;
    int height = 0;
    int width = 0;
    for (int i = 0; i<words.size(); i++){
        //cout << width << " " << height << " " << height_tot << endl;
        int height_act = 8+ceil(((double)40*(words[i].second-4))/(most_frequent-4));
        int width_act = ceil(((double)words[i].first.size()*height_act*9)/16);
        if (width+width_act > w){
            height_tot+=height;
            height=0;
            width=0;
        }
        height = max(height, height_act);
        width+=width_act+10;
    }
    height_tot+=height;

    cout << "CLOUD " << T << ": " << height_tot << endl;

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int w, n;
    int T = 1;
    while (cin >> w >> n) {
        if (w!=0 || n!=0){
            solve(w, n, T);
        }
        T++;
    }
    return 0;
}
