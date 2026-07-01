# Sistema IoT para Monitoramento Ambiental de Racks de Infraestrutura

## Sobre o Projeto
Este projeto propõe uma solução IoT para monitorar as condições ambientais de racks de servidores e infraestrutura de TI. O sistema utiliza um ESP32 para coletar dados de temperatura, umidade e qualidade do ar, transmitindo-os via protocolo MQTT para um dashboard web em tempo real.

O objetivo principal é prevenir o superaquecimento e a degradação silenciosa de componentes de hardware através de alertas automatizados, atuando antes que os equipamentos apresentem falha térmica.

## Tecnologias Utilizadas
* **Microcontrolador:** ESP32 DevKit V1
* **Sensores:** DHT22 (Temperatura/Umidade) e MQ-135 (Qualidade do Ar)
* **Atuadores:** LED RGB e Buzzer
* **Linguagem:** C++ (Arduino IDE)
* **Comunicação:** Protocolo MQTT via Wi-Fi
* **Plataforma IoT:** Adafruit IO / ThingSpeak
* **Simulação:** Wokwi

## Estrutura do Repositório
* `main.cpp` (ou `.ino`): Código-fonte completo responsável pela coleta de dados e comunicação MQTT.
* `Relatorio_Tecnico.pdf`: Documentação técnica completa exigida pela disciplina.

## Como Executar a Simulação (Wokwi)
Caso queira testar o código via navegador:
1. Acesse o [Wokwi](https://wokwi.com/).
2. Crie um novo projeto para o **ESP32**.
3. Copie e cole o código-fonte disponibilizado neste repositório.
4. Adicione os componentes (DHT22, resistores, LEDs) conforme o esquemático descrito no relatório técnico.
5. Dê "Play" na simulação para iniciar a transmissão de dados.

## Demonstração Prática
[lique aqui para assistir ao vídeo de demonstração do sistema em funcionamento](COLOQUE_O_LINK_DO_SEU_VIDEO_AQUI)

---
*Projeto desenvolvido por Matheus Maximowitz Prause como Trabalho Prático para a disciplina de Internet das Coisas (IoT).*
