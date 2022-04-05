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

default_random_engine generator;
default_random_engine generator2;

void mais_leve(vector<item> items, int max_peso) {

  sort(items.begin(), items.end(),
       [](item &x, item &y) { return x.peso < y.peso; });

  int tot_peso = 0;
  int tot_valor = 0;
  vector<int> ids;
  for (auto &e : items) {
    if ((tot_peso + e.peso) <= max_peso) {
      tot_peso += e.peso;
      tot_valor += e.valor;
      ids.push_back(e.id);
    }
  }
  cout << tot_peso << " " << tot_valor << " " << 0 << endl;
  sort(ids.begin(), ids.end(), [](int &x, int &y) { return x < y; });
  for (auto &e : ids) {
    cout << e << " " << items[e].valor << endl;
  }
}

int main() {
  vector<item> items;
  item temp_item;
  float count = 0;
  int quant_obj;
  int max_peso;
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
  mais_leve(items, max_peso);
}