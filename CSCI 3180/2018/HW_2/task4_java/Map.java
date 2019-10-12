/*
 * CSCI3180 Principles of Programming Languages
 *
 * --- Declaration ---
 *
 * I declare that the assignment here submitted is original except for source
 * material explicitly acknowledged. I also acknowledge that I am aware of
 * University policy and regulations on honesty in academic work, and of the
 * disciplinary guidelines and procedures applicable to breaches of such policy
 * and regulations, as contained in the website
 * http://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Assignment 2
 * Name : Wong Sin Yi
 * Student ID : 1155110677
 * Email Addr : 1155110677@link.cuhk.edu.hk
 */

import java.util.ArrayList;

public class Map {
	
	private ArrayList<Object> teleportable_obj = new ArrayList<Object>();
	private Land[][] lands;
	private final int D = 10; //dimension of board
	private int e;// Number of elves
	private int m;//Number of monsters
	private int w;//Number of warriors
	private int p;//Number of Potion
	private int totalNum = 0;
	private int numOfAliveMonsters;
	private int numOfAliveWarriors;
	
	public Map() {
		lands = new Land[D][D];
		e = TheJourney.rand.nextInt(2) + 2;
		m = TheJourney.rand.nextInt(2) + 2;
		w = TheJourney.rand.nextInt(2) + 2;
		p = TheJourney.rand.nextInt(2) + 2;
		totalNum = m + e + w + p;
		this.numOfAliveMonsters = m;
		this.numOfAliveWarriors = w;
	}
	
	public void initializeAll() {
		System.out.println("Welcome to Kafustrok. Light blesses you. ");

		for (int i = 0; i < D; i++)
			for (int j = 0; j < D; j++)
				lands[i][j] = new Land();
		for (int i = 0; i < totalNum; i++) {
			Pos pos = getUnOccupiedPosition();
			if (i < m)
				this.lands[pos.getX()][pos.getY()].setOccupied_obj(new Monster(pos.getX(), pos.getY(), i, this));
			else if (i < m+e)
				this.lands[pos.getX()][pos.getY()].setOccupied_obj(new Elf(pos.getX(), pos.getY(), i-m, this));
			else if (i < m+e+p){
				this.lands[pos.getX()][pos.getY()].setOccupied_obj(new Potion(pos.getX(), pos.getY(), i-m-e, this));
                teleportable_obj.add(this.lands[pos.getX()][pos.getY()].getOccupied_obj());
			}else {
				this.lands[pos.getX()][pos.getY()].setOccupied_obj(new Warrior(pos.getX(), pos.getY(), i-m-e-p, this));
				teleportable_obj.add(this.lands[pos.getX()][pos.getY()].getOccupied_obj());
			}
		}
	}
	
	public void teleportAll() {
		for (Object obj : teleportable_obj) {
		    if (obj instanceof Warrior) {
				this.printBoard();
				((Warrior) obj).teleport();
                if(this.numOfAliveMonsters == 0)
					return;
			}
		}

		for (Object obj : teleportable_obj) {
			if (obj instanceof Potion){
                ((Potion)obj).teleport();
			}
		}
	}
	
	public boolean coming(int posx, int posy, Warrior warrior) {
		return this.lands[posx][posy].coming(warrior);
	}
	
	public void setLand(Pos _pos, Object occupied_obj) {
		this.lands[_pos.getX()][_pos.getY()].setOccupied_obj(occupied_obj);
	}
	
	public void deleteTeleportableObj(Object obj) {
		int index = this.teleportable_obj.indexOf(obj);
		this.teleportable_obj.set(index, null);
	}
	/**
	 * Make sure all position is unique
	 * @return an unique position
	 */
	public Pos getUnOccupiedPosition() {
    	int randx = TheJourney.rand.nextInt(D);
		int randy = TheJourney.rand.nextInt(D);
    	while (this.lands[randx][randy].getOccupied_obj() != null) {    
        	randx = TheJourney.rand.nextInt(D);
    		randy = TheJourney.rand.nextInt(D);
		}
		return new Pos(randx,randy);
    }
    
    
	public void printBoard() {
		String printObject[][] = new String[D][D];

		// initialize printObject
		for (int i = 0; i < D; i++) {
			for (int j = 0; j < D; j++) {
				String occupantName = lands[i][j].getOccupantName();
				if (occupantName == null)
					occupantName = "  ";
				printObject[i][j] = occupantName;
			}
		}

		// printing
		System.out.print(" ");
		for (int i = 0; i < D; i++)
			System.out.print(String.format("| %d  ", i));

		System.out.println("|");

		for (int i = 0; i < D * 5.5; i++)
			System.out.print("-");
		System.out.println("");

		for (int row = 0; row < D; row++) {
			System.out.print(row);
			for (int col = 0; col < D; col++)
				System.out.print(String.format("| %s ",
				printObject[row][col]));
			System.out.println("|");
			for (int i = 0; i < D * 5.5; i++)
				System.out.print("-");
			System.out.println("");
		}

	}
    
	public void decreaseNumOfAliveMonsters() {
		this.numOfAliveMonsters--;
	}
	public void decreaseNumOfWarriors() {
		this.numOfAliveWarriors--;
	}
	
	public int getNumOfAliveMonsters() {
		return numOfAliveMonsters;
	}

	public void setNumOfAliveMonsters(int numOfAliveMonsters) {
		this.numOfAliveMonsters = numOfAliveMonsters;
	}

	public int getNumOfAliveWarriors() {
		return numOfAliveWarriors;
	}

	public void setNumOfAliveWarriors(int numOfAliveWarriors) {
		this.numOfAliveWarriors = numOfAliveWarriors;
	}
}
