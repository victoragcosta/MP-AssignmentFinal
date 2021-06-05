# MP - Projeto Final
Implementação do projeto final de Métodos de Programação.

## Membros
Victor André Gris Costa - 16/0019311
André Filipe Caldas Laranjeira - 16/0023777
Luiz Antônio Borges Martins - 16/0013615

## Requisitos
É necessário possuir Qt instalado para rodar o aplicativo

## Compilação
Para compilar o projeto, vá para a pasta src/build/ e execute ```make clean``` e logo após ```make``` e execute ```./MP-Proj-Final-Qt```.

## Testes
Para compilar os testes, na pasta src/ execute ```./compilarTestes.sh clean``` para limpar as compilações, ```./compilarTestes.sh make``` para compilar e ```./compilarTestes.sh exec``` para executar todos os testes, cppcheck e gcov em todos os módulos do projeto.

## Doxygen
Na pasta doxygen execute o comando ```doxygen```.

## Objetivos Atingidos
- Cadastro de usuário
- Login/Logout de usuário
- Busca por produtos
- Listagem de Transações por Admin
- Deleção de Transações por Admin
- Criação de transação por Admin
- Listagem de Transações abertas por usuários comuns
- Documentação
- Diagramas
- Gcov, valgrind e cppcheck passam tranquilamente

## Objetivos Não Atingidos
Devido a falta de tempo e mudança da interface gráfica de última hora, os seguintes objetivos não foram alcançados no aplicativo, mas estão contidos no código devidamente documentados:
- Finalização de Transações por parte de Usuário (compra de produto)
- Criação de Transações por ofertantes
- Alteração de Dados do usuário
- Remoção de usuários indesejados
- Rede Social dos usuários

## Acesso de Admin
user: jose123
senha: 987654

## Página do Github
https://github.com/victoragcosta/MP-Proj-Final

### Observações
- Caso seu programa fique em um loop infinito, feche-o, abra o arquivo db/transactions.txt e troque todos os pontos por vírgulas.
- Caso algum arquivo .txt esteja corrompido, rode os testes automáticos segundo as instruções acima.
