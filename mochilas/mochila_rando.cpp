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

void rando(vector<item> items, float max_peso) {

  float tot_peso = 0.0;
  float tot_valor = 0.0;

  vector<int> ids;
  for (int i = 0; (long unsigned)i < items.size(); i++) {
    int t = i;
    uniform_real_distribution<double> distribution(0.0, 1.0);
    if (distribution(generator) > 0.75) {
      uniform_int_distribution<int> distribution2(t, items.size());
      t = distribution2(generator2);

      if (find(ids.begin(), ids.end(), items[t].id) == ids.end()) {
        if ((tot_peso + items[t].peso) < max_peso) {
          tot_peso += items[t].peso;
          tot_valor += items[t].valor;
          ids.push_back(items[t].id);
        }
      }
    }
    if (find(ids.begin(), ids.end(), items[i].id) == ids.end()) {
      if ((tot_peso + items[i].peso) < max_peso) {
        tot_peso += items[i].peso;
        tot_valor += items[i].valor;
        ids.push_back(items[i].id);
      }
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
  rando(items, max_peso);
}