#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
  unsigned char car;

  FILE *archivo;
  int counter{0};
  string code{""};
  unsigned int code1;
  unsigned int code2;
  if ((archivo = fopen("./paquetesRedes/ethernet_1.bin", "rb")) == NULL)
  {
    cout << "Error en la apertura. Es posible que el fichero no exista \n";
  }
  else
  {
    while (!feof(archivo))
    {
      car = fgetc(archivo);
      if (counter == 0)
      {
        code1 = static_cast<int>(car);

        cout << "Direccion MAC destino: ";
      }
      if (counter == 6)
      {
        cout << "\nDireccion MAC origen: ";
      }
      if (counter == 12)
      {
        cout << "\nTipo de codigo: ";
      }
      if (counter == 13)
      {
        code2 = static_cast<int>(car);
      }
      if (counter == 14)
      {
        cout << "\nData: ";
      }
      if (car < 9)
        cout << '0';
      cout << hex << static_cast<int>(car) << ":";
      ++counter;
    }
    fclose(archivo);
    code = (code1 < 9 ? '0' + to_string(code1) : to_string(code1)) + (code2 < 9 ? '0' + to_string(code2) : to_string(code2));
    cout << "\ncodigo: " << code;
    int test = std::stoi(code);
    cout << "prueba: " << test;
    // switch (test)
    // {
    // case '':
    //   /* code */
    //   break;

    // default:
    //   break;
    // }
  }
}

// std::cout << MACAddressDestino;

// while (!feof(archivo))
// {
//   car = fgetc(archivo);
//   if (car < 9)
//     std::cout << '0';
//   if (counter < 6)
//   {
//     MACAddressDestino += car;
//   }
//   else if (counter > 5 and counter < 12)
//   {
//     // MACAddressOrigen += static_cast<int>(car);
//     std::cout << hex << static_cast<int>(car) << " ";
//   }
//   else if (counter > 12 and counter < 14)
//   {
//     // code += static_cast<int>(car);
//     std::cout << hex << static_cast<int>(car) << " ";
//   }
//   else
//   {
//     // data += static_cast<int>(car);
//     std::cout << hex << static_cast<int>(car) << " ";
//   }
//   ++counter;
// }
