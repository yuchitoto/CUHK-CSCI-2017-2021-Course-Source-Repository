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
from npc import npc
from warrior import warrior

class land:

    def __init__(self):
        self.__occupied_obj = None 

    def coming(self, warrior):
        if isinstance(self.__occupied_obj, npc):
            return self.__occupied_obj.action_on_warrior(warrior)
        return True

    @property
    def occupied_obj(self):
        return self.__occupied_obj

    @occupied_obj.setter
    def occupied_obj(self, occupied_obj):
        self.__occupied_obj = occupied_obj

    @property
    def occupant_name(self):
        if self.__occupied_obj is not None:
            return self.__occupied_obj.name
        return None
