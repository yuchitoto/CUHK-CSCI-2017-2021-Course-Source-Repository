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
public class Monster extends NPC {
    
	private static final int DAMAGE_CAP = 20;
	public Monster(int posx, int posy, int index, Map map) {
		super(posx, posy, index, map);
		this.setName("M" + Integer.toString(index));
		this.setPower(TheJourney.rand.nextInt(DAMAGE_CAP - 5) + 5);
	}
	
    public boolean actionOnWarrior(Warrior warrior) {
    	this.talk("I am the monster "+ this.getName() +".  Here is my territory.  " + String.format("My damage power is %d.", this.getPower()));
    	this.talk("Your health is " + warrior.getHealth() + ".");
    	this.talk("Do you really want to challenge me?");
    	this.talk("You now have following options: ");

    	System.out.println("1. Yes");
    	System.out.println("2. No");
    	int a = TheJourney.reader.nextInt();
    	
    	if (a == 1) {
    		if( warrior.getHealth() > this.getPower()) {
    			warrior.decreaseHealth(this.getPower());
    			warrior.increaseCrystal(TheJourney.rand.nextInt(5) + 5);
    			warrior.talk("Nice, I have killed the monster "+ this.getName() + ".");
    			this.map.decreaseNumOfAliveMonsters();
    			return true;
    		}
    		warrior.decreaseHealth(this.getPower());
    	}
    	return false;
    }
	 

}
