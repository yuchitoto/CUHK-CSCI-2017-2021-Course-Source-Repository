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

class GameBoard:
    def __init__(self):
        self.board = None
        self.count_O = 0
        self.count_X = 0

#################################################
#inital game board
#################################################
    def init_gameBoard(self):
        self.board = []
        for i in range (8):
            new = []
            for j in range(8):
                new.append(None)
            self.board.append(new)

        self.board[3][3] = 'X'
        self.board[4][4] = 'X'
        self.board[3][4] = 'O'
        self.board[4][3] = 'O'
        self.count_O += 2
        self.count_X += 2
                
#################################################
#check whether end game
#################################################
    def check_ending(self):
        if self.check_legal_move('X') or self.check_legal_move('O'):
            return False
        return True
    
    def check_legal_move(self,symbol):
        for i in range(8):
            for j in range(8):
                if(self.board[i][j] == None):
                    for x_dir, y_dir in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:
                        x = i 
                        y = j
                        x += x_dir
                        y += y_dir
                        if x > 7 or x < 0 or y > 7 or y < 0 :
                            continue     
                        if (self.board[x][y] != symbol and self.board[x][y] != None): 
                            while (self.board[x][y] != symbol and self.board[x][y] != None):                     
                                x += x_dir
                                y += y_dir
                                if x > 7 or x < 0 or y > 7 or y < 0 :
                                    break
                            if x > 7 or x < 0 or y > 7 or y < 0 :
                                continue
                            if(self.board[x][y] == symbol):
                                return True    
        return False

#################################################
#check who is winner
#################################################
    def check_winner(self):
        #return a list[s1,s2], represent the total number for O and X
        s1, s2 = 0, 0
        for i in range(8):
            for j in range(8):
                if self.board[i][j] == 'O':
                    s1 += 1
                elif self.board[i][j] == 'X':
                    s2 += 1
        return s1,s2

#################################################
#doing flip
#################################################
    def execute_flip(self, pos, symbol):
        posx, posy = pos
        self.board[posx - 1][posy - 1] = symbol

        for x_dir, y_dir in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:
            x = posx
            y = posy
            x += x_dir
            y += y_dir
            if x > 8 or x < 1 or y > 8 or y < 1 :
                continue
            if (self.board[x - 1][y - 1] != symbol and self.board[x - 1][y - 1] != None):
                while (self.board[x - 1][y - 1] != symbol and self.board[x - 1][y - 1] != None):
                    x += x_dir
                    y += y_dir
                    if x > 8 or x < 1 or y > 8 or y < 1 :
                        break
                if x > 8 or x < 1 or y > 8 or y < 1 :
                    continue      
                if(self.board[x - 1][y - 1] == symbol):
                    x -= x_dir
                    y -= y_dir
                    while (self.board[x - 1][y - 1] != symbol and self.board[x - 1][y - 1] != None):
                        self.board[x - 1][y - 1] = symbol
                        x -= x_dir
                        y -= y_dir
                        
                                      
        
#################################################
#print game board
#################################################
    def printGameBoard(self):
        for i in range(0, 9):
            for j in range(0, 9):
                if i == 0 and j != 0:
                    print("| {} ".format(str(j)), end = '')
                if i == 0 and j == 0:
                    print("   " , end = '')
                if i != 0 and j == 0:
                    print(" {} ".format(str(i)) , end = '')
                if i != 0 and j != 0:
                    if (self.board[i-1][j-1] == None):
                        print("|   ", end = '')
                    else:
                        print("| {} ".format(self.board[i-1][j-1]) , end = '')
            print("|")
            print("------------------------------------")
        #print("")


class Player:

    def __init__(self, symbol):
        self.playerSymbol = symbol

    def nextMove(self, board):
        pass


#from Player import Player

class Human(Player):
    def nextMove(self,board):
        print("Player "+self.playerSymbol+"'s turn.")
        print("Type the row and col to put the disc: ", end = '')
        while True:
            try:
                posx_str, posy_str = input("").split()
                posx = int(posx_str)
                posy = int(posy_str)
                break
            except:
                print("Invalid Input")
                print("Player "+self.playerSymbol+"'s turn.") 
                print("Type the row and col to put the disc: ", end = '')
        
        while(not self.isValidMove(board, posx, posy)):
            print("Invalid Input")
            print("Player "+self.playerSymbol+"'s turn.")
            print("Type the row and col to put the disc: ", end = '')
            try:
                posx_str, posy_str = input("").split()
                posx = int(posx_str)
                posy = int(posy_str)
            except:
                continue          
        return [posx,posy]

#################################################
#check whether it is valid move
#################################################
    def isValidMove(self, board, posx, posy):
        if posx > 8 or posx < 1 or posy > 8 or posy < 1 :
            return False
        if board[posx-1][posy-1] != None:
            return False
        for x_dir, y_dir in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:
            x = posx
            y = posy
            x += x_dir
            y += y_dir
            if x > 8 or x < 1 or y > 8 or y < 1 :
                continue
            if (board[x - 1][y - 1] != self.playerSymbol and board[x - 1][y - 1] != None):
                while (board[x - 1][y - 1] != self.playerSymbol and board[x - 1][y - 1] != None):
                    x += x_dir
                    y += y_dir
                    if x > 8 or x < 1 or y > 8 or y < 1 :
                        break
                if x > 8 or x < 1 or y > 8 or y < 1 :
                    continue
                if(board[x - 1][y - 1] == self.playerSymbol):
                    return True
        return False

