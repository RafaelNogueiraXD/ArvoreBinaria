import csv
def juntar_linhas_vazias(arquivo_entrada, arquivo_saida):
    with open(arquivo_entrada, 'r', encoding='utf-8') as arquivo_entrada, open(arquivo_saida, 'w', newline='', encoding='utf-8') as arquivo_saida:
        leitor_csv = csv.reader(arquivo_entrada)
        escritor_csv = csv.writer(arquivo_saida)

        linhas = []
        for linha in leitor_csv:
            linhas.append(linha)

        for i in range(1, len(linhas)):
            linha_atual = linhas[i]
            linha_anterior = linhas[i-1]

            if len(linha_atual) < len(linha_anterior):
                linha_atual.extend(['vazio'] * (len(linha_anterior) - len(linha_atual)))

            for j in range(len(linha_atual)):
                if linha_atual[j] == 'vazio':
                    linha_atual[j] = linha_anterior[j]

        escritor_csv.writerows(linhas)
def adicionar_espaco_entre_virgulas(arquivo_entrada, arquivo_saida):
    with open(arquivo_entrada, 'r', encoding='utf-8') as arquivo_entrada, open(arquivo_saida, 'w', newline='', encoding='utf-8') as arquivo_saida:
        leitor_csv = csv.reader(arquivo_entrada)
        escritor_csv = csv.writer(arquivo_saida)

        linhas = []
        for linha in leitor_csv:
            nova_linha = []
            for valor in linha:
                if valor == ',':
                    nova_linha.append(' , ')
                else:
                    nova_linha.append(valor)
            linhas.append(nova_linha)

        escritor_csv.writerows(linhas)
# Exemplo de uso
arquivo_entrada = '../customizado3.csv'
arquivo_saida = 'novo.csv'

adicionar_espaco_entre_virgulas(arquivo_entrada, arquivo_saida)
juntar_linhas_vazias(arquivo_entrada, arquivo_saida)