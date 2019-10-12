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
from pos import pos


class warrior:
    
    HEALTH_CAP = 40
    
    def __init__(self, posx, posy, index, map):
        self.__pos = pos(posx, posy)
        self.__index = index
        self.__map = map
        
        self.__name = "W" + str(index)
        self.__health = self.HEALTH_CAP
        self.__magic_crystal = 10

    def teleport(self):
        print("Hi, " + self.__name + ". " + "Your position is ({},{}) and health is {}.".format( self.__pos.x, self.__pos.y, self.__health))
        print("Specify your target position (Input 'x y').")
        posx_str, posy_str = input("").split()
        posx = int(posx_str)
        posy = int(posy_str)

        while posx == self.__pos.x and posy == self.__pos.y :
            print("Specify your target position (Input 'x y'). It should not be the same as the original one.")
            posx_str, posy_str = input("").split()
            posx = int(posx_str)
            posy = int(posy_str)
        
        result = self.__map.coming(posx,posy,self)
        if (result):
            self.__map.set_land(self.__pos, None)
            self.__pos.set_pos(posx, posy)
            self.__map.set_land(self.__pos, self)
        if (self.__health <= 0):
            print("Very sorry, " + self.__name + " has been killed.")
            self.__map.set_land(self.__pos, None)
            self.__map.delete_teleportable_obj(self)
            self.__map.decrease_num_of_warriors()

    def talk(self, content):
        print(self.__name + ": " +content)

    def increase_crystal(self, value):
        self.__magic_crystal += value

    def decrease_crystal(self, value):
        self.__magic_crystal -= value

    def increase_health(self, value):
        self.__health += value
        if self.__health > self.HEALTH_CAP:
            self.__health = self.HEALTH_CAP

    def decrease_health(self, value):
        self.__health -= value

    @property
    def pos(self):
        return self.__pos

    @property
    def name(self):
        return self.__name

    @property
    def health(self):
        return self.__health

    @health.setter
    def health(self, health):
        self.__health = health

    @property
    def magic_crystal(self):
        return self.__magic_crystal

    @magic_crystal.setter
    def magic_crystal(self, magic_crystal):
        self.__magic_crystal = magic_crystal


