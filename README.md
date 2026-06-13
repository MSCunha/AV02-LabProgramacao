
## Atividade Avaliativa 02 – Laboratório de Programação
#### Engenharia da computação UFMA | Prof. Rondineli Seba Salomão

Este documento detalha o progresso de desenvolvimento de um protótipo funcional para um sistema de banco de dados textual baseado em matrizes estáticas na linguagem C. O projeto cumpre os requisitos da segunda atividade avaliativa da disciplina de Laboratório de Programação.

---

### Análise Primária

A manipulação de coleções textuais em C, sem o uso de estruturas heterogêneas (`structs`) ou persistência em arquivos físicos, exige a modelagem de uma matriz bidimensional de caracteres que atua como um vetor de strings paralelo. 

Como a memória estática alocada na Stack retém lixo de execução, o sistema implementa uma varredura de inicialização. O controle de slots ocupados ou disponíveis é gerenciado manualmente verificando o caractere terminador nulo (`'\0'`) na primeira posição de cada linha da matriz.

Um resumo das decisões e validações implementadas até o momento compreende:
* **Inicialização de Segurança:** Isolamento de lixo de memória em todas as 50 linhas disponíveis.
* **Validação de Exclusividade:** Varredura linear preventiva via comparação de strings para impedir cadastros duplicados.
* **Gerenciamento de Espaço:** Varredura para localização do primeiro slot livre (`'\0'`) e tratamento de estouro de capacidade do banco de dados.
* **Formatação de Listagem:** Exibição tabular alinhada contendo apenas dados ativos com contagem dinâmica em tempo de execução.

---

### Definições Técnicas das Variáveis

| Nome da Variável | Tipo | Finalidade |
| :--- | :---: | :--- |
| `database` | char[][] | Matriz estática ($50 \times 30$) que funciona como o banco de dados textual. |
| `opt` | int | Operador de escolha que direciona o fluxo do menu no bloco `switch-case`. |
| `auxName` | char[] | Vetor auxiliar de caracteres utilizado como buffer temporário para capturar as entradas do usuário. |
| `isDuplicate` | int | Variável do tipo flag (0 ou 1) que sinaliza se o nome digitado já existe na matriz. |
| `emptyIndex` | int | Armazena o índice numérico da primeira linha vaga localizada na matriz (-1 se cheia). |
| `activeCount` | int | Contador acumulador usado na listagem para rastrear a quantidade total de registros válidos. |

---

### Lógica Aplicada:

1 Inicializa a matriz database preenchendo a posição [i][0] com '\0'
2 Entra no laço principal do Menu Interativo (do-while)
3 Captura a opção escolhida pelo usuário (opt)
4 Processa a opção via Switch:
    4.1 Caso 1: Incluir Nome (Create)
        4.1.1 Captura a string de entrada ignorando quebras de linha anteriores
        4.1.2 Percorre a matriz comparando via strcmp() as linhas ocupadas com a entrada
        4.1.3 Se encontrar correspondência: isDuplicate torna-se 1 e a operação é abortada
        4.1.4 Se único: busca a primeira linha onde database[i][0] == '\0'
        4.1.5 Se não houver linha vazia (emptyIndex == -1): exibe erro de banco cheio
        4.1.6 Se houver vaga: copia a string com strcpy() para database[emptyIndex]
    4.2 Caso 5: Listar Todos os Nomes (Read All)
        4.2.1 Inicializa activeCount com 0 e exibe o cabeçalho formatado
        4.2.2 Percorre todas as linhas de 0 a MAX_RECORDS - 1
        4.2.3 Se database[i][0] != '\0', exibe o índice alinhado e o conteúdo da string
        4.2.4 Ao término, se activeCount for 0, emite alerta de banco vazio
    4.3 Caso 0: Altera a condição de parada e encerra o programa

---

