# Roteiro de video (5 a 8 minutos)

**Preparacao:** abrir o terminal dentro da pasta do repositorio, compilar via `gcc -std=c11 -Wall -Wextra -pedantic src/*.c -o laboratorio` e executar `./laboratorio` (no Windows, `laboratorio.exe`). A gravação deve mostrar operacoes reais nos menus, com explicacao do aluno, sem depender de resultados impressos previamente.

| Tempo sugerido | O que fazer no terminal | O que explicar |
|---|---|---|
| 0:00–0:35 | Mostrar `src/`, `README.md` e comando de compilacao | Projeto modular, quatro estruturas independentes em C e convencao de altura |
| 0:35–1:40 | Menu **1** → **2** carregar exemplo → **3** exibir. Tentar inserir 77 como esquerdo de 30 (opcao 1, chave 77, pai 30, E) | Percursos, altura 2, 6 nos, 3 folhas; rejeicao protege subarvore existente |
| 1:40–3:00 | Menu **2**, inserir 50,30,70,20,40,60,80 (opcao 1 por chave), exibir (4); remover 50 (3, 50); exibir (4) | Regra esquerda menor/direita maior; ao excluir raiz com dois filhos, sucessor 60 a substitui; outras remocoes sao demonstradas na suite |
| 3:00–4:10 | Menu **3**, inserir 30,10,20; exibir (3) | A sequencia causa **rotacao dupla LR**, direita apos esquerda no filho; raiz 20, FB 0 e altura 1 |
| 4:10–5:25 | Menu **4**, inserir 50,30,40,10,20,35,60; exibir (4); consultar (2); extrair (3); exibir (4) | A raiz e o maior; sift-up sobe 60; sift-down reorganiza apos remover 60 |
| 5:25–6:25 | Menu principal **5** | A BST cresce para altura 14 com entradas crescentes, AVL mantem altura 3; explicar por que buscar 1 favorece BST |
| 6:25–7:15 | Mostrar `docs/testes.md`, `USO_IA.md` e historico `git log --oneline` | Testes reproduziveis, como IA contribuiu, revisoes e limite dos algoritmos |

**Importante:** no roteiro acima, para remover 50 diretamente, a arvore ainda deve conter 20 e 30; o sucessor 60 torna-se nova raiz. Para a sequencia de remoção exigida pelo enunciado (**20**, depois **30**, depois **50**), use `testes/entrada_demo.txt` e o relatorio de testes para demonstrar que os tres casos foram verificados.

**Fala curta sobre IA:** “Utilizei IA para acelerar a implementacao modular em C, estruturar as validacoes de BST e AVL, preparar casos de teste e a documentacao. Conferi os resultados com as sequencias do enunciado; os arquivos e funcoes impactados estao identificados em USO_IA.md.” Ajustar esta fala se houver novas contribuicoes ou revisoes pessoais.

**Checklist depois de gravar:** subir o video, ajustar permissão do link, inserir o link em `README.md` e executar `git status` para certificar que as atualizacoes foram publicadas.
