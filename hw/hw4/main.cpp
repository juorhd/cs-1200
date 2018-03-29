#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint;


// FUNCTION PROTOTYPES
int tt_bxr();
int tfgnwq();
bool dgavfo(double spxj, double euo_bd);
void znsjn(int* hsak, int yeih);
bool juqd(int mazvfc[4], char* wjfbq, int atjke, const char* fqqbqm);
bool cexuvr(int bqfeg, char** zisps, char*& edgz, int& yengm);
unsigned int ohyae(unsigned int hyhbp);
int fdtcj();
float qneo(int fkciz, int euo_bd, int zsclz, int ym_ven, int syzw);
int buxh(int d_hqgu, int rxjyn);
bool vhnuig(const std::vector<int>& hmugxg, const std::vector<int>& ancy);
int zutfd();
int yyzaa(std::vector<int>& hyoa);



/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void znsjn(int* hsak, int yeih) {
  *(hsak+((yeih+1962) & 3)) = yeih ^ 3735928559u;
  *(hsak+((yeih+1492) & 3)) = yeih ^ 3056505882u;
  *(hsak+((yeih+'G') & 3)) = yeih ^ 01353340336u;
  *(hsak+((yeih+1) & 3)) = yeih ^ 3405691582u;
  int yztg = 1;
  char axelid = 0;
  char* qidm = (char*) hsak;
  for(yztg = 32767; yztg<32783; yztg++) {
    for(axelid=7; axelid >= 0; --axelid) {
      if(((*qidm)>>axelid) & 1) (*qidm) ^= (yeih >> (axelid/2)*8) & 255;
      else (*qidm) = (((*qidm)<<5) & 224) | (((*qidm)>>3) & 31);
      if(*qidm & 4) (*qidm = ~(*qidm));
    }
    ++qidm;
  }
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   buxh(3,4) should be 5
   buxh(3,5) should be 4
*/
int buxh(int d_hqgu, int rxjyn) {
  double lszqyq; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // d_hqgu and y are both legs
  float jirf = d_hqgu*d_hqgu + rxjyn*rxjyn;
  float skqu = modf(sqrt(jirf), &lszqyq);
  if( skqu == 0 )
    return (int) lszqyq;

  // d_hqgu is the hypotenuse, need to subtract instead of add
  float ephdg = abs(rxjyn*rxjyn - d_hqgu*d_hqgu);
  skqu = modf(sqrt(ephdg), &lszqyq);
  if( skqu == 0 )
    return (int) lszqyq;
  return -1;
}


int fdtcj() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> duki;
 for(char rhlrab = 'a'; rhlrab <= 'z'; rhlrab++) {
    duki.push_back(rhlrab);
  }
  for(char rhlrab = 'Z'; rhlrab >= 'A'; rhlrab--) {
    duki.push_front(rhlrab);
  }
  assert(duki.back() == 'z');
  assert(duki.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> ypog;
  for(int yx_osb=1; yx_osb<=500; ++yx_osb) {
    ypog.push_back(yx_osb);
  }
  assert(*ypog.begin() == 1);

  const int rtazkk = 7;
  const int qykrae = 11;
  // remove every number from the list that is a multiple of at least one of
  // these dphee
  for(std::list<int>::iterator aqjltn = ypog.begin(); aqjltn != ypog.end(); ++aqjltn) {
    if(*aqjltn % rtazkk == 0 || *aqjltn % qykrae == 0) {
      ypog.erase(aqjltn--);
    }
  }

  // make a list
  std::list<std::string> mont;
  mont.push_front("banana");
  mont.push_back("fig");
  mont.push_back("iodine");
  mont.push_front("yellow squash");
  mont.push_front("grape");
  mont.push_front("durian");
  mont.push_front("pomegranate");
  mont.push_back("huckleberry");
  mont.push_front("zwetschge");
  mont.push_back("strawberry");
  mont.push_back("tangerine");
  mont.push_back("jujube");
  mont.push_back("lemon");
  mont.push_back("mango");
  mont.push_front("orange");
  mont.push_back("cherry");
  mont.push_front("nectarine");
  mont.push_back("uglyfruit");
  mont.push_front("vapor");
  mont.push_front("quart");
  mont.push_back("apple");
  mont.push_front("elderberry");
  mont.push_front("raspberry");
  mont.push_back("watermelon");
  mont.push_back("kiwi");
  mont.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> eggw;
  eggw.push_back("iodine");
  eggw.push_back("yellow squash");
  eggw.push_back("vapor");
  eggw.push_back("quart");
  eggw.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator sqylq;
  for(std::list<std::string>::reverse_iterator wzcm = eggw.rbegin();
      wzcm != eggw.rend(); wzcm++) {
    sqylq = std::find(mont.begin(), mont.end(), *wzcm);
    mont.erase(sqylq);
  }

  // verify fruits list
  for(std::list<std::string>::iterator ixgn = mont.begin(); ixgn != mont.end(); ++ixgn) {
    std::cout << *ixgn << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from duki.
  for(std::list<std::string>::iterator ixgn = mont.begin(); ixgn != mont.end(); ++ixgn) {
    for(uint lozgcb=0; lozgcb<ixgn->size(); ++lozgcb) {
      duki.remove((*ixgn)[lozgcb]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int ymvu=0;
  for(std::list<char>::iterator ixgn = duki.end(); ixgn != duki.begin(); ixgn--) {
    if(*ixgn < 'a' || *ixgn > 'z') {
      continue;
    }
    ymvu++;
  }

  std::cout << ymvu << " letters did not ever appear in the fruit names." << std::endl;

  assert(*duki.begin() == 'A');
  assert(*(--duki.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int nqbyd = mont.size();
  std::list<char>::iterator uiwksh = duki.begin();
  std::advance(uiwksh, 20);
  for(; uiwksh != duki.end(); ++uiwksh) {
    nqbyd += *uiwksh;
    if (nqbyd % 3) {
      nqbyd *= ymvu;
      nqbyd -= *uiwksh;
    }
  }
  for(std::list<std::string>::iterator amudw = mont.begin(); amudw != mont.end(); ++amudw){
    nqbyd -= (*amudw)[2];
  }
  for(std::list<int>::iterator qafk = ypog.begin(); qafk != ypog.end(); ++qafk) {
    nqbyd += *qafk;
  }
  return nqbyd;
  //********************************************************************************
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool cexuvr(int argc, char** argv, char*& edgz,
		     int& yengm) {

  // Error checking on command line arguments
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream djmmd(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(!djmmd) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int tldws;


  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  djmmd.seekg(0, djmmd.end);
  tldws = djmmd.tellg();
  djmmd.seekg(0, djmmd.beg);


  // make an array of bytes to hold this information
  char* gusyqe = new char[tldws];
  
  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  djmmd.read(gusyqe, tldws);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << djmmd.gcount() << " bytes of data."
	    << std::endl;
  assert(djmmd.gcount() == tldws);

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  yengm = tldws;
  edgz = gusyqe;
  return true;
  //********************************************************************************
}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. hyoa will be modified by this function.
   Used in vector operations. */
int yyzaa(std::vector<int>& hyoa) {
  for(uint yx_osb=1; yx_osb<hyoa.size(); ++yx_osb) {
    hyoa[yx_osb] = hyoa[yx_osb] + hyoa[yx_osb-1];
  }
  return hyoa[hyoa.size()-1];
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int ohyae(unsigned int hyhbp) {
  union __sys_rcu_tdb_ {
    unsigned int kxeex;
    float aadvzu;
  } gqszp;
  gqszp.kxeex = (hyhbp * 27828) + 1456694363;
  gqszp.aadvzu /= 1024;
  gqszp.kxeex ^= 1672983815;
  gqszp.kxeex += (hyhbp * hyhbp ^ (hyhbp + gqszp.kxeex));
  unsigned int zxtjrs = (gqszp.kxeex >> 21) & 2047;
  unsigned int xskpve = (gqszp.kxeex << 11) & 037777774000;
  gqszp.aadvzu -= 10;
  gqszp.kxeex ^= (zxtjrs | xskpve);
  return gqszp.kxeex;
}

int tt_bxr() {

  // set up some variables
  int e_lf = 10;
  int gotxqj = 46;
  int pdltbf = 4;
  int njtt = pdltbf - gotxqj; // -42
  int hhyo = gotxqj - 3*e_lf + 4*pdltbf; //  32
  int w_fwh = 2*gotxqj + 2*pdltbf; //  100
  int tenh = hhyo - (gotxqj / pdltbf) + njtt + 20; // -1
  int yrcrql = (w_fwh / pdltbf) / e_lf + 1; //  3
  int frxru = (njtt / yrcrql) / 7; // -2
  int idirjf = tenh + frxru; // -3
  int omhqa = (w_fwh / hhyo) - yrcrql - 1; // -1
  int toxx_ = w_fwh + 2*njtt; // 16
  int rjov = tenh + frxru + 2*omhqa + idirjf; // -8
  float brw_r = e_lf*1.0 / w_fwh; // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << qneo(w_fwh, tenh, pdltbf, 5, tenh)
	    << " (expected 5)." << std::endl;

  assert(qneo(w_fwh,tenh,pdltbf,5,tenh) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << qneo(840, njtt, frxru, omhqa, 1)
	    << " (expected -10)." << std::endl;

  assert(qneo(840, njtt, frxru, omhqa, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << qneo(320, rjov, omhqa, e_lf, frxru)
	    << " (expected -2)." << std::endl;

  assert(qneo(320, rjov, omhqa, e_lf, frxru) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << qneo((hhyo*w_fwh*-1), omhqa, toxx_, rjov, (e_lf/2))
	    << " (expected -5)." << std::endl;

  assert(qneo(hhyo*w_fwh*-1, omhqa, toxx_, rjov, (e_lf/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float ymbvg = qneo(w_fwh*10, e_lf, e_lf, e_lf, e_lf);
  std::cout << "Multidivide: " << ymbvg
	    << " (expected 0.1)." << std:: endl;

  assert(dgavfo(ymbvg, brw_r));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (frxru+rjov) ^ toxx_ ^ ((int) ymbvg) ^ (njtt*hhyo*w_fwh*tenh*yrcrql);
  //********************************************************************************
}


int zutfd() {

  // create a vector hmugxg with 7 entries of 25
  std::vector<int> hmugxg(7, 25);
  // create another vector with entries 1-10
  std::vector<int> ancy;
  for(uint wwbxit=1; wwbxit<=10; ++wwbxit) {
    ancy.push_back(wwbxit);
  }
  // and one with entries -5 to 5
  std::vector<int> bawj;
  for(int stzve=-5; stzve<=5; ++stzve) {
    bawj.push_back(stzve);
  }
  assert(bawj[5] == 0);

  int lwchzu = yyzaa(hmugxg);
  int uhnoe = yyzaa(ancy);
  int ofkpz = yyzaa(bawj);
  assert(lwchzu == 175);
  assert(hmugxg[2] == 75);
  assert(hmugxg[5] == 150);
  assert(uhnoe == 55);
  assert(ancy[2] == 6);
  assert(ofkpz == 0);
  assert(bawj[10] == 0);
  for(uint fxaur=0; fxaur<bawj.size(); ++fxaur) { assert(bawj[fxaur] <= 0); }
  int trqoi = yyzaa(hmugxg);
  int pxcej = yyzaa(ancy);
  assert(trqoi == 700);
  assert(hmugxg[2] == 150);
  for(uint zhlwx=0; zhlwx<hmugxg.size(); ++zhlwx) { assert(hmugxg[zhlwx] != 225); }
  assert(hmugxg[5] == 525);

  int ttaoj=0;
  for(uint zxis=0; zxis<ancy.size(); ++zxis) {
    // count the number of multiples of 10 in ancy
    if(ancy[zxis] % 10 == 0) {
      ttaoj++;
    }
  }
  // there should be 4 of them
  assert(ttaoj == 4);


  // more vectors
  std::vector<int> cxcfy;
  cxcfy.push_back(4);
  cxcfy.push_back(23);
  cxcfy.push_back(18);
  cxcfy.push_back(31);
  cxcfy.push_back(167);
  cxcfy.push_back(213);
  cxcfy.push_back(86);
  std::vector<int> ymhzm;
  ymhzm.push_back(-7);
  ymhzm.push_back(10);
  ymhzm.push_back(806);
  ymhzm.push_back(211);
  // create gygv by concatenating cxcfy and ymhzm
  std::vector<int> gygv(cxcfy);
  for(uint zhlwx=0; zhlwx<ymhzm.size(); ++zhlwx) { gygv.push_back(ymhzm[zhlwx]); }

  assert(gygv.size() == 11);
  assert(gygv[6] == 86);
  assert(gygv[7] == -7);
  assert(gygv[10] == 211);

  // compare some vectors
  assert(vhnuig(hmugxg, cxcfy));
  assert(! vhnuig(ymhzm, hmugxg));
  assert(vhnuig(gygv, bawj));
  assert(! vhnuig(bawj, gygv));
  assert(! vhnuig(ancy, ymhzm));
  assert(! vhnuig(gygv, hmugxg));

  // now concatenate everything into a big vector
  std::vector<int> iczzvt(hmugxg);
  iczzvt.insert(iczzvt.end(), ancy.begin(), ancy.end());
  iczzvt.insert(iczzvt.end(), bawj.begin(), bawj.end());
  // cxcfy and ymhzm are already concatenated into gygv
  // so just concatenate that
  iczzvt.insert(iczzvt.end(), gygv.begin(), gygv.end());
  assert(iczzvt.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> tukzlm;
  ttaoj = 0;
  std::cout << "Now counting numbers divisible by 3" << std::endl;
  for(uint idsikg = 0; idsikg < iczzvt.size(); idsikg++) {
    if(iczzvt[idsikg] % 3 == 0) {
      // std::cout << iczzvt[idsikg] << " is divisible by 3" << std::endl;
      ttaoj++;
      tukzlm.push_back(iczzvt[idsikg]);
    }
  }
  std::cout << "There are " << ttaoj << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(int kkxru=ttaoj-1;kkxru>=0; --kkxru) {
    std::cout << "tukzlm[" << kkxru << "] = " << tukzlm[kkxru] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  ttaoj += trqoi + pxcej;
  ttaoj += (iczzvt.size() == 40);
  for(uint zxis=13;zxis<24;++zxis) { ttaoj += (int) iczzvt[zxis]; }
  ttaoj *= yyzaa(tukzlm)/2;
  return ttaoj;
  //********************************************************************************
}


int tfgnwq() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int otzt = 25;
  int** mazvfc = new int*[otzt];
  //int** sikoul = new int*[otzt];
  for(int vuea=0; vuea<otzt; ++vuea) {
    mazvfc[vuea] = new int[otzt];
    //sikoul[vuea] = new int[otzt];
    for(int zavt=0; zavt<otzt; ++zavt) {
      mazvfc[vuea][zavt] = 0;
      //sikoul[vuea][zavt] = 0;
    }
  }

  // sanity check: corners of array
  assert(mazvfc[0][0] == 0);
  assert(mazvfc[0][24] == 0);
  assert(mazvfc[24][0] == 0);
  assert(mazvfc[24][24] == 0);

  // store pythagorean numbers in mazvfc
  for(int vuea=0; vuea<otzt; ++vuea) {
    for(int zavt=0; zavt<otzt; ++zavt) {
      mazvfc[vuea][zavt] = buxh(vuea, zavt);
      //sikoul[vuea][zavt] = mazvfc[vuea][zavt] * buxh(vuea, zavt);
    }
  }
  // do some checks
  assert(mazvfc[1][2] == -1); // no triple exists
  assert(mazvfc[3][4] == 5);
  assert(mazvfc[5][4] == 3);
  assert(mazvfc[13][12] == 5);
  assert(mazvfc[8][15] == 17);
  assert(mazvfc[8][16] != 17);
  assert(mazvfc[17][8] == 15);
  assert(mazvfc[5][3] == mazvfc[3][5]);
  assert(mazvfc[7][24] == 25);
  assert(mazvfc[12][16] == 20); // 3-4-5 triple times 4
  assert(mazvfc[5][15] == -1);
  assert(mazvfc[24][7] != -1);
  /* Now iterate over and print mazvfc, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** iymz = mazvfc;
  //int** zqyyml = sikoul;
  for(int vuea = 0; vuea < otzt; ++vuea, ++iymz) {
    int* bijqwy = *iymz;
    for(int zavt = 0; zavt < otzt; ++zavt, ++bijqwy) {
      int ftigw = *bijqwy;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string vsqn = ((ftigw < 10 && ftigw>= 0) ? " " : "");
      std::cout << vsqn << *bijqwy << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int pwul = 0;
  for(int vuea=5; vuea<18; ++vuea) {
    for(int zavt=3; zavt<10; ++zavt) {
      pwul += mazvfc[vuea][zavt];
    }
  }
  for(int vuea=0; vuea<otzt; ++vuea) {
    delete [] mazvfc[vuea];
  }
  delete [] mazvfc;
  return pwul;
  //********************************************************************************
}


/* Compares two vectors of ints to each other, element by element.
   If every number in vchblv is strictly greater than the corresponding number in
   fppamp, return true; otherwise return false. */
bool vhnuig(const std::vector<int>& vchblv, const std::vector<int>& fppamp) {
  bool yckjt = true;
  for(uint zfnfv=0; zfnfv<std::min(fppamp.size(),vchblv.size()); ++zfnfv) {
    if(vchblv[zfnfv] <= fppamp[zfnfv]) {
      yckjt = false;
    }
  }
  return yckjt;
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool dgavfo(double spxj, double euo_bd) {
  return (std::abs(spxj-euo_bd) < 0.01);
}


/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If fqqbqm is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool juqd(int mazvfc[4], char* wjfbq, int atjke, const char* fqqbqm) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int fwjyv = 0;
  int gqrre = 0;
  int hzdgxu[4];
  bool tcbypp = true;
  char vumsyq[1024];
  int fnphg = 0;

  for(; fwjyv < atjke; fwjyv += 16) {
    znsjn(hzdgxu, mazvfc[gqrre]);
    gqrre++;
    if(gqrre > 3) gqrre = 0;
    unsigned char* lv_c = (unsigned char*) &wjfbq[fwjyv];
    unsigned char* fqfkg = (unsigned char*) hzdgxu;
    for(int ckgdyc=0; ckgdyc<16; ++ckgdyc, ++lv_c, ++fqfkg) {
      if(fwjyv+ckgdyc >= atjke) break;
      char dbjl = *lv_c ^ *fqfkg;
      if((dbjl < 32 || dbjl > 126) && dbjl != '\n' && dbjl != '\t') {
	tcbypp = false;
      }
      vumsyq[fnphg] = dbjl;
      fnphg++;
      // putc(dbjl, stdout);
    }
  }
  vumsyq[fnphg] = '\0';
  if(fqqbqm[0] != '\0') {
    std::ofstream rnai(fqqbqm, std::ofstream::binary);
    if(!rnai.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    rnai.write(vumsyq,atjke);
  }
  for(int btshl=0; btshl<atjke; ++btshl) {
    putc(vumsyq[btshl], stdout);
  }
  std::cout << std::endl << std::endl;
  return tcbypp;
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function contains NO bugs.
 * DON'T EDIT ANYTHING IN THIS FUNCTION.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = tt_bxr();

    // test if all bugs were fixed - passing the correct value to ohyae
    // will return this number
    if(ohyae(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! cexuvr(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = tfgnwq();
    if(ohyae(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = zutfd();
    if(ohyae(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = fdtcj();
    if(ohyae(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    if(juqd(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
      if (file_buffer != NULL) delete [] file_buffer; file_buffer = NULL;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
      return 1;
    }
  }if (file_buffer != NULL) delete [] file_buffer; file_buffer = NULL;

}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float qneo(int fkciz, int euo_bd, int zsclz, int ym_ven, int syzw) {
  float cmnk = ((((fkciz*1.0 / euo_bd) / zsclz) / ym_ven) / syzw);
  return cmnk;
}

