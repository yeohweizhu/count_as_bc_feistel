
// #include "stdafx.h"
#ifndef COMMON_H
#include "common.h"
#include <fstream>
#include <bitset>
#endif

#ifndef CP_DIFF_TRAIL_SEARCH_H_
#include "trail_as_search.h"
#endif

using namespace std;
std::map<string, int> truncSet;

long globalCount = 0;
int perm[16] ={5,0,1,4,7,12,3,8,13,6,9,2,15,10,11,14}; //TWINE permutation

void roundProcess(const int n, const int nrounds, int as, int B[], int* Bn,
	unsigned short internalTruncState[NROUNDS + 1][2])
{
	ofstream file;
	file.open("trainingdata4bit4to12(0312).txt", ios::in | ios::app);
	unsigned short ori = internalTruncState[n][1];
	unsigned short new_diff = 0;
	unsigned short mask = 0;
	int hw = 0;
	unsigned short tmp_diff, tmp = 0;

	//1 - 0x1	9 - 0x100
	//2 - 0x2	10- 0x200
	//3 - 0x4	11- 0x400
	//4 - 0x8	12- 0x800
	//5 - 0x10	13- 0x1000
	//6 - 0x20	14- 0x2000
	//7 - 0x40	15- 0x4000
	//8 - 0x80	16- 0x8000
	for (int i=0;i<16;i++){
		if (perm[i] < i){
			new_diff = new_diff | ( (ori & (0x1 << i)) >> (i-perm[i]) );
		}else{
			new_diff = new_diff | ( (ori & (0x1 << i)) << (perm[i]-i) );
		}
	}

    int pos[16] = {0};
    //Generate Mask
	if (((ori&0x2)!=0) && ((ori&0x1)!=0)){
        mask = mask | 0x2;
		pos[hw] = 2;
        hw++;
	}
	if (((ori&0x8)!=0) && ((ori&0x4)!=0)){
        mask = mask | 0x8;
		pos[hw] = 4;
        hw++;
	}
	if (((ori&0x20)!=0) && ((ori&0x10)!=0)){
        mask = mask | 0x20;
		pos[hw] = 6;
        hw++;
	}
	if (((ori&0x80)!=0) && ((ori&0x40)!=0)){
        mask = mask | 0x80;
		pos[hw] = 8;
        hw++;
	}

	if (((ori&0x200)!=0) && ((ori&0x100)!=0)){
        mask = mask | 0x200;
		pos[hw] = 10;
        hw++;
	}
	if (((ori&0x800)!=0) && ((ori&0x400)!=0)){
        mask = mask | 0x800;
		pos[hw] = 12;
        hw++;
	}

	if (((ori&0x2000)!=0) && ((ori&0x1000)!=0)){
        mask = mask | 0x2000;
		pos[hw] = 14;
        hw++;
	}
	if (((ori&0x8000)!=0) && ((ori&0x4000)!=0)){
        mask = mask | 0x8000;
		pos[hw] = 16;
        hw++;
	}

    //Generate Mask End

	for(unsigned i=0;i<(1<<hw);i++){
		// unsigned int tmp_as;
		// unsigned bitIdx = 0;
		// for(unsigned k=0;k<4;k++){
		// 	if(((mask>>k)&(0x1))!=0){
		// 		tmp = tmp ^ (((i>>bitIdx)&0x1)<<k);
		// 		bitIdx++;
		// 	}
		// }

        tmp=0;
        for (int j=0;j<hw;j++){
            tmp = tmp ^ (((i & (1<<j))>>j) << (pos[j]-1) );
        }

		unsigned int tmp_as;
		tmp_as = as + hw16_check_even_pos(ori);

		// only one round
		if (((n == 0) && (nrounds == 1)) /*&& ((tmp_as <= *Bn))*/) {
			internalTruncState[n+1][0]=tmp_as;
			internalTruncState[n+1][1]=new_diff^tmp;
			//------------ update Bn value!!------------
			*Bn = tmp_as;
			B[n] = tmp_as;
		}

		// Round-0 and not last round
		if ((n == 0) && (nrounds > 1)){
			//if (tmp_as <= *Bn){
				internalTruncState[n+1][0]=hw4(ori);
				internalTruncState[n+1][1]=new_diff^tmp;
				cp_AS_threshold_search(n+1, nrounds, B, Bn, internalTruncState);
			//}
		}

		// Round-i and not last round
		if ((n >= 1) && (n != (nrounds - 1))){
			//if (tmp_as <= *Bn) {
				internalTruncState[n+1][0]=hw4(ori);
				internalTruncState[n+1][1]=new_diff^tmp;
				cp_AS_threshold_search(n+1, nrounds, B, Bn, internalTruncState);
			//}
		}

		// last round
		if((n == (nrounds - 1)) && (nrounds > 1)) {
			//if (tmp_as <= *Bn) {
				internalTruncState[n+1][0]=hw4(ori);
				internalTruncState[n+1][1]=new_diff^tmp;
				//------------ update Bn value!!------------
				*Bn = tmp_as;
				B[n] = tmp_as;

				//[round from 0 to NROUNDS-1][0-Number of AS, 1-Truncated Difference]
				if (n==NROUNDS-1)
				{
					int AS = 0;
					for (int i = 0; i < nrounds; i++)
					{
						//print_binary(internalTruncState[i][1]);
						//cout << " : " << internalTruncState[i][0] << endl;
						AS = AS + internalTruncState[i][0];
					}
					//print_binary(internalTruncState[NROUNDS][1]);
					//cout << " : " << internalTruncState[NROUNDS][0] << endl;
					AS = AS + internalTruncState[NROUNDS][0];

					//cout << hex << internalTruncState[0][1] << ", " << hex << internalTruncState[NROUNDS][1] << ", " << AS << ", 11, " << "['0011', '0000', '0001', '0010']" << endl;
					//file << std::bitset<4>(internalTruncState[0][1]) << ", " << std::bitset<4>(internalTruncState[NROUNDS][1]) << ", " << AS << ", 19, " << std::bitset<64>(0x3012) << endl;
					file << std::bitset<4>(internalTruncState[0][1]) << ", " << std::bitset<4>(internalTruncState[NROUNDS][1]) << ", " << AS << ", 12, " << "1, 3, 0, 2" << endl;
				}
			//}
        }
		tmp = 0;
	}
}


