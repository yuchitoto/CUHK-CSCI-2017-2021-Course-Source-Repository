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

from pos import pos

class potion:
    HEAL_CAP = 20

    def __init__(self, posx, posy, index, map):
        self.__map = map
        self.__pos = pos(posx, posy)
        self.__index = index
        self.__name = ("P" + str(index))
        self.__healPower = random.randint(5, self.HEAL_CAP-5 )        
        self.__is_used = False #record whether it is used

	#add warrior health
    def action_on_warrior(self, warrior):  
        warrior.talk("Very good, I got additional healing potion " + self.__name +".")      
        self.__is_used = True
        warrior.increase_health(self.__healPower)
        return True 
        
	#teleport random place if it havent been used
    def teleport(self):
        if self.__is_used == False:
            pos = self.__map.unoccupied_position
            self.__map.set_land(self.__pos, None)
            self.__pos.set_pos(pos.x, pos.y)
            self.__map.set_land(self.__pos, self)

    @property
    def name(self):
        return self.__name
