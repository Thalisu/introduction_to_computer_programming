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

const char *attribute_names[] = {"População", "Área", "PIB",
                                 "Pontos Turísticos", "Densidade Demográfica"};

void clean_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

float calculate_super_power(Card card) {
  float base = card.area + (float)card.population + card.pib +
               (float)card.tourist_attractions + card.pib_per_capita;
  return base * (1.0f / (card.population_density + 1.0f));
}

Card create_fake_card_1() {
  Card card;
  card.state = 'A';
  strcpy(card.card_code, "A01");
  strcpy(card.city_name, "São Paulo");
  card.population = 12325232;
  card.area = 1521.11f;
  card.pib = 699.28f;
  card.tourist_attractions = 50;
  card.population_density = card.population / card.area;
  card.pib_per_capita = card.pib / card.population;
  card.super_power_value = calculate_super_power(card);
  return card;
}

Card create_fake_card_2() {
  Card card;
  card.state = 'B';
  strcpy(card.card_code, "B02");
  strcpy(card.city_name, "Rio de Janeiro");
  card.population = 6747815;
  card.area = 1200.27f;
  card.pib = 364.05f;
  card.tourist_attractions = 75;
  card.population_density = card.population / card.area;
  card.pib_per_capita = card.pib / card.population;
  card.super_power_value = calculate_super_power(card);
  return card;
}

double get_attribute_value(Card card, int attr) {
  switch (attr) {
  case 1:
    return (double)card.population;
  case 2:
    return (double)card.area;
  case 3:
    return (double)card.pib;
  case 4:
    return (double)card.tourist_attractions;
  case 5:
    return (double)card.population_density;
  default:
    return 0.0;
  }
}

void show_dynamic_menu(int excluded_attr) {
  printf("\nEscolha um atributo para comparação:\n");
  if (excluded_attr != 1)
    printf("1 - População\n");
  if (excluded_attr != 2)
    printf("2 - Área\n");
  if (excluded_attr != 3)
    printf("3 - PIB\n");
  if (excluded_attr != 4)
    printf("4 - Pontos Turísticos\n");
  if (excluded_attr != 5)
    printf("5 - Densidade Demográfica\n");
  printf("Sua escolha: ");
}

int get_valid_attribute(int excluded_attr) {
  char choice[2];
  int attr;

  while (1) {
    show_dynamic_menu(excluded_attr);
    fgets(choice, 2, stdin);
    clean_buffer();

    attr = choice[0] - '0';

    if (attr < 1 || attr > 5) {
      printf("Opção inválida! Escolha entre 1 e 5.\n");
      continue;
    }

    if (attr == excluded_attr) {
      printf("Este atributo já foi escolhido! Escolha outro.\n");
      continue;
    }

    return attr;
  }
}

int compare_attribute(double val1, double val2, int is_density) {
  return is_density ? (val1 < val2 ? 1 : (val2 < val1 ? 2 : 0))
                    : (val1 > val2 ? 1 : (val2 > val1 ? 2 : 0));
}

void compare_two_attributes(Card card1, Card card2) {
  printf("\nCarta 1: %s (%c)\n", card1.city_name, card1.state);
  printf("Carta 2: %s (%c)\n", card2.city_name, card2.state);

  printf("\nESCOLHA DO PRIMEIRO ATRIBUTO");
  int attr1 = get_valid_attribute(0);

  printf("\nESCOLHA DO SEGUNDO ATRIBUTO");
  int attr2 = get_valid_attribute(attr1);

  double val1_attr1 = get_attribute_value(card1, attr1);
  double val2_attr1 = get_attribute_value(card2, attr1);
  double val1_attr2 = get_attribute_value(card1, attr2);
  double val2_attr2 = get_attribute_value(card2, attr2);

  double soma_card1 = val1_attr1 + val1_attr2;
  double soma_card2 = val2_attr1 + val2_attr2;

  printf("RESULTADO DA RODADA\n");

  printf("\n>> Atributo 1: %s\n", attribute_names[attr1 - 1]);
  printf("   %s: %.2f\n", card1.city_name, val1_attr1);
  printf("   %s: %.2f\n", card2.city_name, val2_attr1);
  int winner1 = compare_attribute(val1_attr1, val2_attr1, attr1 == 5);
  switch (winner1) {
  case 1:
    printf("-> Vencedor: %s\n", card1.city_name);
    break;
  case 2:
    printf("-> Vencedor: %s\n", card2.city_name);
    break;
  case 0:
    printf("-> Empate neste atributo!\n");
    break;
  }

  printf("\n>> Atributo 2: %s\n", attribute_names[attr2 - 1]);
  printf("   %s: %.2f\n", card1.city_name, val1_attr2);
  printf("   %s: %.2f\n", card2.city_name, val2_attr2);
  int winner2 = compare_attribute(val1_attr2, val2_attr2, attr2 == 5);
  switch (winner2) {
  case 1:
    printf("-> Vencedor: %s\n", card1.city_name);
    break;
  case 2:
    printf("-> Vencedor: %s\n", card2.city_name);
    break;
  case 0:
    printf("-> Empate neste atributo!\n");
    break;
  }

  printf("\n\n");
  printf(">> SOMA DOS ATRIBUTOS:\n");
  printf("%s: %.2f + %.2f = %.2f\n", card1.city_name, val1_attr1, val1_attr2,
         soma_card1);
  printf("%s: %.2f + %.2f = %.2f\n", card2.city_name, val2_attr1, val2_attr2,
         soma_card2);

  if (soma_card1 == soma_card2) {
    printf("EMPATE!\n");
    return;
  }

  (soma_card2 > soma_card1) ? printf("VENCEDOR: %s!\n", card2.city_name)
                            : printf("VENCEDOR: %s!\n", card1.city_name);
}

int main() {
  Card card1 = create_fake_card_1();
  Card card2 = create_fake_card_2();

  compare_two_attributes(card1, card2);

  return 0;
}
