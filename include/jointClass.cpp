#include "jointClass.hpp"

Joint::Joint(glm::vec3 scale, glm::vec3 art, glm::vec3 pos, glm::vec3 mag, glm::vec3 Mag){
	piece = Cube(scale, art, mag, Mag);
	piece.set_pos(pos);
	selected = false;
}

void Joint::add_children(Joint *j){
	children.push_back(j);
}

void Joint::draw(glm::mat4 base, Shader &sh){
	/*
	glm::mat4 cur = piece.trans * glm::scale(glm::mat4(1.0f), 
						glm::vec3(1.0f/(piece.s.x), 
							  1.0f/(piece.s.y), 
							  1.0f/(piece.s.z)));
  */

	if(selected == true) sh.setBool("select", true);

	piece.base = base;
	piece.draw(sh);

	glm::mat4 cur = piece.trans * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.0f,1.0f)/piece.s);
	for(Joint *j : children){
		j->draw(cur, sh);
	}
	if(selected == true) sh.setBool("select", false);
}
