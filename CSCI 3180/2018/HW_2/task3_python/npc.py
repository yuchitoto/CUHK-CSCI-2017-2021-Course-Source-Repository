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

class npc:

    def __init__(self, posx, posy, index, map):
        self._map = map
        self.__pos = pos(posx, posy)
        self.__index = index

    def talk(self, content):
        print(self.__name +": "+ content)

    def action_on_warrior(self, warrior):
        return False

    @property
    def pos(self):
        return self.__pos

    @property
    def name(self):
        return self.__name

    @property
    def power(self):
        return self.__power

    @pos.setter
    def pos(self, pos):
        self.__pos = pos    

    @name.setter
    def name(self, name):
        self.__name = name

    @power.setter
    def power(self, power):
        self.__power = power