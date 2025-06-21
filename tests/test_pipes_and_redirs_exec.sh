#!/bin/bash
source "$(dirname "$0")/common.sh"

echo -e "\n${YELLOW}--- ቧ Iniciando Testes de Pipes e Redirecionamentos (Execução) ---${NC}"

# --- Testes de Pipes ---
EXPECTED=$(bash -c "echo 'hello world' | wc -c" | tr -d ' ')
run_test_stdout "echo 'hello world' | wc -c" "$EXPECTED" "Pipe simples (echo | wc)"

EXPECTED=$(bash -c "env | grep PATH | wc -l" | tr -d ' ')
run_test_stdout_contains "env | grep PATH" "PATH=" "Pipe com built-in (env | grep)"

# --- Testes de Redirecionamento ---
touch test_in.txt
echo "hello from file" > test_in.txt
run_test_stdout "cat < test_in.txt" "hello from file" "Redirecionamento de entrada (<)"
rm test_in.txt

# Testa o append (>>)
touch test_append.txt
"$PROJECT_ROOT/minishell" <<< "echo line1 > test_append.txt"
"$PROJECT_ROOT/minishell" <<< "echo line2 >> test_append.txt"
EXPECTED_APPEND=$'line1\nline2'
ACTUAL_APPEND=$(cat test_append.txt)
if [[ "$ACTUAL_APPEND" == "$EXPECTED_APPEND" ]]; then
    echo -e "${GREEN}✅ PASS:${NC} Redirecionamento de append (>>)"
    ((PASSED_COUNT++))
else
    echo -e "${RED}❌ FAIL:${NC} Redirecionamento de append (>>)"
    ((FAILED_COUNT++))
fi
rm test_append.txt


# --- Testes de Here-document (<<) ---
run_test_stdout "cat << EOF
hello from heredoc
EOF" "hello from heredoc" "Execução de Here-document (<<)"

summary_and_exit
