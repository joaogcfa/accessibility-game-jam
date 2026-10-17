<h1 align="center">Dualsense Unreal Plugin</h1>

<p align="center">
Integre todos os recursos do controle DualSense™ e DualShock 4® da Sony no seu projeto Unreal Engine para Windows, Linux, Mac e PlayStation.
<br />
<br />
<a href="https://github.com/rafaelvaloto/WindowsDualsenseUnreal/issues">Reportar Bug</a>
·
<a href="https://github.com/rafaelvaloto/WindowsDualsenseUnreal/issues">Sugerir Funcionalidade</a>
·
<a target="_blank" href="https://github.com/rafaelvaloto/WindowsDualsenseUnreal/wiki">Documentação
</a>
</p>

<p align="center">
<a href="https://github.com/rafaelvaloto/WindowsDualsenseUnreal/releases">
<img src="https://img.shields.io/github/v/release/rafaelvaloto/WindowsDualsenseUnreal?style=for-the-badge&logo=github" alt="Latest Release">
</a>
<a href="https://github.com/rafaelvaloto/WindowsDualsenseUnreal/blob/main/LICENSE">
<img src="https://img.shields.io/github/license/rafaelvaloto/WindowsDualsenseUnreal?style=for-the-badge" alt="Licença">
</a>
<img src="https://img.shields.io/badge/Unreal%20Engine-5.2+-blue?style=for-the-badge&logo=unrealengine" alt="Unreal Engine 5.x">
<br/>
<img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Platform: Windows">
<img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="Platform: Linux">
<img src="https://img.shields.io/badge/macOS-000000?style=for-the-badge&logo=apple&logoColor=white" alt="Platform: macOS">
<img src="https://img.shields.io/badge/PlayStation-0070D1?style=for-the-badge&logo=playstation&logoColor=white" alt="Platform: PlayStation">
</p>

## Aviso Legal e Marcas Registradas

"PlayStation", "PlayStation Family Mark", "PS5 logo", "PS5", "DualSense" e "DualShock" são marcas registradas ou marcas comerciais da Sony Interactive Entertainment Inc. "SONY" é uma marca registrada da Sony Corporation. "Windows" é uma marca registrada da Microsoft Corporation. "Linux" é uma marca registrada de Linus Torvalds. "Mac" é uma marca registrada da Apple Inc.

O autor deste projeto não é afiliado, associado, autorizado ou de qualquer forma oficialmente conectado com a Sony Interactive Entertainment Inc., Microsoft Corporation, Apple Inc. ou Linus Torvalds. Este é um projeto independente e não oficial.


## 📖 Sobre o Projeto

Construído com uma arquitetura multiplataforma, este plugin para Unreal Engine fornece uma solução unificada para integrar os controles DualSense™ (PlayStation 5) e DualShock 4® (PlayStation 4). Ele oferece suporte nativo no PC e, ao mesmo tempo, foi projetado para ser facilmente compilado para outras plataformas da Unreal Engine, incluindo PlayStation®. Este ativo fornece acesso direto à API ao conjunto completo de recursos de cada controlador, incluindo o revolucionário Haptic Feedback e Adaptive Triggers do DualSense™. Todos os recursos são expostos por meio de uma biblioteca de funções limpa e bem documentada para Blueprint e C++.

Projetado para preencher a lacuna deixada pelo suporte genérico ao controlador, este ativo capacita os desenvolvedores a implementar o feedback imersivo e de alta fidelidade que torna os controladores da Sony únicos.

