#define export exports
extern "C" {
#include <qbe/all.h>
}
#undef export

#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

static void readfn (Fn *fn) {
    std::unordered_map<std::string, std::vector<std::string>> vars_blocks = {};
    std::unordered_map<std::string, std::vector<std::string>> blocks_vars = {};

    for (Blk *blk = fn->start; blk; blk = blk->link) {
		for (int i = 0; i < blk->nins; i++) {
            if (blk->ins[i].to.val >= Tmp0) {
                if (vars_blocks[fn->tmp[blk->ins[i].to.val].name].size() == 0 
                    || vars_blocks[fn->tmp[blk->ins[i].to.val].name].back() != blk->name) {
                    vars_blocks[fn->tmp[blk->ins[i].to.val].name].push_back(blk->name);
                    blocks_vars[blk->name].push_back(fn->tmp[blk->ins[i].to.val].name);
                }
            }
        }
	}


	for (Blk *blk = fn->start; blk; blk = blk->link) {
		printf("@%s", blk->name);

        printf("\n\tgen =");

		for (auto var_name: blocks_vars[blk->name]) {
            std::cout << " @" << blk->name << "%" << var_name;
        }

        printf("\n\tkill =");

        for (auto var_name: blocks_vars[blk->name]) {
            for (auto block: vars_blocks[var_name]) {
                if (block != std::string(blk->name)) {
                    std::cout << " @" << block << "%" << var_name;
                }
            }
        }

		printf("\n\n");
	}
}

static void readdat (Dat *dat) {
	(void) dat;
}

int main () {
	parse(stdin, (char *)"<stdin>", readdat, readfn);
	freeall();
}