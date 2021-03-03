#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
  unsigned char car;

  FILE *archivo;
  int counter{0};
  if ((archivo = fopen("./paquetesRedes/ethernet_1.bin", "rb")) == NULL)
  {
    cout << "Error en la apertura. Es posible que el fichero no exista \n";
  }
  else
  {
    while (!feof(archivo) and counter < 14)
    {
      car = fgetc(archivo);
      if (car < 9)
        cout << '0';
      cout << hex << static_cast<int>(car) << " ";
      ++counter;
    }
    fclose(archivo);
  }
}