#from Player import Player
class Computer(Player):
    weight = []
    weight.append([99, -8, 8 , 6, 6, 8, -8, 99])
    weight.append([-8, -24, -4 , -3, -3, -4, -24, -8])
    weight.append([8, -4, 7 , 4, 4, 7, -4, 8])
    weight.append([6, -3, 4 , 0, 0, 4, -3, 6])
    weight.append([6, -3, 4 , 0, 0, 4, -3, 6])
    weight.append([8, -4, 7 , 4, 4, 7, -4, 8])
    weight.append([-8, -24, -4 , -3, -3, -4, -24, -8])
    weight.append([99, -8, 8 , 6, 6, 8, -8, 99])
    def nextMove(self,board):
        print("Player {}'s turn.".format(self.playerSymbol))
        self.valid = self.find_valid_move(board)
        for i in range(len(self.valid)):
            p1, p2 = self.valid[i]
            #print(self.valid[i], self.weight[p1 - 1][p2 - 1])
        #print(*self.valid, sep = "\n")
        #ran = random.randint(0,len(valid)-1)
        self.max = -999
        for i in range(len(self.valid)):
            p1, p2 = self.valid[i]
            if self.weight[p1 - 1][p2 - 1] > self.max:
                self.max = self.weight[p1 - 1][p2 - 1]
                self.mark = i
                #print(self.mark)
        return self.valid[self.mark]
         
#################################################
#find valid move
#################################################   
    def find_valid_move(self, board):
        valid_move = []
        for i in range(1,9):
            for j in range(1,9):
                    if(self.isValidMove(board, i, j)):
                        valid_move.append([i, j])
        if(len(valid_move) != 0):
            return valid_move                   
        return False

#################################################
#check whether it is valid move
#################################################
    def isValidMove(self, board, posx, posy):
        if posx > 8 or posx < 1 or posy > 8 or posy < 1 :
            return False
        if board[posx-1][posy-1] != None:
            return False
        for x_dir, y_dir in [[0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1], [-1, 0], [-1, 1]]:
            x = posx
            y = posy
            x += x_dir
            y += y_dir
            if x > 8 or x < 1 or y > 8 or y < 1 :
                continue
            if (board[x - 1][y - 1] != self.playerSymbol and board[x - 1][y - 1] != None):
                while (board[x - 1][y - 1] != self.playerSymbol and board[x - 1][y - 1] != None):
                    x += x_dir
                    y += y_dir
                    if x > 8 or x < 1 or y > 8 or y < 1 :
                        break
                if x > 8 or x < 1 or y > 8 or y < 1 :
                    continue
                if(board[x - 1][y - 1] == self.playerSymbol):
                    return True
        return False

class Othello:

    def __init__(self):
        self.gameBoard = GameBoard()
        self.player1 = None
        self.player2 = None
        self.turn = 0

#################################################
#ask player choice
#################################################
    def createPlayer(self, symbol, playerNum):
        print("Please choose player {} ({}):".format(str(playerNum), symbol))
        print("1. Human")
        print("2. Computer Player")

        while True:
            try:
                print("Your choice is: ", end = '')
                choice_str = input('')
                if choice_str == '1':
                    print("Player {} is Human.".format(symbol))
                    return Human(symbol)
                elif choice_str == '2':
                    print("Player {} is Computer.".format(symbol))
                    return Computer(symbol)
                else:
                    print("Invalid choice, please choose again")
            except:
                print("Invalid choice, please choose again")
                
#################################################
#game start
#################################################
    def startGame(self):
        #basic logic
        self.player1 = self.createPlayer('O', 1)
        self.player2 = self.createPlayer('X', 2)
        self.gameBoard.init_gameBoard()
        self.gameBoard.printGameBoard()

        while not self.gameBoard.check_ending():
            current_player = [self.player1,self.player2][self.turn]
             
            if self.gameBoard.check_legal_move(current_player.playerSymbol):
                pos = current_player.nextMove(self.gameBoard.board)
                self.gameBoard.execute_flip(pos, current_player.playerSymbol)
            else:
                print("Player {}'s turn.".format(current_player.playerSymbol))
                print("There is no valid move for Player {}.".format(current_player.playerSymbol))
            self.turn = 1 - self.turn

            self.gameBoard.printGameBoard()

        s1, s2 = self.gameBoard.check_winner()
        if s1 > s2:
            winner = 'O'  # Black
        elif s1 < s2:
            winner = 'X'  # White
        elif s1 == s2:
            winner = ' '  # Tie

        print('Count O : {}'.format(s1))
        print('Count X : {}'.format(s2))
        if winner != ' ':
            print('Player {} won!\n'.format(winner))
        else:
            print('A tie')


if __name__ == "__main__":
    othello = Othello()
    othello.startGame()

