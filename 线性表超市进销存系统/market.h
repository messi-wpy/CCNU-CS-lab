//
// Created by messi-lp on 18-10-11.
//

#ifndef UNTITLED4_MARKET_H
#define UNTITLED4_MARKET_H

#endif //UNTITLED4_MARKET_H

typedef struct {
    int id;
    char *name;
    int  num;
    int price;
    int point;

} merchandise;

void initList();
void purchase();
void wrongMessage(char *message);