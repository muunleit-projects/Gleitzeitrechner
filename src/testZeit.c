/**
 * It takes two unsigned ints, and if they're both less than 24 and 60
 * respectively, it returns 0, otherwise it returns 1
 *
 * @param stundenValue The hour value
 * @param minutenValue The minutes value
 *
 * @return 0 for test okay and 1 for test gone wrong
 */

#include <stdio.h>

int testZeit(unsigned int stundenValue, unsigned int minutenValue) {
  /* Checking if the input is valid. */
  if (stundenValue > 23 || minutenValue > 59) {
    printf(
        "\nDie Zeit %02d:%02d scheint nicht realistisch.\n"
        "Versuchen Sie es noch einmal",
        stundenValue, minutenValue);

    return 1;

  } else {
    return 0;
  }
}