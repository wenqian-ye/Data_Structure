#include <iostream>
#include <cstdlib>



/*
*	This function should print a right triangle of stars
*
*/

void recurse(int index, int length) {
//
    if(index == 0 || length == 0)
        return;

	for(int q=0; q<index; q++)
		std::cout<<'*';
	std::cout<<std::endl;

	recurse(index+1, length-1);
}



int main (int argc, char * argv[]) {
//Please enter the size of the triangle you want to see!
if (argc<2)
{
	std::cout<<"./recurse number"<<std::endl;
	return 0;
}

int input = std::atoi(argv[1]);

recurse(1,input);


}
