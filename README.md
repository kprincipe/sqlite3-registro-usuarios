# Registro de Usuarios
## Sobre
Este é um projeto de experimento desenvolvido para fins educacionais. Sua função é servir de playground para entender o funcionamento do SQLite3 como *biblioteca amalgamada* em um único arquivo `sqlite3.c`.
## Compilação
```bash
$ make
$ ./main
```
## Visualizar tabela do Banco de Dados
```bash
$ ./deps/sqlite/sqlite test.db
sqlite> select * from users
```
