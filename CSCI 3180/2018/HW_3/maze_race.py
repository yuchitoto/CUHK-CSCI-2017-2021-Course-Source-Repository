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
# Assignment 3
# Name : Wong Sin Yi 
# Student ID : 1155110677
# Email Addr : 1155110677@link.cuhk.edu.hk



import sys
import random

#---------Position-------------
class Position:
    def __init__(self):
        self.r = None
        self.c = None

    def getR(self):
        return self.r

    def setR(self, r):
        self.r = r
    
    def getC(self):
        return self.c

    def setC(self, c):
        self.c = c
#------End of Position---------


#----------Cell----------------
class Cell:
    def __init__(self):
        self.pos = None
        self.content = None
        self.explored = 0

    def setExplored(self,explored):
        self.explored = explored

    def getExplored(self):
        return self.explored

    def setContent(self, content):
        self.content = content

    def getContent(self):
        return self.content

    def setPos(self,pos):
        self.pos = pos

    def getPos(self):
        return self.pos

    def isAvailable(self):
        if (self.content == "O" or self.content == "*"):
            return 1
        else:
            return 0
#---------End of Cell-------------


#--------------Maze--------------
class Maze:
    def __init__(self):
        self.height = None
        self.width = None
        self.destPos = Position()

    def getHeight(self):
        return self.height
        
    def getWidth(self):
        return self.width

    def explore(self,pos):
        self.getCell(pos).setExplored(1)

    def getCell(self,pos):
        return self.map[pos.getR()][pos.getC()]

    def setCell(self, pos, cell):
        self.map[pos.getR()][pos.getC()] = cell

    def getCellContent(self, pos):
        return self.map[pos.getR()][pos.getC()].getContent()

    def setCellContent(self, pos, value):
        self.map[pos.getR()][pos.getC()].setContent(value)

    def isAvailable(self, pos):
        R = pos.getR()
        C = pos.getC()
        if C >= self.width or R >= self.height or C < 0 or R<0:
            return 0
        elif self.map[R][C].isAvailable():
            return 1
        else:
            self.explore(pos)
            return -1

    def reachDest(self,pos):
        if pos.getC() == self.destPos.getC() and pos.getR() == self.destPos.getR():
            return 1
        else:
            return 0

    def displayMaze(self):
        h = self.getHeight()
        w = self.getWidth()

        print ("Current Maze > \n\n",end = '')
        indent = "\t\t\t"
        print(indent+"   |", end = '')
        for j in range(w):
            print (" "+str(j)+" |", end = '')
        print("\n"+indent, end = '')
        for j in range(w+1):
            print ("----",end = '')
        print ("\n",end = '')

        for i in range(h):
            print (indent, i,"|", end = '')
            for j in range(w):
                cell = self.map[i][j]
                ch = cell.content
                if(cell.getExplored() == 1):
                    if (ch != "*"):
                        print(" "+ch+" |",end = '')
                    else:
                        print("   |",end = '')
                else:
                    print (" ? |",end = '')

            print("\n"+indent, end = '')
            for j in range (w+1):
                print ("----", end = '')
            print("\n", end = '')
        print ("\n--\n", end = '')

    def load_maze(self, fh):
        self.map = []
        with fh:
            h, w = [int(x) for x in next(fh).split()]
            
            end_h, end_w = 0, 0
            coords = [0, 0, 0, 0]
            
            for i in range (h):
                new = []
                line = fh.readline()

                for j in range (w):
                    ch = line[j]
                    cell = Cell()
                    if ch == 'O':
                        end_h, end_w = i, j
                    else:
                        if ch == '1':
                            coords[0], coords[1] = i, j
                            ch = 'E'
                        else:
                            if ch == '2':
                                coords[2], coords[3] = i, j
                                ch = 'H'
                    
                    cell.setContent(ch)
                    pos = Position()
                    pos.setR(i)
                    pos.setC(j)
                    cell.setPos(pos)
                    new.append(cell)
                    #print(ch, end ='')
                self.map.append(new)
                #print("")

            
            self.height = h
            self.width = w
            #print (end_h )
            #print(end_w)
        
            self.destPos.setR(end_h)
            self.destPos.setC(end_w)
            self.explore(self.destPos)
            return coords

#----------end of Maze-------------




#--------------Player------------
class Player:

    def __init__(self):
        self.rshift = [1,0,-1,0]
        self.cshift = [0,1,0,-1]
        self.name = None
        self.curPos = Position()
        self.specialMovesLeft = 4


    def setName(self, name):
        self.name = name  

    def getName(self):
        return self.name

    def getPos(self):
        return self.curPos

    def occupy(self, maze):
        maze.explore(self.curPos)
        maze.setCellContent(self.curPos, self.name)

    def leave(self, maze):
        maze.setCellContent(self.curPos, "*")

    def move(self, point_to, maze):
        p = self.next(point_to)
        if maze.isAvailable(p) == 1:
            self.leave(maze)
            cur_h = self.curPos.getR()
            cur_w = self.curPos.getC()
            self.curPos.setR(cur_h + self.rshift[point_to])
            self.curPos.setC(cur_w + self.cshift[point_to])
            self.occupy(maze)
        self.rshift = [1,0,-1,0]
        self.cshift = [0,1,0,-1]
        #print(self.rshift[0])
        #print(self.cshift[0])

    def next(self, point_to):
        pos = Position()
        pos.setR(self.curPos.getR() + self.rshift[point_to])
        pos.setC(self.curPos.getC() + self.cshift[point_to])
        return pos

