//g++ test.cpp 
#include <iostream>
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
    int hw=4;
    int pos[hw] = {2,4,8,16};
    unsigned short tmp;
    for (int i=0;i<(1<<hw);i++){
        tmp=0;
        for (int j=0;j<hw;j++){
            tmp = tmp ^ (((i & (1<<j))>>j) << (pos[j]-1) );
        }
        std::cout<<std::hex << (int) tmp << std::endl;  
    }

}