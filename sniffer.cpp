#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <cstring>

using namespace std;

void ipv4()
{
  unsigned char charBuffer;
  int byteInt;
  unsigned char charArray[20];
  string byteString;
  fstream file("./paquetesRedes/ethernet_ipv4_icmp.bin", ios::in);
  file.seekg(14, ios::beg);
  file.read((char *)&charArray, sizeof(charArray));

  // -------- ------- ------ ----- Version and Header Size----- ------ ------- --------

  byteInt = static_cast<int>(charArray[0]);
  byteString = bitset<8>(byteInt).to_string();

  string version = byteString.substr(0, 4);
  cout << "Version: " << stoi(version, 0, 2) << '\n';

  string headerSize = byteString.substr(4, 8);
  cout << "Tamano de cabecera: " << stoi(headerSize, 0, 2) << " Palabras" << '\n';

  // -------- ------- ------ ----- Service ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[1]);
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
  byteInt = static_cast<int>(charArray[2]);
  byteString = bitset<8>(byteInt).to_string();
  byteInt = static_cast<int>(charArray[3]);
  byteString += bitset<8>(byteInt).to_string();
  cout << "Longitud total: " << stoi(byteString, 0, 2) << endl;

  // -------- ------- ------ ----- Identifier ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[4]);
  byteString = bitset<8>(byteInt).to_string();
  byteInt = static_cast<int>(charArray[5]);
  byteString += bitset<8>(byteInt).to_string();
  cout << "Identificador: " << stoi(byteString, 0, 2) << endl;

  // -------- ------- ------ ----- Indicator ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[6]);
  byteString = bitset<8>(byteInt).to_string();

  cout << "Flags: \n";
  cout << "Reservado\n";
  cout << ((byteString[1] == '0') ? "Divisible" : "No divisible") << '\n';
  cout << ((byteString[2] == '0') ? "Ultimo Fragmento" : "Fragmento Intermedio") << '\n';

  // -------- ------- ------ ----- Fragment Position ----- ------ ------- --------
  byteString = byteString.substr(3, 5);
  byteInt = static_cast<int>(charArray[7]);
  byteString += bitset<8>(byteInt).to_string();
  cout << "Posicion de Fragmento: " << stoi(byteString, 0, 2) << endl;

  // -------- ------- ------ ----- Life Time (TTL) ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[8]);
  byteString += bitset<8>(byteInt).to_string();
  cout << "Tiempo de vida: " << stoi(byteString, 0, 2) << '\n';

  // -------- ------- ------ ----- Protocol ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[9]);
  byteString = bitset<8>(byteInt).to_string();
  int protocol = stoi(byteString, 0, 2);
  cout << "Protocolo: ";
  if (protocol == 1)
    cout << "ICMP v4";
  else if (protocol == 6)
    cout << "TCP";
  else if (protocol == 17)
    cout << "UDP";
  else if (protocol == 58)
    cout << "ICMPv6";
  else if (protocol == 118)
    cout << "STP";
  else if (protocol == 121)
    cout << "SMP";
  else
    cout << "Protocolo no identificado";

  // -------- ------- ------ ----- Checksum ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[10]);
  byteString = bitset<8>(byteInt).to_string();
  byteInt = static_cast<int>(charArray[11]);
  byteString += bitset<8>(byteInt).to_string();

  stringstream ss;
  ss << setfill('0') << hex << stoi(byteString, 0, 2);
  string checksum;
  ss >> checksum;
  cout << "\nChecksum: " << checksum << '\n';

  // -------- ------- ------ ----- IP Address Origin ----- ------ ------- --------
  string ipAddressOrigin;
  for (int i = 12; i <= 15; i++)
  {
    if (i > 12)
      ipAddressOrigin += ".";
    byteInt = static_cast<int>(charArray[i]);
    byteString = bitset<8>(byteInt).to_string();
    ipAddressOrigin += to_string(stoi(byteString, 0, 2));
  }

  cout << "Direccion IP de origen: " << ipAddressOrigin << '\n';

  // -------- ------- ------ ----- IP Address Origin ----- ------ ------- --------
  string ipAddressDestination;
  for (int i = 16; i <= 19; i++)
  {
    if (i > 16)
      ipAddressDestination += ".";
    byteInt = static_cast<int>(charArray[i]);
    byteString = bitset<8>(byteInt).to_string();
    ipAddressDestination += to_string(stoi(byteString, 0, 2));
  }

  cout << "Direccion IP de Destino: " << ipAddressDestination << '\n';
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
          // archivo.close();
          ipv4();
          // break;
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
      else if (count == 34)
      {
        string test;
        ss >> test;
        ss.clear();
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