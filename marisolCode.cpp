#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

int main()
{
  string bytes;
  unsigned char byte;
  int count = 0;
  string macDestino;
  string macOrigen;
  string tipo;
  string datos;

  stringstream ss;
  fstream archivo("./paquetesRedes/ethernet_1.bin", ios::in);

  if (!archivo.is_open())
  {
    cout << "error" << endl;
  }
  else
  {
    while (archivo >> byte)
    {
      ++count;
      ss << setw(2) << setfill('0') << hex << static_cast<int>(byte);
      if (count == 6)
      {
        ss >> macDestino;
        ss.clear();
        cout << "MAC Destino: " << macDestino << endl;
      }
      else if (count == 12)
      {
        ss >> macOrigen;
        ss.clear();
        cout << "MAC Origen: " << macOrigen << endl;
      }
      else if (count == 14)
      {
        ss >> tipo;
        ss.clear();
        cout << "Tipo: " << tipo << endl;
      }
      else if (count < 12)
      {
        ss << ":";
      }
    }
    ss >> datos;
    ss.clear();
    cout << "Datos: " << datos << endl;
  }
  archivo.close();
  return 0;
}