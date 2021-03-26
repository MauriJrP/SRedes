#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <bitset>
#include <cstring>

using namespace std;

void ICMPv4()
{
  cout << "-------- ------- ------ ----- ICMPv4 ----- ------ ------- --------\n";
  int byteInt;
  string byteString;
  unsigned char charArray[4];
  fstream file("./paquetesRedes/ethernet_ipv4_icmp.bin", ios::in);
  file.seekg(34, ios::beg);
  file.read((char *)&charArray, sizeof(charArray));

  // -------- ------- ------ ----- Type ----- ------ ------- --------

  byteInt = static_cast<int>(charArray[0]);
  byteString = bitset<8>(byteInt).to_string();
  int type = stoi(byteString, 0, 2);
  cout << "Tipo: " << type << " ";

  if (type == 0)
    cout << "Respuesta de eco";
  else if (type == 3)
    cout << "Destino inaccesible";
  else if (type == 4)
    cout << "Disminucion de trafico desde el origen";
  else if (type == 5)
    cout << "Redireccionar - cambio de ruta";
  else if (type == 8)
    cout << "Solicitud de eco";
  else if (type == 11)
    cout << "Tiempo excedido para un datagrama";
  else if (type == 12)
    cout << "Problema de parametros";
  else if (type == 13)
    cout << "Solicitud de marca de tiempo";
  else if (type == 14)
    cout << "Respuesta de marca de tiempo";
  else if (type == 15)
    cout << "Solicitud de informacion";
  else if (type == 16)
    cout << "Respuesta de informacion";
  else if (type == 17)
    cout << "Solicutod de mascara de direccion";
  else if (type == 18)
    cout << "Respuesta de mascara de direccion";

  // -------- ------- ------ ----- Code ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[1]);
  byteString = bitset<8>(byteInt).to_string();
  int code = stoi(byteString, 0, 2);
  cout << "\nCodigo: " << code << " ";

  if (code == 0)
    cout << "No se puede llegar a la red";
  else if (code == 1)
    cout << "No se puede llegar al host o aplicacion de destino";
  else if (code == 2)
    cout << "El destino no se dispone del protocolo solicitado";
  else if (code == 3)
    cout << "No se puede llegar al puerto destino a la aplicacion destino no esta libre";
  else if (code == 4)
    cout << "Se necesita aplicar fragmentacion, pero el flag correspondiente indica lo contrario";
  else if (code == 5)
    cout << "La ruta de origen no es correcta";
  else if (code == 6)
    cout << "No se conoce la red destino";
  else if (code == 7)
    cout << "No se conoce el host destino";
  else if (code == 8)
    cout << "El host origen esta aislado";
  else if (code == 9)
    cout << "La comunicacion con la red destino esta prohibida por razones administrativas";
  else if (code == 10)
    cout << "La comunicacion con el host destino esta prohibida por razones administrativas";
  else if (code == 11)
    cout << "No se puede llegar a la red destino debido al Tipo de servicio";
  else if (code == 12)
    cout << "No se puede llegar al host destino debido al Tipo de servicio";

  // -------- ------- ------ ----- Checksum ----- ------ ------- --------
  byteInt = static_cast<int>(charArray[2]);
  byteString = bitset<8>(byteInt).to_string();
  byteInt = static_cast<int>(charArray[3]);
  byteString += bitset<8>(byteInt).to_string();

  stringstream ss;
  ss << setfill('0') << hex << stoi(byteString, 0, 2);
  string checksum;
  ss >> checksum;
  cout << "\nChecksum: " << checksum << '\n';
}

void ipv4()
{
  cout << "-------- ------- ------ ----- ipv4 ----- ------ ------- --------\n";
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
  cout << "  Reservado\n";
  cout << ((byteString[1] == '0') ? "  Divisible" : "  No divisible") << '\n';
  cout << ((byteString[2] == '0') ? "  Ultimo Fragmento" : "  Fragmento Intermedio") << '\n';

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

  // -------- ------- ------ ----- Protocol ----- ------ ------- --------
  if (protocol == 1)
    ICMPv4();
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
      else if (count == 38)
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