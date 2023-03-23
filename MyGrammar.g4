grammar MyGrammar;
statement: st_switch;
st_switch: 'SWITCH' '(' INT ')' body_switch;
body_switch: '{' case_arr '}';
case_arr: st_case case_arr | st_default |;
st_case: 'CASE' INT ':' payload;
payload:
	statement payload
	| 'PRINT' '(' INT ');' payload
	| 'BREAK;' payload
	|;
st_default: 'DEFAULT' ':' payload;

INT: [0-9]+;
WHITESPACE: [' '\r\t\n] -> skip;
