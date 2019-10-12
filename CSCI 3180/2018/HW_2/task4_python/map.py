# CSCI3180 Principles of Programming Languages
#
# --- Declaration ---
#
# I declare that the assignment here submitted is original except for source
# material explicitly acknowledged. I also acknowledge that I am aware of
# University policy and regulations on honesty in academic work, and of the
# disciplinary guidelines and procedures applicable to breaches of such policy
# and regulations, as contained in the website
# http://www.cuhk.edu.hk/policy/academichonesty/
#
# Assignment 2
# Name : Wong Sin Yi
# Student ID : 1155110677
# Email Addr : 1155110677@link.cuhk.edu.hk

import random

from land import land
from pos import pos
from warrior import warrior
from elf import elf
from monster import monster
from potion import potion

class map:


    def __init__(self):
        self.__D = 10
        self.__teleportable_obj = []
        self.__e = random.randint(0,1) + 2
        self.__m = random.randint(0,1) + 2
        self.__p = random.randint(0,1) + 2
        self.__w = random.randint(0,1) + 2
        self.__total_num = self.__m + self.__e + self.__w + self.__p
        self.__num_of_alive_monsters = self.__m
        self.__num_of_alive_warriors = self.__w

    def initialize_all(self):  
        print('Welcome to Kafustrok. Light blesses you. ')
        self.__lands = []
        for i in range (0, self.__D):
            new = []
            for j in range (0, self.__D):
                new.append(land())
            self.__lands.append(new)

        for i in range (0, self.__total_num):
            pos = self.unoccupied_position
            if i < self.__m:
                self.__lands[pos.x][pos.y].occupied_obj = monster(pos.x, pos.y, i, self)
            elif i < self.__m + self.__e:
                self.__lands[pos.x][pos.y].occupied_obj = elf(pos.x, pos.y, i-self.__m, self)
            elif i < self.__m + self.__e + self.__p:
                self.__lands[pos.x][pos.y].occupied_obj = potion(pos.x, pos.y, i-self.__m - self.__e, self)
                self.__teleportable_obj.append(self.__lands[pos.x][pos.y].occupied_obj)
            else:
                self.__lands[pos.x][pos.y].occupied_obj = warrior(pos.x, pos.y, i-self.__m-self.__e -self.__p, self)
                self.__teleportable_obj.append(self.__lands[pos.x][pos.y].occupied_obj)

    def teleport_all(self):
        for obj in self.__teleportable_obj:
            if type(obj) is warrior:
                self.print_broad()
                obj.teleport()
                if self.num_of_alive_monsters == 0:
                    return
        for obj in self.__teleportable_obj:
            if type(obj) is potion:
                obj.teleport()

    def coming(self, posx, posy, warrior):
        return self.__lands[posx][posy].coming(warrior)

    def set_land(self,_pos, occupied_obj):
        self.__lands[_pos.x][_pos.y].occupied_obj = occupied_obj

    def delete_teleportable_obj(self, obj):
        index = self.__teleportable_obj.index(obj)
        self.__teleportable_obj[index] = None

    @property
    def unoccupied_position(self):
        randx = random.randint(0, self.__D - 1 )
        randy = random.randint(0, self.__D - 1 )
        while self.__lands[randx][randy].occupied_obj != None:
            randx = random.randint(0, self.__D - 1 )
            randy = random.randint(0, self.__D - 1 )
        return pos(randx, randy)

    def print_broad(self):
        printObject = []
        for i in range (0, self.__D):
            new = []
            printObject.append(new)

        for i in range (0, self.__D):
            for j in range (0, self.__D):
                occupant_name = self.__lands[i][j].occupant_name
                if occupant_name is None:
                    occupant_name = "  "
                printObject[i].append(occupant_name)

        print(" ", end = '')
        for i in range (0, self.__D):
            print("| "+ str(i) + "  ", end = '')
        print("|")

        for i in range (0, int(self.__D * 5.5)):
            print("-", end = '')
        print("")

        for row in range (0, self.__D):
            print(row, end = '')
            for col in range (0, self.__D):
                print("| "+ printObject[row][col] + " ", end = '')
            print("|")
            for i in range (0, int(self.__D * 5.5)):
                print("-", end = '')
            print("")

    def decrease_num_of_alive_monsters(self):
        self.__num_of_alive_monsters -= 1

    def decrease_num_of_warriors(self):
        self.__num_of_alive_warriors -= 1

    @property
    def num_of_alive_monsters(self):
        return self.__num_of_alive_monsters

    @num_of_alive_monsters.setter
    def num_of_alive_monsters(self , num_of_alive_monsters):
        self.__num_of_alive_monsters = num_of_alive_monsters

    @property
    def num_of_alive_warriors(self):
        return self.__num_of_alive_warriors

    @num_of_alive_warriors.setter
    def num_of_alive_warriors(self, num_of_alive_warriors):
        self.__num_of_alive_warriors = num_of_alive_warriors






