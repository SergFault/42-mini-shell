//
// Created by sergey on 01.02.2022.
//

/* single quotes, quotes, escape char*/
process_escape_characters(){

}

/* check input mistakes */
process_errors(){

}

/* set environment to command. Example: $pwd = /etc */
set_env(){

}

/* find binary file at $PATH */
find_binary(){

}

/* decompose commands */
commands_decomposition(){

}

int parse(){
	process_escape_characters();
	process_errors();
	set_env();
	find_binary();
	commands_decomposition();
	return 0;
}