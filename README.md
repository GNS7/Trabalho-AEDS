# Trabalho-AEDS

Universidade do Estado de Minas Gerais
Professor: Edwaldo Soares Rodrigues

AEDS II
Trabalho Prático 1

Instruções:
I. O trabalho deverá ser feito individualmente.
II. O trabalho deverá ser realizado usando a linguagem de programação C.
III. Deverão usar os conceitos aprendidos na disciplina de AEDS II, levando
em consideração as melhores estruturas para representar os itens do jogo
(baralho, mesa, e as mãos dos jogadores).
IV. O trabalho deverá ser entregue até a data 17/12/2022.
V. O trabalho deverá ser postado até a data limite no ClassRoom.
VI. Comece a fazer este trabalho logo, enquanto o problema está fresco na
memória e o prazo para terminá-lo está tão longe quanto jamais poderá
estar;

Enunciado do Trabalho:
O Trabalho Prático 1 deverá ser implementado usando a linguagem de
programação C e tem como objetivo colocar em prática os conceitos vistos
acerca de Algoritmos e Estruturas de Dados II ao longo do semestre.

Problema – Jogo Fedaput*:

O jogo de cartas Fedaput* é um jogo baseado no jogo de cartas muito conhecido
denominado Truco. Este jogo utiliza-se de um baralho, mas não por completo.
São usadas as seguintes cartas:
ÁS (A) (4 naipes);
DOIS (4 naipes);
TRÊS (4 naipes);
QUATRO (4 naipes);
CINCO (4 naipes);
SEIS (4 naipes);
SETE (4 naipes);
DAMA (Q) (4 naipes);
VALETE (J) (4 naipes);
REI (K) (4 naipes);

O Truco possui algumas regras, mas nem todas elas são importantes para o jogo
Fedaput*. Para se jogar o jogo Fedaput*, é necessário apenas saber quais as
cartas são jogadas no Truco, e principalmente quais as regras de valoração das
cartas. Desta forma, a seguir será apresentada a sequência de valor das cartas
no Truco.

• Manilhas - São fixas. Dá mais forte para a mais fraca: 4 de Paus / 7 de
Copas / Ás de Espadas / 7 de Ouros;
• Ordem das cartas (da menor para maior): 4, 5, 6, 7, Q, J, K, A, 2, 3
Para maiores informações sobre o jogo Truco, podem acessar:
https://www.megajogos.com.br/truco-mineiro-online/regras;

Uma vez que é sabido quais as cartas são utilizadas no Truco, bem como a
ordem de valor destas, então é possível agora, inserir as regras para o jogo
Fedaput*.

1. Inicialmente as cartas são embaralhadas e colocadas em uma pilha na
mesa de jogo, com face voltada para baixo.
2. O jogo pode ter de 2 a 8 jogadores.
3. Cada jogador inicia com 5 “vidas”.
4. A quantidade de cartas em cada partida é diferente. Inicialmente, cada
jogador inicia com 5 cartas, e a cada partida esse valor vai decrescendo
até chegar a apenas uma carta. Na sequência, o processo é invertido, e
cada partida tem uma carta a mais que a partida anterior, até chegar ao
limite de 5 cartas por jogador.
5. A cada partida ao menos um jogador, perderá ao menos uma vida.
6. Uma partida funciona da seguinte forma:

a. Cada jogador recebe do monte inicial a partir do topo do monte a
quantidade de cartas de acordo com a partida a ser jogada.
b. Na sequência, o jogador que recebeu as primeiras cartas, diz quantas
rodadas ele faz, ou seja, quantas cartas ele “mata”. Ex: Se o jogador
recebe 5 cartas, terão 5 rodadas, e o máximo de rodadas em que ele
pode matar é 5. O jogador falará essa quantidade de acordo com as
cartas que tem em mãos.
c. Cada rodada acontece em sentido horário, ou seja, o primeiro jogador
que receber as cartas, diz quantas rodadas fará, na sequência o
segundo jogador que recebeu as cartas diz quantas rodadas fará, e
assim por diante, quando houver mais de dois jogadores.
d. Esse sentido horário é respeitado também a cada partida, ou seja, na
segunda partida, o jogador que receberá primeiramente as cartas será
o segundo jogador, e assim por diante, caso tenham mais de dois
jogadores.
e. Uma regra importante é que ao final, na vez do último jogador da
partida dizer quantas rodadas fará, este deve contabilizar a quantidade
que cada um dos jogadores anteriormente disse que fariam, de modo
que a quantidade que este último jogador fará somada ao somatório
dos demais jogadores, não pode ser exatamente a mesma quantidade
de cartas daquela partida.
f. Na sequência, o jogo é inicializado, mantendo o sentido horário, ou
seja, o primeiro jogador joga uma carta e no sentido horário cada
jogador faz sua jogada. No final o jogador que nessa rodada foi dono
da maior carta (regras do Truco), terá feito uma rodada.
• Aqui há uma diferença para o truco. É possível que a maior carta
seja por exemplo um 3 e que dois jogadores tenham jogado uma
carta de valor 3. Nessa situação, o critério de desempate será feito
em relação ao naipe, sendo a sequência do maior para o menor
naipe: paus, copas, espadas e ouros. Obs: Para facilitar, veja que
esta sequência é a mesma em relação aos naipes das manilhas do
Truco.
g. O processo é repetido de acordo com a quantidade de cartas de cada
partida.
h. No final de uma partida, ao menos um jogador, não terá conseguido
cumprir sua meta. Por exemplo: Se o jogador “dois” disse que faria 2
rodadas da partida, no final ele tem que ter feito exatamente 2 rodadas
para não perder nenhuma vida. Se o jogador “dois” disse fazer 2
rodadas, mas no final fez apenas 1, então este perderá uma vida, o
mesmo aconteceria se tivesse feito 3 rodadas ao invés das duas que
disse que faria. Agora, se este jogador não fizer nenhuma, ou fizer 4
rodadas, então perderá duas vidas.

7. O jogo acaba quando restar apenas um jogador com vidas, de modo que
todos os demais terão perdido suas vidas.

Metodologia:
✓ Deve ser incluída uma struct para representar uma Carta, esta deve ter
dois membros, número e naipe. Observe que o membro naipe deverá ser
um valor entre 1 e 4, sendo: 1 -copas / 2 – ouros / 3 – espadas / 4 - paus.
O baralho, a mesa que é onde os jogadores viram suas cartas e as mãos
dos jogadores devem ser compostos por Cartas.
✓ O jogador também deverá ser representado por uma Struct, que deve
conter o nome do jogador e o número de vidas que este possui. (Se
necessário, pode incluir mais algum campo nessa Struct).
✓ Deverá, necessariamente, ser utilizada as estruturas de dados, Pilha, Fila
e Lista. Deverá ser decidido se a estrutura de dados será estática ou
dinâmica de acordo com a aplicação da estrutura de dados no jogo.
✓ Seu código deve permitir que se escolha a quantidade de jogadores que
vão jogar (mínimo 2 e máximo 8). Em seguida, após a execução do jogo,
o código deve apresentar o ganhador (nome do jogador e número de
vida(s) restante(s)).
✓ De modo a manter um log de como ocorreu as jogadas, desde a primeira
até a última, cada jogada deverá ser armazenada em um arquivo de texto.
Desta forma, pelo log pode ser visto tudo o que aconteceu no jogo.
