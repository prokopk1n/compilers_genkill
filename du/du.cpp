#define export exports
extern "C" {
#include <qbe/all.h>
}
#undef export

#include <stdio.h>
#include <iostream>
#include <unordered_set>
#include <string>


static void readfn (Fn *fn) {
  for (Blk *blk = fn->start; blk; blk = blk->link) {
    std::unordered_set<std::string> def;
    std::unordered_set<std::string> use;

    for (int i = 0; i < blk->nins; i++) {
      Ref value = blk->ins[i].to;
      Ref first_arg = blk->ins[i].arg[0];
      Ref second_arg = blk->ins[i].arg[1];

      if (first_arg.val >= Tmp0 && first_arg.type == RTmp &&
          def.find(fn->tmp[first_arg.val].name) == def.end())
          use.insert(fn->tmp[first_arg.val].name);

      if (second_arg.val >= Tmp0 && second_arg.type == RTmp &&
          def.find(fn->tmp[second_arg.val].name) == def.end())
          use.insert(fn->tmp[second_arg.val].name);

      if (value.val >= Tmp0 && value.type == RTmp)
          def.insert(fn->tmp[value.val].name);
    }

    if ((blk->s1 == NULL) && (blk->s2 == NULL)) {
      Ref return_value = blk->jmp.arg;

      if (return_value.val >= Tmp0 && return_value.type == RTmp &&
          def.find(fn->tmp[return_value.val].name) == def.end())
        use.insert(fn->tmp[return_value.val].name);
    }
    
    printf("@%s", blk->name);
    printf("\n\tdef =");
    for (auto elem: def) {
      std::cout << " %" << elem;
    }

    printf("\n\tuse =");
    for (auto elem: use) {
      std::cout << " %" << elem;
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }
}

static void readdat (Dat *dat) {
  (void) dat;
}

int main () {
  parse(stdin, (char *)"<stdin>", readdat, readfn);
  freeall();
}
