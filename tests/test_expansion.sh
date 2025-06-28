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

# --- Expansão de $? (Status de Saída) ---
# O código de saída para "command not found" é tipicamente 127
run_test_stdout "non_existent_command_for_test 2>/dev/null; echo \$?" "127" "Expansão de \$? para comando não encontrado"
run_test_stdout "echo hello > /dev/null; echo \$?" "0" "Expansão de \$? para comando com sucesso"

# --- Expansão dentro de aspas e com texto adjacente ---
export HELLO_VAR=world
run_test_stdout 'echo "hello $HELLO_VAR"' "hello world" "Expansão dentro de aspas duplas"
run_test_stdout 'echo "hello$HELLO_VAR"' "helloworld" "Expansão adjacente a texto"
run_test_stdout 'echo '\''hello $HELLO_VAR'\''' 'hello $HELLO_VAR' "Sem expansão dentro de aspas simples"

# --- Expansão de variável não definida ---
unset UNDEFINED_VAR
run_test_stdout 'echo "hello$UNDEFINED_VAR"' "hello" "Expansão de variável não definida"

summary_and_exit
