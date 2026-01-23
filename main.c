#include <stdio.h>
#include <string.h>

typedef struct {
  char state;
  char card_code[4];
  char city_name[33];
  int population;
  float area;
  float pib;
  int tourist_attractions;
} Card;

void clean_buffer() {
  while (getchar() != '\n')
    ;
}

Card generate_card() {
  Card card = {0};
  printf("Insira um estado: (de A a H)\n");
  char state[2];

  fgets(state, 2, stdin);
  clean_buffer();

  if (state[0] >= 'a' && state[0] <= 'h')
    state[0] -= 32;
  if (state[0] < 'A' || state[0] > 'H') {
    printf("Estado invalido\n");
    return card;
  }

  printf("Insira o codigo da sua carta: (de 1 a 4)\n");
  char card_code[4];
  fgets(card_code, 2, stdin);
  clean_buffer();

  if (card_code[0] < '1' || card_code[0] > '4') {
    printf("Codigo invalido\n");
    return card;
  }
  card.card_code[0] = state[0];
  card.card_code[1] = '0';
  card.card_code[2] = card_code[0];
  card.card_code[3] = '\0';

  printf("Insira o nome da sua cidade:\n");
  fgets(card.city_name, 33, stdin);
  clean_buffer();
  card.city_name[strcspn(card.city_name, "\n")] = 0;

  printf("Insira a população da sua cidade:\n");
  scanf("%d", &card.population);
  clean_buffer();

  printf("Insira a área da cidade:\n");
  scanf("%f", &card.area);
  clean_buffer();

  printf("insira o PIB da sua cidade:\n");
  scanf("%f", &card.pib);
  clean_buffer();

  printf("insira o numero de pontos turisticos da sua cidade:\n");
  scanf("%d", &card.tourist_attractions);
  clean_buffer();

  card.state = state[0];

  return card;
}

int main() {
  Card blank = {0};

  printf("Vamos fazer sua primeira carta!\n");
  Card card1 = generate_card();
  if (card1.state == blank.state)
    return 0;

  printf("Agora, vamos para a segunda!\n");
  Card card2 = generate_card();
  if (card2.state == blank.state)
    return 0;

  printf("Carta 1:\nEstado: %c\nCódigo: %s\nNome da cidade: %s\nPopulação: "
         "%i\nÁrea: %f km²\nPIB: %f Bilhões de Reais\nNúmero de Pontos "
         "Turísticos: %i\n",
         card1.state, card1.card_code, card1.city_name, card1.population,
         card1.area, card1.pib, card1.tourist_attractions);

  printf("Carta 2:\nEstado: %c\nCódigo: %s\nNome da cidade: %s\nPopulação: "
         "%i\nÁrea: %f km²\nPIB: %f Bilhões de Reais\nNúmero de Pontos "
         "Turísticos: %i\n",
         card2.state, card2.card_code, card2.city_name, card2.population,
         card2.area, card2.pib, card2.tourist_attractions);
  return 0;
}