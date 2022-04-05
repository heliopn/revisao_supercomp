#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

struct item {
  int id;
  string stock;
  double value;
  double payment;
  double tax;
};
struct result {
  float tot_valor, tot_peso;
};

default_random_engine generator;
default_random_engine generator2;

double exaustiva(int W, vector<item> items, vector<item> &usados,
                 vector<item> &melhor) {
  double valor = 0.0;
  double payment = 0.0;
  double tax = 0.0;
  double sem_i = 0.0, com_i = 0.0;
  vector<item> items2 = items;
  if (items.empty() || W == 0){
    return 0;
  }
    
  if (items[0].value <= W) {
    usados.push_back(items[0]);
    valor = items[0].value;
    payment = items[0].payment;
    tax = items[0].tax;
    items.erase(items.begin());
    com_i = exaustiva(W - valor, items, usados, melhor);
  }
  items2.erase(items2.begin());
  sem_i = exaustiva(W, items2, usados, melhor);
  double valor_atual = 0.0, valor_melhor = 0.0;
  for (auto &el : usados) {
    valor_atual += (el.payment - el.tax);
  }
  for (auto &el : melhor) {
    valor_melhor += (el.payment - el.tax);
  }
  if (valor_atual > valor_melhor){
    melhor = usados;
  }
  usados.clear();
  return max(sem_i, (payment-tax) + com_i);
}

int main() {
  vector<item> stocks;
  item temp_item;
  float count = 0;
  float quant_obj;
  int W;
  cin >> quant_obj;
  cin >> W;
  // generator.seed(10);
  // generator2.seed(10);
  while (count < quant_obj) {
    temp_item.id = count;
    cin >> temp_item.stock;
    cin >> temp_item.value;
    cin >> temp_item.payment;
    cin >> temp_item.tax;
    stocks.push_back(temp_item);
    count++;
  }
  vector<item> usado;
  vector<item> melhor;
  sort(stocks.begin(), stocks.end(),
       [](item &x, item &y) { return x.value > y.value; });
  cout << "RESULTADO = " << exaustiva(W, stocks, usado, melhor) << "\n";
  for (auto &el : melhor) {
    cout << el.id << " ";
  }
	cout << endl;
}
