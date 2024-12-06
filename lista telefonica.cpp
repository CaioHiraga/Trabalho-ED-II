#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <ctype.h>

#define TAM 101  

typedef struct Contato {
    char nome[50];
    char telefone[15];
    struct Contato* proximo;
} Contato;

typedef struct {
    Contato* lista;
} TabelaHash;

TabelaHash tabela[TAM];

int funcaoHash(char* nome) {
    int soma = 0;
    for (int i = 0; nome[i] != '\0'; i++) {
        soma += nome[i];
    }
    return soma % TAM;
}

void inicializarTabela() {
    for (int i = 0; i < TAM; i++) {
        tabela[i].lista = NULL;
    }
}

int validarNome(const char* nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') { 
            return 0; 
        }
    }
    return 1; 
}

int validarTelefone(const char* telefone) {
    for (int i = 0; telefone[i] != '\0'; i++) {
        if (!isdigit(telefone[i])) { 
            return 0; 
        }
    }
    return 1; 
}

void adicionarContato(char* nome, char* telefone) {
    if (!validarNome(nome)) {
        printf("Erro: O nome deve conter apenas letras.\n");
        return;
    }

    if (!validarTelefone(telefone)) {
        printf("Erro: O telefone deve conter apenas números.\n");
        return;
    }

    int indice = funcaoHash(nome);
    
    Contato* atual = tabela[indice].lista;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Contato já existe. Adicionando novo número.\n");
            Contato* novoContato = (Contato*)malloc(sizeof(Contato));
            if (novoContato == NULL) {
                printf("Erro ao alocar memória.\n");
                return;
            }
            strcpy(novoContato->nome, nome);
            strcpy(novoContato->telefone, telefone);
            novoContato->proximo = atual->proximo;
            atual->proximo = novoContato;
            printf("Novo número adicionado com sucesso.\n");
            return;
        }
        atual = atual->proximo;
    }

    Contato* novoContato = (Contato*)malloc(sizeof(Contato));
    
    if (novoContato == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = tabela[indice].lista;
    tabela[indice].lista = novoContato;
    
    printf("Contato adicionado com sucesso.\n");
}

void buscarContato(char* nome) {
    int indice = funcaoHash(nome);
    Contato* atual;

    clock_t start = clock(); 

  
    atual = tabela[indice].lista; 
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            break; 
        }
        atual = atual->proximo;
    }

    clock_t end = clock(); 
    double tempoBusca = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; 

    if (atual != NULL) {
        printf("Telefone(s) de %s: ", atual->nome);
        while (atual != NULL) { 
            printf("%s ", atual->telefone);
            atual = atual->proximo;
        }
        printf("(tempo de busca: %.2f ms)\n", tempoBusca);
    } else {
        printf("Contato não encontrado. (tempo de busca: %.2f ms)\n", tempoBusca);
    }
}

void removerContato(char* nome) {
    int indice = funcaoHash(nome);
    Contato* atual = tabela[indice].lista;
    Contato* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Contato não encontrado.\n");
        return;
    }

    while (atual != NULL && strcmp(atual->nome, nome) == 0) {
        Contato* temp = atual;

        if (anterior == NULL) { 
            tabela[indice].lista = atual->proximo; 
        } else {
            anterior->proximo = atual->proximo; 
        }

        atual = atual->proximo; 
        free(temp); 
        printf("Número removido com sucesso.\n");
        
        if (anterior == NULL && tabela[indice].lista == NULL) { 
            printf("Todos os números de %s foram removidos.\n", nome);
            return;
        }
        
        anterior = temp; 
    }
}

void exibirContatos() {
    for (int i = 0; i < TAM; i++) {
        Contato* atual = tabela[i].lista;
        if (atual != NULL) {
            printf("Índice %d:\n", i);
            while (atual != NULL) {
                printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
                atual = atual->proximo;
            }
        }
    }
}

int main() {
	setlocale(LC_ALL, ""); 

	inicializarTabela();

	char nome[50], telefone[15];
	int opcao;

	printf("\n*************************************************\n");
	printf(" AGENDA TELEFÔNICA\n");

	do {
		printf("*************************************************\n");
		printf("\nEscolha uma opção:\n");
		printf("1 - Adicionar contato\n");
		printf("2 - Buscar contato por nome\n");
		printf("3 - Remover contato\n");
		printf("4 - Exibir todos os contatos\n");
		printf("0 - Sair\n");
		printf("Digite uma opção: ");
		scanf("%d", &opcao);

		while (getchar() != '\n');

		switch(opcao) {
			case 1:
				printf("Nome: ");
				fgets(nome, sizeof(nome), stdin);
				nome[strcspn(nome, "\n")] = '\0'; 
				printf("Telefone: ");
				fgets(telefone, sizeof(telefone), stdin);
				telefone[strcspn(telefone, "\n")] = '\0'; 
				adicionarContato(nome, telefone);
				break;
			case 2:
				printf("Nome: ");
				fgets(nome, sizeof(nome), stdin);
				nome[strcspn(nome, "\n")] = '\0'; 
				buscarContato(nome);
				break;
			case 3:
				printf("Nome: ");
				fgets(nome, sizeof(nome), stdin);
				nome[strcspn(nome, "\n")] = '\0'; 
				removerContato(nome);
				break;
			case 4:
				exibirContatos();
				break;
			case 0:
				printf("Saindo...\n");
				break;
			default:
				printf("Opção inválida!\n");
		}

	} while(opcao != 0);

	return 0;
}