###
    def rush(self, point_to, maze):
        r_move = self.rshift[point_to]
        c_move = self.cshift[point_to]
        p = self.next(point_to)
        while maze.isAvailable(p) == 1:
            maze.explore(p)
            self.rshift[point_to] += r_move
            self.cshift[point_to] += c_move
            p = self.next(point_to)
        self.rshift[point_to] -= r_move
        self.cshift[point_to] -= c_move
        self.move(point_to, maze)

    def throughBlocked(self, point_to, maze):
        r_move = self.rshift[point_to]
        c_move = self.cshift[point_to]
        p = self.next(point_to)
        if maze.isAvailable(p) == -1:
            maze.explore(p)
            self.rshift[point_to] += r_move
            self.cshift[point_to] += c_move
            p = self.next(point_to)
            if maze.isAvailable(p) == 1:
                maze.explore(p)
                p = self.next(point_to)
        self.move(point_to, maze)
        

    def teleport(self, maze):
        self.rshift[0] = random.randint(0, maze.height - 1) - self.getPos().getR() 
        self.cshift[0] = random.randint(0, maze.width - 1) - self.getPos().getC()
        #print(self.rshift[0])
        #print(self.cshift[0])
        self.move(0, maze)
##

    def makeMove(self,maze):
        p_name = self.getName()
        if self.specialMovesLeft <= 0:
            print ("Your (Player "+p_name+") moving type: normal move.\n",end = '')
            print ("Your (Player "+p_name+") moving direction (0: S, 1: E, 2: N, 3: W) > ", end = '')
            
            d = input("")
            while (d != "0" and d != "1" and d != "2" and d != "3"):
                print ("The moving direction can only be 0, 1, 2, or 3, please re-input > ")
                d = input("")
            d = int(d)
            self.move(d, maze)
        else:
            scnt = self.specialMovesLeft
            if (scnt > 1):
                print ("You (Player "+p_name+") can make a normal move (unlimited) or a special move (only "+str(scnt)+" times left).")
            else:
                print ("You (Player "+p_name+") can make a normal move or a special move (only "+str(scnt)+" time left).")
            print ("Your (Player "+p_name+") moving type (0: rush, 1: through-blocked, 2: teleport, default: normal move) > ",end = '')
            op = input("")
            while (op != "0" and op != "1" and op != "2" and op != ""):
                print ("This moving type can only be 0, 1, or 2, please re-input > ", end = '')
                op = input("")

            if op == "":
                op = "-1"
            op = int(op)

            if (op == 2):
                self.teleport(maze)
                self.specialMovesLeft -= 1
            else:
                print ("Your (Player "+p_name+") moving direction (0: S, 1: E, 2: N, 3: W) > ", end = '')
                d = input("")

                while (d != "0" and d != "1" and d != "2" and d != "3"):
                    print ("The moving direction can only be 0, 1, 2, or 3, please re-input > ")
                    d = input("")
                d = int(d)

                if op == -1:
                    self.move(d, maze)
                else:
                    if op == 0:
                        self.rush(d, maze)
                    else:
                        self.throughBlocked(d,maze)
                    self.specialMovesLeft -= 1
 #-------end of Player-----------------


class MazeRace:
    def __init__(self, file):
        maze = Maze()
        p1 = Player()
        p2 = Player()

        p1.name = 'E'
        p2.name = 'H'

        try:
            fh = open(file, "r")
            with fh:
                coords = maze.load_maze(fh)
                p1.getPos().setR(coords[0])
                p1.getPos().setC(coords[1])
                p2.getPos().setR(coords[2])
                p2.getPos().setC(coords[3])

                maze.explore(p1.getPos())
                maze.explore(p2.getPos())
        except Exception as e: 
            print(e)
            print ("Could not load file " + file)
            sys.exit()

        self.maze = maze
        self.p1 = p1
        self.p2 = p2
    
    def start(self):
        maze = self.maze
        maze.displayMaze()
        pArr = [self.p1, self.p2]
        turn = 0
        finished = 0

        while finished == 0:
            pArr[turn].makeMove(maze)
            maze.displayMaze()
            if (maze.reachDest(pArr[turn].getPos())):
                i = turn + 1
                print("")
                print("--")
                print("Player"+ str(i) +" wins! ")
                finished = 1
            turn = (turn + 1) % 2


config_file = "maze.test"
game = MazeRace(config_file)
game.start()



                            