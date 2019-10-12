
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
import sys
import random

from map import map

class the_journey:
    def __init__(self):
        self.__map = map()

    def game_start(self):
        self.__map.initialize_all()
        num_of_alive_monsters = self.__map.num_of_alive_monsters
        num_of_alive_warriors = self.__map.num_of_alive_warriors

        while ((num_of_alive_monsters > 0) and (num_of_alive_warriors > 0)):
           # self.__map.print_broad()
            self.__map.teleport_all()

            num_of_alive_monsters = self.__map.num_of_alive_monsters
            num_of_alive_warriors = self.__map.num_of_alive_warriors
        
        if num_of_alive_monsters == 0:
            print("Congratulations, all the monsters have been killed.")
        else:
            print("Unfortunately, the mission failed and all the warriors died.")

the_journey = the_journey()
the_journey.game_start()
