#include "OrderPool.cpp"

#include <iostream>
#include <vector>


int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.

    OrderPool order_pool = OrderPool(1000000);
    Order* test = order_pool.acquire();


    return 0;
}