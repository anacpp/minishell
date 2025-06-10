#!/bin/bash
source "$(dirname "$0")/common.sh"

echo -e "\n${YELLOW}--- ⚙️ Iniciando Testes de Execução ---${NC}"

# Redir de saída sem comando (válido)
###run_test "> out.txt" "" "Criar arquivo com redir (sem comando)"

# Redir de entrada sem comando (erro de runtime)
###rm -f in.txt
###run_test "< in.txt" "minishell: in.txt: No such file or directory" "Redir entrada sem arquivo"

# --- Redirecionamento para diretório ---

###mkdir -p tempdir
###run_test "ls > tempdir" "minishell: tempdir: Is a directory" "Redir para diretório"
###rmdir tempdir

# Comando inexistente
###run_test "fakecmd" "minishell: fakecmd: command not found" "Comando inexistente"

# Sem permissão (ajuste conforme necessário)
###touch protected.txt
###chmod 000 protected.txt
###run_test "cat protected.txt" "minishell: permission denied" "Sem permissão de leitura"
###chmod 644 protected.txt
###rm protected.txt

summary_and_exit
