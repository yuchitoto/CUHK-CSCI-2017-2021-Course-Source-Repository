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

public class Potion{
	private static final int HEAL_CAP = 20;
	private Pos pos;
	private int index;
	private String name;
	private Map map;
	private int healPower;
	private boolean isUsed = false;
 
 
	//constructor
	public Potion(int posx, int posy, int index, Map map) {
		this.pos = new Pos(posx, posy);
		this.index = index;
		this.map = map;
		this.name = "P" + Integer.toString(index);
		this.healPower = HEAL_CAP;
	}
	//when warrior get potion, he will add health
    public boolean actionOnWarrior(Warrior warrior) {
		warrior.talk("Very good, I got additional healing potion "+this.getName()+".");
	//	this.map.setLand(this.pos, warrior);
		this.isUsed = true;
		warrior.increaseHealth(this.healPower);
		return true;
	}

	//teleport to random place if the potion has not be used
	public void teleport() {
		if(isUsed == false){
			Pos pos = this.map.getUnOccupiedPosition();
			//System.out.println("HI");
			this.map.setLand(this.pos, null);
			this.pos.setPos(pos.getX(), pos.getY());
			this.map.setLand(this.pos, this);
		}
	}

	//check whether used
	public boolean checkUsed(){
		return isUsed;
	}

	public String getName() {
		return name;
	}

}