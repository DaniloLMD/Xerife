#include <iostream>
#include <vector>

using namespace std;

const int MAX_SAQUE = 5100;
const int N_NOTAS = 6;

vector<int> qtd_notas(N_NOTAS, 0);
vector<int> pesos = {2, 5, 10, 20, 50, 100};
vector<vector<int>> dp(MAX_SAQUE, vector<int>(N_NOTAS, -1));

int banco(int saque, int nota_atual = 0){

    if(saque == 0) return 1;
    if(saque < 0) return 0;
    if(nota_atual >= N_NOTAS) return 0;
    if(dp[saque][nota_atual] != -1) return dp[saque][nota_atual];

    int tot = 0;
    for(int i = 0; i <= qtd_notas[nota_atual]; i++){
        if(i * pesos[nota_atual] > saque) break;

        tot += banco(saque - i * pesos[nota_atual], nota_atual+1);
    }

    dp[saque][nota_atual] = tot;

    return tot;
}

int main(){
    int s;
    cin >> s;

    for(int i = 0; i < qtd_notas.size(); i++)
        cin >> qtd_notas[i];
    
    cout << banco(s) << endl;

    return 0;
}