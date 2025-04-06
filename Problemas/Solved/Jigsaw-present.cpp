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
#define piezas first;
#define dificultad second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

void Imprime(vi &vect) {
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

void Imprime_set(unordered_set<int> s) {
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

vector<pair<pii, lli>> meet_in_the_middle (int l, int r, vector<pii>& puzzles) {
    vector<pair<pii, lli>> subsets{{{0, 0}, 0}};
    
    for (int i = l; i < r; i++) {
        int s = subsets.size();
        subsets.resize(3 * s);
        for (int j = 0; j < s; j++) {
            subsets[j + s] = subsets[j + 2 * s] = subsets[j];
            subsets[j + s].first.first += puzzles[i].first;
            subsets[j + s].first.second += puzzles[i].second;
            subsets[j + s].second |= 1LL << ((i-l) << 1); // Nos ayuda a saber que elementos están en el set
            subsets[j + 2 * s].first.first -= puzzles[i].first; // Las combinaciones restando nos sirve para cubrir que pasaría si sumara en el otro lado
            subsets[j + 2 * s].first.second -= puzzles[i].second;
            subsets[j + 2 * s].second |= 1LL << ((i-l) << 1 | 1); // Nos ayuda a saber que elementos están en el set
        }

        //Sort de forma óptima ya que son 3 listas concatenadas ordenadas
        inplace_merge(subsets.begin(), subsets.begin() + s, subsets.begin() + 2 * s);//Sort de la primera lista con la segunda
        inplace_merge(subsets.begin(), subsets.begin() + 2 * s, subsets.end());//Sort del resto
    }
    return subsets;
};

int solve() {
    // Code aquí
    int n;
    cin >> n;
    n = min(n, 28); // Clave para entrar en espacio, con una muestra es suficiente

    vector<pii> puzzles;
    for (int i = 0; i<n; i++){
        puzzles.PB({});
        cin>> puzzles[puzzles.size()-1].first >> puzzles[puzzles.size()-1].second;
    }
    vector<pair<pii, lli>> pos_l = meet_in_the_middle(0, n/2, puzzles),pos_r = meet_in_the_middle(n/2, n, puzzles);

    // Creamos un for de dos variables (para recorrer ambas listas a la vez partiendo de que están ordenadas)
    int j = 0;
    for (int i = 0; i < pos_l.size(); i++) {
        while (j < pos_r.size() && pos_l[i].first > pos_r[j].first) {
            j++;
        }
        if (j == pos_r.size()) {
            break;
        }

        //cout << pos_l[i].first.first << " " << pos_l[i].first.second << " " << pos_l[i].second << endl;
        //cout << pos_r[j].first.first << " " << pos_r[j].first.second << " " << pos_r[j].second << endl;
        if (pos_l[i].first == pos_r[j].first && (pos_l[i].second || pos_r[j].second)) { // Son iguales y los dos no son la combinación de ningún regalo
            vector<int> opt1 = {}, opt2 = {};
            for (int k = 0; pos_l[i].second!=0; k++) {
                //cout << pos_l[i].second << endl;
                if ((pos_l[i].second%4) == 1){
                    opt2.emplace_back(k+1);
                } else if ((pos_l[i].second%4) == 2){
                    opt1.emplace_back(k+1);
                }
                pos_l[i].second/=4;
            }

            for (int k = n/2; pos_r[j].second!=0; k++) {
                //cout << pos_r[j].second << endl;
                if ((pos_r[j].second%4) == 1){
                    opt1.emplace_back(k+1);
                } else if ((pos_r[j].second%4) == 2){
                    opt2.emplace_back(k+1);
                }
                pos_r[j].second/=4;
            }

            cout << "no\n";
            cout << opt1.size() << " ";
            Imprime(opt1);
            cout << opt2.size() << " ",
            Imprime(opt2);
            return 0;
        }
    }
    cout << "yes" << endl;

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    solve();
    return 0;
}
