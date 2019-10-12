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
public class Elf extends NPC{
    
    private static final int MAGIC_CAP = 20;
  
	public Elf(int posx, int posy, int index, Map map) {
		super(posx, posy, index, map);
		this.setName("E" + Integer.toString(index));
		this.setPower(TheJourney.rand.nextInt(MAGIC_CAP - 5) + 5);
	}
 
    public boolean actionOnWarrior(Warrior warrior) {
    	this.talk("My name is "+ this.getName() +".  Welcome to my home.  " + String.format("My magic power is %d.", this.getPower()));
    	this.talk("Your magic crystal is " + warrior.getMagic_crystal()+".");
    	this.talk("Do you need my help?");
    	this.talk("You now have following options: ");
    	System.out.println("1. Yes");
    	System.out.println("2. No");
    	int a = TheJourney.reader.nextInt();
    	
    	if (a == 1) {
    		int value = TheJourney.rand.nextInt(this.getPower()-2)+2;
    		if (warrior.getMagic_crystal() > value) {
    			warrior.decreaseCrystal(value);
    			warrior.increaseHealth(value);
    			warrior.talk("Thanks for your help! "+ this.getName()+".");
    		} else {
    			warrior.talk("Very embarrassing, I don't have enough crystals.");
    		}
    	}
    	return false;
    }
}
