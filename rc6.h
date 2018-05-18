
//RC6 info -- https://www.sbprojects.net/knowledge/ir/rc6.php


#ifndef RC6_H
#define RC6_H

//freq 36khz  ..time period ~= 28us
//All rounded to nearest value as per specs.

#define RC6_LEADER_COUNT 97    //   2666/28
#define RC6_BIT_ONE_COUNT 17   //   444/28
#define RC6_BIT_ZERO_COUNT 17  //   444/28
#define RC6_TRAILER_COUNT 33   //   889/28


//Blank intervals(delay).
//blank step = 50us.

#define RC6_LEADER_BLANK 17  //     900/50 us
#define RC6_BIT_ONE_BLANK 8  //     444/50 us
#define RC6_BIT_ZERO_BLANK 8 //     444/50 us
#define RC6_TRAILER_BLANK 17 //     889/50 us



#define RC6_DELAY 70


void start_tx_rc6(uint32_t);




#endif
