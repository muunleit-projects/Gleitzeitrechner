/**
 * It takes two unsigned ints, and if they're both less than 24 and 60
 * respectively, it returns 0, otherwise it returns 1
 *
 * @param stundenValue The hour value
 * @param minutenValue The minutes value
 *
 * @return 0 for test okay and 1 for test gone wrong
 */

int testZeit(unsigned int stundenValue, unsigned int minutenValue) {
  /* Checking if the input is valid. */
  return stundenValue > 23 || minutenValue > 59 ? -1 : 0;
}