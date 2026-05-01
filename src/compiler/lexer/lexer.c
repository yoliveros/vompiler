
u8 lexer_peak(lexer *lexer) { return lexer->column; }

token *lexer_next_token(lexer *lexer) {

  state_machine state;

  while (lexer_peak(lexer) != '\0') {
    switch (state) {
    // u8 curr_char = token -
    case START:
      if (lexer_peak(lexer))
        break;
    case IN_ID:
      break;
    case IN_NUM:
      break;
    case IN_OPERATOR:
      break;
    case IN_STR:
      break;
    }
  }

  lexer_next_token(lexer);
  return nullptr;
}

void lexer_init(lexer *lexer, string8 buff) {
  lexer->buff = buff;
  lexer->position = 0;
  lexer->column = 1;
  lexer->line = 1;
}