int cp_init_estimate(uint32_t next_round,  int B[NROUNDS], unsigned short internalTruncState[NROUNDS+1][2])
{
	int Bn_init;

	unsigned short diff = internalTruncState[next_round][1];

	int estimate_as = hw16_check_even_pos(diff) + 2;  // error is set to 2

	Bn_init = B[next_round-1] + estimate_as;

	cout << "Extend trail to round "<< next_round<<", "<< dec <<"Next round estimated as: "<< estimate_as
	  <<", Bn_init = "<< Bn_init <<endl;
	cout<<"-----------------------------------------------------"<<endl;
	return Bn_init;
}

void cp_AS_threshold_search(const int n, const int nrounds, int B[NROUNDS], int* Bn,
								unsigned short internalTruncState[NROUNDS + 1][2])
{
	// Only one round
	if ((n == 0) && (nrounds == 1)) {
		assert(*Bn == 2);
		for(unsigned short diff = 1; diff < 16; diff++){
					internalTruncState[0][0]=0;
					internalTruncState[0][1]=diff; // plaintext differences
					roundProcess(n, nrounds, 0, B, Bn, internalTruncState);
		}
	}

	// Round-0 and not last round
	if ((n == 0) && (nrounds > 1)) {
		for(unsigned short diff = 1; diff < 16; diff++){
                internalTruncState[0][0]=0;
                internalTruncState[0][1]=diff; // plaintext differences
                unsigned int as = B[nrounds-1-(n+1)];  // assign B[nrounds-2] to pn,  ( B[0],...,B[nrounds-2],B[nrounds-1])
                roundProcess(n, nrounds, as, B, Bn, internalTruncState);
		}
	}

	// Round-i and not last round
	if ((n >= 1) && (n != (nrounds - 1))) {
		int as = 0;
		for(int k = 0; k < n; k++) { // as[0] + as[1]+...
			as += internalTruncState[k+1][0];
		}
		as += B[nrounds-1-(n+1)];
		roundProcess(n, nrounds, as, B, Bn, internalTruncState);
	}

	// last round
	if ((n == (nrounds - 1)) && (nrounds > 1)) {
		int as = 0;
		for(int k = 0; k < n; k++) { // as[0] + as[1]+...
			as += internalTruncState[k+1][0];
		}
		roundProcess(n, nrounds, as, B, Bn, internalTruncState);
	}
}

uint32_t cp_AS_search(int B[])
{
	// uint32_t num_rounds = NROUNDS; //UNUSED 
	// number of AS, truncated_diff,
	// [0] = AS
	// [1] = truncated state for 16 different F-function unit
	unsigned short internalTruncState[NROUNDS+1][2]={0};  
	//Can be changed to shorter bit length as the original intention of the author was to use it for 16bit structure only. Now we have to define it to be one sbox unit (in this case byte 8-bit to cover potential expansion to 8-bit sbox [still require to change something])

	// init bounds for number of AS
	//B[i] = number of minimum AS at round i+1
	for(int i = 0; i < NROUNDS; i++)
	{
		B[i] = 0;
	}

	// initial bound - best largest round prob estimation
	int Bn_init = 2; // largest as for one round

	uint32_t nrounds = 0;

	do {
		nrounds++; //Lets do the first/n round
		//cout<<"number rounds to process(nrounds) = "<<nrounds <<", Bn_init = "<<Bn_init<<endl;

		int Bn = Bn_init;		  //Set the min AS to initial bound
		B[nrounds - 1] = Bn_init;
		int r = 0;						  // initial round

		// initialize the diff path and probability for NROUNDS
		for (int i = 0; i <= NROUNDS; i++) {
			internalTruncState[i][0] = 0; // AS
			internalTruncState[i][1] = 0; // truncated_diff
		}

		// r: index of current round(0~), nrounds: total number of rounds(NROUNDS), Bn: the best found probability on n rounds
		cp_AS_threshold_search(r, nrounds, B, &Bn, internalTruncState);
		assert(B[nrounds - 1] == Bn);

		// print out the active sbox found for "nrounds" rounds
		for (uint32_t i = 0; i < nrounds; i++) {
			cout<<"B[" << i << "] = "<< B[i] ;
			cout<<endl;
		}

		// compute initial estimate for next round
		uint32_t next_round = nrounds;
		Bn_init = cp_init_estimate(next_round, B, internalTruncState);

	} while ((nrounds < NROUNDS) //Check rounds complete after doing round n
		&& ((B[nrounds - 1] < max_as) || (nrounds == 0)));

    cout << "Number of best paths: " << dec << globalCount << endl;
	return nrounds;
}