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
public class Land{
    
	private Object occupied_obj;
    
	public Land() {
		// TODO Auto-generated constructor stub
		this.occupied_obj = null;
	}
	
	public boolean coming(Warrior warrior) {
		// TODO Auto-generated method stub
		if (occupied_obj instanceof NPC) {
			return ((NPC)occupied_obj).actionOnWarrior(warrior);
		} 
		if (occupied_obj instanceof Potion) {
			return ((Potion)occupied_obj).actionOnWarrior(warrior);
		} 
		if (occupied_obj instanceof Warrior) {
			return ((Warrior)occupied_obj).actionOnWarrior(warrior);
		} 
		return true;
	}
	
	 
	public Object getOccupied_obj() {
		return occupied_obj;
	}

	public void setOccupied_obj(Object occupied_obj) {
		this.occupied_obj = occupied_obj;
	}

	public String getOccupantName() {
		// TODO Auto-generated method stub
		if (occupied_obj instanceof NPC) {
			return ((NPC)occupied_obj).getName();
		} else if (occupied_obj instanceof Warrior) {
			return ((Warrior)occupied_obj).getName();
		} else if (occupied_obj instanceof Potion){
			return ((Potion)occupied_obj).getName();
		}
		
		return null;
	}
}
