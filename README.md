# Sincronização do metrô

Projeto da disciplina de Infraestrutura de Software, implementado em C com
pthreads. O programa coordena o embarque de passageiros em um vagão, respeitando
a quantidade de assentos e aguardando a confirmação dos embarques antes da partida.

## Arquivos

- `sync_car.c`: implementação das quatro funções de sincronização.
- `sync_car.h`: definição de `struct station` e declaração das funções.
- `sync_car-runner.c`: programa de testes fornecido pelo professor, com a
  função `main` e a criação das threads.
- `Makefile`: compilação do executável e limpeza dos arquivos gerados.
- `README.md`: descrição do projeto e instruções de uso.
- `evidencias.log`: registro dos comandos e das saídas do terminal durante o
  desenvolvimento, incluindo erros anteriores às correções.

## Ambiente e requisitos

O projeto foi desenvolvido e executado no Ubuntu pelo WSL. Para compilar,
é necessário ter GCC, Make e suporte à biblioteca pthreads.

Os comandos abaixo devem ser executados no terminal Ubuntu/WSL, dentro da
pasta do projeto.

## Compilação e execução

Para compilar:

```bash
make
```

O Makefile compila `sync_car.c` e `sync_car-runner.c` e gera o executável
`sync_car`. A opção `-pthread` habilita o suporte a threads; `-Wall` e
`-Wextra` ativam avisos do compilador.

Para executar o runner:

```bash
./sync_car
```

Para remover o executável e depois recompilar do zero:

```bash
make clean
make
```

## Funcionamento

A estação mantém três contadores: `esperando`, para passageiros sem reserva;
`vagas_livres`, para assentos ainda disponíveis; e `embarcando`, para passageiros
que reservaram lugar e ainda não confirmaram o embarque.

As quatro funções dividem o controle da estação:

- `station_init`: zera os contadores e inicializa o mutex e as condições.
- `station_wait_for_car`: registra a chegada do passageiro, aguarda uma vaga
  e reserva o assento antes de retornar.
- `station_on_board`: confirma o embarque e avisa o vagão quando não há mais
  confirmações pendentes.
- `station_load_car`: anuncia as vagas, acorda os passageiros e aguarda o
  término do embarque antes de liberar a partida.

Um único mutex protege os contadores de cada estação. As variáveis de condição
permitem aguardar vagas e confirmações sem espera ocupada. A reserva e a
confirmação são separadas para permitir vários embarques em andamento.

A solução considera apenas um vagão por vez em cada estação, capacidades
não negativas e uma confirmação para cada reserva.

## Testes

O runner cria 100 passageiros e simula vagões com capacidades aleatórias.
Ele verifica a quantidade de passageiros liberados em cada viagem e se o
vagão aguarda as confirmações antes de sair. Também inclui chamadas com
capacidade zero e com a estação vazia.

A saída informa as vagas de cada vagão e a quantidade de passageiros embarcados.
Quando a execução termina sem detectar erros, aparece:

```text
Looks good!
```

As capacidades podem mudar entre execuções. Passar no runner não garante a
correção em todos os escalonamentos possíveis das threads.