## ✨ Funcionalidades
* 🏗️ **Arquitetura Multiplataforma Extensível**: Sua arquitetura flexível permite a compilação para todas as plataformas disponíveis na Unreal Engine. A adaptação para novos hardwares é feita simplesmente implementando a interface de conexão.
* 🔌 **Conexão Dinâmica (Hot-Swap)**: Detecta a conexão e desconexão de controles automaticamente, mesmo durante o gameplay.
* ⚡ **Otimizado para Multiplayer**: Arquitetura de alta performance com impacto mínimo em jogos de rede.
* 🎮 **Integração Perfeita de Input**: Coexiste perfeitamente com os gerenciadores de input nativos da Unreal (como o Enhanced Input) e outros plugins de gamepad, evitando conflitos entre dispositivos.
* 🎯 **Gatilhos Adaptáveis**: Controle total sobre resistência, efeito e vibração nos gatilhos R2/L2.
* 🔊 **Vibração Baseada em Áudio**: Sincronize o feedback háptico do controle com qualquer fonte de áudio do jogo.
* 💡 **Controle da Lightbar**: Altere a cor do LED do controle dinamicamente.
* 🎤 **Microfone e Áudio**: Gerencie o LED do botão de mudo, o volume do alto-falante e o áudio do headset.
* ⚙️ **Force Feedback**: Integração nativa com o sistema de Force Feedback da Unreal Engine para a vibração padrão dos motores.
* 🎮 **Suporte a Múltiplos Controles**: Gerencie até 4 controles conectados simultaneamente.

## 🚀 New Feature: Live Trigger Effect Testing via Console

You can now test and fine-tune adaptive trigger effects directly in the Unreal Engine console. This allows for rapid prototyping and debugging of haptic sensations without recompiling code or setting up Blueprint nodes.

Use the `ds.SetTrigL` and `ds.SetTrigR` commands to send raw 10-byte HEX arrays directly to the controller, or use preset helper commands like `ds.BowR` and `ds.GallopR` to test specific common effects.

