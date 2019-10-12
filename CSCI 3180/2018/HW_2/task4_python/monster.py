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

from npc import npc

class monster(npc):
    DAMAGE_CAP = 20

    def __init__(self, posx, posy, index, map):
        super(monster, self).__init__(posx, posy, index, map)
        self.name = ("M" + str(index))
        self.power = random.randint(5, self.DAMAGE_CAP-5 )

    def action_on_warrior(self, warrior):
        self.talk("I am the Monster "+ self.name + ".  Here is my territory.  " + "My damage power is {}.".format(str(self.power)))
        self.talk("Your health is " + str(warrior.health)+".")
        self.talk("Do you really want to challenge me?")
        self.talk("You now have following options: ")
        print("1. Yes")
        print("2. No")
        a_str = input('')
        a = int(a_str)

        if a is 1:
            if warrior.health > self.power:
                warrior.decrease_health(self.power)
                warrior.increase_crystal(random.randint(5, 9))
                warrior.talk("Nice, I have killed the monster "+ self.name + ".")
                self._map.decrease_num_of_alive_monsters()
                return True
            warrior.decrease_health(self.power)
        
        return False 
