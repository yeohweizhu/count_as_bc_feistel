//g++ test.cpp 
#include <iostream>
#include <string>
#include <bitset>

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

    int mask = 0x2 | 0x8 | 0x20;
    int hw=4;
    int pos[hw] = {1,3,7,15};
    unsigned short tmp;
    for (int i=0;i<(1<<hw);i++){
        tmp=0;
        for (int j=0;j<hw;j++){
            tmp = tmp ^ (((i & (1<<j))>>j) << (pos[j]-1) );
        }
        std::cout<<std::hex << (int) tmp << std::endl;  
    }

    //Test for permutation str
    // int perm[16] ={5,0,1,4,7,12,3,8,13,6,9,2,15,10,11,14}; //TWINE permutation
    // std::string perm_str = "";
    // for (int i=0;i<15;i++){
    //     perm_str += ( std::to_string(perm[i]) + " ,");
    // }
    // perm_str+= std::to_string(perm[15]);
    // std::cout << perm_str;

    //TEst for AS1 at non even pos
    // for(unsigned int diff = 1; diff < 65536; diff <<= 1){
    //     if (hw16_check_even_pos(diff)==1){ //No active AS first round
    //         continue;
    //     }

    //     std::cout << std::hex << diff << std::endl;
    // }


    // int something = 1;
    // std::cout  << std::bitset<16>(something);

    // int perm[16] ={1,4,5,0,13,6,9,2,7,12,3,8,11,14,15,10}; //TWINE permutation
    // int perm_reverse[16]={3,0,7,10,1,2,5,8,11,6,15,12,9,4,13,14};
    // // for (unsigned int diff=0;diff<65536;){
    // for(unsigned int diff = 1; diff < 65536; diff<<=1){
    //     // std::cout << diff;

    //     unsigned int new_diff=0;
    //     for (int i=0;i<16;i++){
    //         if (perm_reverse[i] < i){
    //             new_diff = new_diff | ( (diff & (0x1 << i)) >> (i-perm_reverse[i]) );
    //         }else{
    //             new_diff = new_diff | ( (diff & (0x1 << i)) << (perm_reverse[i]-i) );
    //         }
    //     } 

    //     unsigned int new_diff2=0;
    //     for (int i=0;i<16;i++){
    //         if (perm[i] < i){
    //             new_diff2 = new_diff2 | ( (new_diff & (0x1 << i)) >> (i-perm[i]) );
    //         }else{
    //             new_diff2 = new_diff2 | ( (new_diff & (0x1 << i)) << (perm[i]-i) );
    //         }
    //     } 

    //     std::cout << std::bitset<16>(diff) << " : " << std::bitset<16>(new_diff) << " :" <<  std::bitset<16>(new_diff2)<<std::endl;

    // }
}