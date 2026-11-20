# Publicacao no GitHub e conferencia do historico

O arquivo compactado do projeto inclui a pasta oculta `.git`, com **commits locais reais** realizados durante a implementacao. Nenhum repositorio remoto foi conectado e **nenhum push foi efetuado** nesta sessao.

## Antes de publicar

1. Extrair o ZIP integralmente, incluindo `.git`. Entrar na pasta `laboratorio-arvores` no terminal.
2. Conferir `git status` (deve estar limpo) e `git log --oneline --reverse` (deve mostrar pelo menos seis commits).
3. Revisar os arquivos, compilar e executar `sh scripts/verificar.sh`, corrigindo e registrando quaisquer problemas encontrados.
4. **Ajustar a identidade de autoria do Git.** Os commits locais deste pacote usam o autor provisório `Autor do trabalho (configurar) <autor.local@example.invalid>`, para nao inventar e-mail pessoal ou credenciais. Modificar apenas `git config user.name`/`git config user.email` muda os *commits futuros*, nao os anteriores. Se decidir reatribuir o historico com rebase, atualizar em `USO_IA.md` os hashes que mudarem; preserve a origem assistida por IA.
5. Criar um repositorio vazio no GitHub e anotar a URL HTTPS ou SSH.

## Conexao com o GitHub

```bash
git config user.name "SEU NOME"
git config user.email "SEU EMAIL CONFIGURADO NO GITHUB"
git remote add origin https://github.com/USUARIO/laboratorio-arvores.git
git branch -M main
```

**Historico por etapas:** o enunciado exige pelo menos seis commits e envios distribuidos pelo desenvolvimento. Os commits locais registram etapas separadas (menu, arvore binaria, BST, AVL, heap, integracao, testes/documentacao), mas o requisito de **envios remotos progressivos ainda depende de voce**. Publique a evolucao enquanto revisa cada etapa; nao diga que enviou commits ao longo do trabalho antes que isso realmente aconteca.

Depois de conferir as etapas e os envios, sincronize a versao atual:

```bash
git push -u origin main
```

No GitHub, verificar se os arquivos `.c`/`.h`, `README.md`, `USO_IA.md`, os relatorios e os commits estao visiveis. O repositorio pode ser publico ou privado com acesso ao professor. Reproduzir a compilacao em uma **copia limpa clonada do GitHub**:

```bash
git clone https://github.com/USUARIO/laboratorio-arvores.git
cd laboratorio-arvores
sh scripts/verificar.sh
```

## Ultimo commit antes da entrega

Depois de adicionar autoria/RA, link do video e qualquer revisao, criar um commit real de documentacao final:

```bash
git add README.md USO_IA.md docs/
git commit -m "docs: finalizar autoria, evidencias e link da demonstracao"
git push origin main
```

Lembre-se de conferir que as mensagens e as datas do historico correspondam a atividades reais. Nao e necessario incluir executaveis compilados no repositorio.
