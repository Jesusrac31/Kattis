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
        cout << vect[i] << "\n";
    }
    cout << flush;
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

// 100000
#define MAX_Q 100000
#define Nsize 20

// Transformación de caracter a número
int numeric (char a){
    return a - 'a';
}

// Operación suma de números binarios con puertas lógicas a múltiples números a la vez
int ADD (vector<bitset<MAX_Q>>& a, bitset<MAX_Q>& carry, int index = 0){
    bitset<MAX_Q> b = a[index];
    a[index] = (b^carry);
    carry = b & carry;
    
    if (carry != 0){
        ADD(a, carry, index+1);
    }
    return 0;
}

int solve() {
    // Code aquí
    int n, q, k;
    cin >> n >> q >> k;
    string cadena;
    cin >> cadena;
    n--;
    // Almacen de parjas del string original con su orden
    vector<int> pairs(n, 0);
    for(int i = 0; i<n; i++){
        pairs[i] = numeric(cadena[i])*26+numeric(cadena[i+1]);
    }

    // Matriz donde están en 1 aquellos valores los cuales estén contenidos en la consulta
    vector<bitset<MAX_Q>> container(26*26, bitset<MAX_Q>(0));
    // Step contendrá los valores de la sesión anterior para no repetir
    // Carry contendrá a cuales elementos debemos sumar 1 y cuales no
    bitset<MAX_Q> step(0), carry(0);
    // Detecta las consultas y lo almacenamos como acabamos de indicar en container
    for (int i = 0; i<q; i++){
        string s;
        cin >> s;
        for (int j = 0; j<k*2; j+=2){
            container[numeric(s[j])*26+numeric(s[j+1])][i] = 1;
        }
    }
    vector<bitset<MAX_Q>> sol(Nsize ,bitset<MAX_Q>(0)); // Contador de todas las soluciones de las queries
    // Añadimos 1 a aquellos bits que esten en 1 en la secuencia que vamos calculando en step
    for (int i = 0; i<pairs.size(); i++){
        carry = step = (container[pairs[i]] & (~step));
        ADD(sol, carry);
    }

    /*for (int i = 0; i<sol.size(); i++){
        cout << sol[i] << endl;
    }
    cout << endl;*/

    // En sol están los resultados escritos en cada columna y en binario, debemos leerlos y obtener el resultado en decimal
    vector<int>resp(q,0);
    int mult = 1;
    for (int i = 0; i<Nsize; i++){
        for (int j = 0; j<q; j++){
            resp[j] += sol[i][j]*mult;
        }
        mult*=2;
    }
    Imprime(resp);

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    solve();
    return 0;
}

// Este resultado está incompleto, tarda 20 segundos para un input muy grande lo que lo hace inviable, sin embargo ya usa procesamiento de bits de forma paralela
