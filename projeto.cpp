#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Mapeia tipos para índice em Af
 P=0, N=1, A=2, B=3, T=4 */
int typeId(char c){
  if (c == 'P')
    return 0;
  if (c == 'N')
    return 1;
  if (c == 'A')
    return 2;
  if (c == 'B')
    return 3;
  return 4;
}

struct aminoacid{
  unsigned long long _pot;
  int _type;
};

void buildseq(int l, int r, vector<vector<int>> &bestK, vector<int> &out){
  if (r <= l + 1)
    return;
  int k = bestK[l][r];
  buildseq(l, k, bestK, out);
  buildseq(k, r, bestK, out);
  out.push_back(k);
}

int main(){
  // Matriz de afinidades Af[typeL][typeR]
  unsigned long long Af[5][5] = {
    // P  N  A  B  T
      {1, 3, 1, 3, 1}, // P
      {5, 1, 0, 1, 1}, // N
      {0, 1, 0, 4, 1}, // A
      {1, 3, 2, 3, 1}, // B
      {1, 1, 1, 1, 1}  // T
  };

  int n;
  cin >> n;

  vector<unsigned long long> pots;
  pots.reserve(n);
  for (int i = 0; i < n; ++i) {
    unsigned long long p;
    cin >> p;
    pots.push_back(p);
  }

  string types;
  cin >> types;

  vector<aminoacid> protein;
  protein.reserve(n + 2);
  protein.push_back({1, typeId('T')});

  for (int i = 0; i < n; ++i) {
    protein.push_back({pots[i], typeId(types[i])});
  }
  protein.push_back({1, typeId('T')});

  // dp[l][r] = energia máxima no intervalo [l,r]
  // bestK[l][r] = melhor k (índice removido por último em [l,r])
  vector<vector<unsigned long long>> dp(n + 2, vector<unsigned long long>(n + 2, 0));
  vector<vector<int>> bestK(n + 2, vector<int>(n + 2, -1));

  for(int len = 2; len < n + 2; len++){
    for(int l = 0; l + len < n + 2; l++){
      int r = l + len;
      for(int k = l + 1; k < r; k++){
        unsigned long long energy =
            dp[l][k] + dp[k][r] +
            protein[l]._pot * Af[protein[l]._type][protein[k]._type] *protein[k]._pot +
            protein[k]._pot * Af[protein[k]._type][protein[r]._type] *protein[r]._pot;
        if(energy >= dp[l][r]){
          dp[l][r] = energy;
          bestK[l][r] = k;
        }
      }
    }
  }
  unsigned long long max_energy = dp[0][n + 1];

  // Reconstrói e imprime sequência ótima
  vector<int> answer;
  buildseq(0, n + 1, bestK, answer);

  cout << max_energy << endl;
  for(size_t i = 0; i < answer.size(); i++)
    cout << answer[i] << (i + 1 < answer.size() ? ' ' : '\n');

  return 0;
}
