#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <cstring>

using namespace std;

void ipv4()
{
  unsigned char *charBuffer;
  int byteInt;
  string byteString;
  fstream file("./paquetesRedes/ethernet_ipv4_icmp.bin", ios::in);
  file.seekg(14, ios::beg);

  // -------- ------- ------ ----- Version and Header Size----- ------ ------- --------
  file.read((char *)charBuffer, sizeof(char));
  byteInt = static_cast<int>(*charBuffer);
  byteString = bitset<8>(byteInt).to_string();

  string version = byteString.substr(0, 4);
  cout << "Version: " << stoi(version, 0, 2) << '\n';

  string headerSize = byteString.substr(4, 8);
  cout << "Tamano de cabecera: " << stoi(headerSize, 0, 2) << " Palabras" << '\n';

  // -------- ------- ------ ----- Service ----- ------ ------- --------
  file.read((char *)charBuffer, sizeof(char));
  byteInt = static_cast<int>(*charBuffer);
  byteString = bitset<8>(byteInt).to_string();

  string priority = byteString.substr(0, 3);
  if (priority == "000")
    priority = "De rutina";
  else if (priority == "001")
    priority = "Prioritario";
  else if (priority == "010")
    priority = "Inmediato";
  else if (priority == "011")
    priority = "Relampago";
  else if (priority == "100")
    priority = "Invalidacion relampago";
  else if (priority == "101")
    priority = "Procesando llamada critica y de emergencia";
  else if (priority == "110")
    priority = "Control de trabajo de internet";
  else
    priority = "Control de red";

  cout << "Prioridad: " << priority;
  cout << "\nRetardo: " << ((byteString[3] == '0') ? "normal" : "bajo");
  cout << "\nRendimiento: " << ((byteString[4] == '0') ? "normal" : "alto");
  cout << "\nFiabilidad: " << ((byteString[5] == '0') ? "normal" : "alta") << '\n';

  // -------- ------- ------ ----- Total Length ----- ------ ------- --------
  file.read((char *)charBuffer, sizeof(char) * 2);
  byteInt = static_cast<int>(charBuffer[0]);
  byteString = bitset<8>(byteInt).to_string();
  byteInt = static_cast<int>(charBuffer[1]);
  byteString += bitset<8>(byteInt).to_string();
  cout << "Longitud total: " << stoi(byteString, 0, 2) << endl;

  // -------- ------- ------ ----- Identifier ----- ------ ------- --------
  file.read((char *)charBuffer, sizeof(char) * 2);
  byteInt = static_cast<int>(charBuffer[0]);
  byteString = bitset<8>(byteInt).to_string();
  byteInt = static_cast<int>(charBuffer[1]);
  byteString += bitset<8>(byteInt).to_string();
  cout << "Identificador: " << stoi(byteString, 0, 2) << endl;
}

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
  fstream archivo("./paquetesRedes/ethernet_ipv4_icmp.bin", ios::in);

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
        cout << "Tipo: " << tipo << " ";

        if (tipo == "0800")
        {
          cout << "IPv4" << endl;
          archivo.close();
          ipv4();
          break;
        }
        else if (tipo == "0806")
          cout << "ARP" << endl;
        else if (tipo == "8035")
          cout << "RARP" << endl;
        else if (tipo == "86DD")
          cout << "IPv6" << endl;
        else
        {
          cout << "El IP no está contemplado.";
        }

        ss.clear();
      }
      else if (count < 12)
      {
        ss << ":";
      }
    }
    ss >> datos;
    ss.clear();
    // cout << "Datos: " << datos << endl;
  }
  archivo.close();
  return 0;
}