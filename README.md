# 🐚 Minishell — 42RJ Project

![C](https://img.shields.io/badge/language-C-blue) ![status](https://img.shields.io/badge/status-in%20progress-yellow)

## ✨ Objetivo
Criar uma shell mínima inspirada no Bash, com funcionalidades como:
- Prompt interativo
- Execução de comandos (built-ins e externos)
- Pipes (`|`) e redirecionamentos (`>`, `<`, `>>`, `<<`)
- Expansão de variáveis de ambiente (`$VAR`, `$?`)
- Tratamento de sinais (`ctrl-C`, `ctrl-D`)
- AST para parsing e execução

## 🛠️ Compilação

```bash
make
./minishell
```

## 📁 Estrutura

```
includes/          # headers
libft/             # libft copiada
src/               # código fonte
tests/             # scripts e casos de teste
Makefile           # compilação
README.md          # documentação
```

## 📌 Funcionalidades Implementadas

- [x] Prompt interativo
- [x] Histórico com readline
- [x] Execução de comandos externos
- [x] Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- [x] Pipes (`|`)
- [x] Redirecionamentos (`>`, `<`, `>>`, `<<`)
- [x] Expansão de variáveis (`$VAR`, `$?`)
- [x] Sinais (`ctrl-C`, `ctrl-D`)
- [ ] Wildcards `*` (bonus)
- [ ] Operadores `&&`, `||` (bonus)

## 🧪 Testes

Use os testes em `tests/` para validar:
```bash
bash tests/run_all.sh
```

## 🤝 Autores

- Ana Carla — [@yourgithub](https://github.com/yourgithub)
- Raquel — [@raquelgithub](https://github.com/raquelgithub)

## 📄 Licença
Projeto educacional para a 42 rj. Sem fins lucrativos.
```
