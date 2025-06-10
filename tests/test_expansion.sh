#!/bin/bash
source "$(dirname "$0")/common.sh"

echo -e "\n${YELLOW}--- 💥 Iniciando Testes de Expansão ---${NC}"

# Comandos simples com variáveis expandidas
export TEST_VAR="Hello"
run_test "echo \$TEST_VAR" "" "Expansão de variável \$TEST_VAR"

#Todo: Fazer testes com variáveis indefinidas
#unset EMPTY_VAR
#run_test "echo ok > \$EMPTY_VAR" "minishell: ambiguous redirect" "Redir com var indefinida (sem aspas)"

# Descomentar quando o execute forçar o erro de redirecionamento
#run_test "echo ok > \"\$EMPTY_VAR\"" "minishell: : No such file or directory" "Redir com var indefinida (com aspas)"


summary_and_exit
