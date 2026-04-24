#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deps/sqlite/sqlite3.h"

#define trim_left(x)            \
    int __i = 0;                \
    while(x[__i++] != '\n');    \
    x[__i - 1] = '\0';          \


int main(void) {
    // declaracao de estruturas para conexao e interacao com banco de dados
    sqlite3 *db;
    sqlite3_stmt *stmt;

    // variavel para codigos de erro
    int r;

    // abre conexao com o banco de dados
    sqlite3_open("test.db", &db);
    if (db == NULL) {
        printf("error: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("LOG: connection ok.\n");

    // prepara um comando sql para ser executado
    // cria tabela `users` se ela nao existir
    char *comm = "CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, age INTEGER)";
    r = sqlite3_prepare(db, comm, strlen(comm), &stmt, NULL);
    if (r == SQLITE_ERROR) {
        printf("prepare error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // executa o comando sql anteriormente preparado
    r = sqlite3_step(stmt);
    if (r == SQLITE_ERROR) {
        printf("step error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // entrada de nomes
    char buffer[256], name[256];
    int age;

    printf("----------------\n");
    
    printf("nome: ");
    fgets(name, 256, stdin);
    trim_left(name);

    printf("idade: ");
    fgets(buffer, 256, stdin);
    age = atoi(buffer);
    printf("----------------\n");
    
    // inserir na tabela
    comm = "INSERT INTO users(name, age) VALUES(?, ?)";
    r = sqlite3_prepare(db, comm, strlen(comm), &stmt, NULL);
    sqlite3_bind_text(stmt, 1, name, sizeof(name), NULL);
    sqlite3_bind_int(stmt, 2, age);
    r = sqlite3_step(stmt);

    // limpa comando preparado e fecha conexao com banco de dados
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    printf("LOG: close ok.\n");

    return 0;
}
