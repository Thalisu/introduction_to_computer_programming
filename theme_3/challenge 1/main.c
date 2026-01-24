#include <stdio.h>
#include <string.h>

typedef struct {
  char state;
  char card_code[4];
  char city_name[33];
  unsigned long int population;
  float area;
  float pib;
  int tourist_attractions;
  float population_density;
  float pib_per_capita;
  float super_power_value;
} Card;

void clean_buffer() {
  while (getchar() != '\n')
    ;
}

float calculate_super_power(Card card) {
  float base = card.area + (float)card.population + card.pib +
               (float)card.tourist_attractions + card.pib_per_capita;
  return base * (1.0f / (card.population_density + 1.0f));
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
  scanf("%ld", &card.population);
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

  card.population_density = card.population / card.area;
  card.pib_per_capita = card.pib / card.population;

  card.state = state[0];

  card.super_power_value = calculate_super_power(card);

  return card;
}

void print_card(Card card, int card_number) {
  printf("Carta %i:\nEstado: %c\nCódigo: %s\nNome da cidade: %s\nPopulação: "
         "%li\nÁrea: %f km²\nPIB: %f Bilhões de Reais\nNúmero de Pontos "
         "Turísticos: %i\nDensidade Populacional: %f hab/km²\nPIB per Capita: "
         "%f reais\nSuper poder: %f\n",
         card_number, card.state, card.card_code, card.city_name,
         card.population, card.area, card.pib, card.tourist_attractions,
         card.population_density, card.pib_per_capita, card.super_power_value);
}

void print_card_winner_between_two_values(long double value_1,
                                          long double value_2) {
  if (value_1 == value_2) {
    printf("As cartas empataram!\n");
    return;
  }

  if (value_2 > value_1) {
    printf("Carta 2 venceu\n");
  } else
    printf("Carta 1 venceu\n");
}

void print_winner(Card card_1, Card card_2) {
  printf("Carta 1 - %s (%c): %ld", card_1.city_name, card_1.state,
         card_1.population);
  printf("Carta 2 - %s (%c): %ld", card_2.city_name, card_2.state,
         card_2.population);
  print_card_winner_between_two_values(card_1.population, card_2.population);
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

  print_card(card1, 1);
  printf("\n");
  print_card(card2, 2);
  printf("\n");
  printf("comparação de Cartas:\n");
  print_winner(card1, card2);
  return 0;
}