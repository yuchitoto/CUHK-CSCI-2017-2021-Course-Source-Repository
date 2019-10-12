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

public class Warrior{
	private static final int HEALTH_CAP = 40;
	private Pos pos;
	private int index;
	private int health;
	private String name;
	private Map map;
	private int magic_crystal;
	public Warrior(int posx, int posy, int index, Map map) {
		this.pos = new Pos(posx, posy);
		this.index = index;
		this.map = map;
		// TODO Auto-generated constructor stub
		this.name = "W" + Integer.toString(index);
		this.health = HEALTH_CAP;
		this.magic_crystal = 10;
	}
	
	public void teleport() {
		System.out.println("Hi, " + name + ". " + String.format("Your position is (%d,%d) and health is %d.", this.pos.getX(), this.pos.getY(), this.health));
		System.out.println("Specify your target position (Input 'x y').");
		int posx = TheJourney.reader.nextInt(), posy = TheJourney.reader.nextInt();
		while((posx == this.pos.getX()) && (posy == this.pos.getY())) {
			System.out.println("Specify your target position (Input 'x y'). It should not be the same as the original one.");
			posx = TheJourney.reader.nextInt();
			posy = TheJourney.reader.nextInt();
		}
		boolean result = this.map.coming(posx,posy,this);
		if(result) {
			this.map.setLand(this.pos, null);
			this.pos.setPos(posx, posy);
			this.map.setLand(this.pos, this);
		}
		if( this.health <= 0) {
			System.out.println("Very sorry, " + this.name + " has been killed.");
			this.map.setLand(this.pos, null);
			this.map.deleteTeleportableObj(this);
			this.map.decreaseNumOfWarriors();
		}
	}

	public void talk(String content) {
		System.out.println(this.name+": "+content);
	}
	
	//share crystal random
    public boolean actionOnWarrior(Warrior warrior) {
		this.talk("Hi, bro. You can call me " + this.name +". I am very happy to meet you. I have " + this.magic_crystal +" magic crystals.");
		this.talk("The number of your magic crystals is " + warrior.getMagic_crystal() + ".");
		this.talk("Need I share with you some magic crystals?");
		this.talk("You now have following options:");
    	System.out.println("1. Yes");
    	System.out.println("2. No");
    	int a = TheJourney.reader.nextInt();
    	
    	if (a == 1) {
				if(this.magic_crystal <= 0){
					this.talk("Very embarrassing, I don't have enough crystals.");
					return false;
				}
    		int sharedCrystal = TheJourney.rand.nextInt(5) + 5;
			if (sharedCrystal > this.magic_crystal)
				sharedCrystal = this.magic_crystal;

    		warrior.increaseCrystal(sharedCrystal);
			this.decreaseCrystal(sharedCrystal);

    		warrior.talk("Thanks for your shared "+ sharedCrystal + " magic crystals! " + this.name + ".");
    	}
		return false;
	}




    public void increaseCrystal(int value) {
		this.magic_crystal += value;
	}
	public void decreaseCrystal(int value) {
		this.magic_crystal -= value;
	}
	
	public void increaseHealth(int value) {
		this.health += value;
		if (this.health > HEALTH_CAP) {
			this.health = HEALTH_CAP;
		}
	}	
	public void decreaseHealth(int value) {
		this.health -= value;
	}
	
	public Pos getPos() {
		return pos;
	}
	
	public String getName() {
		return name;
	}
	

	public int getHealth() {
		return health;
	}

	public void setHealth(int health) {
		this.health = health;
	}

	public int getMagic_crystal() {
		return magic_crystal;
	}

	public void setMagic_crystal(int magic_crystal) {
		this.magic_crystal = magic_crystal;
	}

}
