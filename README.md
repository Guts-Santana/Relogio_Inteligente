# Relogio-Inteligente
# MSP430F5529 Sensor and Bluetooth Integration

Este projeto com o microcontrolador MSP430F5529 tem o intuito de monitorar frequência cardíaca, tremores e temperatura exibindo os resultados em um display LCD e na porta serial do celular através de um módulo bluetooth.

## Sumário

- [Descrição](#descrição)
- [Componentes](#componentes)
- [Esquema de Ligação](#esquema-de-ligação)
- [Instalação](#instalação)
- [Uso](#uso)
- [Autores](#autores)

## Descrição

O projeto lê dados do sensor MPU6050 (aceleração, giroscópio e temperatura) e do módulo MAX30102 (frequência cardíaca) e os envia via Bluetooth usando o módulo HM10. Os dados também são exibidos em um display LCD.

## Componentes

- MSP430F5529
- Módulo Bluetooth HM10
- Sensor MPU6050
- Sensor MAX30102
- Display LCD
- Fios de conexão
- Uma protoboard

## Esquema de Ligação

### Conexões do HM10

| HM10 Pin | MSP430 Pin       |
|----------|------------------|
| VCC      | 5V               |
| GND      | GND              |
| TXD      | P3.3             |
| RXD      | P3.4             |

### Conexões do MPU6050

| MPU6050 Pin | MSP430 Pin     |
|-------------|----------------|
| VCC         | 5V             |
| GND         | GND            |
| SDA         | P3.1           |
| SCL         | P3.0           |

### Conexões do MAX30102

| MAX30102 Pin | MSP430 Pin     |
|--------------|----------------|
| VCC          | 5V             |
| GND          | GND            |
| SDA          | P3.1           |
| SCL          | P3.0           |

### Conexões do Display LCD

| LCD Pin | MSP430 Pin |
|---------|------------|
| VCC     | 5V         |
| GND     | GND        |
| SCL     | P3.0       |
| SDA     | P3.1       |

## Instalação

1. **Configuração do Ambiente de Desenvolvimento**:
    - Instale o [Code Composer Studio](https://www.ti.com/tool/CCSTUDIO).
    - Baixe e configure os drivers do MSP430.

2. **Configuração do Código**:
    - Clone o repositório:
      ```bash
      git clone https://github.com/Guts-Santana/Relogio-inteligente.git
      ```
    - Importe o projeto no Code Composer Studio.

3. **Carregue o Código no MSP430**:
    - Conecte o MSP430 ao seu computador via USB.
    - Compile e carregue o código usando o Code Composer Studio.

## Uso

1. **Inicialização**:
    - Ligue o MSP430.
    - O dispositivo conectado ao HM-10 receberá uma mensagem pedindo o horário.
    - O display LCD exibirá a hora, frequência cardíaca, temperatura e se há tremores ou não.

2. **Leitura dos Dados**:
    - Os dados do sensor serão lidos e exibidos no display LCD.
    - Os dados também serão enviados via Bluetooth para dispositivos conectados.

## Autores

- [Gustavo Santana](https://github.com/Guts-Santana)
