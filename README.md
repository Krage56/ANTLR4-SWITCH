# Грамматика
```
<statement> ::= <st_switch>
<st_switch> ::= SWITCH(INT)<body_switch>
<body_switch> ::= {<case_arr>}
<case_arr> ::= <st_case><case_arr> | <st_default> | e
<st_case> ::= CASE INT:<payload>
<payload> ::= <statement><payload> | print(INT); <payload> | BREAK; <payload> | e
<st_default> ::= DEFAULT:<payload>
```

# Запуск
Открыть в консоли директорию с проектом и вызвать make.

# Зависимости
1. ANTLR4
2. Make
3. CMake