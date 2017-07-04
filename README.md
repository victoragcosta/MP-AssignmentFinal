# MP-Proj-Final
Implementação do projeto final de Métodos de Programação.

## Compilação
Para compilar o projeto, vá para a pasta src/build/ e execute ```make clean``` e logo após ```make``` e execute ```./MP-Proj-Final-Qt```.

## Testes
Para compilar os testes, na pasta src/ execute ```./compilarTestes.sh clean``` para limpar as compilações, ```./compilarTestes.sh make``` para compilar e ```./compilarTestes.sh exec``` para executar todos os testes, cppcheck e gcov em todos os módulos do projeto.

## Página do Github
https://github.com/victoragcosta/MP-Proj-Final

#### Bug Bizarro
Caso seu programa fique em um loop infinito, feche-o, abra o arquivo db/transactions.txt e troque todos os pontos por vírgulas