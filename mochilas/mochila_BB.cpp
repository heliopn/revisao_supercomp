#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

struct item {
  int id;
  double peso;
  double valor;
};
struct result {
  float tot_valor = 0.0;
  float tot_peso = 0.0;
};

int num_leaf = 0;
int num_copy = 0;
int num_bound = 0;
double valor_melhor = 0.0;

default_random_engine generator;
default_random_engine generator2;

double knapSack2(int W, vector<item> items, vector<item> &usados,
                 vector<item> &melhor) {
  double valor = 0.0;
  double peso = 0.0;
  double sem_i = 0.0, com_i = 0.0;
  vector<item> items2 = items;
  if (items.empty() || W == 0){
    num_leaf++;
    return 0;
  }
    
  if (items[0].peso <= W) {
    num_copy++;
    usados.push_back(items[0]);
    valor = items[0].valor;
    peso = items[0].peso;
    items.erase(items.begin());
    com_i = knapSack2(W - peso, items, usados, melhor);
  }
  items2.erase(items2.begin());
  sem_i = knapSack2(W, items2, usados, melhor);
  double valor_atual = 0.0, valor_melhor = 0.0;
  for (auto &el : usados) {
    valor_atual += el.valor;
  }
  for (auto &el : melhor) {
    valor_melhor += el.valor;
  }
  num_leaf++;
  if (valor_atual > valor_melhor){
    melhor = usados;
  }
  usados.clear();
  return max(sem_i, valor + com_i);
}

int main() {
  vector<item> items;
  item temp_item;
  float count = 0;
  float quant_obj;
  float max_peso;
  cin >> quant_obj;
  cin >> max_peso;
  // generator.seed(10);
  // generator2.seed(10);
  while (count < quant_obj) {
    temp_item.id = count;
    cin >> temp_item.peso;
    cin >> temp_item.valor;
    items.push_back(temp_item);
    count++;
  }
	int W = max_peso;
  vector<item> usado;
  vector<item> melhor;
  sort(items.begin(), items.end(),
       [](item &x, item &y) { return x.valor > y.valor; });

  cout << "RESULTADO = " << knapSack2(W, items, usado, melhor) << "\n";
  for (auto &el : melhor) {
    cout << el.id << " ";
  }
	cout << endl;
  cout << "leaf: " << num_leaf << " copy: " << num_copy << endl;
}