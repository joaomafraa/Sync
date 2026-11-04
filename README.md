# Sincronização do metrô

Atividade em C que controla o embarque de passageiros em um vagão usando pthreads,
um mutex por estação e duas variáveis de condição.

## Arquivos

- `sync_car.c`: implementa as quatro funções de sincronização.
- `sync_car.h`: define a estrutura da estação e declara as funções.
- `sync_car-runner.c`: teste fornecido pelo professor, com a função `main`.
  Foi acrescentado `(void)foo` para eliminar o aviso de parâmetro não utilizado.
- `Makefile`: compila o programa e limpa o executável.
- `evidencias.log`: histórico do terminal, incluindo erros anteriores às correções.

## Como usar

O projeto foi desenvolvido e testado no Ubuntu pelo WSL, com GCC e Make.
Execute os comandos na pasta do projeto.

Para compilar e executar:

```bash
make
./sync_car
```

O runner simula 100 passageiros e vagões com capacidades aleatórias.
Ao terminar sem erros, mostra `Looks good!`.

Para remover o executável:

```bash
make clean
```

## Funcionamento e testes

Os passageiros aguardam uma vaga, reservam o assento e depois confirmam o embarque.
O vagão espera todas as confirmações e só parte quando está cheio ou não há mais
passageiros esperando. A implementação usa esperas com `pthread_cond_wait`, sem
semáforos nem espera ocupada, e permite várias reservas antes das confirmações.

O runner passou em 20 execuções consecutivas. Também passaram testes separados de
estação vazia, zero vagas, lotação, vagas sobrando, reservas simultâneas e chegada
após a partida. O teste auxiliar foi executado fora do repositório;
`./sync_car` executa o runner do professor. Esses resultados não garantem a
correção em todos os cenários.
