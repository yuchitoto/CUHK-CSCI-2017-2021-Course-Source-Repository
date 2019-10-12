import java.util.Random;
import java.util.Scanner;

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

public class TheJourney {
	
	public static Scanner reader = new Scanner(System.in);
	public static Random rand = new Random();
	
	private Map map;
	
	public TheJourney() {
		map = new Map();
	}
    void gameStart() {
    	
    	map.initializeAll();
    	
    	int numOfAliveMonsters = this.map.getNumOfAliveMonsters();
    	int numOfAliveWarriors = this.map.getNumOfAliveWarriors();
    	//this.map.printBoard();

    	while ((numOfAliveMonsters > 0) && (numOfAliveWarriors > 0)) {
    		
    		this.map.teleportAll();
    		
    		numOfAliveMonsters = this.map.getNumOfAliveMonsters();
    		numOfAliveWarriors = this.map.getNumOfAliveWarriors();
    	}
    	if (numOfAliveMonsters == 0)
    		System.out.println("Congratulations, all the monsters have been killed.");
    	else
    		System.out.println("Unfortunately, the mission failed and all the warriors died.");
    }
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TheJourney game = new TheJourney();
		game.gameStart();
	}
}

