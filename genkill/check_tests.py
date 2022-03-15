import sys
import re


def parse_gen_kill(map, file, block):
    line = file.readline()
    if line.find("kill") != -1 and line.find("gen") != -1:
        return
    if not line:
        return
    if line.find("kill") != -1 or line.find("gen") != -1:
        line = line.split("gen =")[1]
        for string in line.split(" "):
            if re.match(r".*\w.*", string):
                map[block][0].append(string.strip(" \n\t"))
        line = file.readline()
        line = line.split("kill =")[1]
        for string in line.split(" "):
            if re.match(r".*\w.*", string):
                map[block][1].append(string.strip(" \n\t"))


def create_map(file):
    map = {}
    with open(file, "r") as f:
        for line in f:
            if line.startswith("@"):
                map[line.split("@")[1].strip(" \n\t")] = (list(), list())
                parse_gen_kill(map, f, line.split("@")[1].strip(" \n\t"))
    return map


def compare_maps(map1, map2):
    for key in map1:
        gen1 = map1[key][0]
        gen2 = map2[key][0]
        if len(gen2) != len(gen1):
            return False
        for elem in gen1:
            if elem not in gen2:
                return False
        kill1 = map1[key][1]
        kill2 = map2[key][1]
        if len(kill1) != len(kill2):
            return False
        for elem in kill1:
            if elem not in kill2:
                return False
    return True




if __name__ == '__main__':
    correct_map = create_map(sys.argv[1])
    getting_map = create_map(sys.argv[2])
    if compare_maps(correct_map, getting_map):
        print("TEST PASSED")
    else:
        print("TEST FAILED")

