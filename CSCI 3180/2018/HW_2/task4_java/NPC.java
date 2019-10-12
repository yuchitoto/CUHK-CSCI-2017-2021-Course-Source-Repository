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
public class NPC {
	private Pos pos;
	private int index;
	private String name;
	private int power;
	protected Map map;
	
	public NPC(int posx, int posy, int index, Map map) {
		this.map = map;
		this.pos = new Pos(posx, posy);
		this.index = index;
	}
	
	public void talk(String content) {
		System.out.println(this.name + ": " + content);
	}
	
	public boolean actionOnWarrior(Warrior warrior) {
		return false;
	}

	public void setPos(Pos pos) {
		this.pos = pos;
	}
	
	public Pos getPos() {
		return this.pos;
	}

	public void setName(String name) {
		this.name = name;
	}
	public String getName() {
		return name;
	}

	public int getPower() {
		return power;
	}

	public void setPower(int power) {
		this.power = power;
	}
}
