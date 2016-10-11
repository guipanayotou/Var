/* 
 *  ESCOPO DO PROJETO - Versionamento no final do arquivo 
 *  
 *  Autor: Guilherme Martins Panayotou
 *  Sistema de automação da varanda urbana - projeto FACENS - outubro de 2016
 *  
 *  Declaração das constantes e váriaveis seguem o seguinte padrão:
 *   
 *   _componentePin = pino de entrada ou saída, valor constante (não altera o valor) - Usar " _ " no início e " Pin " no final  
 *   _variavelControle = variaveis de valores fixos que não têm pinos - valor constante (não altera o valor) - Usar " _ " no início
 *   variavelNome = variável com valores que serão alterados, utilizados em qualquer lugar no projeto
 *   
 *   lerSensor() = chamada de função de leitura de qualquer sensor - Usar " ler " em minusculo e depois o nome do sensor a ser lido, 
 *   primeira letra do nome do sensor em maiusculo 
 *   
 *   escreverSensor() = chamada de função de escrita de qualquer sensor - Usar " escrever " em minusculo e depois o nome do sensor a ser escrito, 
 *   primeira letra do nome do sensor em maiusculo 
 */

// Sensores LDR
byte _L1Pin = 0; // Define o LDR1
byte _L2Pin = 1; // Define o LDR2
byte _L3Pin = 2; // Define o LDR3
int luminosidade = 0; // Váriavel que recebe o valor da luminosidade, o valor é dado pela média entre os 3 LDRs
float _proporcaoLuz = 1.5; // Constante que será utilizada para multiplicar a luz de entrada caso exista mais luz

// Sensor de movimento PIR
byte _PIRPin = 2; //Pino ligado ao sensor PIR
byte movimento = 0; //Variavel para guardar valor do sensor

/*
 *  Função utilizada para declarar portas e valores, é utilizada apenas uma vez no inicio da execução
 */
void setup() {
  Serial.begin(9600); // Inicia a comunicação serial 
  pinMode(_PIRPin, INPUT); //Define pino sensor de movimento como entrada
}

/*
 * Função que se repete o tempo todo e é realizada infinitas vezes indefinidamente, todo o código vai aqui
 */
void loop() {
    luminosidade = lerLDR(); // Lê o sensor de luminosidade
    movimento = lerPIR(); // Lê o sensor de movimento 
    
    // Caso exista movimento, a luminosidade de entrada seria como se fosse maior do que realmente é
    if(movimento == HIGH){
       luminosidade = (luminosidade / _proporcaoLuz);  // divide a luminosidade de entrada por um valor fixo (declarado no escopo)
    }

    Serial.println(luminosidade);
    delay(300);
}

/*
 *  Função utilizada para fazer a leitura de todos os LDRs e retornar um valor já tratado, ou seja, a média entre todos eles 
 *  Quanto menor o valor, significa que tem mais luz no ambiente, valores variam de uns 100 até uns 1020
 */
 int lerLDR(){
    return ((analogRead(_L1Pin) + analogRead(_L2Pin) + analogRead(_L3Pin)) / 3); 
 }


 /*
  *  Função utilizada para fazer a leitura do sensor de movimento
  *  Retorna 1 caso haja movimento e caso contrário, retorna 0
  */
 byte lerPIR(){
    return digitalRead(_PIRPin);
 }


 /*
  *   VERSIONAMENTO
  *   
  *  Colocar a versão e o que foi moificado com data e hora para controle interno
  *   
  * Versão Alpha 0: 11/10/2016 - 01:30
  *   Iniciado projeto e fazendo a leitura dos sensores PIR e LDRs
  */