### Fluxograma
```mermaid
flowchart TD
    Start([Início]) --> Init[Inicializa todas as linhas de database com \0]
    Init --> Menu[Exibe Menu de Opções e lê opt]
    Menu --> CheckOpt{Qual a opção opt?}

    %% CASO 1: INCLUIR REGISTRO
    CheckOpt -- 1: Incluir --> InName[Entrada de dados: auxName]
    InName --> LoopDup[Percorre database procurando auxName]
    LoopDup --> CheckDup{isDuplicate == 1?}
    CheckDup -- sim --> ErrDup[Exibe: Erro O nome já existe] --> Menu
    CheckDup -- não --> LoopVaga[Percorre database procurando linha vazia]
    LoopVaga --> CheckVaga{emptyIndex == -1?}
    CheckVaga -- sim --> ErrCheio[Exibe: Erro Banco de dados cheio] --> Menu
    CheckVaga -- não --> SaveName[strcpy auxName para database emptyIndex] --> PrintSave[Exibe: Sucesso ao gravar nome] --> Menu

    %% CASO 2: BUSCAR REGISTRO

    %% CASO 3: MODIFICAR REGISTRO

    %% CASO 4: APAGAR REGISTRO
    CheckOpt -- 4: Apagar --> InDel[Entrada de dados: auxName]
    InDel --> [Busca pelo registro]
    LoopDel --> {Encontrou registro?}
    CheckDel -- não --> ErrDel[Exibe: Nome não encontrado] --> Menu
    CheckDel -- sim --> ClearLine[Define primeiro caractere da linha como \0] --> PrintDel[Exibe: Registro removido] --> Menu

    %% CASO 5: LISTAR REGISTROS
    CheckOpt -- 5: Listar --> ResetCount[activeCount = 0]
    ResetCount --> LoopList[Percorre database de 0 até MAX_RECORDS-1]
    LoopList --> CheckActive{database i 0 != \0?}
    CheckActive -- sim --> PrintLine[Exibe Índice i e a String contida] --> IncCount[activeCount++] --> NextLine[Próxima linha]
    CheckActive -- não --> NextLine
    NextLine --> LoopList
    LoopList -- Fim do loop --> CheckEmpty{activeCount == 0?}
    CheckEmpty -- sim --> PrintEmpty[Exibe: Banco de dados vazio] --> Menu
    CheckEmpty -- não --> PrintTotal[Exibe total de registros ativos] --> Menu

    %% SAÍDA E PADRÃO
    CheckOpt -- 0: Sair --> EndProgram[Exibe mensagem de encerramento] --> Fim([Fim])
    CheckOpt -- Opção Inválida --> ErrOpt[Exibe: Opção inválida] --> Menu

    classDef default fill:#ffffff,stroke:#cad2d9,stroke-width:1px,color:#4a5568;
    classDef decision fill:#ffffff,stroke:#cad2d9,stroke-width:1px,color:#4a5568;
    class CheckOpt,CheckDup,CheckVaga,CheckFound,CheckTarget,CheckNewDup,CheckDel,CheckActive,CheckEmpty decision;
```

---

### Instalação / Compilação

O código apresentado utiliza linguagem C padrão, e pode ser executado em qualquer compilador como GCC ou utilizando IDEs como CodeBlocks, VS Code ou onlinegdb.com.

---

### Entradas e Saidas

```C
1. Incluir Nome
2. Buscar Nome
3. Modificar Nome
4. Apagar Nome
5. Listar Todos os Nomes
0. Sair
Selecione uma opcao: 1

--- INCLUIR NOVO REGISTRO ---
Digite o nome: Matheus Cunha
Sucesso: Nome gravado com sucesso no indice [0]!

Selecione uma opcao: 1

--- INCLUIR NOVO REGISTRO ---
Digite o nome: Matheus Cunha
Erro: O nome 'Matheus Cunha' ja existe no sistema! Escolha um nome unico.

Selecione uma opcao:
...
>>>5

--- LISTAR TODOS OS REGISTROS ---
INDICE     | NOME
------------------------------------
[0       ] | Matheus Cunha
------------------------------------
Total de registros ativos: 1
```

---

### Autores
Matheus Silva Cunha - 2021052782 | 
[@MSCunha](https://www.github.com/MSCunha)
### Licença

[MIT](https://choosealicense.com/licenses/mit/)



