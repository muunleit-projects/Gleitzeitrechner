
int testUhrzeit(unsigned int stundenValue, unsigned int minutenValue) {
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