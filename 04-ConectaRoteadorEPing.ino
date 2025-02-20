/*********
  Professor Marcos Costa
  Conectando a um roteador e
  Fazendo um Ping com Esp32 para verificar se 
  o Esp32 está na Web validando dois sites.
*********/

#include <WiFi.h>
#include <ESP32Ping.h>

//Constantes que terão o dados da Rede WiFi
const char* ssid = "IoT-Senac";
const char* password = "Senac@2025";

//"Banco de Dados" com os sites para pings
const char* site[] = {"www.senactaboao.com.br", "www.google.com.br", "www.marcoscosta.eti.br"};

void setup() {
  //Iniciar a comunicação serial
  Serial.begin(115200); 
  //Chamada da função para conexão com WiFi
  conectaWiFi();
  Serial.println("==============================================================");
  //Chamada da função para verificações dos Pings
  verificaSite();
}

void loop(){  
  //Não possui execução
}

void conectaWiFi() {
  Serial.print("Conectando em ");
  Serial.println(ssid);

  //Inicia a conexão de acorod com os parâmetros do roteador escolhido
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());  
}

void verificaSite() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi não está conectado. Não será possível realizar o ping.");
    return;
  }

  for (int x = 0; x < sizeof(site) / sizeof(site[0]); x++) {
    Serial.print("Pingando o site: ");
    Serial.println(String(site[x]));

    //Variável booelana que recebe True ou False do Ping realizado de até 5 segundos
    bool success = Ping.ping(site[x], 5); 
  
    if (!success) {
      Serial.println("O Ping falhou!");
    } else {
      Serial.println("Ping no site foi realizado com sucesso!");
    }
    
    Serial.println("==============================================================");
  }
}