For a complete guide on the available commands and the raw byte structure for each effect, please see the new Wiki documentation page:
**[➡️ Wiki Page: Console Commands & HEX Reference](https://github.com/rafaelvaloto/WindowsDualsenseUnreal/wiki/%F0%9F%8E%AE-DualSense-Trigger-Effects:-Console-Commands-&-HEX-Reference)**

## 🎮 Projeto de Exemplo: Arena Shooter UE 5.6

To demonstrate the practical use of the **Dualsense Unreal Plugin**, a sample project has been developed using the [*Arena Shooter* template](https://www.unrealengine.com/marketplace/en-US/product/arena-shooter-template) and upgraded to Unreal Engine 5.6. This project integrates key features of the DualSense controller to enhance the player's experience.

* 🎯 **Mira por Giroscópio**: Um tutorial completo sobre como implementar um sistema de mira por giroscópio (ADS) preciso e responsivo, utilizando o template Arena Shooter.
    ➡️ **[[Leia o Tutorial de Mira por Giroscópio]](https://github.com/rafaelvaloto/WindowsDualsenseUnreal/wiki/Example-Project:-Gyroscope-Aiming)**

* 🔫 **Arena Shooter**: Um exemplo utilizando o template Arena Shooter que implementa gatilhos adaptáveis para armas automáticas/semiautomáticas e feedback háptico para dano no jogador.
    ➡️ **[[Leia o Tutorial do Arena Shooter]](https://github.com/rafaelvaloto/WindowsDualsenseUnreal/wiki/Example-Project:-Arena-Shooter-Tutorial)**
  
![Arena Shooter UE 5.6](Images/ArenaBanner.jpg)

### Funcionalidades Implementadas

Neste exemplo, as seguintes funcionalidades do DualSense foram integradas para proporcionar uma experiência de jogo mais imersiva:

* 🔫 **Automatic Gun**: Experimente disparos totalmente automáticos com feedback háptico apropriado, simulando recuo e vibração realistas da arma.
* 🎯 **Semi-Automatic Gun**: Participe de tiroteios precisos com armas semiautomáticas, onde cada tiro oferece sensações hápticas distintas e resistência nos gatilhos.
* 💥 **Vibration on Player Hit & Visual Feedback**: Sinta o impacto! O controle vibra dinamicamente quando o jogador sofre dano, complementado por um feedback visual na tela para uma imersão aprimorada e percepção imediata.
* 💡 **LED Color Change on Player Hit**: A luz de LED do controle DualSense muda de cor dinamicamente quando o jogador é atingido, oferecendo um sinal visual imediato e intuitivo do dano recebido, melhorando a consciência situacional.

### Onde Baixar

Você pode baixar o Parrot Game Sample com a integração do DualSense diretamente pelo link.

- [**Download the example project for the editor here**](https://drive.google.com/file/d/1oornHLpanEoHoDPRL1jfF_hvU17phsbp/view?usp=drive_link)
- [**Download the compiled version of the example project here**](https://drive.google.com/file/d/1H6lvd0Ta-M4Pwtu2w2s4YyTaPobaqKfc/view?usp=drive_link)

> 📝 **Note**: The examples for these features are implemented directly within the Arena Shooter template's `BP_ShooterPlayerController` and `BP_ShooterCharacter` Blueprints.

## 🎮 Projeto de Exemplo: Parrot Game Sample

Para demonstrar o uso prático do **Windows Dualsense Unreal Plugin**, foi desenvolvido um projeto de exemplo utilizando o [*Parrot Game Sample*](https://dev.epicgames.com/documentation/pt-br/unreal-engine/parrot-game-sample-for-unreal-engine) da Epic Games. Este projeto integra funcionalidades-chave do controle DualSense para aprimorar a experiência do jogador.

![Parrot Game Sample](Images/parrot-game-sample-banner.jpg)

### Funcionalidades Implementadas

Neste exemplo, as seguintes funcionalidades do DualSense foram integradas para proporcionar uma jogabilidade mais imersiva:

* **Feedback Visual**: A Lightbar do controle é utilizada para fornecer feedback visual em tempo real ao jogador, alterando cores e efeitos de acordo com eventos do jogo.
* **Vibração (Force Feedback)**: O sistema nativo de Force Feedback foi utilizado para criar efeitos de vibração detalhados, aumentando a imersão em momentos importantes do gameplay.

> 💡 **Dica Pro para Maior Imersão**: Para uma experiência de áudio ainda mais profunda, conecte o controle via USB e utilize um fone de ouvido diretamente nele. Essa configuração também funciona com o controle conectado via Bluetooth, oferecendo maior flexibilidade.

Este projeto serve como um guia prático para desenvolvedores que desejam ver o plugin em ação e aprender como integrar os recursos exclusivos do controle DualSense em seus próprios jogos.

### Onde Baixar

Você pode baixar o projeto de exemplo *Parrot Game Sample* com a integração do DualSense diretamente do nosso repositório no GitHub.


- [**Baixe o projeto de exemplo para o editor aqui**](https://drive.google.com/file/d/198Dko7ZwIX1vz9jw7RtYp4arY9Qp5bJ4/view?usp=drive_link)
- [**Baixe a versão compilada do projeto de exemplo aqui**](https://drive.google.com/file/d/144hM71xZufBe29UzpTNQ1rRe0AYWC-Ka/view?usp=drive_link)


## 🚀 Começando

### Pré-requisitos
* **Unreal Engine**: 5.2 ou superior.
* **Sistema Operacional**: Windows 10 ou 11.
* **Controle**: DualSense™ ou DualShock 4®.

### Instalação Rápida
1.  Acesse a página oficial do plugin na Unreal Engine Marketplace (FAB): [Página do Plugin - FAB](https://www.fab.com/listings/e77a8f1d-8bbe-4673-a5ae-7f222c8c0960)
2.  Clique em **Install** ou **Add to Project** e selecione seu projeto Unreal Engine.
3.  Ative o plugin no Unreal Engine:
    * Abra seu projeto.
    * Vá até `Edit > Plugins`.
    * Procure por **Windows Dualsense Plugin** e ative a caixa de seleção.
4.  Reinicie o Unreal Engine quando solicitado.

## 💻 Uso Básico

O plugin expõe todas as funcionalidades através de bibliotecas de funções estáticas em Blueprint, o que significa que você pode chamar os métodos de qualquer lugar sem precisar adicionar componentes.

### Bibliotecas de Funções em Blueprint
As funções são divididas em duas categorias principais para facilitar o acesso:

* **Sony Gamepad**: Contém métodos de gerenciamento comuns a controles Sony (DualShock e DualSense), como controle de LED, giroscópio, nível de bateria, etc.
* **DualSense Effects**: Contém métodos específicos para os recursos exclusivos do DualSense, como a configuração dos Gatilhos Adaptáveis.

Chame as funções diretamente para controlar os recursos do DualSense. Alguns dos efeitos disponíveis incluem:

* 🐎 **Galope (Galloping)**: Simula o trote de um cavalo.
* 💪 **Resistência (Resistance)**: Aplica uma força contrária constante ao pressionar o gatilho.
* 🔫 **Arma (Weapon)**: Cria um efeito de recuo para armas semiautomáticas.
* 🔥 **Tiro Automático (Automatic Gun)**: Vibra rapidamente para simular uma arma automática.

### 📚 Para a documentação completa, acesse a **[Wiki](https://github.com/rafaelvaloto/WindowsDualsenseUnreal/wiki)**.

## 🛠️ Estendendo para Outras Plataformas (ex: PlayStation)
O plugin foi projetado com uma arquitetura extensível, permitindo que desenvolvedores com acesso a outros SDKs de plataforma (como o SDK oficial da Sony PlayStation®) possam integrá-los com o mínimo de esforço.

A comunicação de baixo nível com o hardware é abstraída através da interface `IPlatformHardwareInfoInterface`. A implementação padrão para Windows e Linux utiliza a API HID para se comunicar com os controles.

Para desenvolvedores licenciados, estender o plugin envolve os seguintes passos:

1.  **Criar uma nova classe de implementação**: Crie uma nova classe C++ que herde de `IPlatformHardwareInfoInterface` e implemente seus métodos virtuais utilizando as funções do SDK específico da plataforma.
2.  **Modificar o Singleton**: No arquivo `IPlatformHardwareInfoInterface.cpp`, inclua o cabeçalho da sua nova classe e instancie-a dentro do bloco de compilação condicional apropriado.

> ➡️ **Para um guia detalhado e passo a passo sobre como adicionar suporte a uma nova plataforma, [consulte nosso tutorial na Wiki](https://github.com/rafaelvaloto/WindowsDualsenseUnreal/wiki/🎮-Extending-the-Plugin-for-Other-Platforms).**

## 🤝 Como Contribuir

Contribuições são bem-vindas! Se você tiver ideias, sugestões ou correções, sinta-se à vontade para abrir uma *Issue* ou enviar um *Pull Request*.

## 📄 Licença

Este projeto é distribuído sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.

## ⭐ Créditos e Agradecimentos

Agradecimento especial a todos que já contribuíram com sugestões, reportaram bugs e ofereceram melhorias de implementação. Um agradecimento também aos desenvolvedores das bibliotecas usadas como inspiração e referência para a criação deste projeto.

Um agradecimento especial também à equipe da Epic Games por criar e disponibilizar o *Parrot Game Sample*, que serviu como uma excelente base para o projeto de exemplo que demonstra as funcionalidades deste plugin.

* [DualSense on Windows API](https://github.com/Ohjurot/DualSense-Windows)
* [Nielk1 on GIST](https://gist.github.com/Nielk1/6d54cc2c00d2201ccb8c2720ad7538db)
* [DualSenseAPI](https://github.com/BadMagic100/DualSenseAPI/tree/master)
* [flok pydualsense](https://github.com/flok/pydualsense)
