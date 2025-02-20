/*
  Professor Marcos Costa
  ESP32 WiFi Scanning
  Verifica as conexões disponíveis e se há necessidade 
  de informar senha e conectar a melhor rede aberta disponível
 */

//Biblioteca WiFi
#include "WiFi.h"

String wifiConnected = ""; //Variável para controle do nome da rede conectada

void setup() {
  // Iniciando a comunicação serial:
  Serial.begin(115200); //Velocidade -> Comunicação Serial
  Serial.println("Iniciando WiFi ...");
  WiFi.mode(WIFI_STA); // Modo de conexão, neste caso iremos procurar roteadores
  Serial.println("Configuração concluída!");
}

void loop() {
  Serial.println("Procurando ...");

  int qtdeRedes = WiFi.scanNetworks(); //Quantidade de redes encontradas
  Serial.println("Verificação concluída.");

  if (qtdeRedes == 0){
    Serial.println("Nenhuma rede encontrada.");
  }else{
    Serial.print("Total de rede(s) encontrada(s): ");
    Serial.println(qtdeRedes);

    //Estrutura de repetição para mostrarmos todas as redes encontradas
    for (int i = 0; i < qtdeRedes; i++){
      Serial.print(i + 1); //Sequencia numérica
      Serial.print(": ");

      Serial.print(WiFi.SSID(i)); //Nome da rede encontrada
      Serial.print(" - Sinal (");

      Serial.print(WiFi.RSSI(i)); //Itensidade do Sinal
      Serial.print(") - Possui senha? ");
      
      //WIFI_AUTH_OPEN verifica se a rede possui senha
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Não" : "SIM");
      delay(10);
    }

    //Verificando a rede aberta com melhor sinal
    Serial.println("--------------------------------------------");
    Serial.println("Verificando a rede aberta com melhor sinal");
    for (int i = 0; i < qtdeRedes; ++i) {
      if (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) {
        Serial.print("Rede aberta com melhor sinal: ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" - Sinal: ");
        Serial.println(WiFi.RSSI(i));
        Serial.println("--------------------------------------------");
        
        Serial.println();
        
        if (wifiConnected == ""){
          //Conectando a rede aberta com melhor sinal
          Serial.print("Conectando a melhor rede aberta encontrada: ");
          Serial.println(WiFi.SSID(i));
  
          //Efetua a conexão com a rede wifi
          WiFi.begin(WiFi.SSID(i)); 
  
          //Variável para controlar as tentativas de conexão
          int tentativas = 0;
  
          while (WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
            tentativas++;
            //Foi tentado conectar 100 vezes, como não conseguir, para o processo
            if (tentativas == 100) break; //Mantém aguardando conexão por 15 segundos
            delay(100);
          }
          
          Serial.println("");
          
          if (WiFi.status() == WL_CONNECTED) {
            wifiConnected = WiFi.SSID(i);
            Serial.println("WiFi conectado!" + wifiConnected);
          } else {
            wifiConnected = "";
            Serial.println("Nao foi possivel conectar.");
          }
          break; //Finaliza o loop
        }else{
          Serial.println("ESP32 ja conectado a Rede: " + wifiConnected);
        }
        Serial.println("--------------------------------------------");
      }
    }

    //Tempo para próxima verificação
    delay(5000);
  }
}
