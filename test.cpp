//g++ test.cpp 
#include <iostream>
#include <string>

uint32_t hw16_check_even_pos(uint32_t x){
    int i;
    int w=0;
    int offset = 0x2;
    for (i=0; i<16; i++){
        if ((x&offset)!=0)
            w++;
        offset = offset<<2;
    }
    return w;
}


int main(){
 

    // for (int i=0;i<(1<<3);i++){
    //     unsigned int tmp_as;
	// 	unsigned bitIdx = 0;
    //     for(unsigned k=0;k<8;k++){
    //         if(((mask>>k)&(0x1))!=0){
    //             tmp = tmp ^ (((i>>bitIdx)&0x1)<<k);
    //             bitIdx++;
    //         }
    //     }
    //     std::cout<<std::hex << (int) tmp << std::endl;  
    // }

    // int mask = 0x2 | 0x8 | 0x20;
    // int hw=4;
    // int pos[hw] = {2,4,8,16};
    // unsigned short tmp;
    // for (int i=0;i<(1<<hw);i++){
    //     tmp=0;
    //     for (int j=0;j<hw;j++){
    //         tmp = tmp ^ (((i & (1<<j))>>j) << (pos[j]-1) );
    //     }
    //     std::cout<<std::hex << (int) tmp << std::endl;  
    // }

    //Test for permutation str
    // int perm[16] ={5,0,1,4,7,12,3,8,13,6,9,2,15,10,11,14}; //TWINE permutation
    // std::string perm_str = "";
    // for (int i=0;i<15;i++){
    //     perm_str += ( std::to_string(perm[i]) + " ,");
    // }
    // perm_str+= std::to_string(perm[15]);
    // std::cout << perm_str;

    //TEst for AS1 at non even pos
    for(unsigned int diff = 1; diff < 65536; diff <<= 1){
        if (hw16_check_even_pos(diff)==1){ //No active AS first round
            continue;
        }

        std::cout << std::hex << diff << std::endl;
    }

}