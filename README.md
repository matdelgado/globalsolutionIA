# Projeto de Monitoramento com ESP32, MQTT e Node-RED (Wokwi Simulator)

## Ideia do Projeto

Criamos um sistema de monitoramento de painéis solares ligado à inteligência artificial (IA). Este sistema inicial tem a IA ajustada para exibir um relatório simples, e o prompt será personalizado para cada cliente, permitindo que ele escolha como deseja visualizar as informações. O retorno da IA será integrado ao nosso front-end futuramente, permitindo a visualização de dados de consumo e eficiência energética de maneira dinâmica e personalizada.

## Descrição

Este projeto simula a leitura de sensores (LDR, Potenciômetro, DHT22) com um ESP32, utilizando o **Wokwi Simulator**. Os dados são enviados via MQTT para um broker online e podem ser consumidos diretamente pelo Node-RED para visualização em tempo real e geração de insights. O fluxo no Node-RED já está pronto e configurado, você só precisa importar o projeto e rodar.

## Arquitetura

1. **Wokwi Simulator**: Simula o ESP32 e os sensores.
2. **Broker MQTT**: Utiliza o `broker.hivemq.com` para transmissão dos dados.
3. **Node-RED**: Lê os dados MQTT, visualiza no dashboard e envia para a IA do Gemini.
4. **Gemini AI**: Geração de insights baseados nos dados coletados.

## Requisitos

- **Plataforma**:
  - Acesse o [Wokwi Simulator](https://wokwi.com).
  - Não é necessário hardware físico, tudo é simulado na web.

- **Software**:
  - **Wokwi Simulator**: Para simulação do ESP32.
  - **Node-RED**: Para consumir e visualizar os dados via MQTT.
  - **Broker MQTT**: Broker público `broker.hivemq.com`.

## Passo a Passo para Rodar a Solução

### 1. Importando o Projeto no Node-RED

O fluxo do Node-RED já está configurado e pronto para uso. Para rodá-lo:

1. **Clone o Repositório do GitHub**:
   - Clone o repositório para sua máquina.

2. **Importe o Fluxo no Node-RED**:
   - Abra o Node-RED e vá até o menu `Import` (no canto superior direito).
   - Importe o fluxo `.json` que está incluído no repositório.
   - O fluxo já estará configurado para conectar ao broker MQTT e visualizar os dados no dashboard.

3. **Rodando o Fluxo**:
   - Após importar o fluxo, clique em **Deploy** no Node-RED para começar a execução.
   - O Node-RED começará a ler os dados enviados pelo ESP32 e exibirá no dashboard em tempo real.
   - Você poderá observar o retorno do Gemini através da aba Debug do Node-RED.

   ![image](https://github.com/user-attachments/assets/e39ae28c-efd8-432b-8820-26b70908cce6)

4. **Rodando o Dashboard**:
   Para visualizar o dashboard no Node-RED:
   - Acesse o **UI do Node-RED**:
     1. No menu do Node-RED, clique em **Deploy**.
     2. Acesse o dashboard na URL: `http://localhost:1880/ui`.
     3. Se o Node-RED foi instalado localmente, basta abrir seu navegador e digitar `http://localhost:1880/ui` para visualizar os dados em tempo real.
    
    ![image](https://github.com/user-attachments/assets/2eb66c55-5b6d-482d-8b43-1fd2031e57dd)


   Caso você esteja usando o Node-RED em um servidor remoto, substitua `localhost` pelo IP do servidor.

### 2. Testando a Solução no Wokwi

Para testar a solução, siga os seguintes passos:

1. **Acesse o Projeto no Wokwi**: 
   - Abra o link do projeto: [Projeto no Wokwi](https://wokwi.com/projects/414401668996590593).
   - Clique em **Start Simulation** para iniciar a simulação.
  
   ![image](https://github.com/user-attachments/assets/1e892d80-9a89-4072-ba78-18f2167fc877)


2. **Simulação dos Sensores**:
   - No Wokwi, o ESP32 será simulado, e você poderá ver os sensores LDR, Potenciômetro e DHT22 sendo lidos a cada 5 segundos.

   ![image](https://github.com/user-attachments/assets/f49c4078-3198-4f07-ae52-af337a5ad214)


### 3. IA Gemini e Insights

A integração com a IA do Gemini permite gerar insights adicionais sobre o consumo, eficiência energética e condições ambientais. Esta etapa depende de como você deseja usar os dados coletados e se adaptará a cada cliente.

![image](https://github.com/user-attachments/assets/db9aca6a-9782-4efa-8bbb-6ed97c006630)

Podemos observar a geração de insights feita pela IA Gemini, que analisa os dados coletados dos sensores para fornecer informações valiosas sobre o consumo de energia, eficiência dos painéis solares e as condições ambientais. A partir desses insights, o sistema pode sugerir melhorias no uso da energia, identificar padrões de consumo e até prever possíveis falhas nos painéis solares.

Esses insights são personalizáveis de acordo com as necessidades de cada cliente, permitindo que ele visualize informações detalhadas sobre o desempenho de seus painéis solares de maneira dinâmica e ajustada ao seu contexto específico. Além disso, a IA pode adaptar os relatórios e recomendações baseadas nas variáveis de consumo e na eficiência energética, promovendo uma gestão mais eficaz e inteligente da energia gerada.

## Diagrama do Fluxo de Utilização

```plaintext
              +---------------------+
              |   Wokwi Simulator    |
              |  (Simula ESP32 +     |
              |   Sensores LDR,      |
              |   Potenciômetro,     |
              |   DHT22)             |
              +---------------------+
                        |
                        | MQTT
                        v
              +---------------------+
              |  Broker MQTT         |
              |  (broker.hivemq.com) |
              +---------------------+
                        |
                        | MQTT
                        v
              +---------------------+
              |     Node-RED         |
              |  (Recebe dados e     |
              |  Exibe no Dashboard) |
              +---------------------+
                        |
                        | Envia para Gemini
                        v
              +---------------------+
              |     Gemini AI        |
              |  (Geração de Insights|
              |  sobre Consumo e     |
              |  Eficiência Energética)|
              +---------------------+
