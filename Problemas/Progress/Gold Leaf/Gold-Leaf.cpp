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

vi minimo (vector<vi> options){
    vi sol = options[0];
    for (int i = 1; i<options.size(); i++){
        bool change = false;
        for (int j = 0; j<options[i].size(); j++){
            if (options[i][j]<sol[j]){
                change=true;
                break;
            } else if (options[i][j]>sol[j]){
                break;
            }
        }
        if (change){
            sol = options[i];
        }
    }
    return sol;
}

bool debuging = false;

int solve (int n, int m){
    vector<string> sheet(n);
    for (int i = 0; i<n; i++){
        cin >> sheet[i];
    }

    set<pii> opciones; //{dir, num inicio} 0=horizontal, 1=vertical, 2=diagonal 45, 3 = diagonal 135
    //Iniciación posibilidades horizontales
    for (int i = 1; i<sheet.size(); i++){
        opciones.insert({0, i});
    }
    //Iniciación posibilidades verticales
    for (int i = 1; i<sheet[0].size(); i++){
        opciones.insert({1, i});
    }
    //Iniciación posibilidades diagonal 45
    for (int i = 1; i<sheet[0].size()+sheet.size(); i++){
        opciones.insert({2, i});
    }
    //Iniciación posibilidades diagonal 135
    for (int i = 1; i<sheet[0].size()+sheet.size(); i++){
        opciones.insert({3, i});
    }

    for (int y1 = 0; y1<sheet.size(); y1++){
        for (int x1 = 0; x1<sheet[y1].size(); x1++){
            set<pii> vistas;
            
            //Horizontal
            for (int y2 = ((y1+1)%2); y2<sheet.size(); y2+=2){
                if (sheet[y2][x1] == '#'){
                    vistas.insert({0,(y1+y2+1)/2});
                }
            }

            // Vertical
            for (int x2 = ((x1+1)%2); x2<sheet[0].size(); x2+=2){
                if (sheet[y1][x2] == '#'){
                    vistas.insert({1,(x1+x2+1)/2});
                }
            }

            //Diagonal 45
            int offset_x = x1-y1;
            for (int i = 0; i<sheet.size(); i++){
                if (i+offset_x >=0 && i+offset_x < sheet[i].size()){
                    int y2 = i, x2 = i+offset_x;
                    if (sheet[y2][x2] == '#' && !(y2==y1 && x2==x1)){
                        vistas.insert({2,(x1+y1)+((y2-y1)+(x2-x1))/2});
                    }
                }
            }

            //Diagonal 135
            offset_x = x1+y1;
            for (int i = 0; i<sheet.size(); i++){
                int y2 = i, x2 = offset_x-i;
                if (x2 >=0 && x2 < sheet[i].size()){
                    if (sheet[y2][x2] == '#' && !(y2==y1 && x2==x1)){
                        vistas.insert({3,(y1-x1+sheet[y1].size())+((y2-y1)-(x2-x1))/2});
                    }
                }
            }

            if (sheet[y1][x1] == '.'){
                vector<pii> s1s2_intsec;
                set_intersection(opciones.begin(), opciones.end(),
                          vistas.begin(), vistas.end(),
                          back_inserter(s1s2_intsec));
                opciones.clear();
                opciones.insert(s1s2_intsec.begin(), s1s2_intsec.end());
            } else {
                set<pii> diferencia;
                set_difference(opciones.begin(), opciones.end(), vistas.begin(), vistas.end(), inserter(diferencia, diferencia.begin()));
                opciones.clear();
                opciones.insert(diferencia.begin(), diferencia.end());
            }
            if (debuging){
                cout << "Vistas: " << endl;
                for (auto it:vistas){ 
                    cout << it.first << " " << it.second << endl;
                }
                cout << "Opciones: " << endl;
                for (auto it:opciones){ 
                    cout << it.first << " " << it.second << endl;
                }
                cout << "---------------------" << endl;
            }
        }
    }
    if (debuging){
        cout << "Opciones: " << endl;
        for (auto it:opciones){ 
            cout << it.first << " " << it.second << endl;
        }
    }
    if (opciones.size() == 0){
        if (debuging){
            cout << "ERROR" << endl;
        }
        cout << "1 1 1 1" << endl;
        return 0;
    }
    vector<vi> soluciones;
    for (auto sol:opciones){
        if (debuging){
            cout << "sol:" << endl;
            cout << sol.first << " " << sol.second << endl;
        }

        if (sol.first == 0){
            soluciones.emplace_back(vector<int>{sol.second, 1, sol.second, (int)sheet[0].size()});
        } else if (sol.first == 1){
            soluciones.emplace_back(vector<int>{1, sol.second, (int)sheet.size(), sol.second});
        } else if (sol.first == 2){
            soluciones.emplace_back(vector<int>{});
            for (int i = 0; sol.second-i>=0 && i<sheet[0].size(); i++){
                if (sol.second-i<sheet.size() && soluciones[soluciones.size()-1].size()==0){
                    soluciones[soluciones.size()-1].emplace_back(sol.second-i+1);
                    soluciones[soluciones.size()-1].emplace_back(i+1);
                }
                if (!(sol.second-i-1>=0 && i+1<sheet[0].size())){
                    soluciones[soluciones.size()-1].emplace_back(sol.second-i+1);
                    soluciones[soluciones.size()-1].emplace_back(i+1);
                }
            }
        } else if (sol.first == 3) {
            soluciones.emplace_back(vector<int>{});
            for (int i = 0; sol.second+i-((int)sheet[0].size())<(int)sheet.size() && i<(int)sheet[0].size(); i++){
                if (debuging){
                    cout << sol.second+i-(int)sheet[0].size() << " " << i << endl;
                }
                if (sol.second+i-(int)sheet[0].size()>=0 && soluciones[soluciones.size()-1].size()==0){
                    soluciones[soluciones.size()-1].emplace_back(sol.second+i-(int)sheet[0].size()+1);
                    soluciones[soluciones.size()-1].emplace_back(i+1);
                }
                if (!(sol.second+i+1-(int)sheet[0].size()<(int)sheet.size() && i+1<(int)sheet[0].size())){
                    soluciones[soluciones.size()-1].emplace_back(sol.second+i-(int)sheet[0].size()+1);
                    soluciones[soluciones.size()-1].emplace_back(i+1);
                }
            }
        }
    }
    ord(soluciones);
    Imprime(soluciones[0]);

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int n, m;
    while (cin >> n >> m) {
        solve(n, m);
    }
    return 0;
}
