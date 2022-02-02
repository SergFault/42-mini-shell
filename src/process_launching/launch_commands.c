//
// Created by sergey on 01.02.2022.
//

int launch_commands(){

	if is_built_in(){
		launch_bin();
	} else{
		launch_built_in();
	}
}