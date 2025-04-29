#!/bin/bash

echo "🛠️  Verificando dependências do projeto Minishell..."

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "🔍 Sistema detectado: Linux"

    if ! dpkg -s libreadline-dev &> /dev/null; then
        echo "❌ Biblioteca 'libreadline-dev' não está instalada."
        read -p "Deseja instalar agora? [S/n] " resposta
        if [[ "$resposta" == "" || "$resposta" == "s" || "$resposta" == "S" ]]; then
            sudo apt-get update
            sudo apt-get install libreadline-dev
        else
            echo "⚠️  Atenção: readline não instalada. O projeto pode não compilar corretamente."
        fi
    else
        echo "✅ Biblioteca 'libreadline-dev' já instalada."
    fi

elif [[ "$OSTYPE" == "darwin"* ]]; then
    echo "🔍 Sistema detectado: macOS"

    if ! brew list readline &> /dev/null; then
        echo "❌ Biblioteca 'readline' não está instalada via Homebrew."
        read -p "Deseja instalar agora? [S/n] " resposta
        if [[ "$resposta" == "" || "$resposta" == "s" || "$resposta" == "S" ]]; then
            brew install readline
        else
            echo "⚠️  Atenção: readline não instalada. O projeto pode não compilar corretamente."
        fi
    else
        echo "✅ Biblioteca 'readline' já instalada."
    fi

else
    echo "❌ Sistema operacional não suportado automaticamente."
    echo "Instale a biblioteca readline manualmente."
fi
