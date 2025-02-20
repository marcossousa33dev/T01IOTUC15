/*
  Professor Marcos Costa
  ESP32 WiFi Scanning
  Verifica as conexões disponíveis e se há necessidade 
  de informar senha.
 */

//Biblioteca WiFi
#include "WiFi.h"

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

    //Tempo para próxima verificação
    delay(5000);
  }
}
